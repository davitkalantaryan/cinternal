//
// repo:			cinternal
// file:            undisable_compiler_warnings.h
// path:			include/cinternal/undisable_compiler_warnings.h
// created on:		2023 Jul 07
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifdef CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H
#undef CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H

#ifdef _MSC_VER
#ifdef CPPUTILS_COMPILER_WARNINGS_PUSHED_2
#pragma warning( pop )
#undef CPPUTILS_COMPILER_WARNINGS_PUSHED_2
#endif
#endif

#ifdef CPPUTILS_COMPILER_WARNINGS_PUSHED
CPPUTILS_WARNINGS_POP
#undef CPPUTILS_COMPILER_WARNINGS_PUSHED
#endif


#endif  //  #ifdef CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H
