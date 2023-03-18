//
// file:            cinternal_core_intern_tokenizer01_common.c
// path:			src/intern/cinternal_core_intern_tokenizer01_common.c
// created on:		2023 Mar 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <private/cinternal/parser/tokenizer01_common_p.h>
#include <cinternal/parser/tokenizer01.h>
#include <cinternal/load_lib_on_remote_process.h>
#include <stddef.h>


CPPUTILS_BEGIN_C


static int CinternalTokenizerForDllInject01b(void* a_clbkData, const char* a_cpcNextString)
{
	const int pid = (int)((size_t)a_clbkData);
	return CInternalLoadLibOnRemoteProcess(pid, a_cpcNextString)?0:-2;
}


CPPUTILS_DLL_PRIVATE int CInternalTokenizer01b(char* CPPUTILS_ARG_NONULL a_pcBuffer, int a_pid)
{
	return CInternalTokenizer01a(a_pcBuffer, ';', &CinternalTokenizerForDllInject01b,(void*)((size_t)a_pid));
}



CPPUTILS_END_C
