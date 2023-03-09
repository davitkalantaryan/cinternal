//
// file:            main_cinternal_core_windows_ld_preload.cpp
// path:			src/tests/main_cinternal_core_windows_ld_preload.cpp
// created on:		2023 Mar 09
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cinternal/export_symbols.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <assert.h>
#include <cinternal/disable_compiler_warnings.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

#define MAX_BUFFER_SIZE		4095


static HANDLE	s_mainThreadHandle;

static void SignalHandler(int a_signal);


int main(int a_argc, char* a_argv[])
{
	bool bShouldWaitForProcess = true;
	BOOL bCrtPrcRet;
	int i, nRet;
	size_t unOffset = 0;
	char vcCmdLine[MAX_BUFFER_SIZE+1];
	STARTUPINFOA aStartInfo;
	PROCESS_INFORMATION aProcInf = {0};

	fprintf(stdout, "Press any key then enter to continue "); fflush(stdout);
	nRet = getchar();
	CPPUTILS_STATIC_CAST(void, nRet);

	for (i = 1; i < a_argc; ++i) {
		if (strcmp("---no-wait", a_argv[i])==0) {
			bShouldWaitForProcess = false;
			if (i < (a_argc - 1)) {
				memmove(&a_argv[i], a_argv[i] + 1, (CPPUTILS_STATIC_CAST(size_t, a_argc)- CPPUTILS_STATIC_CAST(size_t,i)) * sizeof(char*));
			}
			else {
				a_argv[i] = CPPUTILS_NULL;
			}
			--a_argc;
			break;
		}  // if (strcmp("---no-wait", a_argv[i])==0) {
	}  //  for (i = 2; i < a_argc; ++i) {

	if (a_argc < 2) {
		fprintf(stderr, "name of application to start is not specified!\n");
		return 1;
	}

	vcCmdLine[0] = 0;

	for (i = 2; i < a_argc; ++i) {
		nRet = snprintf(vcCmdLine + unOffset, MAX_BUFFER_SIZE - unOffset, " %s",a_argv[i]);
		unOffset += CPPUTILS_STATIC_CAST(size_t, nRet);
		if (unOffset >= MAX_BUFFER_SIZE) {
			break;
		}
	}  //  for (i = 2; i < a_argc; ++i) {

	ZeroMemory(&aStartInfo, sizeof(aStartInfo));
	aStartInfo.wShowWindow = SW_SHOWNOACTIVATE;

	bCrtPrcRet = CreateProcessA(
		a_argv[1],			// lpApplicationName
		vcCmdLine,			// lpCommandLine
		CPPUTILS_NULL,		// lpProcessAttributes
		CPPUTILS_NULL,		// lpThreadAttributes
		FALSE,				// bInheritHandles   => todo: think on this
		CREATE_SUSPENDED,	// dwCreationFlags   => todo: maybe I'll switch this to 0
		CPPUTILS_NULL,		// lpEnvironment
		CPPUTILS_NULL,		// lpCurrentDirectory
		&aStartInfo,		// lpStartupInfo
		&aProcInf			// lpProcessInformation
	);
	if (!bCrtPrcRet) {
		fprintf(stderr,"Unable to create process with the name %s\n", a_argv[0]);
		return 1;
	}

	ResumeThread(aProcInf.hThread);
	if (bShouldWaitForProcess) {
		DWORD dwWaitResult;
		s_mainThreadHandle = GetCurrentThread();
		signal(SIGINT, &SignalHandler);
		dwWaitResult = WaitForSingleObjectEx(aProcInf.hProcess, INFINITE, TRUE);
		switch (dwWaitResult) {
		case WAIT_IO_COMPLETION:
			TerminateProcess(aProcInf.hProcess, 1);
			break;
		default:
			break;
		}
	}
	CloseHandle(aProcInf.hThread);
	CloseHandle(aProcInf.hProcess);


	return 0;
}


static VOID NTAPI InterruptFunctionStatic(_In_ ULONG_PTR a_parameter)
{
	CPPUTILS_STATIC_CAST(void, a_parameter);
}


static void SignalHandler(int a_signal)
{
	assert(a_signal == SIGINT);
	QueueUserAPC(&InterruptFunctionStatic, s_mainThreadHandle, 0);
}
