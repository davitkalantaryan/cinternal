//
// repo:			cinternal
// file:			cinternal_core_unit_test_main.c
// path:			src/core/cinternal_core_unit_test_main.c
// created on:		2023 May 18
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/internal_header.h>
#define CPPUTILS_UNIT_TEST_WEAKNESS		CPPUTILS_ONLY_CLANG_ATTR_WEAK

#include <cinternal/unit_test_tools.h>
#include <stdlib.h>


CPPUTILS_BEGIN_C


#if (!defined(CinternalAddUnitTestFunction_defined)) || (!defined(CinternalIterateAndCallUnitTestFunctions_defined))

struct SFunctionsToCall {
	struct SFunctionsToCall *prev, *next;
	TypeFunction			func;
};


static struct SFunctionsToCall* s_pFirst = CPPUTILS_NULL;

#endif



int main(void)
{
	CinternalIterateAndCallUnitTestFunctions();
	return ( 0);
}


#ifndef CinternalAddUnitTestFunction_defined
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
#endif


#ifndef CinternalIterateAndCallUnitTestFunctions_defined
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
#endif


#ifdef __clang__

//#ifndef CinternalAddUnitTestFunction_defined
//CPPUTILS_ONLY_CLANG_ATTR_WEAK void CinternalAddUnitTestFunction(TypeFunction a_function) {
//    CinternalAddUnitTestFunction_alternate(a_function);
//}
//#endif
//
//
//#ifndef CinternalIterateAndCallUnitTestFunctions_defined
//CPPUTILS_ONLY_CLANG_ATTR_WEAK void CinternalIterateAndCallUnitTestFunctions(void) {
//    CinternalIterateAndCallUnitTestFunctions_alternate();
//}
//#endif

#ifndef CinternalAddUnitTestFunction_defined
void CinternalAddUnitTestFunction(TypeFunction a_function) {
	CinternalAddUnitTestFunction_alternate(a_function);
}
#pragma weak CinternalAddUnitTestFunction
#endif


#ifndef CinternalIterateAndCallUnitTestFunctions_defined
void CinternalIterateAndCallUnitTestFunctions(void) {
	CinternalIterateAndCallUnitTestFunctions_alternate();
}
#pragma weak CinternalIterateAndCallUnitTestFunctions
#endif


#else   //  #ifndef _MSC_VER

#ifndef CinternalAddUnitTestFunction_defined
CPPUTILS_WEAK_SYMBOL_ALIAS(CinternalAddUnitTestFunction, CinternalAddUnitTestFunction_alternate)
#endif
#ifndef CinternalIterateAndCallUnitTestFunctions_defined
CPPUTILS_WEAK_SYMBOL_ALIAS(CinternalIterateAndCallUnitTestFunctions, CinternalIterateAndCallUnitTestFunctions_alternate)
#endif


#endif  //  #ifndef _MSC_VER


CPPUTILS_END_C
