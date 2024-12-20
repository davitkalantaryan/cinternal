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
#include <cinternal/disable_compiler_warnings.h>
#include <stdlib.h>
#include <stdio.h>
#include <cinternal/undisable_compiler_warnings.h>



int main(void)
{
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

	return 0;
}
