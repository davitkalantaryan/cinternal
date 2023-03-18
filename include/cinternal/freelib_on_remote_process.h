//
// file:            freelib_on_remote_process_sys.h
// path:			include/cinternal/freelib_on_remote_process_sys.h
// created on:		2023 Mar 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_FREELIB_ON_REMOTE_PROCESS_SYS_H
#define CINTERNAL_INCLUDE_CINTERNAL_FREELIB_ON_REMOTE_PROCESS_SYS_H

#include <cinternal/export_symbols.h>

#ifdef _WIN32

#include <stdbool.h>
#include <cinternal/disable_compiler_warnings.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>


CPPUTILS_BEGIN_C



CINTERNAL_EXPORT bool CInternalFreeLibOnRemoteProcessByName(int a_pid, const char* a_libraryName);
CINTERNAL_EXPORT bool CInternalFreeLibOnRemoteProcessByHandle(int a_pid, void* a_libraryHandle);


CPPUTILS_END_C


#endif  //  #ifdef _WIN32


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_FREELIB_ON_REMOTE_PROCESS_SYS_H
