//
// file:            load_lib_on_remote_process.h
// path:			include/cinternal/load_lib_on_remote_process.h
// created on:		2023 Mar 10
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_LOAD_LIB_ON_REMOTE_PROCESS_H
#define CINTERNAL_INCLUDE_CINTERNAL_LOAD_LIB_ON_REMOTE_PROCESS_H

#include <cinternal/export_symbols.h>
#include <stdbool.h>


CPPUTILS_BEGIN_C


CINTERNAL_EXPORT bool	CInternalLoadLibOnRemoteProcess(int a_pid, const char* a_libraryName);
CINTERNAL_EXPORT void*	CInternalLoadLibOnRemoteProcessAnGetModule(int a_pid, const char* a_libraryName);


CPPUTILS_END_C



#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_LOAD_LIB_ON_REMOTE_PROCESS_H
