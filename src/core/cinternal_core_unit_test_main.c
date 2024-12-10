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
#include <cinternal/logger.h>
#include <stdlib.h>


CPPUTILS_BEGIN_C


struct SFunctionsToCall {
	struct SFunctionsToCall *prev, *next;
	TypeFunction			func;
	const char				*maj, *min;
};


static struct SFunctionsToCall* s_pFirst = CPPUTILS_NULL;

CINTERNAL_EXPORT const char* CINTERNAL_UNIT_TEST_FN_ARG1_NAME = "";
CINTERNAL_EXPORT const char* CINTERNAL_UNIT_TEST_FN_ARG2_NAME = "";


CPPUTILS_ONLY_GCCLIKE_ATTR_WEAK int CPPUTILS_WEAK_SYMBOL_NAME(main)(void)
{
	CInternalLogInfo("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	CinternalIterateAndCallUnitTestFunctions();
	return g_bHasFailedTest?1:0;
}
CPPUTILS_WEAK_SYMBOL(main)


CPPUTILS_ONLY_GCCLIKE_ATTR_WEAK void CPPUTILS_WEAK_SYMBOL_NAME(CinternalAddUnitTestFunction)(TypeFunction a_function, const char* a_maj, const char* a_min)
{
	struct SFunctionsToCall* pNextFn = (struct SFunctionsToCall*)malloc(sizeof(struct SFunctionsToCall));
	if (pNextFn) {
		pNextFn->prev = CPPUTILS_NULL;
		pNextFn->next = s_pFirst;
		pNextFn->func = a_function;
		pNextFn->maj = a_maj;
		pNextFn->min = a_min;
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
		CINTERNAL_UNIT_TEST_FN_ARG1_NAME = pFn->maj;
		CINTERNAL_UNIT_TEST_FN_ARG2_NAME = pFn->min;
        (*(pFn->func))(pFn->maj, pFn->min);
		free(pFn);
		pFn = pFnNext;
	}
}
CPPUTILS_WEAK_SYMBOL(CinternalIterateAndCallUnitTestFunctions)


CPPUTILS_END_C
