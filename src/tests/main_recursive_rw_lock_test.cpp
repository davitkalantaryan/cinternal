//
// file:            main_recursive_rw_lock_test.cpp
// path:			src/tests/main_recursive_rw_lock_test.cpp
// created on:		2026 Jun 15
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/recursive_rwlock.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdio.h>
#include <cinternal/undisable_compiler_warnings.h>


int main(void)
{

    int lockRestult;
    const CinternalRecursiveRWLockT recursive_rw_lock = CinternalRecursiveRWLockCreate();

    if (!recursive_rw_lock) {
        return 1;
    }

    CinternalRecursiveRWLockSharedLock(recursive_rw_lock);
    CinternalRecursiveRWLockSharedLock(recursive_rw_lock);
    CinternalRecursiveRWLockUnlock(recursive_rw_lock);
    CinternalRecursiveRWLockUnlock(recursive_rw_lock);

    lockRestult = CinternalRecursiveRWLockUniqueLock(recursive_rw_lock);
    printf("lockRestult = %d\n", lockRestult);
    lockRestult = CinternalRecursiveRWLockUniqueLock(recursive_rw_lock);
    printf("lockRestult = %d\n", lockRestult);
    CinternalRecursiveRWLockUnlock(recursive_rw_lock);
    CinternalRecursiveRWLockUnlock(recursive_rw_lock);

    lockRestult = CinternalRecursiveRWLockUniqueLock(recursive_rw_lock);
    printf("lockRestult = %d\n", lockRestult);
    CinternalRecursiveRWLockSharedLock(recursive_rw_lock);
    CinternalRecursiveRWLockUnlock(recursive_rw_lock);
    CinternalRecursiveRWLockUnlock(recursive_rw_lock);

    CinternalRecursiveRWLockSharedLock(recursive_rw_lock);
    lockRestult = CinternalRecursiveRWLockUniqueLock(recursive_rw_lock);
    printf("lockRestult = %d\n", lockRestult);
    CinternalRecursiveRWLockUnlock(recursive_rw_lock);

    CinternalRecursiveRWLockDelete(recursive_rw_lock);

	return 0;
}
