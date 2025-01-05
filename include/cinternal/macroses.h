//
// repo:			cinternal
// file:			macroses.h
// path:			include/cinternal/macroses.h
// created on:		2021 Apr 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_MACROSES_H
#define CINTERNAL_INCLUDE_CINTERNAL_MACROSES_H

#include <cinternal/internal_header.h>
#include <cinternal/macroses_variadic.h>


#define CPPUTILS_ALL_NAMES(...)			CPPUTILS_VAR_MACRO_APPY_COMMA(CPPUTILS_MACRO_NAME,__VA_ARGS__)


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_MACROSES_H
