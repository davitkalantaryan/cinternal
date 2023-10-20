//
// repo:			cinternal
// file:			cinternal_core_unit_test_checks.c
// path:			src/core/cinternal_core_unit_test_checks.c
// created on:		2023 May 18
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test_only_checks.h>
#define FileNameFromPossiblePathInline_needed
#include <cinternal/fs.h>
#include <cinternal/logger.h>
#include <stdlib.h>


CPPUTILS_BEGIN_C


#define CINTERNAL_GAP_IN_PRINT	60
CINTERNAL_EXPORT bool	g_bHasFailedTest = false;

static inline void PrintTestPositionInline(enum CinternalLogTypes a_type, const char* a_cpcSrcPath, int a_line, const char* a_testName, const char* a_subtestName) {
	int i, nCharacters = 0;

	if (a_cpcSrcPath[0]) {
		const char* cpcReturn = FileNameFromPossiblePathInline(a_cpcSrcPath);
		nCharacters = CinternalMakeLogNoExtraData(a_type, false, "src_fl:\"%s\" ", cpcReturn);
	}
	if (a_line >= 0) {
		nCharacters += CinternalMakeLogNoExtraData(a_type, false, "src_ln:%d ", a_line);
	}
	if (a_testName[0]) {
		nCharacters += CinternalMakeLogNoExtraData(a_type, false, "test:\"%s\" ", a_testName);
	}
	if (a_subtestName[0]) {
		nCharacters += CinternalMakeLogNoExtraData(a_type, false, "subtest:\"%s\" ", a_subtestName);
	}

	if (nCharacters < CINTERNAL_GAP_IN_PRINT) {
		nCharacters = CINTERNAL_GAP_IN_PRINT - nCharacters;
	}
	else {
		nCharacters = 1;
	}
	for (i = 0; i < nCharacters; ++i) {
		CinternalMakeLogNoExtraData(a_type, false, " ");
	}

	CinternalMakeLogNoExtraData(a_type, false, "=> ");
}


static inline int CinternalUnitTestCheckRawFnInline(
	bool a_condition, const char* a_cpcCondition, 
	const char* a_testName, const char* a_subtestName,
	const char* a_cpcSrcPath, int a_line,
	bool a_bExit)
{
	if (a_condition) {
		PrintTestPositionInline(CinternalLogTypeInfo, a_cpcSrcPath, a_line,a_testName, a_subtestName);
		CinternalMakeLogNoExtraData(CinternalLogTypeInfo, true, "OK (%s)\n", a_cpcCondition);
		return 0;
	}

	PrintTestPositionInline(CinternalLogTypeError, a_cpcSrcPath, a_line, a_testName, a_subtestName);
	CinternalMakeLogNoExtraData(CinternalLogTypeError, true, "FAILURE (%s)\n", a_cpcCondition);
	g_bHasFailedTest = true;
	if (a_bExit) {
		exit(1);
	}
	return 1;
}


CINTERNAL_EXPORT int CinternalUnitTestCheckRawFn(bool a_condition, const char* a_cpcCondition, const char* a_testName, const char* a_subtestName, const char* a_cpcSrcPath, int a_line)
{
	return CinternalUnitTestCheckRawFnInline(a_condition, a_cpcCondition, a_testName, a_subtestName, a_cpcSrcPath, a_line, false);
}


CINTERNAL_EXPORT void CinternalUnitTestAssertCheckRawFn(bool a_condition, const char* a_cpcCondition, const char* a_testName, const char* a_subtestName, const char* a_cpcSrcPath, int a_line)
{
	CinternalUnitTestCheckRawFnInline(a_condition, a_cpcCondition, a_testName, a_subtestName, a_cpcSrcPath, a_line, true);
}


CPPUTILS_END_C
