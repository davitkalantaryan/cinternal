//
// file:            cinternal_core_intern_tokenizer02_common.c
// path:			src/intern/cinternal_core_intern_tokenizer02_common.c
// created on:		2023 Mar 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <private/cinternal/parser/tokenizer02_common_p.h>
#include <cinternal/parser/tokenizer01.h>
#include <cinternal/freelib_on_remote_process.h>


CPPUTILS_BEGIN_C


static int CinternalTokenizerForWindowsDllUnload02a(void* a_clbkData, const char* a_cpcNextString)
{
	const int pid = (int)((size_t)a_clbkData);
	return CInternalFreeLibOnRemoteProcessByName(pid, a_cpcNextString)?0:-2;
}


CPPUTILS_DLL_PRIVATE int CInternalTokenizer02b(char* CPPUTILS_ARG_NONULL a_pcBuffer, int a_pid)
{
	return CInternalTokenizer01a(a_pcBuffer, ';', &CinternalTokenizerForWindowsDllUnload02a, (void*)((size_t)a_pid));
}


CPPUTILS_END_C
