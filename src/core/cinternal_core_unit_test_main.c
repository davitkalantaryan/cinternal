//
// repo:			cinternal
// file:			cinternal_core_unit_test_main.c
// path:			src/core/cinternal_core_unit_test_main.c
// created on:		2023 May 18
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test_tools.h>


CPPUTILS_BEGIN_C


static void CallCinternalIterateAndCallUnitTestFunctions(void);

int main(void)
{
	//CinternalIterateAndCallUnitTestFunctions();
    CallCinternalIterateAndCallUnitTestFunctions();
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
#ifdef CPPUTILS_FNAME_PREFIX_HAS_UNDERLINE

#define HAS_ACTIVE_CALL
extern CPPUTILS_DLL_PRIVATE void CinternalAddUnitTestFunction(TypeFunction a_function) __attribute__((weak_import));
extern CPPUTILS_DLL_PRIVATE void CinternalIterateAndCallUnitTestFunctions(void) __attribute__((weak_import));

//#pragma clang attribute push ([[weak]], _CinternalAddUnitTestFunction = CinternalAddUnitTestFunction_alternate)
//#pragma weak _CinternalAddUnitTestFunction=CinternalAddUnitTestFunction_alternate
//#pragma weak _CinternalIterateAndCallUnitTestFunctions=CinternalIterateAndCallUnitTestFunctions_alternate
//CPPUTILS_DLL_PRIVATE void CinternalAddUnitTestFunction(TypeFunction a_function) __attribute__((weak, alias("CinternalAddUnitTestFunction_alternate")));
//CPPUTILS_DLL_PRIVATE void CinternalIterateAndCallUnitTestFunctions(void) __attribute__((weak, alias("CinternalIterateAndCallUnitTestFunctions_alternate")));
#else
#pragma weak CinternalAddUnitTestFunction=CinternalAddUnitTestFunction_alternate
#pragma weak CinternalIterateAndCallUnitTestFunctions=CinternalIterateAndCallUnitTestFunctions_alternate
#endif
#endif


CPPUTILS_DLL_PRIVATE void CallCinternalAddUnitTestFunction(TypeFunction a_function) {
#ifdef HAS_ACTIVE_CALL
    if (CinternalAddUnitTestFunction) {
        CinternalAddUnitTestFunction(a_function);
    }
    else {
        CinternalAddUnitTestFunction_alternate(a_function);
    }
#else
    CinternalAddUnitTestFunction(a_function);
#endif
}


static void CallCinternalIterateAndCallUnitTestFunctions(void) {
#ifdef HAS_ACTIVE_CALL
    if (CinternalIterateAndCallUnitTestFunctions) {
        CinternalIterateAndCallUnitTestFunctions();
    }
    else {
        CinternalIterateAndCallUnitTestFunctions_alternate();
    }
#else
    CinternalIterateAndCallUnitTestFunctions();
#endif
}


CPPUTILS_END_C
