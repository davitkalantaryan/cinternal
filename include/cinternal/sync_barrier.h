//
// repo:			cinternal
// file:            sync_barrier.h
// path:			include/cinternal/sync_barrier.h
// created on:		2023 Jul 23
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_SYNC_BARRIER_H
#define CINTERNAL_INCLUDE_CINTERNAL_SYNC_BARRIER_H

#include <cinternal/internal_header.h>
#include <cinternal/disable_compiler_warnings.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#else
#include <pthread.h>
#include <errno.h>
#endif
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C

//#define __APPLE__
//#ifndef cinternal_sync_barrier_needed
//#define cinternal_sync_barrier_needed
//#endif

#ifdef __APPLE__

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int tripCount;
} cinternal_sync_barrier_t;

#endif


#ifdef _WIN32

typedef SYNCHRONIZATION_BARRIER	cinternal_sync_barrier_t;

#define cinternal_sync_barrier_create(_pBarrier,_threadsCount)	( InitializeSynchronizationBarrier(_pBarrier,_threadsCount,-1)?0:(GetLastError()) )
#define cinternal_sync_barrier_destroy(_pBarrier)				DeleteSynchronizationBarrier(_pBarrier)
#define cinternal_sync_barrier_wait(_pBarrier)					(EnterSynchronizationBarrier(_pBarrier,SYNCHRONIZATION_BARRIER_FLAGS_NO_DELETE)?1:0)

#elif defined(__APPLE__)

#if defined(cinternal_sync_barrier_create_needed) || defined(cinternal_sync_barrier_needed)
#ifdef cinternal_sync_barrier_create_needed
#undef cinternal_sync_barrier_create_needed
#endif
static inline int cinternal_sync_barrier_create(cinternal_sync_barrier_t* a_pBarrier, int a_count) CPPUTILS_NOEXCEPT  {
    if (a_count == 0) {
        return EINVAL;
    }
    if (pthread_mutex_init(&(a_pBarrier->mutex), 0) < 0) {
        return errno;
    }
    if (pthread_cond_init(&(a_pBarrier->cond), 0) < 0) {
        pthread_mutex_destroy(&(a_pBarrier->mutex));
        return -1;
    }
    a_pBarrier->tripCount = a_count;
    a_pBarrier->count = 0;
    return 0;
}
#endif  //  #if defined(cinternal_sync_barrier_create_needed) || defined(cinternal_sync_barrier_needed)

#if defined(cinternal_sync_barrier_destroy_needed) || defined(cinternal_sync_barrier_needed)
#ifdef cinternal_sync_barrier_destroy_needed
#undef cinternal_sync_barrier_destroy_needed
#endif
static inline void cinternal_sync_barrier_destroy(cinternal_sync_barrier_t* a_pBarrier) CPPUTILS_NOEXCEPT  {
    pthread_cond_destroy(&(a_pBarrier->cond));
    pthread_mutex_destroy(&(a_pBarrier->mutex));
}
#endif  //  #if defined(cinternal_sync_barrier_create_needed) || defined(cinternal_sync_barrier_needed)

#if defined(cinternal_sync_barrier_wait_needed) || defined(cinternal_sync_barrier_needed)
#ifdef cinternal_sync_barrier_wait_needed
#undef cinternal_sync_barrier_wait_needed
#endif
static inline int cinternal_sync_barrier_wait(cinternal_sync_barrier_t* a_pBarrier) CPPUTILS_NOEXCEPT  {
    if (pthread_mutex_lock(&(a_pBarrier->mutex)) < 0) {
        return -1;
    }
    ++(a_pBarrier->count);
    if ((a_pBarrier->count) >= (a_pBarrier->tripCount)) {
        a_pBarrier->count = 0;
        if (pthread_cond_broadcast(&(a_pBarrier->cond)) < 0) {
            pthread_mutex_unlock(&(a_pBarrier->mutex));
            return -1;
        }
        if (pthread_mutex_unlock(&(a_pBarrier->mutex)) < 0) {
            return -1;
        }
        return 1;
    }

    if (pthread_cond_wait(&(a_pBarrier->cond), &(a_pBarrier->mutex)) < 0) {
        return -1;
    }

    if (pthread_mutex_unlock(&(a_pBarrier->mutex)) < 0) {
        return -1;
    }

    return 0;
}
#endif  //  #if defined(cinternal_sync_barrier_create_needed) || defined(cinternal_sync_barrier_needed)

#ifdef cinternal_sync_barrier_needed
#undef cinternal_sync_barrier_needed
#endif


#else   //  #ifdef _WIN32

typedef pthread_barrier_t		cinternal_sync_barrier_t;

#define cinternal_sync_barrier_create(_pBarrier,_threadsCount)	pthread_barrier_init(_pBarrier,CPPUTILS_NULL,_threadsCount)
#define cinternal_sync_barrier_destroy(_pBarrier)				pthread_barrier_destroy(_pBarrier)
#define cinternal_sync_barrier_wait(_pBarrier)					((pthread_barrier_wait(_pBarrier)==PTHREAD_BARRIER_SERIAL_THREAD)?1:0)

#endif  // #ifdef _WIN32


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_SYNC_BARRIER_H
