//
// file:            main_c_global_initer_test.c
// path:			src/tests/main_c_global_initer_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/internal_header.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdio.h>
#include <assert.h>
#include <cinternal/undisable_compiler_warnings.h>

#define CINTERNALS_GLB_CONS_DSGN_VAL	1

static int s_nData = 0;

CPPUTILS_BEGIN_C

CPPUTILS_C_CODE_INITIALIZER(code_init) {

    printf("Hello from C global constructor\n");
	s_nData = CINTERNALS_GLB_CONS_DSGN_VAL;
}

CPPUTILS_END_C

int main(void)
{
	printf("s_nData = %d\n", s_nData);
	assert(s_nData == CINTERNALS_GLB_CONS_DSGN_VAL);
	return 0;
}
