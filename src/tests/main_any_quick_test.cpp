//
// file:            main_any_quick_test.c
// path:			src/tests/main_any_quick_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/hash.h>
#include <cinternal/logger.h>
#include <cinternal/bistateflags.h>
#include <cinternal/fourstateflags.h>
#include <cinternal/unit_test_only_checks.h>
#include <cinternal/typeinfo.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdlib.h>
#include <stdio.h>
#include <cinternal/undisable_compiler_warnings.h>

typedef const char* ConstCharPtr;

#define CPPUTILS_VAR_MACRO_FOR_ENUM(_x)     CPPUTILS_ID(_x)

#define TEST_ENUM_MCR(_name,...)  \
    enum {  \
        CPPUTILS_VAR_MACRO_APPY_COMMA(CPPUTILS_VAR_MACRO_FOR_ENUM,__VA_ARGS__)  \
    }

#define TEST_ENUM_NAMES_MCR(...)  CPPUTILS_VAR_MACRO_APPY_COMMA(CPPUTILS_MACRO_NAME,__VA_ARGS__) 


#define TEST_ENUM_FIELDS_MCR    \
    EnumNamefield1,             \
    EnumNamefield2 = 5

#define TestStruct \
    (int,field1)    \
    (int,field2)


TEST_ENUM_MCR(EnumName,TEST_ENUM_FIELDS_MCR);

#define _MyMacro0(type, name) CPPUTILS_ID(type) CPPUTILS_ID(name)
#define MyMacro0(_expr) _MyMacro0 CPPUTILS_ID(_expr)

#define _MyMacro1(type, name) name
#define MyMacro1(_expr) _MyMacro1 _expr

#define _MyMacro2(type, name) offsetof(CPPUTILS_ID(type),CPPUTILS_ID(name))
#define MyMacro2(_expr) _MyMacro2 _expr

#define TestStructMacro(_name,...)  \
    struct CPPUTILS_ID(_name) { \
        CPPUTILS_VAR_MACRO_APPY_OP(MyMacro0,;,__VA_ARGS__)  \
    }

//#define CPPUTILS_VAR_MACRO_HELPER01(_x1,_x2,_op)            CPPUTILS_ID(_x1) CPPUTILS_ID(_op) CPPUTILS_ID(_x2)
//#define CPPUTILS_VAR_MACRO_APPY_OP(_macro01,_op, ...)       CPPUTILS_VAR_MACRO_APPY_GEN(CPPUTILS_ID(_macro01),CPPUTILS_VAR_MACRO_HELPER01,_op,__VA_ARGS__)
//
//#define CPPUTILS_VAR_MACRO_HELPER02(_x1,_x2,_op)            CPPUTILS_ID(_x1) , CPPUTILS_ID(_x2)
//#define CPPUTILS_VAR_MACRO_APPY_COMMA(_macro01, ...)        CPPUTILS_VAR_MACRO_APPY_GEN(CPPUTILS_ID(_macro01),CPPUTILS_VAR_MACRO_HELPER02, _macro01,__VA_ARGS__)

//#define CPPUTILS_VAR_MACRO_HELPER02(_x1,_x2,_op)            CPPUTILS_ID(_x1) , CPPUTILS_ID(_x2)

#define CPPUTILS_VAR_MACRO_HELPER04(_x1,_x2,_macro)            CPPUTILS_ID(_x1) , CPPUTILS_ID(_x2)
#define CPPUTILS_VAR_MACRO_APPY_TEST(_macro01, ...)        CPPUTILS_VAR_MACRO_APPY_GEN(CPPUTILS_ID(_macro01),CPPUTILS_VAR_MACRO_HELPER02, _macro01,__VA_ARGS__)

//TestStructMacro(StructName, TestStruct);

int main(void)
{
    size_t i;
    //int field1 = 5;
    const ConstCharPtr enumNames[] = { TEST_ENUM_NAMES_MCR(TEST_ENUM_FIELDS_MCR)};
    const size_t cunNamesSize = sizeof(enumNames) / sizeof(ConstCharPtr);

    CPPUTILS_BISTATE_FLAGS_UN(field1, field2) aFlags;
    CPPUTILS_BISTATE_FLAGS_UN(field1, field2) aFlags4St;

    CInternalLogCritical("1");
    CInternalLogError("%d",2);
    CInternalLogWarning("%d", 3);
    CInternalLogInfo("%d", 4);
    CInternalLogDebug("%d", 5);

    aFlags.wr_all = CPPUTILS_BISTATE_MAKE_ALL_BITS_FALSE;
    CInternalLogDebug("field1_true=%d, field2_true=%d", (int)aFlags.rd.field1_true, (int)aFlags.rd.field2_true);
    aFlags.wr.field1 = CPPUTILS_BISTATE_MAKE_BITS_TRUE;
    CInternalLogDebug("field1_true=%d, field2_true=%d", (int)aFlags.rd.field1_true, (int)aFlags.rd.field2_true);

    aFlags4St.wr_all = CPPUTILS_FOURSTATE_MAKE_ALL_BITS_FALSE;
    CInternalLogDebug("field1_true=%d, field2_true=%d", (int)aFlags4St.rd.field1_true, (int)aFlags4St.rd.field2_true);
    aFlags4St.wr.field1 = CPPUTILS_FOURSTATE_MAKE_BITS_ONGOING_FT;
    CInternalLogDebug("field1_true=%d, field2_true=%d", (int)aFlags4St.rd.field1_true, (int)aFlags4St.rd.field2_true);

    CInternalLogDebug("SOME_ENUM1=%d, SOME_ENUM2=%d, cunNamesSize=%d", (int)EnumNamefield1, (int)EnumNamefield2,(int)cunNamesSize);

    for (i = 0; i < cunNamesSize; ++i) {
        CInternalLogDebug("%d => %s", (int)i, enumNames[i]);
    }

    //CInternalLogDebug("%d", MyMacro((int,field1)));

	return 0;
}
