//
// repo:			cinternal
// file:            unit_test.h
// path:			include/cinternal/unit_test.h
// created on:		2023 Apr 15
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CUTILS_INCLUDE_CUTILS_UNIT_TEST_H
#define CUTILS_INCLUDE_CUTILS_UNIT_TEST_H

#include <cinternal/export_symbols.h>
#include <cinternal/unit_test_only_checks.h>
#include <stdbool.h>


CPPUTILS_BEGIN_C

#define CINTERNAL_UNIT_TEST_FN_ARG1_NAME		__a_testName
#define CINTERNAL_UNIT_TEST_FN_ARG2_NAME		__a_subtestName

#ifndef CPPUTILS_CONDITIONAL_WEAKNESS
#define CPPUTILS_CONDITIONAL_WEAKNESS		CPPUTILS_ONLY_GCCLIKE_ATTR_STRONG
#endif

typedef void (*TypeFunction)(const char* a_maj, const char* a_min);

// one can overrwrite below 2 functions
CPPUTILS_CONDITIONAL_WEAKNESS void CinternalAddUnitTestFunction(TypeFunction a_function, const char* a_maj, const char* a_min);
CPPUTILS_CONDITIONAL_WEAKNESS void CinternalIterateAndCallUnitTestFunctions(void);


#ifndef CPPUTILS_UNIT_TEST_NOEXCEPT
#define CPPUTILS_UNIT_TEST_NOEXCEPT CPPUTILS_NOEXCEPT
#endif

#define CINTERNAL_UNIT_TEST_IGNORE_ARGS()	CPPUTILS_STATIC_CAST(void,CINTERNAL_UNIT_TEST_FN_ARG1_NAME);CPPUTILS_STATIC_CAST(void,CINTERNAL_UNIT_TEST_FN_ARG2_NAME)

#define CPPUTILS_UTEST_BEFORE_MAIN(_maj,_min)	\
	static void cinternal_unit_test_bm_raw_ ## _maj ## _min (const char* a_maj, const char* a_min);	\
	CPPUTILS_CODE_INITIALIZER(cinternal_unit_test_bm_ ## _maj ## _min){								\
		cinternal_unit_test_bm_raw_ ## _maj ## _min (# _maj, # _min);								\
	}																								\
	static void cinternal_unit_test_bm_raw_ ## _maj ## _min (const char* CINTERNAL_UNIT_TEST_FN_ARG1_NAME, const char* CINTERNAL_UNIT_TEST_FN_ARG2_NAME)

#define CPPUTILS_UTEST_AFTER_MAIN(_maj,_min)	\
	static void cinternal_unit_test_raw_ ## _maj ## _min (const char* a_maj, const char* a_min) CPPUTILS_UNIT_TEST_NOEXCEPT;	\
	CPPUTILS_CODE_INITIALIZER(cinternal_unit_test_adder_ ## _maj ## _min){														\
		CinternalAddUnitTestFunction(& cinternal_unit_test_raw_ ## _maj ## _min,# _maj, # _min);								\
	}																															\
	static void cinternal_unit_test_raw_ ## _maj ## _min (const char* CINTERNAL_UNIT_TEST_FN_ARG1_NAME, const char* CINTERNAL_UNIT_TEST_FN_ARG2_NAME) CPPUTILS_UNIT_TEST_NOEXCEPT


#define CPPUTILS_UTEST_ALL(_maj,_min)	\
	static void cinternal_unit_test_raw_ ## _maj ## _min (const char* a_maj, const char* a_min) CPPUTILS_UNIT_TEST_NOEXCEPT;	\
	CPPUTILS_CODE_INITIALIZER(cinternal_unit_test_adder_ ## _maj ## _min){														\
		CinternalAddUnitTestFunction(& cinternal_unit_test_raw_ ## _maj ## _min,# _maj, # _min);								\
		cinternal_unit_test_raw_ ## _maj ## _min (# _maj, # _min);																\
	}																															\
	static void cinternal_unit_test_raw_ ## _maj ## _min (const char* CINTERNAL_UNIT_TEST_FN_ARG1_NAME, const char* CINTERNAL_UNIT_TEST_FN_ARG2_NAME) CPPUTILS_UNIT_TEST_NOEXCEPT 


CPPUTILS_END_C


#define CinternalUnitTestCheckTst(_condition)	CinternalUnitTestCheckRaw(_condition,CINTERNAL_UNIT_TEST_FN_ARG1_NAME,CINTERNAL_UNIT_TEST_FN_ARG2_NAME,"",-1)
#define CinternalUnitTestCheckAll(_condition)	CinternalUnitTestCheckRaw(_condition,CINTERNAL_UNIT_TEST_FN_ARG1_NAME,CINTERNAL_UNIT_TEST_FN_ARG2_NAME,__FILE__,__LINE__)

#define CinternalUnitTestAssertCheckTst(_condition)	CinternalUnitTestAssertCheckRaw(_condition,CINTERNAL_UNIT_TEST_FN_ARG1_NAME,CINTERNAL_UNIT_TEST_FN_ARG2_NAME,"",-1)
#define CinternalUnitTestAssertCheckAll(_condition)	CinternalUnitTestAssertCheckRaw(_condition,CINTERNAL_UNIT_TEST_FN_ARG1_NAME,CINTERNAL_UNIT_TEST_FN_ARG2_NAME,__FILE__,__LINE__)

#define CinternalUnitTestCheckOpt CinternalUnitTestCheckTst
#define CinternalUnitTestAssertCheckOpt CinternalUnitTestAssertCheckTst


#ifdef CINTERNAL_UNIT_TEST_USE_GTEST_LIKE_MACROSES
#define TEST						CPPUTILS_UTEST_AFTER_MAIN
#define EXPECT_EQ(_left,_right)		CinternalUnitTestCheckTst(((_left)==(_right)))
#define ASSERT_EQ(_left,_right)		CinternalUnitTestAssertCheckTst(((_left)==(_right)))
#define ASSERT_FALSE(_condition)	CinternalUnitTestAssertCheckTst((!(_condition)))
#define ASSERT_TRUE					CinternalUnitTestAssertCheckTst
#endif


#endif  // #ifndef CUTILS_INCLUDE_CUTILS_UNIT_TEST_H
