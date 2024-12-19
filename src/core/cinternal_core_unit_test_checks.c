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
#include <cinternal/disable_compiler_warnings.h>
#include <stdlib.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C


#define CINTERNAL_GAP_IN_PRINT	60
CINTERNAL_EXPORT bool	g_bHasFailedTest = false;


static inline void PrintTestPositionInline(enum CinternalLogCategory a_type, const char* a_cpcSrcPath, int a_line, const char* a_testName, const char* a_subtestName) CPPUTILS_NOEXCEPT {
	size_t i, unCharacters;
    unsigned int logFlags = CinternalLogEnumToInt(CinternalLogTypeTime);

    CinternalLoggerSetCurrentLogLevel(2);

	if (a_cpcSrcPath[0]) {
        logFlags |= CinternalLogEnumToInt(CinternalLogTypeFile);
	}
	if (a_line >= 0) {
        logFlags |= CinternalLogEnumToInt(CinternalLogTypeLine);
	}

    CinternalLoggerMakeLog(0, "", a_cpcSrcPath, a_line, "", CinternalLogIntToEnum(logFlags), a_type, "");

	if (a_testName[0]) {
        CinternalLoggerMakeLogOnlyText(0,"test:\"%s\" ", a_testName);
	}
	if (a_subtestName[0]) {
        CinternalLoggerMakeLogOnlyText(0, "subtest:\"%s\" ", a_subtestName);
	}

    unCharacters = CinternalLoggerGetLogSize();

	if (unCharacters < CINTERNAL_GAP_IN_PRINT) {
        unCharacters = CINTERNAL_GAP_IN_PRINT - unCharacters;
	}
	else {
        unCharacters = 1;
	}
	for (i = 0; i < unCharacters; ++i) {
        CinternalLoggerMakeLogOnlyText(0, " ");
	}

    //CinternalLoggerMakeLog(0, "", a_cpcSrcPath, a_line, "", CinternalLogTypeFinalize, a_type, "");
}


static inline int CinternalUnitTestCheckRawFnInline(
	bool a_condition, const char* a_cpcCondition, 
	const char* a_testName, const char* a_subtestName,
	const char* a_cpcSrcPath, int a_line,
	bool a_bExit) CPPUTILS_NOEXCEPT
{
	if (a_condition) {
		PrintTestPositionInline(CinternalLogCategoryInfo, a_cpcSrcPath, a_line,a_testName, a_subtestName);
        CinternalLoggerMakeLog(0, "", a_cpcSrcPath, a_line, "", CinternalLogEnumConcat(CinternalLogTypeFinalize, CinternalLogTypeMainText), CinternalLogCategoryInfo, "OK (%s)", a_cpcCondition);
		return 0;
	}

	PrintTestPositionInline(CinternalLogCategoryError, a_cpcSrcPath, a_line, a_testName, a_subtestName);
    CinternalLoggerMakeLog(0, "", a_cpcSrcPath, a_line, "", CinternalLogEnumConcat(CinternalLogTypeFinalize, CinternalLogTypeMainText), CinternalLogCategoryError, "FAILURE (%s)", a_cpcCondition);
	g_bHasFailedTest = true;
	if (a_bExit) {
		exit(1);
	}
	return 1;
}


CINTERNAL_EXPORT int CinternalUnitTestCheckRawFn(bool a_condition, const char* a_cpcCondition, const char* a_testName, const char* a_subtestName, const char* a_cpcSrcPath, int a_line) CPPUTILS_NOEXCEPT
{
	return CinternalUnitTestCheckRawFnInline(a_condition, a_cpcCondition, a_testName, a_subtestName, a_cpcSrcPath, a_line, false);
}


CINTERNAL_EXPORT void CinternalUnitTestAssertCheckRawFn(bool a_condition, const char* a_cpcCondition, const char* a_testName, const char* a_subtestName, const char* a_cpcSrcPath, int a_line) CPPUTILS_NOEXCEPT
{
	CinternalUnitTestCheckRawFnInline(a_condition, a_cpcCondition, a_testName, a_subtestName, a_cpcSrcPath, a_line, true);
}


CPPUTILS_END_C
