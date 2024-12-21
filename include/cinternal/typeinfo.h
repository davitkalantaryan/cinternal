//
// repo:			cinternal
// file:			typeinfo.h
// path:			include/cinternal/typeinfo.h
// created on:		2021 Apr 11
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_TYPEINFO_H
#define CINTERNAL_INCLUDE_CINTERNAL_TYPEINFO_H

#include <cinternal/export_symbols.h>
#include <cinternal/macroses.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stddef.h>
#include <cinternal/undisable_compiler_warnings.h>

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

#define CPPUTILS_ENUM_LIKE_DATA_NAMES(...)                  CPPUTILS_VAR_MACRO_APPY_COMMA(CPPUTILS_MACRO_NAME,__VA_ARGS__)


#define CPPUTILS_DEFINE_VARIABLE_HEPLER(_type,_name)        _type _name
#define CPPUTILS_DEFINE_VARIABLE(_expr)                     CPPUTILS_DEFINE_VARIABLE_HEPLER CPPUTILS_ID(_expr)

#define CPPUTILS_VARIABLE_NAME_HEPLER(_type,_name)          CPPUTILS_ID(_name)
#define CPPUTILS_VARIABLE_NAME(_expr)                       CPPUTILS_VARIABLE_NAME_HEPLER CPPUTILS_ID(_expr)
#define CPPUTILS_VARIABLE_NAME_STR_HEPLER(_type,_name)      #_name
#define CPPUTILS_VARIABLE_NAME_STR(_expr)                   CPPUTILS_VARIABLE_NAME_STR_HEPLER CPPUTILS_ID(_expr)

#define CPPUTILS_VARIABLE_OFFSETOF(_strType,_expr)          ( (size_t)offsetof(CPPUTILS_ID(_strType),CPPUTILS_VARIABLE_NAME(_expr)) )

#define CPPUTILS_SEMICOLON_TYPE_MEMBER_MCR_NM(_type,_name,...)  \
    CPPUTILS_ID(_type) CPPUTILS_ID(_name) {  \
        CPPUTILS_VAR_MACRO_APPY_OP(CPPUTILS_DEFINE_VARIABLE,;,__VA_ARGS__);  \
    }

#define CPPUTILS_SEMICOLON_TYPE_MEMBER_MCR(_type,...)  \
    CPPUTILS_ID(_type) {  \
        CPPUTILS_VAR_MACRO_APPY_OP(CPPUTILS_DEFINE_VARIABLE,;,__VA_ARGS__);  \
    }

#define CPPUTILS_STRUCT_LIKE_DATA_NAMES(...)                  CPPUTILS_VAR_MACRO_APPY_COMMA(CPPUTILS_VARIABLE_NAME_STR,__VA_ARGS__)



CPPUTILS_BEGIN_C


typedef const char* CinternalConstCharPtr;
struct CInternalTypeinfoEnumNames;
struct CInternalTypeinfoStructNames;

CINTERNAL_EXPORT struct CInternalTypeinfoEnumNames* CInternalTypeinfoCreateEnumNames(int a_number, ...) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT struct CInternalTypeinfoStructNames* CInternalTypeinfoCreateStructNames(int a_number, ...) CPPUTILS_NOEXCEPT;


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_TYPEINFO_H