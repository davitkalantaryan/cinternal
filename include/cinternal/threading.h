//
// repo:			cinternal
// file:            threading.h
// path:			include/cinternal/threading.h
// created on:		2023 Jul 24
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_THREADING_H
#define CINTERNAL_INCLUDE_CINTERNAL_THREADING_H

#include <cinternal/internal_header.h>
#include <cinternal/disable_compiler_warnings.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#else
#include <pthread.h>
#endif
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C


#ifdef _WIN32

typedef HANDLE	cinternal_thread_t;
typedef DWORD	cinternal_thread_ret_t;

#define CPPUTILS_THR_CALL											WINAPI

#define cinternal_thread_exit_thread								ExitThread
#define cinternal_thread_create(_pThread,_startFn,_arg)				( ( *(_pThread) = CreateThread(CPPUTILS_NULL,0,_startFn,_arg,0,CPPUTILS_NULL) )?0:(GetLastError()) )
#define cinternal_thread_wait_and_clean(_pThread,_exitCodePtr)		WaitForSingleObjectEx(*(_pThread),INFINITE,TRUE);GetExitCodeThread(*(_pThread),_exitCodePtr),CloseHandle(*(_pThread))
#define cinternal_thread_detach(_pThread)							CloseHandle(*(_pThread))
#define cinternal_thread_attach(_pThread,_thread_id)				( (*(_pThread) = OpenThread(THREAD_ALL_ACCESS,FALSE,_thread_id))?0:(GetLastError()) )
#define cinternal_thread_thread_id(_thread)							GetThreadId(_thread)
#define cinternal_thread_destroy(_pThread)							CloseHandle(*(_pThread))
#define cinternal_thread_wait(_thread)								WaitForSingleObjectEx(_thread,INFINITE,TRUE)
#define cinternal_thread_get_exit_code(_thread,_exitCodePtr)		GetExitCodeThread(_thread,_exitCodePtr)

#else   //  #ifdef _WIN32


#define CPPUTILS_THR_CALL

typedef pthread_t	cinternal_thread_t;
typedef void*	cinternal_thread_ret_t;

#define cinternal_thread_exit_thread								pthread_exit
#define cinternal_thread_create(_pThread,_startFn,_arg)				pthread_create(_pThread,CPPUTILS_NULL,_startFn,_arg)
#define cinternal_thread_wait_and_clean(_pThread,_exitCodePtr)		pthread_join(*(_pThread),_exitCodePtr)
#define cinternal_thread_detach(_pThread)							pthread_detach(*(_pThread))

#endif  // #ifdef _WIN32


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_THREADING_H
