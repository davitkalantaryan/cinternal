//
// repo:			cinternal
// file:            lw_mutex_recursive.h
// path:			include/cinternal/lw_mutex_recursive.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_LW_MUTEX_RECURSIVE_H
#define CINTERNAL_INCLUDE_CINTERNAL_LW_MUTEX_RECURSIVE_H

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

typedef CRITICAL_SECTION	cinternal_lw_recursive_mutex_t;

#ifdef cinternal_lw_recursive_mutex_create_needed
#undef cinternal_lw_recursive_mutex_create_needed
static inline int cinternal_lw_recursive_mutex_createInline(cinternal_lw_recursive_mutex_t* a_pMutex){
	InitializeCriticalSection(a_pMutex);
	return 0;
}
#endif
#define cinternal_lw_recursive_mutex_create				cinternal_lw_recursive_mutex_createInline
#define cinternal_lw_recursive_mutex_destroy(a_pMutex)	DeleteCriticalSection(a_pMutex)
#define cinternal_lw_recursive_mutex_lock(a_pMutex)		EnterCriticalSection(a_pMutex)
#define cinternal_lw_recursive_mutex_unlock(a_pMutex)	LeaveCriticalSection(a_pMutex)

#else   //  #ifdef _WIN32

typedef pthread_mutex_t		cinternal_lw_recursive_mutex_t;

#ifdef cinternal_lw_recursive_mutex_create_needed
#undef cinternal_lw_recursive_mutex_create_needed
static inline int cinternal_lw_recursive_mutex_createInline(cinternal_lw_recursive_mutex_t* a_pMutex) {
	int nRet;
	pthread_mutexattr_t attr;
	if ((nRet = pthread_mutexattr_init(&attr))) {
		return nRet;
	}
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	nRet = pthread_mutex_init(a_pMutex, &attr);
	pthread_mutexattr_destroy(&attr);
	return nRet;
}
#endif
#define cinternal_lw_recursive_mutex_create				cinternal_lw_recursive_mutex_createInline
#define cinternal_lw_recursive_mutex_destroy(a_pMutex)	pthread_mutex_destroy(a_pMutex)
#define cinternal_lw_recursive_mutex_lock(a_pMutex)		pthread_mutex_lock(a_pMutex)
#define cinternal_lw_recursive_mutex_unlock(a_pMutex)	pthread_mutex_unlock(a_pMutex)

#endif  // #ifdef _WIN32


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_LW_MUTEX_RECURSIVE_H
