//
// repo:			cinternal
// file:            sync_barrier.h
// path:			include/cinternal/sync_barrier.h
// created on:		2023 Jul 23
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_UNNAMED_SEMAPHORE_H
#define CINTERNAL_INCLUDE_CINTERNAL_UNNAMED_SEMAPHORE_H

#include <cinternal/internal_header.h>
#include <cinternal/disable_compiler_warnings.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#elif defined(__APPLE__)
#include <dispatch/dispatch.h>
#else
#include <semaphore.h>
#include <sys/time.h>
#define UNNAMED_SHARING_TYPE	0/* 0 means semaphores is shared between threads in same process */
#endif
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C


#ifdef _WIN32

typedef HANDLE	cinternal_unnamed_sema_t;

#define cinternal_unnamed_sema_create(_pSema,_count)					( (*(_pSema) = CreateSemaphore(CPPUTILS_NULL,CPPUTILS_STATIC_CAST(LONG,_count),1024,CPPUTILS_NULL))?0:(-1) )
#define cinternal_unnamed_sema_destroy(_pSema)							CloseHandle(*(_pSema))
#define cinternal_unnamed_sema_post_cnt_get_cnt(_pSema,_count,_cntPtr)	ReleaseSemaphore( *(_pSema), CPPUTILS_STATIC_CAST(LONG,_count), _cntPtr  )
#define cinternal_unnamed_sema_post(_pSema)								ReleaseSemaphore( *(_pSema), 1, CPPUTILS_NULL  )
#define cinternal_unnamed_sema_wait(_pSema)								WaitForSingleObjectEx( *(_pSema), INFINITE,TRUE )
#define cinternal_unnamed_sema_wait_ms(_pSema,_timeMs)					WaitForSingleObjectEx( *(_pSema), CPPUTILS_STATIC_CAST(DWORD,_timeMs),TRUE )


#elif defined(__APPLE__)

typedef dispatch_semaphore_t	cinternal_unnamed_sema_t;

#define cinternal_unnamed_sema_create(_pSema,_count)	( (*(_pSema) = dispatch_semaphore_create(CPPUTILS_STATIC_CAST(intptr_t,_count)))?0:(-1) )
#define cinternal_unnamed_sema_destroy(_pSema)			dispatch_release(*(_pSema))
#define cinternal_unnamed_sema_post(_pSema)				dispatch_semaphore_signal( *(_pSema) )
#define cinternal_unnamed_sema_wait(_pSema)				dispatch_semaphore_wait( *(_pSema), DISPATCH_TIME_FOREVER )
#define cinternal_unnamed_sema_wait_ms(_pSema,_timeMs)	dispatch_semaphore_wait( *(_pSema), CPPUTILS_STATIC_CAST(dispatch_time_t,_timeMs) )


#else   //  #ifdef _WIN32

typedef sem_t	cinternal_unnamed_sema_t;

#define cinternal_unnamed_sema_create(_pSema,_count)	sem_init( _pSema, 0, CPPUTILS_STATIC_CAST(unsigned int,(_count)) )
#define cinternal_unnamed_sema_destroy(_pSema)			sem_destroy(_pSema)
#define cinternal_unnamed_sema_post(_pSema)				sem_post( _pSema )
#define cinternal_unnamed_sema_wait(_pSema)				sem_wait( _pSema )
#ifdef cinternal_unnamed_sema_wait_ms_needed
#undef cinternal_unnamed_sema_wait_ms_needed
static inline int cinternal_unnamed_sema_wait_ms_inline(cinternal_unnamed_sema_t* a_pSema, size_t a_waitTimeMs) {
    struct timespec finalAbsTime;
    struct timeval currentTime;
    long long int nExtraNanoSeconds;
    gettimeofday(&currentTime, NULL);
    nExtraNanoSeconds = (long long int)currentTime.tv_usec * 1000 + (long long int)((a_waitTimeMs % 1000) * 1000000);
    finalAbsTime.tv_sec = currentTime.tv_sec + a_waitTimeMs / 1000 + nExtraNanoSeconds / 1000000000;
    finalAbsTime.tv_nsec = nExtraNanoSeconds % 1000000000;
    return sem_timedwait(a_pSema, &finalAbsTime);
}
#define cinternal_unnamed_sema_wait_ms(_pSema,_timeMs)  cinternal_unnamed_sema_wait_ms_inline(_pSema,CPPUTILS_STATIC_CAST(size_t,_timeMs))
#endif

#endif  // #ifdef _WIN32


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_UNNAMED_SEMAPHORE_H
