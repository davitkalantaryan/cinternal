//
// repo:			cinternal
// file:			macroses_base.h
// path:			include/cinternal/macroses_base.h
// created on:		2021 Apr 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_MACROSES_BASE_H
#define CINTERNAL_INCLUDE_CINTERNAL_MACROSES_BASE_H

#include <cinternal/internal_header.h>

#define CPPUTILS_ID(_x)							_x
#define CPPUTILS_MACRO_APPLY_IMPL(_macro, ...)	CPPUTILS_ID(_macro(__VA_ARGS__))
#define CPPUTILS_CAT_IMPL(_a, _b)				_a ## _b
#define CPPUTILS_CAT(_a, _b)					CPPUTILS_CAT_IMPL(_a, _b)
#define CPPUTILS_MACRO_NAME(_arg)			    #_arg



#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_MACROSES_BASE_H
