//
// repo:			cinternal
// file:			cinternal_core_unit_test_main.c
// path:			src/core/cinternal_core_unit_test_main.c
// created on:		2023 May 18
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test_tools.h>


CPPUTILS_BEGIN_C



int main(void)
{
	CinternalIterateAndCallUnitTestFunctions();
	return 0;
}


CPPUTILS_DLL_PRIVATE void CinternalAddUnitTestFunction_alternate(TypeFunction a_function)
{
	CPPUTILS_STATIC_CAST(void,a_function);
}


CPPUTILS_DLL_PRIVATE void CinternalIterateAndCallUnitTestFunctions_alternate(void)
{
	//
}


#ifdef _MSC_VER
#pragma comment(linker, "/alternatename:" CPPUTILS_FNAME_PREFIX "CinternalAddUnitTestFunction=" CPPUTILS_FNAME_PREFIX "CinternalAddUnitTestFunction_alternate")
#pragma comment(linker, "/alternatename:" CPPUTILS_FNAME_PREFIX "CinternalIterateAndCallUnitTestFunctions=" CPPUTILS_FNAME_PREFIX "CinternalIterateAndCallUnitTestFunctions_alternate")
#else

#ifdef __clang__


CPPUTILS_DLL_PRIVATE void CinternalAddUnitTestFunction(TypeFunction a_function) __attribute__((weak)) {
    CinternalAddUnitTestFunction_alternate(a_function);
}


CPPUTILS_DLL_PRIVATE void CinternalIterateAndCallUnitTestFunctions(void) __attribute__((weak)) {
    CinternalIterateAndCallUnitTestFunctions_alternate();
}

#else   //  #ifdef __clang__
#pragma weak CinternalAddUnitTestFunction=CinternalAddUnitTestFunction_alternate
#pragma weak CinternalIterateAndCallUnitTestFunctions=CinternalIterateAndCallUnitTestFunctions_alternate
#endif
#endif


CPPUTILS_END_C
