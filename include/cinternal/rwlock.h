//
// repo:            cinternal
// file:            rwlock.h
// path:			include/cinternal/rwlock.h
// created on:		2024 Dec 16
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_RWLOCK_H
#define CINTERNAL_INCLUDE_CINTERNAL_RWLOCK_H

#include <cinternal/internal_header.h>
#include <cinternal/disable_compiler_warnings.h>

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
typedef SRWLOCK CInternalRWLock;
#define CInternalRWLockInit(_lockPtr)           InitializeSRWLock(_lockPtr)
#define CInternalRWLockClean(_lockPtr)      
#define CInternalRWLockWrLock(_lockPtr)         AcquireSRWLockExclusive(_lockPtr)
#define CInternalRWLockRdLock(_lockPtr)         AcquireSRWLockShared(_lockPtr)
#define CInternalRWLockTryWrLock(_lockPtr)      TryAcquireSRWLockExclusive(_lockPtr)
#define CInternalRWLockTryRdLock(_lockPtr)      TryAcquireSRWLockShared(_lockPtr)
#define CInternalRWLockWrUnlock(_lockPtr)       ReleaseSRWLockExclusive(_lockPtr)
#define CInternalRWLockRdUnlock(_lockPtr)       ReleaseSRWLockShared(_lockPtr)
#else
#include <pthread.h>
#define CInternalRWLockInit(_lockPtr)           pthread_rwlock_init(_lockPtr)
#define CInternalRWLockClean(_lockPtr)          pthread_rwlock_destroy(_lockPtr);
#define CInternalRWLockWrLock(_lockPtr)         pthread_rwlock_wrlock(_lockPtr)
#define CInternalRWLockRdLock(_lockPtr)         pthread_rwlock_rdlock(_lockPtr)
#define CInternalRWLockTryWrLock(_lockPtr)      (pthread_rwlock_trywrlock(_lockPtr) ? 0 : 1)
#define CInternalRWLockTryRdLock(_lockPtr)      (pthread_rwlock_tryrdlock(_lockPtr) ? 0 : 1)
#define CInternalRWLockWrUnlock(_lockPtr)       pthread_rwlock_unlock(_lockPtr)
#define CInternalRWLockRdUnlock(_lockPtr)       pthread_rwlock_unlock(_lockPtr)

#endif
#include <cinternal/undisable_compiler_warnings.h>


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_RWLOCK_H
