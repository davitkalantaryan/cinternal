//
// repo:			cinternal
// file:			cinternal_core_unit_test_main.c
// path:			src/core/cinternal_core_unit_test_main.c
// created on:		2023 May 18
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test_tools.h>


CPPUTILS_BEGIN_C


#ifdef _MSC_VER
#pragma comment(linker, "/alternatename:" CPPUTILS_FNAME_PREFIX "CinternalAddUnitTestFunction=" CPPUTILS_FNAME_PREFIX "CinternalAddUnitTestFunction_alternate")
#pragma comment(linker, "/alternatename:" CPPUTILS_FNAME_PREFIX "CinternalIterateAndCallUnitTestFunctions=" CPPUTILS_FNAME_PREFIX "CinternalIterateAndCallUnitTestFunctions_alternate")
#else
#pragma weak CPPUTILS_FNAME_PREFIX_NO_STR(CinternalAddUnitTestFunction)=CPPUTILS_FNAME_PREFIX_NO_STR(CinternalAddUnitTestFunction_alternate)
#pragma weak CPPUTILS_FNAME_PREFIX_NO_STR(CinternalIterateAndCallUnitTestFunctions)=CPPUTILS_FNAME_PREFIX_NO_STR(CinternalIterateAndCallUnitTestFunctions_alternate)
#endif


int main(void)
{
	CinternalIterateAndCallUnitTestFunctions();
	return 0;
}


CPPUTILS_EXTERN_C CPPUTILS_DLL_PRIVATE void CinternalAddUnitTestFunction_alternate(TypeFunction a_function)
{
	CPPUTILS_STATIC_CAST(void,a_function);
}


CPPUTILS_DLL_PRIVATE void CinternalIterateAndCallUnitTestFunctions_alternate(void)
{
	//
}


CPPUTILS_END_C
