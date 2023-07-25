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
#include <stdbool.h>

#define CUTILS_UNIT_TEST_SPECIAL_SUBTEST_NUMBER		(-11)

CPPUTILS_BEGIN_C

#ifndef CPPUTILS_CONDITIONAL_WEAKNESS
#define CPPUTILS_CONDITIONAL_WEAKNESS		CPPUTILS_ONLY_GCCLIKE_ATTR_STRONG
#endif

typedef void (*TypeFunction)(void);

// if you need to have tests after main called, then overrwrite below 2 functions
CPPUTILS_CONDITIONAL_WEAKNESS void CinternalAddUnitTestFunction(TypeFunction a_function);
CPPUTILS_CONDITIONAL_WEAKNESS void CinternalIterateAndCallUnitTestFunctions(void);

CINTERNAL_EXPORT int  CinternalUnitTestCheckRawFn(bool a_condition, const char* a_cpcCondition, const char* a_testName, int a_subtestNumber, const char* a_cpcSrcPath, int a_line);
CINTERNAL_EXPORT void CinternalUnitTestAssertCheckRawFn(bool a_condition, const char* a_cpcCondition, const char* a_testName, int a_subtestNumber, const char* a_cpcSrcPath, int a_line);

#ifndef CPPUTILS_UNIT_TEST_NOEXCEPT
#define CPPUTILS_UNIT_TEST_NOEXCEPT CPPUTILS_NOEXCEPT
#endif

#define CPPUTILS_UTEST_BEFORE_MAIN(_maj,_min)	CPPUTILS_CODE_INITIALIZER(cinternal_unit_test_bm_ ## _maj ## _min)

#define CPPUTILS_UTEST_AFTER_MAIN(_maj,_min)	static void cinternal_unit_test_ ## _maj ## _min (void) CPPUTILS_UNIT_TEST_NOEXCEPT;	\
	CPPUTILS_CODE_INITIALIZER(cinternal_unit_test_adder_ ## _maj ## _min){						\
		CinternalAddUnitTestFunction(& cinternal_unit_test_ ## _maj ## _min);					\
	}																							\
	static void cinternal_unit_test_ ## _maj ## _min (void) CPPUTILS_UNIT_TEST_NOEXCEPT


#define CPPUTILS_UTEST_ALL(_maj,_min)	static void cinternal_unit_test_ ## _maj ## _min (void) CPPUTILS_UNIT_TEST_NOEXCEPT;\
	CPPUTILS_CODE_INITIALIZER(cinternal_unit_test_adder_ ## _maj ## _min){						\
		CinternalAddUnitTestFunction(& cinternal_unit_test_ ## _maj ## _min);					\
		cinternal_unit_test_ ## _maj ## _min ();												\
	}																							\
	static void cinternal_unit_test_ ## _maj ## _min (void) CPPUTILS_UNIT_TEST_NOEXCEPT 


CPPUTILS_END_C


#define CinternalUnitTestCheckRaw(_condition,_testName,_subtestNumber,_cpcSrcPath,_line)	\
			CinternalUnitTestCheckRawFn((_condition)?true:false,#_condition,_testName,_subtestNumber,_cpcSrcPath,_line)
#define CinternalUnitTestCheck(_condition)	CinternalUnitTestCheckRaw(_condition,"",CUTILS_UNIT_TEST_SPECIAL_SUBTEST_NUMBER,__FILE__,__LINE__)
#define CinternalUnitTestAssertCheckRaw(_condition,_testName,_subtestNumber,_cpcSrcPath,_line)	\
			CinternalUnitTestAssertCheckRawFn((_condition)?true:false,#_condition,_testName,_subtestNumber,_cpcSrcPath,_line)
#define CinternalUnitTestAssertCheck(_condition)	CinternalUnitTestAssertCheckRaw(_condition,"",CUTILS_UNIT_TEST_SPECIAL_SUBTEST_NUMBER,__FILE__,__LINE__)

#ifdef CINTERNAL_UNIT_TEST_USE_GTEST_LIKE_MACROSES
#define TEST						CPPUTILS_UTEST_AFTER_MAIN
#define EXPECT_EQ(_left,_right)		CinternalUnitTestCheck(((_left)==(_right)))
#define ASSERT_EQ(_left,_right)		CinternalUnitTestAssertCheck(((_left)==(_right)))
#define ASSERT_FALSE(_condition)	CinternalUnitTestAssertCheck((!(_condition)))
#define ASSERT_TRUE					CinternalUnitTestAssertCheck
#endif


#endif  // #ifndef CUTILS_INCLUDE_CUTILS_UNIT_TEST_H
