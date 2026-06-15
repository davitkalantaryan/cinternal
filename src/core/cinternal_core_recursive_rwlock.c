//
// repo:			cinternal
// file:            cinternal_core_recursive_rwlock.c
// path:			src/core/cinternal_core_recursive_rwlock.c
// created on:		2026 Jun 15
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// comment:			recursive RW mutex
//


#ifndef cinternal_gettid_needed
#define cinternal_gettid_needed
#endif

#include <cinternal/recursive_rwlock.h>
#include <cinternal/gettid.h>
#include <cinternal/rwlock.h>
#include <cinternal/thread_local_sys.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stddef.h>
#include <stdlib.h>
#include <cinternal/undisable_compiler_warnings.h>


#ifdef _MSC_VER
#pragma warning(disable: 4820)
#endif


CPPUTILS_BEGIN_C


struct CinternalRecursiveRWLock{
    int64_t             wr_owner_tid;
    CInternalRWLock     rw_lock;
    CinternalTlsData    tlsInd;
};


CINTERNAL_EXPORT CinternalRecursiveRWLockT CinternalRecursiveRWLockCreate(void) CPPUTILS_NOEXCEPT
{
    struct CinternalRecursiveRWLock* const recursive_rw_lock = CPPUTILS_STATIC_CAST(struct CinternalRecursiveRWLock*, malloc(sizeof(struct CinternalRecursiveRWLock)));
    if (recursive_rw_lock) {
        if (CinternalTlsAlloc( &(recursive_rw_lock->tlsInd), CPPUTILS_NULL)) {
            free(recursive_rw_lock);
            return CPPUTILS_NULL;
        }
        CInternalRWLockInitNoCheck(&(recursive_rw_lock->rw_lock));
        recursive_rw_lock->wr_owner_tid = 0;
        return recursive_rw_lock;
    }  //  if (recursive_rw_lock) {
    return CPPUTILS_NULL;
}


CINTERNAL_EXPORT void CinternalRecursiveRWLockDelete(CinternalRecursiveRWLockT a_recursive_rw_lock) CPPUTILS_NOEXCEPT
{
    if (a_recursive_rw_lock) {
        CinternalTlsDelete(a_recursive_rw_lock->tlsInd);
        CInternalRWLockClean(&(a_recursive_rw_lock->rw_lock));
        free(a_recursive_rw_lock);
    }
}


CINTERNAL_EXPORT void CinternalRecursiveRWLockSharedLock(ConstCinternalRecursiveRWLockT a_recursive_rw_lock) CPPUTILS_NOEXCEPT
{
    const size_t threadSpecCount = (size_t)CinternalTlsGetSpecific(a_recursive_rw_lock->tlsInd);
    if (threadSpecCount>0) {
        CinternalTlsSetSpecific(a_recursive_rw_lock->tlsInd, (void*)(threadSpecCount+1));
        return;
    }  //  if (threadSpecCount) {

    CInternalRWLockRdLock( CPPUTILS_CONST_CAST(CInternalRWLock*,&(a_recursive_rw_lock->rw_lock)));
    CinternalTlsSetSpecific(a_recursive_rw_lock->tlsInd, (void*)1);
}


CINTERNAL_EXPORT int  CinternalRecursiveRWLockUniqueLock(CinternalRecursiveRWLockT a_recursive_rw_lock) CPPUTILS_NOEXCEPT
{
    const int64_t currentTid = CinternalGetCurrentTid();
    const size_t threadSpecCount = (size_t)CinternalTlsGetSpecific(a_recursive_rw_lock->tlsInd);
    if (threadSpecCount > 0) {
        if ((a_recursive_rw_lock->wr_owner_tid) != currentTid) {
            // trying to upgrade lock, not possible
            return -1;
        }  //  if ((a_recursive_rw_lock->tlsInd) != currentTid) {
        CinternalTlsSetSpecific(a_recursive_rw_lock->tlsInd, (void*)(threadSpecCount + 1));
        return 0;
    }  //  if (threadSpecCount > 0) {

    CInternalRWLockWrLock(&(a_recursive_rw_lock->rw_lock));
    a_recursive_rw_lock->wr_owner_tid = currentTid;
    CinternalTlsSetSpecific(a_recursive_rw_lock->tlsInd, (void*)1);
    return 0;
}


CINTERNAL_EXPORT void CinternalRecursiveRWLockUnlock(ConstCinternalRecursiveRWLockT a_recursive_rw_lock) CPPUTILS_NOEXCEPT
{
    const size_t threadSpecCount = (size_t)CinternalTlsGetSpecific(a_recursive_rw_lock->tlsInd);
    CinternalTlsSetSpecific(a_recursive_rw_lock->tlsInd, (void*)(threadSpecCount - 1));
    if (threadSpecCount < 2) {
        if ((a_recursive_rw_lock->wr_owner_tid) > 0) {
            CPPUTILS_CONST_CAST(struct CinternalRecursiveRWLock*,a_recursive_rw_lock)->wr_owner_tid = 0;
            CInternalRWLockWrUnlock(CPPUTILS_CONST_CAST(CInternalRWLock*, &(a_recursive_rw_lock->rw_lock)));
        }  //  if ((a_recursive_rw_lock->wr_owner_tid) > 0) {
        else {
            CInternalRWLockRdUnlock(CPPUTILS_CONST_CAST(CInternalRWLock*, &(a_recursive_rw_lock->rw_lock)));
        }  //  else of 'if ((a_recursive_rw_lock->wr_owner_tid) > 0) {'
    }  //  if (threadSpecCount < 2) {
}


CPPUTILS_END_C
