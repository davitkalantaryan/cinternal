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
#include <cinternal/win_threading.h>
#else
#include <pthread.h>
#endif
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C


#ifdef _WIN32

typedef cinternal_win_thread_t      cinternal_thread_t;
typedef cinternal_win_thread_ret_t	cinternal_thread_ret_t;

#define CPPUTILS_THR_CALL											CPPUTILS_WIN_THR_CALL
#define CINTERNAL_UNREACH_CODE_AFTER_THR_EXIT                       CINTERNAL_UNREACH_CODE_AFTER_WIN_THR_EXIT

#define cinternal_thread_exit_thread								cinternal_win_thread_exit_thread
#define cinternal_thread_create(_pThread,_startFn,_arg)				cinternal_win_thread_create(_pThread,_startFn,_arg,CPPUTILS_NULL)
#define cinternal_thread_detach(_pThread)							CloseHandle((HANDLE)(*(_pThread)))
#define cinternal_thread_attach(_pThread,_thread_id)				( (*(_pThread) = (cinternal_thread_t)OpenThread(THREAD_ALL_ACCESS,FALSE,(DWORD)(_thread_id)))?0:(GetLastError()) )
#define cinternal_thread_thread_id(_thread)							GetThreadId((HANDLE)(_thread))
#define cinternal_thread_destroy(_pThread)							CloseHandle((HANDLE)(*(_pThread)))
#define cinternal_thread_wait(_thread)								WaitForSingleObjectEx((HANDLE)(_thread),INFINITE,TRUE)
#ifdef CINTERNAL_CRT_WIN_THREADING_IS_USED
#if defined(cinternal_thread_wait_and_clean_needed) || defined(cinternal_thread_wait_and_clean_or_getexitcode_needed)
inline void cinternal_thread_wait_and_clean(cinternal_win_thread_t* CPPUTILS_ARG_NN _pThread, cinternal_win_thread_id_t* CPPUTILS_ARG_NN _exitCodePtr) CPPUTILS_NOEXCEPT {
    DWORD dwExitCode;
    WaitForSingleObjectEx((HANDLE)(*(_pThread)), INFINITE, TRUE);
    if (GetExitCodeThread((HANDLE)(*(_pThread)),&dwExitCode)) {
        *_exitCodePtr = (cinternal_win_thread_id_t)dwExitCode;
    }
    CloseHandle((HANDLE)(*(_pThread)));
}
#endif
#if defined(cinternal_thread_get_exit_code_needed) || defined(cinternal_thread_wait_and_clean_or_getexitcode_needed)
inline void cinternal_thread_get_exit_code(cinternal_win_thread_t _thread, cinternal_win_thread_id_t* CPPUTILS_ARG_NN _exitCodePtr) CPPUTILS_NOEXCEPT {
    DWORD dwExitCode;
    if (GetExitCodeThread((HANDLE)(_thread), &dwExitCode)) {
        *_exitCodePtr = (cinternal_win_thread_id_t)dwExitCode;
    }
}
#endif
#else
#define cinternal_thread_wait_and_clean(_pThread,_exitCodePtr)		WaitForSingleObjectEx((HANDLE)(*(_pThread)),INFINITE,TRUE);GetExitCodeThread((HANDLE)(*(_pThread)),_exitCodePtr),CloseHandle((HANDLE)(*(_pThread)))
#define cinternal_thread_get_exit_code(_thread,_exitCodePtr)		GetExitCodeThread((HANDLE)(_thread),_exitCodePtr)
#endif

#else   //  #ifdef _WIN32


#define CPPUTILS_THR_CALL
#define CINTERNAL_UNREACH_CODE_AFTER_THR_EXIT(_retStat)

typedef pthread_t	cinternal_thread_t;
typedef void*	cinternal_thread_ret_t;

#define cinternal_thread_exit_thread								pthread_exit
#define cinternal_thread_create(_pThread,_startFn,_arg)				pthread_create(_pThread,CPPUTILS_NULL,_startFn,_arg)
#define cinternal_thread_wait_and_clean(_pThread,_exitCodePtr)		pthread_join(*(_pThread),_exitCodePtr)
#define cinternal_thread_detach(_pThread)							pthread_detach(*(_pThread))

#endif  // #ifdef _WIN32


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_THREADING_H
