//
// repo:			cinternal
// file:			cinternal_core_unit_test_tools_and_main.c
// path:			src/core/cinternal_core_unit_test_tools_and_main.c
// created on:		2023 May 18
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/internal_header.h>
#define CPPUTILS_CONDITIONAL_WEAKNESS		CPPUTILS_ONLY_GCCLIKE_ATTR_WEAK

#include <cinternal/unit_test.h>
#define FileNameFromPossiblePathInline_needed
#include <cinternal/fs.h>
#include <cinternal/logger.h>
#include <stdlib.h>


CPPUTILS_BEGIN_C


struct SFunctionsToCall {
	struct SFunctionsToCall *prev, *next;
	TypeFunction			func;
};


static struct SFunctionsToCall* s_pFirst = CPPUTILS_NULL;


CPPUTILS_ONLY_GCCLIKE_ATTR_WEAK int CPPUTILS_WEAK_SYMBOL_NAME(main)(void)
{
	CinternalIterateAndCallUnitTestFunctions();
	return ( 0);
}
CPPUTILS_WEAK_SYMBOL(main)


CPPUTILS_ONLY_GCCLIKE_ATTR_WEAK void CPPUTILS_WEAK_SYMBOL_NAME(CinternalAddUnitTestFunction)(TypeFunction a_function)
{
	struct SFunctionsToCall* pNextFn = (struct SFunctionsToCall*)malloc(sizeof(struct SFunctionsToCall));
	if (pNextFn) {
		pNextFn->prev = CPPUTILS_NULL;
		pNextFn->next = s_pFirst;
		pNextFn->func = a_function;
		if (s_pFirst) {
			s_pFirst->prev = pNextFn;
		}
		s_pFirst = pNextFn;
	}
}
CPPUTILS_WEAK_SYMBOL(CinternalAddUnitTestFunction)


CPPUTILS_ONLY_GCCLIKE_ATTR_WEAK void CPPUTILS_WEAK_SYMBOL_NAME(CinternalIterateAndCallUnitTestFunctions)(void)
{
	struct SFunctionsToCall* pFnNext, * pFn = s_pFirst;
	while (pFn) {
		pFnNext = pFn->next;
		(*(pFn->func))();
		free(pFn);
		pFn = pFnNext;
	}
}
CPPUTILS_WEAK_SYMBOL(CinternalIterateAndCallUnitTestFunctions)


static inline void PrintSourceInformationInline(enum CinternalLogTypes a_type, const char* a_cpcSrcPath, int a_line) {
	if (a_cpcSrcPath[0]) {
		const char* cpcReturn = FileNameFromPossiblePathInline(a_cpcSrcPath);
		CinternalMakeLogNoExtraData(a_type,false, "src_fl: \"%s\" ", cpcReturn);
	}
	if (a_line >= 0) {
		CinternalMakeLogNoExtraData(a_type, false, "src_ln: %d ", a_line);
	}
}

#define CINTERNAL_GAP_IN_PRINT	80


static inline void PrintConditionOfTestInline(enum CinternalLogTypes a_type, const char* a_cpcCondition) {
	int i,nCharacters = CinternalMakeLogNoExtraData(a_type, false, "%s", a_cpcCondition);
	if (nCharacters < CINTERNAL_GAP_IN_PRINT) {
		nCharacters = CINTERNAL_GAP_IN_PRINT - nCharacters;
	}
	else {
		nCharacters = 1;
	}
	for (i = 0; i < nCharacters; ++i) {
		CinternalMakeLogNoExtraData(a_type, false, " ");
	}
}


static inline int CinternalUnitTestCheckRawFnInline(
	bool a_condition, const char* a_cpcCondition, 
	const char* a_testName, int a_subtestNumber, 
	const char* a_cpcSrcPath, int a_line,
	bool a_bExit)
{
	if (a_condition) {
		switch (a_subtestNumber) {
		case CUTILS_UNIT_TEST_SPECIAL_SUBTEST_NUMBER:
			a_testName = FileNameFromPossiblePathInline(a_cpcSrcPath);
			a_subtestNumber = a_line;
			break;
		default:
			PrintSourceInformationInline(CinternalLogTypeInfo, a_cpcSrcPath, a_line);
			break;
		}  //  switch (a_subtestNumber) {
		PrintConditionOfTestInline(CinternalLogTypeInfo, a_cpcCondition);
		CinternalMakeLogNoExtraData(CinternalLogTypeInfo, true, "OK      => test: \"%s\", subTestNumber: %d\n", a_testName, a_subtestNumber);
		return 0;
	}

	switch (a_subtestNumber) {
	case CUTILS_UNIT_TEST_SPECIAL_SUBTEST_NUMBER:
		a_testName = FileNameFromPossiblePathInline(a_cpcSrcPath);
		a_subtestNumber = a_line;
		break;
	default:
		PrintSourceInformationInline(CinternalLogTypeError, a_cpcSrcPath, a_line);
		break;
	}  //  switch (a_subtestNumber) {
	PrintConditionOfTestInline(CinternalLogTypeError, a_cpcCondition);
	CinternalMakeLogNoExtraData(CinternalLogTypeError, true, "FAILURE => test: \"%s\", subTestNumber: %d is ok\n", a_testName, a_subtestNumber);
	if (a_bExit) {
		exit(1);
	}
	return 1;
}


CINTERNAL_EXPORT int CinternalUnitTestCheckRawFn(bool a_condition, const char* a_cpcCondition, const char* a_testName, int a_subtestNumber, const char* a_cpcSrcPath, int a_line)
{
	return CinternalUnitTestCheckRawFnInline(a_condition, a_cpcCondition, a_testName, a_subtestNumber, a_cpcSrcPath, a_line, false);
}


CINTERNAL_EXPORT void CinternalUnitTestAssertCheckRawFn(bool a_condition, const char* a_cpcCondition, const char* a_testName, int a_subtestNumber, const char* a_cpcSrcPath, int a_line)
{
	CinternalUnitTestCheckRawFnInline(a_condition, a_cpcCondition, a_testName, a_subtestNumber, a_cpcSrcPath, a_line, true);
}


CPPUTILS_END_C
