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
#include <stdlib.h>
#include <stdio.h>


CPPUTILS_BEGIN_C


struct SFunctionsToCall {
	struct SFunctionsToCall *prev, *next;
	TypeFunction			func;
};


static struct SFunctionsToCall* s_pFirst = CPPUTILS_NULL;


int main(void)
{
	CinternalIterateAndCallUnitTestFunctions();
	return ( 0);
}


void CinternalAddUnitTestFunction_alternate(TypeFunction a_function)
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


void CinternalIterateAndCallUnitTestFunctions_alternate(void)
{
	struct SFunctionsToCall* pFnNext, * pFn = s_pFirst;
	while (pFn) {
		pFnNext = pFn->next;
		(*(pFn->func))();
		free(pFn);
		pFn = pFnNext;
	}
}


#ifdef __clang__

//CPPUTILS_ONLY_CLANG_ATTR_WEAK void CinternalAddUnitTestFunction(TypeFunction a_function) {
//    CinternalAddUnitTestFunction_alternate(a_function);
//}
//
//
//CPPUTILS_ONLY_CLANG_ATTR_WEAK void CinternalIterateAndCallUnitTestFunctions(void) {
//    CinternalIterateAndCallUnitTestFunctions_alternate();
//}

void CinternalAddUnitTestFunction(TypeFunction a_function) {
	CinternalAddUnitTestFunction_alternate(a_function);
}
#pragma weak CinternalAddUnitTestFunction


void CinternalIterateAndCallUnitTestFunctions(void) {
	CinternalIterateAndCallUnitTestFunctions_alternate();
}
#pragma weak CinternalIterateAndCallUnitTestFunctions


#else   //  #ifdef __clang__

CPPUTILS_WEAK_SYMBOL_ALIAS(CinternalAddUnitTestFunction, CinternalAddUnitTestFunction_alternate)
CPPUTILS_WEAK_SYMBOL_ALIAS(CinternalIterateAndCallUnitTestFunctions, CinternalIterateAndCallUnitTestFunctions_alternate)

#endif  //  #ifdef __clang__


static inline void PrintSourceInformationInline(FILE* a_file, const char* a_cpcSrcPath, int a_line) {
	if (a_cpcSrcPath[0]) {
		const char* cpcReturn = FileNameFromPossiblePathInline(a_cpcSrcPath);
		fprintf(a_file, "src_fl: \"%s\" ", cpcReturn);
	}
	if (a_line >= 0) {
		fprintf(a_file, "src_ln: %d ", a_line);
	}
}


CINTERNAL_EXPORT int CinternalUnitTestCheckRawFn(bool a_condition, const char* a_testName, int a_subtestNumber, const char* a_cpcSrcPath, int a_line)
{
	if (a_condition) {
		switch (a_subtestNumber) {
		case CUTILS_UNIT_TEST_SPECIAL_SUBTEST_NUMBER:
			a_testName = FileNameFromPossiblePathInline(a_cpcSrcPath);
			a_subtestNumber = a_line;
			break;
		default:
			PrintSourceInformationInline(stdout, a_cpcSrcPath, a_line);
			break;
		}  //  switch (a_subtestNumber) {
		fprintf(stdout, "OK      => test: \"%s\", subTestNumber: %d\n", a_testName, a_subtestNumber);
		fflush(stdout);
		return 0;
	}

	switch (a_subtestNumber) {
	case CUTILS_UNIT_TEST_SPECIAL_SUBTEST_NUMBER:
		a_testName = FileNameFromPossiblePathInline(a_cpcSrcPath);
		a_subtestNumber = a_line;
		break;
	default:
		PrintSourceInformationInline(stderr, a_cpcSrcPath, a_line);
		break;
	}  //  switch (a_subtestNumber) {
	fprintf(stderr, "FAILURE => test: \"%s\", subTestNumber: %d is ok\n", a_testName, a_subtestNumber);
	fflush(stderr);
	return 1;
}


CINTERNAL_EXPORT void CinternalUnitTestAssertCheckRawFn(bool a_condition, const char* a_testName, int a_subtestNumber, const char* a_cpcSrcPath, int a_line)
{
	if (a_condition) {
		switch (a_subtestNumber) {
		case CUTILS_UNIT_TEST_SPECIAL_SUBTEST_NUMBER:
			a_testName = FileNameFromPossiblePathInline(a_cpcSrcPath);
			a_subtestNumber = a_line;
			break;
		default:
			PrintSourceInformationInline(stdout, a_cpcSrcPath, a_line);
			break;
		}  //  switch (a_subtestNumber) {
		fprintf(stdout, "OK      => test: \"%s\", subTestNumber: %d\n", a_testName, a_subtestNumber);
		fflush(stdout);
		return;
	}

	switch (a_subtestNumber) {
	case CUTILS_UNIT_TEST_SPECIAL_SUBTEST_NUMBER:
		a_testName = FileNameFromPossiblePathInline(a_cpcSrcPath);
		a_subtestNumber = a_line;
		break;
	default:
		PrintSourceInformationInline(stderr, a_cpcSrcPath, a_line);
		break;
	}  //  switch (a_subtestNumber) {
	fprintf(stderr, "FAILURE => test: \"%s\", subTestNumber: %d is ok\n", a_testName, a_subtestNumber);
	fflush(stderr);
	exit(1);
}


CPPUTILS_END_C
