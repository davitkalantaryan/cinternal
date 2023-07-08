//
// file:            disable_compiler_warnings.h
// path:			include/cinternal/disable_compiler_warnings.h
// created on:		2021 Nov 15
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H
#define CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H

#include <cinternal/internal_header.h>

#ifdef CPPUTILS_COMPILER_WARNINGS_PUSH_POP
CPPUTILS_WARNINGS_PUSH
#endif


#if defined(_MSC_VER)

#pragma warning(disable: 4191)
#pragma warning(disable:4710)
#pragma warning(disable:4711)
#pragma warning(disable:4668)
#pragma warning(disable:4820)
#pragma warning(disable:5039) // 'TpSetCallbackCleanupGroup': pointer or reference to potentially throwing function
#pragma warning (disable:4061) // enumerator 'MonAppHiderEventNone' in switch of enum
#pragma warning (disable:4365)
#ifndef __cplusplus
#pragma warning(disable:4255)
#endif
#if (_MSC_VER>=1929) && (_MSC_FULL_VER>192930100)
#pragma warning(disable:5246)
#endif

#elif defined(CPPUTILS_GCC_FAMILY) 

#pragma GCC diagnostic ignored "-Wattributes"

#endif


#ifdef CPPUTILS_COMPILER_WARNINGS_PUSH_POP
#define CINTERNAL_COMPILER_WARNINGS_DISABLED	1
#endif


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H
