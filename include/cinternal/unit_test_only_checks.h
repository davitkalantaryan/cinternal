//
// repo:			cinternal
// file:            unit_test_only_checks.h
// path:			include/cinternal/unit_test_only_checks.h
// created on:		2023 Apr 15
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CUTILS_INCLUDE_CUTILS_UNIT_TEST_ONLY_CHECKS_H
#define CUTILS_INCLUDE_CUTILS_UNIT_TEST_ONLY_CHECKS_H

#include <cinternal/export_symbols.h>
#include <stdbool.h>


CPPUTILS_BEGIN_C


CINTERNAL_EXPORT int  CinternalUnitTestCheckRawFn(bool a_condition, const char* a_cpcCondition, const char* a_testName, const char* a_subtestName, const char* a_cpcSrcPath, int a_line);
CINTERNAL_EXPORT void CinternalUnitTestAssertCheckRawFn(bool a_condition, const char* a_cpcCondition, const char* a_testName, const char* a_subtestName, const char* a_cpcSrcPath, int a_line);

#define CinternalUnitTestCheckRaw(_condition,_testName,_subtestName,_cpcSrcPath,_line)	\
			CinternalUnitTestCheckRawFn((_condition)?true:false,#_condition,_testName,_subtestName,_cpcSrcPath,_line)
#define CinternalUnitTestCheckSrc(_condition)	CinternalUnitTestCheckRaw(_condition,"","",__FILE__,__LINE__)
#define CinternalUnitTestAssertCheckRaw(_condition,_testName,_subtestName,_cpcSrcPath,_line)	\
			CinternalUnitTestAssertCheckRawFn((_condition)?true:false,#_condition,_testName,_subtestName,_cpcSrcPath,_line)
#define CinternalUnitTestAssertCheckSrc(_condition)	CinternalUnitTestAssertCheckRaw(_condition,"","",__FILE__,__LINE__)


extern CINTERNAL_EXPORT bool	g_bHasFailedTest;

CPPUTILS_END_C



#endif  // #ifndef CUTILS_INCLUDE_CUTILS_UNIT_TEST_ONLY_CHECKS_H
