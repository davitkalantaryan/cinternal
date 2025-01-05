//
// repo:			cinternal
// file:            disable_compiler_warnings.h
// path:			include/cinternal/disable_compiler_warnings.h
// created on:		2021 Nov 15
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H
#define CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H

#if defined(_MSC_VER)

#ifndef CPPUTILS_WARNINGS_POP
#define CPPUTILS_WARNINGS_POP		__pragma(warning (pop))
#endif

#pragma warning(disable: 4061)  // enumerator 'Bla' in switch of enum 'CinternalLogCategory' is not explicitly handled by a case label
#pragma warning(disable: 4355)  // this will help to keep functions pointers also in the containers
#pragma warning(disable: 4152)  // this will help to keep functions pointers also in the containers
#pragma warning(disable:5039) // 'TpSetCallbackCleanupGroup': pointer or reference to potentially throwing function
#pragma warning(disable:5031)  //  #pragma warning(pop): likely mismatch, popping warning state pushed in different file


#ifndef CPPUTILS_COMPILER_WARNINGS_PUSHED
#pragma warning( push)
#define CPPUTILS_COMPILER_WARNINGS_PUSHED
#endif
#ifndef CPPUTILS_COMPILER_WARNINGS_PUSHED_2
#pragma warning( push, 3 )
#define CPPUTILS_COMPILER_WARNINGS_PUSHED_2
#endif
#pragma warning (disable:4820)  // 'bytes' bytes padding added after construct 'member_name'
#pragma warning(disable: 4191)
#pragma warning(disable:4710)
#pragma warning(disable:4711)
#pragma warning(disable:4668)
#pragma warning(disable:4820)
#pragma warning (disable:4365)
#pragma warning (disable:4574)  //  winnt.h(1229,1): warning C4574: '__has_builtin' is defined to be '0': did you mean to use '#if __has_builtin'?
#pragma warning (disable:4365)  //  mstcpip.h(1110,26): warning C4365: 'initializing': conversion from 'int' to 'UINT8',
#pragma warning (disable:4514)  //  mstcpip.h(757,1): warning C4514: 'IN4_IS_UNALIGNED_ADDR_LINKLOCAL': unreferenced inline function has been removed
#pragma warning (disable:5204)
#ifndef __cplusplus
#pragma warning(disable:4255)
#endif
#if (_MSC_VER>=1929) && (_MSC_FULL_VER>192930100)
#pragma warning(disable:5246)
#endif

#elif defined(__GNUC__) || defined(__clang__) || defined(LINUX_GCC) || defined(__CYGWIN__) || defined(__MINGW64__) || defined(__MINGW32__)

#ifndef CPPUTILS_GCC_FAMILY
#define CPPUTILS_GCC_FAMILY		1
#endif
#ifndef CPPUTILS_WARNINGS_POP
#define CPPUTILS_WARNINGS_POP		_Pragma("GCC diagnostic push")
#endif

#ifndef CPPUTILS_COMPILER_WARNINGS_PUSHED
#pragma GCC diagnostic push
#define CPPUTILS_COMPILER_WARNINGS_PUSHED
#endif
#pragma GCC diagnostic ignored "-Wattributes"

#endif  //  #if defined(_MSC_VER)


#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H
