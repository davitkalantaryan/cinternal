//
// repo:			cinternal
// file:			typeinfo.h
// path:			include/cinternal/typeinfo.h
// created on:		2021 Apr 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_TYPEINFO_H
#define CINTERNAL_INCLUDE_CINTERNAL_TYPEINFO_H

#include <cinternal/internal_header.h>
#include <cinternal/macroses.h>

#define CPPUTILS_VAR_MACRO_FOR_TYPE(_x)     CPPUTILS_ID(_x)

#define CPPUTILS_TYPE_NAMES_MCR(...)  CPPUTILS_VAR_MACRO_APPY_COMMA(CPPUTILS_MACRO_NAME,__VA_ARGS__)

#define CPPUTILS_COMMA_TYPE_MEMBER_MCR_NM(_type,_name,...)  \
    CPPUTILS_ID(_type) CPPUTILS_ID(_name) {  \
        CPPUTILS_VAR_MACRO_APPY_COMMA(CPPUTILS_VAR_MACRO_FOR_TYPE,__VA_ARGS__)  \
    }

#define CPPUTILS_COMMA_TYPE_MEMBER_MCR(_type,...)  \
    CPPUTILS_ID(_type) {  \
        CPPUTILS_VAR_MACRO_APPY_COMMA(CPPUTILS_VAR_MACRO_FOR_TYPE,__VA_ARGS__)  \
    }


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_TYPEINFO_H
