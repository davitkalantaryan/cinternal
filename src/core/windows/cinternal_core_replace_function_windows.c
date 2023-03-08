//
// file:            cinternal_core_replace_function_windows.c
// path:			src/core/windows/cinternal_core_replace_function_windows.c
// created on:		2023 Mar 08
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/internal_header.h>

#ifdef _WIN32

#include <cinternal/replace_function.h>
#include <string.h>
#include <cinternal/disable_compiler_warnings.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <Psapi.h>
#include <winternl.h>


CPPUTILS_BEGIN_C
static void MakeHookForModule(LPBYTE a_pAddress, PIMAGE_IMPORT_DESCRIPTOR a_pIID, size_t a_count,struct SCInternalReplaceFunctionData* a_replaceData);


CINTERNAL_EXPORT void CInternalReplaceFunctions(size_t a_count, struct SCInternalReplaceFunctionData* a_replaceData) 
{
    size_t ind;
    MODULEINFO modInfo = { 0 };
    HMODULE hModule = GetModuleHandleA(0);

    // Find the base address
    GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));

    // Find Import Directory
    LPBYTE pAddress = (LPBYTE)modInfo.lpBaseOfDll;
    PIMAGE_DOS_HEADER pIDH = (PIMAGE_DOS_HEADER)pAddress;

    PIMAGE_NT_HEADERS pINH = (PIMAGE_NT_HEADERS)(pAddress + pIDH->e_lfanew);
    PIMAGE_OPTIONAL_HEADER pIOH = (PIMAGE_OPTIONAL_HEADER) & (pINH->OptionalHeader);
    PIMAGE_IMPORT_DESCRIPTOR pIID = (PIMAGE_IMPORT_DESCRIPTOR)(pAddress + pIOH->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

    for (ind = 0; ind < a_count; ++ind) {
        a_replaceData[ind].bFound = false;
    }

    // Find ntdll.dll
    for (; pIID->Characteristics; ++pIID) {
        //if (!strcmp("ntdll.dll", (char*)(pAddress + pIID->Name)))
        //    break;
        MakeHookForModule(pAddress, pIID, a_count, a_replaceData);
    }
}


static void MakeHookForModule(LPBYTE a_pAddress, PIMAGE_IMPORT_DESCRIPTOR a_pIID, size_t a_count, struct SCInternalReplaceFunctionData* a_replaceData)
{
    DWORD dwOld, dwOldTmp;
    size_t ind;
    // Search for a_funcname
    PIMAGE_THUNK_DATA pITD;
    PIMAGE_THUNK_DATA pFirstThunkTest;
    PIMAGE_IMPORT_BY_NAME pIIBM;

    for (ind = 0; ind < a_count; ++ind) {
        pITD = (PIMAGE_THUNK_DATA)(a_pAddress + a_pIID->OriginalFirstThunk);
        pFirstThunkTest = (PIMAGE_THUNK_DATA)((a_pAddress + a_pIID->FirstThunk));

        for (; !(pITD->u1.Ordinal & IMAGE_ORDINAL_FLAG) && pITD->u1.AddressOfData; ++pITD) {
            pIIBM = (PIMAGE_IMPORT_BY_NAME)(a_pAddress + pITD->u1.AddressOfData);
            if (!strcmp(a_replaceData[ind].funcname, (const char*)(pIIBM->Name))) {
                VirtualProtect((LPVOID) & (pFirstThunkTest->u1.Function), sizeof(ULONGLONG), PAGE_READWRITE, &dwOld);
                pFirstThunkTest->u1.Function = (size_t)a_replaceData[ind].newFuncAddress;
                VirtualProtect((LPVOID) & (pFirstThunkTest->u1.Function), sizeof(ULONGLONG), dwOld, &dwOldTmp);
                a_replaceData[ind].bFound = true;
                break;
            }  //  if (!strcmp(a_replaceData->funcname, (const char*)(pIIBM->Name))) {
            pFirstThunkTest++;
        }  //  for (; !(pITD->u1.Ordinal & IMAGE_ORDINAL_FLAG) && pITD->u1.AddressOfData; pITD++) {
    }  //  for (ind = 0; ind < a_count; ++ind) {

}


CPPUTILS_END_C


#endif  //  #ifdef _WIN32
