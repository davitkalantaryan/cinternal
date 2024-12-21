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

//#define _MyMacro(type, name) name
//#define MyMacro(_expr) _MyMacro _expr
//
//
//#define CPPUTILS_STR_TEST(_type,_token)     CPPUTILS_ID(_type) CPPUTILS_ID(_token)
//#define testMacro2(_type_and_token)         CPPUTILS_ID(_type_and_token)
//#define testMacro3(...)                     CPPUTILS_VAR_MACRO_APPY_OP(testMacro2,;,__VA_ARGS__)


CPPUTILS_BEGIN_C


typedef const char* CinternalConstCharPtr;
struct CInternalTypeinfoEnumNames;
struct CInternalTypeinfoStructNames;

CINTERNAL_EXPORT struct CInternalTypeinfoEnumNames* CInternalTypeinfoCreateEnumNames(int a_number, ...) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT struct CInternalTypeinfoStructNames* CInternalTypeinfoCreateStructNames(int a_number, ...) CPPUTILS_NOEXCEPT;


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_TYPEINFO_H
