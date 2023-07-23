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


CPPUTILS_BEGIN_C



int main(void)
{
	CinternalIterateAndCallUnitTestFunctions();
	return ( 0);
}


#ifndef CinternalAddUnitTestFunction_defined
void CinternalAddUnitTestFunction_alternate(TypeFunction a_function)
{
	CPPUTILS_STATIC_CAST(void,a_function);
}
#endif


#ifndef CinternalIterateAndCallUnitTestFunctions_defined
void CinternalIterateAndCallUnitTestFunctions_alternate(void)
{
	//
}
#endif


#ifdef __clang__

#ifndef CinternalAddUnitTestFunction_defined
CPPUTILS_ONLY_CLANG_ATTR_WEAK void CinternalAddUnitTestFunction(TypeFunction a_function) {
    CinternalAddUnitTestFunction_alternate(a_function);
}
#endif


#ifndef CinternalIterateAndCallUnitTestFunctions_defined
CPPUTILS_ONLY_CLANG_ATTR_WEAK void CinternalIterateAndCallUnitTestFunctions(void) {
    CinternalIterateAndCallUnitTestFunctions_alternate();
}
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
