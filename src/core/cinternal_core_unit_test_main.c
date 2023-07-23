//
// repo:			cinternal
// file:			cinternal_core_unit_test_main.c
// path:			src/core/cinternal_core_unit_test_main.c
// created on:		2023 May 18
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/internal_header.h>
#define CPPUTILS_UNIT_TEST_WEAKNESS		CPPUTILS_ONLY_GCCLIKE_ATTR_WEAK

#include <cinternal/unit_test_tools.h>
#include <stdlib.h>


CPPUTILS_BEGIN_C



int main(void)
{
	CinternalIterateAndCallUnitTestFunctions();
	exit( 0);
}


void CinternalAddUnitTestFunction_alternate(TypeFunction a_function)
{
	CPPUTILS_STATIC_CAST(void,a_function);
}


void CinternalIterateAndCallUnitTestFunctions_alternate(void)
{
	//
}


#ifndef _MSC_VER


CPPUTILS_ONLY_GCCLIKE_ATTR_WEAK void CinternalAddUnitTestFunction(TypeFunction a_function) {
    CinternalAddUnitTestFunction_alternate(a_function);
}


CPPUTILS_ONLY_GCCLIKE_ATTR_WEAK void CinternalIterateAndCallUnitTestFunctions(void) {
    CinternalIterateAndCallUnitTestFunctions_alternate();
}

#else   //  #ifndef _MSC_VER

CPPUTILS_WEAK_SYMBOL_ALIAS(CinternalAddUnitTestFunction, CinternalAddUnitTestFunction_alternate)
CPPUTILS_WEAK_SYMBOL_ALIAS(CinternalIterateAndCallUnitTestFunctions, CinternalIterateAndCallUnitTestFunctions_alternate)


#endif  //  #ifndef _MSC_VER


CPPUTILS_END_C
