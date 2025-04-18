//
// repo:            cinternal
// file:			cinternal_unit_test_0001_lw_mutex_recursive.c
// path:			src/tests/unit_test/cinternal_unit_test_0001_lw_mutex_recursive.c
// created on:		2023 Jun 20
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test.h>
#define cinternal_lw_recursive_mutex_create_needed
#include <cinternal/lw_mutex_recursive.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stddef.h>
#include <cinternal/undisable_compiler_warnings.h>



CPPUTILS_UTEST_ALL(f_0001_lw_mutex_recursive, t_0001) {

    cinternal_lw_recursive_mutex_t aMutex;
    cinternal_lw_recursive_mutex_create(&aMutex);
    cinternal_lw_recursive_mutex_lock(&aMutex);
    cinternal_lw_recursive_mutex_lock(&aMutex);
    cinternal_lw_recursive_mutex_unlock(&aMutex);
    cinternal_lw_recursive_mutex_unlock(&aMutex);
    cinternal_lw_recursive_mutex_destroy(&aMutex);
    CinternalUnitTestAssertCheckOpt(true);
}
