//
// repo:			cinternal
// file:            win_threading.h
// path:			include/cinternal/win_threading.h
// created on:		2026 Mar 13
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#ifndef CINTERNAL_INCLUDE_CINTERNAL_WIN_THREADING_H
#define CINTERNAL_INCLUDE_CINTERNAL_WIN_THREADING_H

#include <cinternal/internal_header.h>

#ifdef _WIN32

#include <cinternal/disable_compiler_warnings.h>
#if !defined(_MT) || defined(CINTERNAL_WTHREAD_FORCE_CREATETHREAD)
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
typedef HANDLE      cinternal_win_thread_t;
typedef DWORD	    cinternal_win_thread_ret_t;
typedef DWORD	    cinternal_win_thread_id_t;
#ifdef CINTERNAL_CRT_WIN_THREADING_IS_USED
#undef CINTERNAL_CRT_WIN_THREADING_IS_USED
#endif
#define CINTERNAL_UNREACH_CODE_AFTER_WIN_THR_EXIT(_retStat)
#define CPPUTILS_WIN_THR_CALL										WINAPI
#define cinternal_win_thread_exit_thread							ExitThread
#define cinternal_win_thread_create(_pThread,_startFn,_arg,_id_p)	( ( *(_pThread) = CreateThread(CPPUTILS_NULL,0,_startFn,_arg,0,_id_p) )?0:(GetLastError()) )
#else
#include <process.h>
#include <errno.h>
typedef uintptr_t   cinternal_win_thread_t;
typedef unsigned	cinternal_win_thread_ret_t;
typedef unsigned	cinternal_win_thread_id_t;
#define CINTERNAL_CRT_WIN_THREADING_IS_USED
#define CINTERNAL_UNREACH_CODE_AFTER_WIN_THR_EXIT(_retStat)         _retStat;
#define CPPUTILS_WIN_THR_CALL										__stdcall
#define cinternal_win_thread_exit_thread							_endthreadex
#define cinternal_win_thread_create(_pThread,_startFn,_arg,_id_p)	( ( *(_pThread) = _beginthreadex(CPPUTILS_NULL,0,_startFn,_arg,0,_id_p) )?0:(errno) )
#endif
#include <cinternal/undisable_compiler_warnings.h>

#endif  //  #ifdef _WIN32
#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_WIN_THREADING_H
