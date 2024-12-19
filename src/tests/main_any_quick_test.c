//
// file:            main_any_quick_test.c
// path:			src/tests/main_any_quick_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/hash.h>
#include <cinternal/logger.h>
#include <cinternal/unit_test_only_checks.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdlib.h>
#include <stdio.h>
#include <cinternal/undisable_compiler_warnings.h>



int main(void)
{
    CInternalLogCritical("1");
    CInternalLogError("%d",2);
    CInternalLogWarning("%d", 3);
    CInternalLogInfo("%d", 4);
    CInternalLogDebug("%d", 5);

	return 0;
}
