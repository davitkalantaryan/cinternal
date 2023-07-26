//
// repo:            cinternal
// file:			cinternal_unit_test_0004_threading.c
// path:			src/tests/unit_test/cinternal_unit_test_0004_threading.c
// created on:		2023 Jul 24
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test.h>
#include <cinternal/threading.h>
#include <stddef.h>

#define CINTERNAL_THREAD_RET_CODE     ((cinternal_thread_ret_t)0)

static cinternal_thread_ret_t CPPUTILS_THR_CALL ThreadFunction(void* a_pArg);


CPPUTILS_UTEST_AFTER_MAIN(f_0004_threading, t_0001) {

    cinternal_thread_ret_t retCode;
    cinternal_thread_t aThread;
    CinternalUnitTestAssertCheckAll(cinternal_thread_create(&aThread, &ThreadFunction,CPPUTILS_NULL)==0);
    cinternal_thread_wait_and_clean(&aThread,&retCode);
    CinternalUnitTestAssertCheckAll(retCode== CINTERNAL_THREAD_RET_CODE);

    // now detaching
    CinternalUnitTestAssertCheckAll(cinternal_thread_create(&aThread, &ThreadFunction, CPPUTILS_NULL) == 0);
    cinternal_thread_detach(&aThread);

#ifdef _WIN32  //  #ifdef _WIN32
    
    {
        DWORD dwId;
        CinternalUnitTestAssertCheckAll(cinternal_thread_create(&aThread, &ThreadFunction, CPPUTILS_NULL) == 0);
        dwId = cinternal_thread_thread_id(aThread);
        cinternal_thread_detach(&aThread);
        CinternalUnitTestAssertCheckAll(cinternal_thread_attach(&aThread, dwId)==0);
        cinternal_thread_wait(aThread);
        cinternal_thread_get_exit_code(aThread ,&retCode);
        cinternal_thread_destroy(&aThread);
        CinternalUnitTestAssertCheckAll(retCode == CINTERNAL_THREAD_RET_CODE);
    }

#endif

}


static cinternal_thread_ret_t CPPUTILS_THR_CALL ThreadFunction(void* a_pArg)
{
    CPPUTILS_STATIC_CAST(void, a_pArg);
    cinternal_thread_exit_thread(CINTERNAL_THREAD_RET_CODE);
}
