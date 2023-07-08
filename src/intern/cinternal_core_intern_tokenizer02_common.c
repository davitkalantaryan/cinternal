//
// file:            cinternal_core_intern_tokenizer02_common.c
// path:			src/intern/cinternal_core_intern_tokenizer02_common.c
// created on:		2023 Mar 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <private/cinternal/parser/tokenizer02_common_p.h>
#include <cinternal/parser/tokenizer01.h>
#include <cinternal/loadfreelib_on_remote_process.h>
#include <stdio.h>


CPPUTILS_BEGIN_C


static int CinternalTokenizerForWindowsDllUnload02a(void* a_clbkData, const char* a_cpcNextString) CPPUTILS_NOEXCEPT
{
	const int pid = (int)((size_t)a_clbkData);
    if(CInternalFreeLibOnRemoteProcessByName(pid, a_cpcNextString)){
        return 0;
    }
    fprintf(stderr,"Library with the name \"%s\" is not possible to unload from the process with the pid %d\n",a_cpcNextString,pid);
    return -2;
}


CPPUTILS_DLL_PRIVATE int CInternalTokenizer02b(char* CPPUTILS_ARG_NONULL a_pcBuffer, int a_pid)
{
	return CInternalTokenizer01a(a_pcBuffer, ';', &CinternalTokenizerForWindowsDllUnload02a, (void*)((size_t)a_pid));
}


CPPUTILS_END_C
