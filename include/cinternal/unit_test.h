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

#define CPPUTILS_UTEST_BEFORE_MAIN(_maj,_min)	\
	static void cinternal_unit_test_bm_ ## _maj ## _min _raw(const char* a_maj, const char* a_min);	\
	CPPUTILS_CODE_INITIALIZER(cinternal_unit_test_bm_ ## _maj ## _min){								\
		cinternal_unit_test_bm_ ## _maj ## _min _raw(# _maj, # _min);								\
	}																								\
	static void cinternal_unit_test_bm_ ## _maj ## _min _raw(const char* CINTERNAL_UNIT_TEST_FN_ARG1_NAME, const char* CINTERNAL_UNIT_TEST_FN_ARG2_NAME)

#define CPPUTILS_UTEST_AFTER_MAIN(_maj,_min)	\
	static void cinternal_unit_test_ ## _maj ## _min _raw (const char* a_maj, const char* a_min) CPPUTILS_UNIT_TEST_NOEXCEPT;	\
	CPPUTILS_CODE_INITIALIZER(cinternal_unit_test_adder_ ## _maj ## _min){														\
		CinternalAddUnitTestFunction(& cinternal_unit_test_ ## _maj ## _min _raw,# _maj, # _min);								\
	}																															\
	static void cinternal_unit_test_ ## _maj ## _min _raw (const char* CINTERNAL_UNIT_TEST_FN_ARG1_NAME, const char* CINTERNAL_UNIT_TEST_FN_ARG2_NAME) CPPUTILS_UNIT_TEST_NOEXCEPT


#define CPPUTILS_UTEST_ALL(_maj,_min)	\
	static void cinternal_unit_test_ ## _maj ## _min _raw (const char* a_maj, const char* a_min) CPPUTILS_UNIT_TEST_NOEXCEPT;	\
	CPPUTILS_CODE_INITIALIZER(cinternal_unit_test_adder_ ## _maj ## _min){														\
		CinternalAddUnitTestFunction(& cinternal_unit_test_ ## _maj ## _min _raw,# _maj, # _min);								\
		cinternal_unit_test_ ## _maj ## _min _raw(# _maj, # _min);																\
	}																															\
	static void cinternal_unit_test_ ## _maj ## _min _raw (const char* CINTERNAL_UNIT_TEST_FN_ARG1_NAME, const char* CINTERNAL_UNIT_TEST_FN_ARG2_NAME) CPPUTILS_UNIT_TEST_NOEXCEPT 


CPPUTILS_END_C


#ifdef CINTERNAL_UNIT_TEST_USE_GTEST_LIKE_MACROSES
#define TEST						CPPUTILS_UTEST_AFTER_MAIN
#define EXPECT_EQ(_left,_right)		CinternalUnitTestCheckTst(((_left)==(_right)))
#define ASSERT_EQ(_left,_right)		CinternalUnitTestAssertCheckTst(((_left)==(_right)))
#define ASSERT_FALSE(_condition)	CinternalUnitTestAssertCheckTst((!(_condition)))
#define ASSERT_TRUE					CinternalUnitTestAssertCheckTst
#endif


#endif  // #ifndef CUTILS_INCLUDE_CUTILS_UNIT_TEST_H
