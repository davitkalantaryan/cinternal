//
// repo:			cinternal
// file:			cinternal_unit_test_0000_initial.c
// path:			src/tests/unit_test/cinternal_unit_test_0000_initial.c
// created on:		2023 May 19
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#include <cinternal/unit_test.h>
#include <stdbool.h>


CPPUTILS_UTEST_BEFORE_MAIN(f_0000_initial, t_0001) {
	CINTERNAL_UNIT_TEST_IGNORE_ARGS();
	CinternalUnitTestAssertCheckSrc(true);
}


CPPUTILS_UTEST_AFTER_MAIN(f_0000_initial, t_0002) {
	CinternalUnitTestAssertCheckTst(true);
}


CPPUTILS_UTEST_ALL(f_0000_initial, t_0003) {
	CinternalUnitTestAssertCheckAll(true);
}

CPPUTILS_UTEST_ALL(f_0000_initial, t_0004) {
	CinternalUnitTestAssertCheckOpt(true);
}
