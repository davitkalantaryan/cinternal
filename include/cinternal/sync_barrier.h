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
#endif
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C


#ifdef _WIN32

typedef SYNCHRONIZATION_BARRIER	cinternal_sync_barrier_t;

#define cinternal_sync_barrier_create(_pBarrier,_threadsCount)	( InitializeSynchronizationBarrier(_pBarrier,_threadsCount,-1)?0:(GetLastError()) )
#define cinternal_sync_barrier_destroy(_pBarrier)				DeleteSynchronizationBarrier(_pBarrier)
#define cinternal_sync_barrier_wait(_pBarrier)					(EnterSynchronizationBarrier(_pBarrier,SYNCHRONIZATION_BARRIER_FLAGS_NO_DELETE)?1:0)

#else   //  #ifdef _WIN32

typedef pthread_barrier_t		cinternal_sync_barrier_t;

#define cinternal_sync_barrier_create(_pBarrier,_threadsCount)	pthread_barrier_init(_pBarrier,CPPUTILS_NULL,_threadsCount)
#define cinternal_sync_barrier_destroy(_pBarrier)				pthread_barrier_destroy(_pBarrier)
#define cinternal_sync_barrier_wait(_pBarrier)					((pthread_barrier_wait(_pBarrier)==PTHREAD_BARRIER_SERIAL_THREAD)?1:0)

#endif  // #ifdef _WIN32


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_SYNC_BARRIER_H
