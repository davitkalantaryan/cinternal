//
// repo:			cinternal
// file:			thread_local_sys.h
// path:			include/cinternal/thread_local_sys.h
// created on:		2023 Mar 24
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_THREAD_LOCAL_SYS_H
#define CINTERNAL_INCLUDE_CINTERNAL_THREAD_LOCAL_SYS_H


#include <cinternal/internal_header.h>

#ifdef _MSC_VER
#pragma warning(disable:4191)
#endif

#include <cinternal/disable_compiler_warnings.h>

#ifdef _WIN32

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <fibersapi.h>

typedef DWORD           CinternalTlsData;

#define	CINTERNAL_TLS_OUT_OF_INDEXES		FLS_OUT_OF_INDEXES
#define CinternalTlsAlloc(_key_ptr,_destructor)     (     (    (  (*(_key_ptr)) = FlsAlloc(CPPUTILS_REINTERPRET_CAST(PFLS_CALLBACK_FUNCTION,_destructor))  )==FLS_OUT_OF_INDEXES    ) ?      \
            CPPUTILS_STATIC_CAST(int,GetLastError()) : 0     )
#define CinternalTlsGetSpecific     FlsGetValue
#define CinternalTlsSetSpecific     FlsSetValue
#define CinternalTlsDelete          FlsFree

#else

#include <pthread.h>

typedef pthread_key_t   CinternalTlsData;

#define	CINTERNAL_TLS_OUT_OF_INDEXES		CPPUTILS_STATIC_CAST(pthread_key_t,-1)
#define CinternalTlsAlloc           pthread_key_create
#define CinternalTlsGetSpecific     pthread_getspecific
#define CinternalTlsSetSpecific     pthread_setspecific
#define CinternalTlsDelete          pthread_key_delete

#endif

#include <cinternal/undisable_compiler_warnings.h>


#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_THREAD_LOCAL_SYS_H
