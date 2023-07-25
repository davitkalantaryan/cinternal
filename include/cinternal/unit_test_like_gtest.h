//
// repo:			cinternal
// file:            unit_test_like_gtest.h
// path:			include/cinternal/unit_test_like_gtest.h
// created on:		2023 Jul 24
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CUTILS_INCLUDE_CUTILS_UNIT_TEST_LIKE_GTEST_H
#define CUTILS_INCLUDE_CUTILS_UNIT_TEST_LIKE_GTEST_H

#include <cinternal/internal_header.h>
#include <cinternal/unit_test.h>
#include <cinternal/unit_test_tools.h>


#define TEST						CPPUTILS_UTEST_AFTER_MAIN
#define EXPECT_EQ(_left,_right)		CinternalUnitTestCheck(((_left)==(_right)))
#define ASSERT_EQ(_left,_right)		CinternalUnitTestAssertCheck(((_left)==(_right)))
#define ASSERT_FALSE(_condition)	CinternalUnitTestAssertCheck((!(_condition)))
#define ASSERT_TRUE					CinternalUnitTestAssertCheck



#endif  // #ifndef CUTILS_INCLUDE_CUTILS_UNIT_TEST_LIKE_GTEST_H
