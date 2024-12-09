//
// file:            disable_compiler_warnings.h
// path:			include/cinternal/disable_compiler_warnings.h
// created on:		2021 Nov 15
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H
#define CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H

#include <cinternal/internal_header.h>


#ifndef CPPUTILS_COMPILER_WARNINGS_PUSHED
CPPUTILS_WARNINGS_PUSH
#define CPPUTILS_COMPILER_WARNINGS_PUSHED
#endif


#if defined(_MSC_VER)

#pragma warning( push, 3 )
#pragma warning(disable:5031)  //  #pragma warning(pop): likely mismatch, popping warning state pushed in different file
#pragma warning (disable:4061)  // enumerator 'MonAppHiderEventNone' in switch of enum
#pragma warning (disable:4820)  // enumerator 'MonAppHiderEventNone' in switch of enum
#pragma warning (disable:4355)  // 'this': used in base member initializer list
#pragma warning(disable: 4191)
#pragma warning(disable:4710)
#pragma warning(disable:4711)
#pragma warning(disable:4668)
#pragma warning(disable:4820)
#pragma warning(disable:5039) // 'TpSetCallbackCleanupGroup': pointer or reference to potentially throwing function
#pragma warning (disable:4365)
#pragma warning (disable:4574)  //  winnt.h(1229,1): warning C4574: '__has_builtin' is defined to be '0': did you mean to use '#if __has_builtin'?
#pragma warning (disable:4365)  //  mstcpip.h(1110,26): warning C4365: 'initializing': conversion from 'int' to 'UINT8',
#pragma warning (disable:4514)  //  mstcpip.h(757,1): warning C4514: 'IN4_IS_UNALIGNED_ADDR_LINKLOCAL': unreferenced inline function has been removed
#ifndef __cplusplus
#pragma warning(disable:4255)
#endif
#if (_MSC_VER>=1929) && (_MSC_FULL_VER>192930100)
#pragma warning(disable:5246)
#endif

#elif defined(CPPUTILS_GCC_FAMILY) 

#pragma GCC diagnostic ignored "-Wattributes"

#endif  //  #if defined(_MSC_VER)


#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H
