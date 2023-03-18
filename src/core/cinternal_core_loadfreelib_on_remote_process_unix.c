//
// file:            cinternal_core_replace_function_unix.c
// path:			src/core/windows/cinternal_core_replace_function_unix.c
// created on:		2023 Mar 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/internal_header.h>

#ifndef _WIN32


#include <cinternal/loadfreelib_on_remote_process_sys.h>
#include <cinternal/loadfreelib_on_remote_process.h>


CPPUTILS_BEGIN_C


#ifndef _GNU_SOURCE
#define  _GNU_SOURCE
#endif
#ifndef __USE_GNU
#define  __USE_GNU
#endif
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <dlfcn.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>

#define LIBDL_DLL_NAME  "libdl-2.31.so"


static inline unsigned long long int FindLibraryOffsetByPid(const char* a_library, int a_pid) {
    char mapFilename[1024];
    char buffer[9076];
    FILE* fdMaps;
    unsigned long long int addr = 0;

    if (a_pid == -1) {
        snprintf(mapFilename, sizeof(mapFilename), "/proc/self/maps");
    } else {
        snprintf(mapFilename, sizeof(mapFilename), "/proc/%d/maps", a_pid);
    }

    fdMaps = fopen(mapFilename, "r");
    if(!fdMaps){
        return 0;
    }

    while(fgets(buffer, sizeof(buffer), fdMaps)) {
        if (strstr(buffer, a_library)) {
            addr = strtoull(buffer, CPPUTILS_NULL, 16);
            break;
        }
    }

    fclose(fdMaps);

    return addr;
}


static inline unsigned long long int FindFreeAddressSpaceOnRemoteProcess(int a_pid){
    FILE *fp;
    char filename[30];
    char line[850];
    unsigned long long int addr = 0;
    char str[20];
    char perms[5];

    sprintf(filename, "/proc/%d/maps", a_pid);
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("[!] Error, could not open maps file for process %d\n", a_pid);
        return 0;
    }

    while(fgets(line, 850, fp) != NULL) {
        sscanf(line, "%llx-%*x %s %*s %s %*d", &addr, perms, str);
        if(strstr(perms, "x") != NULL) {break;}
    }

    fclose(fp);
    return addr;
}


static inline bool WriteDataToProcess(int a_pid, unsigned long a_addr, const unsigned char* a_data, size_t a_dataLen){
    long data = 0;
    size_t rmn, itr = 0;
    const size_t itersCount = a_dataLen / 8;

    for(;itr<itersCount;++itr){
        memcpy(&data, a_data + 8*itr, 8);
        if (ptrace(PTRACE_POKETEXT, (pid_t)a_pid, (void *)(a_addr + 8*itr), data)){
            return false;
        }
    }

    rmn = a_dataLen % 8;
    if(rmn){
        memcpy(&data, a_data + 8*itr, rmn);
        if (ptrace(PTRACE_POKETEXT, (pid_t)a_pid, (void *)(a_addr + 8*itr), data)){
            return false;
        }
    }

    return true;
}


CINTERNAL_EXPORT bool CInternalFreeLibOnRemoteProcessByName(int a_pid, const char* a_libraryName)
{
    void*const pLib = CInternalLoadLibOnRemoteProcessAndGetModule(a_pid,a_libraryName);
    if(!pLib){return false;}

    if(!CInternalFreeLibOnRemoteProcessByHandle(a_pid,pLib)){
        return false;
    }

    // we have to decrement reference 2 times
    return CInternalFreeLibOnRemoteProcessByHandle(a_pid,pLib);
}


CINTERNAL_EXPORT bool CInternalLoadLibOnRemoteProcess(int a_pid, const char* a_libraryName)
{
    return CInternalLoadLibOnRemoteProcessAndGetModule(a_pid,a_libraryName) ? true : false;
}


CINTERNAL_EXPORT bool CInternalFreeLibOnRemoteProcessByHandle(int a_pid, void* a_libraryHandle)
{
    unsigned long long int addr,fn_addr,dlclose_address_here, dlclose_address_on_remote, lib_dl_address_on_remote, lib_dl_address_here;
    unsigned long long int save[1024];
    struct user_regs_struct oldregs, regs;
    siginfo_t info;
    char* error;
    void* handle;
    size_t itr;
    int status;
    bool bRet = false;
    const unsigned char injectCode[] = {0xff,0xd0,0xcd,0x03};
    const size_t injectCodeSize = sizeof(injectCode);
    const size_t itersCount = (injectCodeSize/8)+1;

    handle = dlopen(LIBDL_DLL_NAME, RTLD_LAZY);
    if (!handle) {
        return false;
    }
    dlclose_address_here = (unsigned long long int)dlsym(handle, "dlclose");
    if ((error = dlerror()) != CPPUTILS_NULL)  {
        CPPUTILS_STATIC_CAST(void,error);
        return false;
    }
    dlclose(handle);

    lib_dl_address_on_remote = FindLibraryOffsetByPid(LIBDL_DLL_NAME, a_pid);
    if(!lib_dl_address_on_remote){
        return false;
    }
    lib_dl_address_here = FindLibraryOffsetByPid(LIBDL_DLL_NAME, -1);
    if(!lib_dl_address_here){
        return false;
    }

    addr = FindFreeAddressSpaceOnRemoteProcess(a_pid);
    if ((!addr) || (addr & 7)) {
        return false;
    }

    fn_addr= addr;
    dlclose_address_on_remote = lib_dl_address_on_remote + (dlclose_address_here - lib_dl_address_here);

    /* Attach to the target process. */
    if (ptrace(PTRACE_ATTACH, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL)) {
        return false;
    }

    /* Wait for attaching to complete. */
    waitid(P_PID, (pid_t)a_pid, &info, WSTOPPED);

    /* Get target process (main thread) register state. */
    if (ptrace(PTRACE_GETREGS, (pid_t)a_pid, NULL, &oldregs)) {
        ptrace(PTRACE_DETACH, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL);
        return false;
    }

    /* Save the bytes at the specified address in the target process. */
    for(itr=0;itr<itersCount;++itr){
        save[itr] = ptrace(PTRACE_PEEKTEXT, (pid_t)a_pid, (void *)(addr + itr*8), CPPUTILS_NULL);
    }

    /* Replace the bytes */
    if(!WriteDataToProcess(a_pid,fn_addr,injectCode,injectCodeSize)){
        ptrace(PTRACE_DETACH, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL);
        return false;
    }

    /* Modify process registers, to execute the inserted code. */
    regs = oldregs;
    regs.rip = (unsigned long long int)fn_addr;
    regs.rax = (unsigned long long int)dlclose_address_on_remote;
    regs.rdi = (unsigned long long int)a_libraryHandle;
    if (ptrace(PTRACE_SETREGS, (pid_t)a_pid, CPPUTILS_NULL, &regs)) {
        /* Revert the bytes we modified. */
        for(itr=0;itr<itersCount;++itr){
            ptrace(PTRACE_POKETEXT, (pid_t)a_pid, (void *)(addr + 8*itr), (void *)save[itr]);
        }
        ptrace(PTRACE_DETACH, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL);
        return CPPUTILS_NULL;
    }

    /* Execute inserted code */
    if (ptrace(PTRACE_CONT, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL)) {
        /* Revert the registers, too, to the old state. */
        ptrace(PTRACE_SETREGS, (pid_t)a_pid, CPPUTILS_NULL, &oldregs);
        /* Revert the bytes we modified. */
        for(itr=0;itr<itersCount;++itr){
            ptrace(PTRACE_POKETEXT, (pid_t)a_pid, (void *)(addr + 8*itr), (void *)save[itr]);
        }
        ptrace(PTRACE_DETACH, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL);
        return CPPUTILS_NULL;
    }

    /* Wait for the client to execute the syscall, and stop. */
    waitpid((pid_t)a_pid, &status, WUNTRACED);
    if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
        // Get process registers, indicating if the injection suceeded
        ptrace(PTRACE_GETREGS, (pid_t)a_pid, CPPUTILS_NULL, &regs);
        bRet = regs.rax ? false : true;
    }

    /* Revert the registers, too, to the old state. */
    ptrace(PTRACE_SETREGS, (pid_t)a_pid, CPPUTILS_NULL, &oldregs);
    /* Revert the bytes we modified. */
    for(itr=0;itr<itersCount;++itr){
        ptrace(PTRACE_POKETEXT, (pid_t)a_pid, (void *)(addr + 8*itr), (void *)save[itr]);
    }
    ptrace(PTRACE_DETACH, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL);

    return bRet;

}


CINTERNAL_EXPORT void* CInternalLoadLibOnRemoteProcessAndGetModule(int a_pid, const char* a_libraryName)
{
    void* pRemoteLibHandle = CPPUTILS_NULL;
    struct user_regs_struct oldregs, regs;
    siginfo_t info;
    int status;
    const char *error;
    void* handle;
    size_t itr;
    unsigned long long int save[1024];
    unsigned long long int addr,fn_addr,data_addr,dlopen_address_here,dlopen_address_on_remote,lib_dl_address_on_remote, lib_dl_address_here;
    const unsigned char injectCode[] = {0xff,0xd0,0xcd,0x03};
    const size_t injectCodeSize = sizeof(injectCode);
    const size_t strLenPlus1 = strlen(a_libraryName) + 1;
    const size_t itersCount = ((strLenPlus1 + injectCodeSize)/8)+1;


    handle = dlopen(LIBDL_DLL_NAME, RTLD_LAZY);
    if (!handle) {
        return CPPUTILS_NULL;
    }
    dlopen_address_here = (unsigned long long int)dlsym(handle, "dlopen");
    if ((error = dlerror()) != CPPUTILS_NULL)  {
        CPPUTILS_STATIC_CAST(void,error);
        return CPPUTILS_NULL;
    }
    dlclose(handle);

    lib_dl_address_on_remote = FindLibraryOffsetByPid(LIBDL_DLL_NAME, a_pid);
    if(!lib_dl_address_on_remote){
        return CPPUTILS_NULL;
    }
    lib_dl_address_here = FindLibraryOffsetByPid(LIBDL_DLL_NAME, -1);
    if(!lib_dl_address_here){
        return CPPUTILS_NULL;
    }

    addr = FindFreeAddressSpaceOnRemoteProcess(a_pid);
    if ((!addr) || (addr & 7)) {
        return CPPUTILS_NULL;
    }


    fn_addr= addr;
    data_addr = addr + injectCodeSize;
    dlopen_address_on_remote = lib_dl_address_on_remote + (dlopen_address_here - lib_dl_address_here);

    /* Attach to the target process. */
    if (ptrace(PTRACE_ATTACH, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL)) {
        return CPPUTILS_NULL;
    }

    /* Wait for attaching to complete. */
    waitid(P_PID, (pid_t)a_pid, &info, WSTOPPED);

    /* Get target process (main thread) register state. */
    if (ptrace(PTRACE_GETREGS, (pid_t)a_pid, NULL, &oldregs)) {
        ptrace(PTRACE_DETACH, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL);
        return CPPUTILS_NULL;
    }

    /* Save the bytes at the specified address in the target process. */
    for(itr=0;itr<itersCount;++itr){
        save[itr] = ptrace(PTRACE_PEEKTEXT, (pid_t)a_pid, (void *)(addr + itr*8), CPPUTILS_NULL);
    }

    /* Replace the bytes */
    if(!WriteDataToProcess(a_pid,fn_addr,injectCode,injectCodeSize)){
        ptrace(PTRACE_DETACH, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL);
        return CPPUTILS_NULL;
    }
    if(!WriteDataToProcess(a_pid,data_addr,(const unsigned char*)a_libraryName,strLenPlus1)){
        /* Revert the bytes we modified. */
        for(itr=0;itr<itersCount;++itr){
            ptrace(PTRACE_POKETEXT, (pid_t)a_pid, (void *)(addr + 8*itr), (void *)save[itr]);
        }
        ptrace(PTRACE_DETACH, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL);
        return CPPUTILS_NULL;
    }

    /* Modify process registers, to execute the inserted code. */
    regs = oldregs;
    regs.rip = (unsigned long long int)fn_addr;
    regs.rax = (unsigned long long int)dlopen_address_on_remote;
    regs.rdi = (unsigned long long int)data_addr;
    regs.rsi = (unsigned long long int)RTLD_NOW;
    if (ptrace(PTRACE_SETREGS, (pid_t)a_pid, CPPUTILS_NULL, &regs)) {
        /* Revert the bytes we modified. */
        for(itr=0;itr<itersCount;++itr){
            ptrace(PTRACE_POKETEXT, (pid_t)a_pid, (void *)(addr + 8*itr), (void *)save[itr]);
        }
        ptrace(PTRACE_DETACH, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL);
        return CPPUTILS_NULL;
    }

    /* Execute inserted code */
    if (ptrace(PTRACE_CONT, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL)) {
        /* Revert the registers, too, to the old state. */
        ptrace(PTRACE_SETREGS, (pid_t)a_pid, CPPUTILS_NULL, &oldregs);
        /* Revert the bytes we modified. */
        for(itr=0;itr<itersCount;++itr){
            ptrace(PTRACE_POKETEXT, (pid_t)a_pid, (void *)(addr + 8*itr), (void *)save[itr]);
        }
        ptrace(PTRACE_DETACH, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL);
        return CPPUTILS_NULL;
    }

    /* Wait for the client to execute the syscall, and stop. */
    waitpid((pid_t)a_pid, &status, WUNTRACED);
    if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
        // Get process registers, indicating if the injection suceeded
        ptrace(PTRACE_GETREGS, (pid_t)a_pid, CPPUTILS_NULL, &regs);
        pRemoteLibHandle = (void*)(regs.rax);
    }

    /* Revert the registers, too, to the old state. */
    ptrace(PTRACE_SETREGS, (pid_t)a_pid, CPPUTILS_NULL, &oldregs);
    /* Revert the bytes we modified. */
    for(itr=0;itr<itersCount;++itr){
        ptrace(PTRACE_POKETEXT, (pid_t)a_pid, (void *)(addr + 8*itr), (void *)save[itr]);
    }
    ptrace(PTRACE_DETACH, (pid_t)a_pid, CPPUTILS_NULL, CPPUTILS_NULL);

    return pRemoteLibHandle;
}


CPPUTILS_END_C


#endif  //  #ifndef _WIN32
