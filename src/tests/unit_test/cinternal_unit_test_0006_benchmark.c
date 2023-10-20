//
// repo:            cinternal
// file:			cinternal_unit_test_0005_threading_and_sync.c
// path:			src/tests/unit_test/cinternal_unit_test_0005_threading_and_sync.c
// created on:		2023 Jul 24
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test.h>
#define CINTERNAL_BENCHMARK_FIN_needed
#include <cinternal/benchmark.h>



CPPUTILS_UTEST_AFTER_MAIN(f_0006_benchmark, t_0001) {
    double val1, val2;
    CINTERNAL_BENCHMARK_DECL(1);
    CINTERNAL_BENCHMARK_START(1);
    // --- bla bla, that should be mesured
    CINTERNAL_BENCHMARK_FIN(1);
    val1 = CPPUTILS_STATIC_CAST(double, CINTERNAL_BENCHMARK_TIME_DIFF(1).tv_sec) + (CPPUTILS_STATIC_CAST(double, CINTERNAL_BENCHMARK_TIME_DIFF(1).tv_usec) / 1000000.);
    val2 = CINTERNAL_BENCHMARK_TIME_DIFF_SECS_DBL(1);
    CinternalUnitTestAssertCheckOpt((val2 - val1) < 0.0001);
}
