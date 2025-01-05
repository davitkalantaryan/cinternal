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


#define TEST_ENUM_FIELDS_MCR    \
    EnumNamefield1,             \
    EnumNamefield2 = 5

#define TestStruct \
    (int,structField1),    \
    (int,structField2)


CPPUTILS_COMMA_TYPE_MEMBER_MCR_NM(enum,EnumName,TEST_ENUM_FIELDS_MCR);
CPPUTILS_SEMICOLON_TYPE_MEMBER_MCR_NM(struct,StructName, TestStruct);

CPPUTILS_FOURSTATE_FLAGS_UN_NM(
    FourstateFlags,
    loggedIn, clockedIn, inBreak, inIdle);

int main(void)
{
    size_t i;
    const ConstCharPtr enumNames[] = { CPPUTILS_ENUM_LIKE_DATA_NAMES(TEST_ENUM_FIELDS_MCR)};
    const size_t cunEnumNamesSize = sizeof(enumNames) / sizeof(ConstCharPtr);
    const ConstCharPtr structNames[] = { CPPUTILS_STRUCT_LIKE_DATA_NAMES(TestStruct) };
    const size_t cunStructNamesSize = sizeof(structNames) / sizeof(ConstCharPtr);

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

    CInternalLogDebug("SOME_ENUM1=%d, SOME_ENUM2=%d, cunEnumNamesSize=%d", (int)EnumNamefield1, (int)EnumNamefield2,(int)cunEnumNamesSize);
    for (i = 0; i < cunEnumNamesSize; ++i) {
        CInternalLogDebug("%d => %s", (int)i, enumNames[i]);
    }

    CInternalLogDebug("cunStructNamesSize=%d", (int)cunStructNamesSize);
    for (i = 0; i < cunStructNamesSize; ++i) {
        CInternalLogDebug("%d => %s", (int)i, structNames[i]);
    }

    //CInternalLogDebug("%d", MyMacro((int,field1)));

	return 0;
}
