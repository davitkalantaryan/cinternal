//
// repo:            cinternal
// file:			cinternal_unit_test_0008_typeinfo.c
// path:			src/tests/unit_test/cinternal_unit_test_0008_typeinfo.c
// created on:		2024 Dec 21
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test.h>
#include <cinternal/typeinfo.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdint.h>
#include <cinternal/undisable_compiler_warnings.h>


#define TestEnumMacro           \
    EnumNamefield1,             \
    EnumNamefield2 = 5

#define TestStructMacro \
    (int,structField1),    \
    (int,structField2),     \
    (int64_t,structField3)
    


CPPUTILS_UTEST_AFTER_MAIN(f_0008_typeinfo, t_0001_names_static) {
    const CinternalConstCharPtr enumNames[] = { CPPUTILS_ENUM_LIKE_DATA_NAMES(TestEnumMacro) };
    const size_t cunEnumNamesSize = sizeof(enumNames) / sizeof(CinternalConstCharPtr);
    const CinternalConstCharPtr structNames[] = { CPPUTILS_STRUCT_LIKE_DATA_NAMES(TestStructMacro) };
    const size_t cunStructNamesSize = sizeof(structNames) / sizeof(CinternalConstCharPtr);

    CinternalUnitTestCheckOpt(cunEnumNamesSize==2);
    CinternalUnitTestCheckOpt(cunStructNamesSize == 3);
}
