//
// repo:            cinternal
// file:			cinternal_unit_test_0001_lw_mutex_recursive.c
// path:			src/tests/unit_test/cinternal_unit_test_0001_lw_mutex_recursive.c
// created on:		2023 Jun 20
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test_tools.h>
#include <cinternal/unit_test.h>
#define cinternal_sync_barrier_needed
#include <cinternal/sync_barrier.h>



CPPUTILS_UTEST_ALL(f_0002_sync_barrier, t_0001) {

    cinternal_sync_barrier_t aBarrier;
    CinternalUnitTestAssertCheck(cinternal_sync_barrier_create(&aBarrier, 1)==0);
    CinternalUnitTestAssertCheck(cinternal_sync_barrier_wait(&aBarrier)==1);
    cinternal_sync_barrier_destroy(&aBarrier);
    CinternalUnitTestAssertCheck(true);
}
