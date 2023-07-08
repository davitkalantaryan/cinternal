//
// repo:			cinternal
// file:            undisable_compiler_warnings.h
// path:			include/cinternal/undisable_compiler_warnings.h
// created on:		2023 Jul 07
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_UNDISABLE_COMPILER_WARNINGS_H
#define CINTERNAL_INCLUDE_CINTERNAL_UNDISABLE_COMPILER_WARNINGS_H
#include <cinternal/internal_header.h>
#endif

#if defined(_MSC_VER)
#pragma warning(disable:5031)  //  #pragma warning(pop): likely mismatch, popping warning state pushed in different file
#endif

#ifdef CINTERNAL_COMPILER_WARNINGS_DISABLED
CPPUTILS_WARNINGS_POP
//#undef CINTERNAL_COMPILER_WARNINGS_DISABLED
#endif


// disable some warnings, those are assumed as errors
#if defined(_MSC_VER)

#ifndef CPPUTILS_DO_NOT_IGNORE_MISSING_SWITCH_CASE
#pragma warning (disable:4061)
#endif

#elif defined(CPPUTILS_GCC_FAMILY) 

#ifdef CPPUTILS_IGNORE_GCC_ATTRIBUTES
#pragma GCC diagnostic ignored "-Wattributes"
#endif

#endif
