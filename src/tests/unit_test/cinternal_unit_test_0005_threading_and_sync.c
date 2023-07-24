//
// repo:            cinternal
// file:			cinternal_unit_test_0005_threading_and_sync.c
// path:			src/tests/unit_test/cinternal_unit_test_0005_threading_and_sync.c
// created on:		2023 Jul 24
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test_tools.h>
#include <cinternal/unit_test.h>
#include <cinternal/threading.h>
#include <cinternal/sync_barrier.h>
#define cinternal_unnamed_sema_wait_ms_needed
#include <cinternal/unnamed_semaphore.h>
#include <stddef.h>

#define CINTERNAL_THREAD_RET_CODE     ((cinternal_thread_ret_t)0)

static cinternal_thread_ret_t CPPUTILS_THR_CALL ThreadFunctionBarier(void* a_pArg);
static cinternal_thread_ret_t CPPUTILS_THR_CALL ThreadFunctionSema(void* a_pArg);
static int s_nBarierReturns = 0;


CPPUTILS_UTEST_AFTER_MAIN(f_0005_threading_and_sync, t_0001_barier) {

    int nRet;
    cinternal_thread_ret_t retCode;
    cinternal_thread_t aThread;
    cinternal_sync_barrier_t aBarrier;
    
    CinternalUnitTestAssertCheck(cinternal_sync_barrier_create(&aBarrier,2)==0);
    CinternalUnitTestAssertCheck(cinternal_thread_create(&aThread, &ThreadFunctionBarier, &aBarrier) == 0);
    nRet = cinternal_sync_barrier_wait(&aBarrier);
    if (nRet) {
        s_nBarierReturns += nRet;
    }
    cinternal_thread_wait_and_clean(&aThread,&retCode);
    CinternalUnitTestAssertCheck(retCode== CINTERNAL_THREAD_RET_CODE);
    CinternalUnitTestAssertCheck(s_nBarierReturns == 1);

}


CPPUTILS_UTEST_AFTER_MAIN(f_0005_threading_and_sync, t_0002_sema) {

    cinternal_thread_ret_t retCode;
    cinternal_thread_t aThread;
    cinternal_unnamed_sema_t aSema;

    CinternalUnitTestAssertCheck(cinternal_unnamed_sema_create(&aSema,0) == 0);
    CinternalUnitTestAssertCheck(cinternal_thread_create(&aThread, &ThreadFunctionSema, &aSema) == 0);
    cinternal_unnamed_sema_wait(&aSema);
    cinternal_thread_wait_and_clean(&aThread, &retCode);
    CinternalUnitTestAssertCheck(retCode == CINTERNAL_THREAD_RET_CODE);
}


static cinternal_thread_ret_t CPPUTILS_THR_CALL ThreadFunctionBarier(void* a_pArg)
{
    cinternal_sync_barrier_t* const pBarrier = (cinternal_sync_barrier_t*)a_pArg;
    const int nRet = cinternal_sync_barrier_wait(pBarrier);
    if (nRet) {
        s_nBarierReturns += nRet;
    }
    cinternal_thread_exit_thread(CINTERNAL_THREAD_RET_CODE);
}


static cinternal_thread_ret_t CPPUTILS_THR_CALL ThreadFunctionSema(void* a_pArg)
{
    cinternal_unnamed_sema_t* const pSema = (cinternal_unnamed_sema_t*)a_pArg;
    cinternal_unnamed_sema_post(pSema);
    cinternal_thread_exit_thread(CINTERNAL_THREAD_RET_CODE);
}
