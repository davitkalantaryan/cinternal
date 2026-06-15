//
// repo:            cinternal
// file:            recursive_rwlock.h
// path:			include/cinternal/recursive_rwlock.h
// created on:		2026 Jun 15
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_RECURSIVE_RWLOCK_H
#define CINTERNAL_INCLUDE_CINTERNAL_RECURSIVE_RWLOCK_H


#include <cinternal/export_symbols.h>


CPPUTILS_BEGIN_C


struct CinternalRecursiveRWLock;
typedef struct CinternalRecursiveRWLock* CinternalRecursiveRWLockT;
typedef const struct CinternalRecursiveRWLock* ConstCinternalRecursiveRWLockT;

CINTERNAL_EXPORT CinternalRecursiveRWLockT CinternalRecursiveRWLockCreate(void) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CinternalRecursiveRWLockDelete(CinternalRecursiveRWLockT a_recursive_rw_lock) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CinternalRecursiveRWLockSharedLock(ConstCinternalRecursiveRWLockT a_recursive_rw_lock) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT int  CinternalRecursiveRWLockUniqueLock(CinternalRecursiveRWLockT a_recursive_rw_lock) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CinternalRecursiveRWLockUnlock(ConstCinternalRecursiveRWLockT a_recursive_rw_lock) CPPUTILS_NOEXCEPT;


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_RECURSIVE_RWLOCK_H
