//
// repo:            cinternal
// file:			cinternal_unit_test_0003_unnamed_sema.c
// path:			src/tests/unit_test/cinternal_unit_test_0003_unnamed_sema.c
// created on:		2023 Jul 24
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test_tools.h>
#if 1
#include <cinternal/unit_test.h>
#define cinternal_unnamed_sema_wait_ms_needed
#include <cinternal/unnamed_semaphore.h>
#include <stddef.h>



CPPUTILS_UTEST_ALL(f_0003_unnamed_sema, t_0001) {

    cinternal_unnamed_sema_t aSema;
    CinternalUnitTestAssertCheck(cinternal_unnamed_sema_create(&aSema, 0)==0);
    cinternal_unnamed_sema_destroy(&aSema);
    CinternalUnitTestAssertCheck(true);
}


#endif
