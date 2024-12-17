//
// repo:            cinternal
// file:			cinternal_core_logger.c
// path:			src/core/cinternal_core_logger.c
// created on:		2023 Mar 30
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cinternal/logger.h>
#include <cinternal/thread_local_sys.h>
#define FileNameFromPossiblePathInline_needed
#include <cinternal/fs.h>
#include <cinternal/rwlock.h>
#include <cinternal/disable_compiler_warnings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C

#define CINTERNALLOGGER_TIME_BUFF_MIN_SIZE_MIN1  (CINTERNALLOGGER_TIME_BUFF_MIN_SIZE  - 1)
#define CINTERNALLOGGER_TLS_BUF_SIZE_MIN1        (0xfffff)
#define CINTERNALLOGGER_TLS_BUF_SIZE             (CINTERNALLOGGER_TLS_BUF_SIZE_MIN1 + 1)

//#ifdef _MSC_VER
//#pragma warning (disable:4061)
//#endif

#ifdef _MSC_VER
#define ctime_s_t(_timep,_buffer,_numberOfElements)     ctime_s(_buffer,_numberOfElements,_timep)
#define snprintf_cint_t(_buffer,_count,...)             _snprintf_s(_buffer,_count,__VA_ARGS__)
#else
#define ctime_s_t(_timep,_buffer,_numberOfElements)     CPPUTILS_STATIC_CAST(void,_numberOfElements);ctime_r(_timep,_buffer)
#define snprintf_cint_t                                 snprintf
#endif


struct CinternalLoggerItemPrivate {
    struct CinternalLoggerItem  publ;
    struct CinternalLoggerItemPrivate *prev, *next;
};


struct SCinternalLoggerData {
    struct CinternalLoggerItemPrivate*  pFirstLogger;
    CInternalRWLock                     rwLock;
    CinternalTlsData                    tlsData;
    int                                 logLevel;
    int                                 filesDeepness;
};


static void CinternalDefaultLoggerFunction(void* a_userData, enum CinternalLogType a_type, enum CinternalLogCategory a_category, const char* a_textToLog) CPPUTILS_NOEXCEPT;


static struct SCinternalLoggerData  s_loggerData;


static inline void CinternalCleanAllLoggersInline(void) CPPUTILS_NOEXCEPT {
    struct CinternalLoggerItemPrivate *pLoggerNext, *pLogger;

    CInternalRWLockWrLock(&(s_loggerData.rwLock));
    pLogger = s_loggerData.pFirstLogger;
    s_loggerData.pFirstLogger = CPPUTILS_NULL;
    CInternalRWLockWrUnlock(&(s_loggerData.rwLock));

    while (pLogger) {
        pLoggerNext = pLogger->next;
        free(pLogger);
        pLogger = pLoggerNext;
    }  //  while (pLogger) {
}


static inline struct CinternalLoggerItem* CinternalLoggerAddLoggerInline(TypeCinternalLogger a_fnc, void* a_userData) CPPUTILS_NOEXCEPT
{
    struct CinternalLoggerItemPrivate* const pRetStr = (struct CinternalLoggerItemPrivate*)calloc(1, sizeof(struct CinternalLoggerItemPrivate));
    if (!pRetStr) {
        return CPPUTILS_NULL;
    }

    pRetStr->publ.fnc = a_fnc;
    pRetStr->publ.userData = a_userData;
    pRetStr->prev = CPPUTILS_NULL;

    CInternalRWLockWrLock(&(s_loggerData.rwLock));

    pRetStr->next = s_loggerData.pFirstLogger;
    if (s_loggerData.pFirstLogger) {
        s_loggerData.pFirstLogger->prev = pRetStr;
    }
    s_loggerData.pFirstLogger = pRetStr;

    CInternalRWLockWrUnlock(&(s_loggerData.rwLock));

    return &(pRetStr->publ);
}


static inline void CinternalLoggerCreateTimeLogInline(char* CPPUTILS_ARG_NN a_pEnoughBigBuffer) CPPUTILS_NOEXCEPT {
    char* pcTemp;
    time_t currentTime;

    currentTime = time(&currentTime);
    ctime_s_t(&currentTime, a_pEnoughBigBuffer, CINTERNALLOGGER_TIME_BUFF_MIN_SIZE_MIN1);
    pcTemp = strchr(a_pEnoughBigBuffer, '\n');
    if (pcTemp) { (*pcTemp) = 0; }
}



CINTERNAL_EXPORT const char* CinternalLoggerCreateTimeLog(char* CPPUTILS_ARG_NN a_pEnoughBigBuffer) CPPUTILS_NOEXCEPT
{
    CinternalLoggerCreateTimeLogInline(a_pEnoughBigBuffer);
    return a_pEnoughBigBuffer;
}


CINTERNAL_EXPORT struct CinternalLoggerItem* CinternalLoggerAddLogger(TypeCinternalLogger a_fnc, void* a_userData) CPPUTILS_NOEXCEPT
{
    return CinternalLoggerAddLoggerInline(a_fnc,a_userData);
}


CINTERNAL_EXPORT struct CinternalLoggerItem* CinternalLoggerAddDefaultLogger(void) CPPUTILS_NOEXCEPT
{
    return CinternalLoggerAddLoggerInline(&CinternalDefaultLoggerFunction, CPPUTILS_NULL);
}


CINTERNAL_EXPORT void CinternalLoggerRemoveLogger(struct CinternalLoggerItem* a_logger) CPPUTILS_NOEXCEPT
{
    if (a_logger) {
        struct CinternalLoggerItemPrivate* const pRetStr = (struct CinternalLoggerItemPrivate*)a_logger;

        CInternalRWLockWrLock(&(s_loggerData.rwLock));

        if (pRetStr->next) {
            pRetStr->next->prev = pRetStr->prev;
        }

        if (pRetStr->prev) {
            pRetStr->prev->next = pRetStr->next;
        }
        else {
            s_loggerData.pFirstLogger = pRetStr->next;
        }

        CInternalRWLockWrUnlock(&(s_loggerData.rwLock));

        free(pRetStr);
    }  //  if (a_logger) {
}


CINTERNAL_EXPORT void CinternalLoggerCleanAllLoggers(void) CPPUTILS_NOEXCEPT
{
    CinternalCleanAllLoggersInline();
}


CINTERNAL_EXPORT void CinternalLoggerIterateOverAllLoggers(TypeCinternalLoggerIterator CPPUTILS_ARG_NN a_iterator, void* a_clbkData) CPPUTILS_NOEXCEPT
{
    struct CinternalLoggerItemPrivate *pLoggerNext, *pLogger;

    CInternalRWLockRdLock(&(s_loggerData.rwLock));
    pLogger = s_loggerData.pFirstLogger;
    while (pLogger) {
        pLoggerNext = pLogger->next;
        (*a_iterator)(a_clbkData, &(pLogger->publ));
        pLogger = pLoggerNext;
    }  //  while (pLogger) {
    s_loggerData.pFirstLogger = CPPUTILS_NULL;
    CInternalRWLockRdUnlock(&(s_loggerData.rwLock));
}


CINTERNAL_EXPORT void CinternalLoggerSetCurrentLogLevel(int a_newLogLevel) CPPUTILS_NOEXCEPT
{
    s_loggerData.logLevel = a_newLogLevel;
}


CINTERNAL_EXPORT int CinternalLoggerGetCurrentLogLevel(void) CPPUTILS_NOEXCEPT
{
    return s_loggerData.logLevel;
}


CINTERNAL_EXPORT void CinternalLoggerSetCurrentFilesDeepness(int a_filesDeepness) CPPUTILS_NOEXCEPT
{
    s_loggerData.filesDeepness = a_filesDeepness;
}


CINTERNAL_EXPORT int CinternalLoggerGetCurrentFilesDeepness(void) CPPUTILS_NOEXCEPT
{
    return s_loggerData.filesDeepness;
}


CINTERNAL_EXPORT void CinternalLoggerMakeLog(int a_logLevel, const char* CPPUTILS_ARG_NN a_file, int a_line,
                                             enum CinternalLogType a_type, enum CinternalLogCategory a_category, const char* CPPUTILS_ARG_NN a_fmtStr, ...) CPPUTILS_NOEXCEPT
{
    int i, nSnprintfRet;
    size_t unRemainingBuf = CINTERNALLOGGER_TLS_BUF_SIZE_MIN1;
    size_t unOffset = 0;
    const unsigned int logType = CinternalLogEnumToInt(a_type);
    const char *cpcFileName = a_file;
    char* pcData = (char*)CinternalTlsGetSpecific(s_loggerData.tlsData);
    if (!pcData) {
        pcData = (char*)malloc(CINTERNALLOGGER_TLS_BUF_SIZE);
        if (!pcData) {
            // todo: think on error handling
            return;
        }
        CinternalTlsSetSpecific(s_loggerData.tlsData, pcData);
    }

    if (logType & CinternalLogEnumToInt(CinternalLogTypeStartLogging)) {
        nSnprintfRet = snprintf_cint_t(pcData + unOffset, unRemainingBuf,"[")
    }

    for (i = 0; i < s_loggerData.filesDeepness; ++i) {
        cpcFileName = FileNameFromPossiblePathInline(cpcFileName);
    }


}













static inline int CinternalMakeLogPrivateInline(enum CinternalLogTypes a_type, bool a_bSync, const char* a_fmtStr, ...){
    int nRet;
    va_list argptr;
    va_start(argptr, a_fmtStr);
    nRet = CinternalMakeLogPrivateInlineV(a_type,a_bSync,a_fmtStr, &argptr);
    va_end(argptr);
    return nRet;
}


static inline void CinternalLogPrintDateAndTimeInline(enum CinternalLogTypes a_type, bool a_bSync){
    char* pcTemp;
    char vcCurTimeStr[128];
    time_t currentTime;

    currentTime = time(&currentTime);
    ctime_s_t(&currentTime,vcCurTimeStr,127);
    pcTemp = strchr(vcCurTimeStr,'\n');
    if(pcTemp){(*pcTemp)=0;}
    CinternalMakeLogPrivateInline(a_type,a_bSync,"%s",vcCurTimeStr);
}


CINTERNAL_EXPORT void CinternalLogPrintDateAndTime(enum CinternalLogTypes a_type, bool a_bSync)
{
    CinternalLogPrintDateAndTimeInline(a_type,a_bSync);
}


CINTERNAL_EXPORT void CinternalInstallLogger(void* a_userData, TypeCinternalLogger a_clbk)
{
    s_userData = a_userData;
    s_loggerClbk = a_clbk ? a_clbk : (&CinternalDefaultLoggerFunction);
}


CINTERNAL_EXPORT void CinternalGetLogger(void** a_pUserData, TypeCinternalLogger* a_pClbk)
{
    if (a_pUserData) { *a_pUserData = s_userData; }
    if (a_pClbk) { *a_pClbk = s_loggerClbk; }
}


CINTERNAL_EXPORT int  CinternalMakeLogNoExtraData(enum CinternalLogTypes a_type, bool a_bSync, const char* a_fmtStr, ...)
{
    int nRet;
    va_list argptr;
    va_start(argptr, a_fmtStr);
    nRet = CinternalMakeLogPrivateInlineV(a_type,a_bSync,a_fmtStr, &argptr);
    va_end(argptr);
    return nRet;
}


CINTERNAL_EXPORT void CinternalMakeLog(const char* a_src, int a_line, enum CinternalLogTypes a_type, const char* a_fmtStr, ...)
{
	va_list argptr;
    const char* cpcSrc = FileNameFromPossiblePathInline(a_src);

    CinternalMakeLogPrivateInline(a_type, false,"[");
    CinternalLogPrintDateAndTimeInline(a_type, false);
    CinternalMakeLogPrivateInline(a_type, false,"], src:\"%s\",ln:%d - ", cpcSrc, a_line);
	va_start(argptr, a_fmtStr);
    CinternalMakeLogPrivateInlineV(a_type, false,a_fmtStr, &argptr);
	va_end(argptr);
    CinternalMakeLogPrivateInline(a_type, true,"\n");
}


//CPPUTILS_CODE_INITIALIZER(cinternal_core_logger_initialize) {
//
//    s_userData = CPPUTILS_NULL;
//    s_loggerClbk = &CinternalDefaultLoggerFunction;
//}


static void CinternalDefaultLoggerFunction(void* a_userData, enum CinternalLogType a_type, enum CinternalLogCategory a_category, const char* a_textToLog) CPPUTILS_NOEXCEPT
{
    int nRet = 0;
    CPPUTILS_STATIC_CAST(void, a_userData);
    switch (a_type) {
    case CinternalLogTypeInfo:
        nRet = vprintf(a_fmtStr, a_argptr);
        if (a_bSync) { fflush(stdout); }
        break;
    case CinternalLogTypeDebug:
#if defined(NDEBUG) || (defined(CUTILS_NO_DEBUG_LOGS) && defined(CUTILS_NO_DEBUG_LOGS_FOR_LIB))
        CPPUTILS_STATIC_CAST(void, a_userData);
#else
        nRet = vprintf(a_fmtStr, a_argptr);
        if (a_bSync) { fflush(stdout); }
#endif
        break;
    default:
        nRet = vfprintf(stderr, a_fmtStr, a_argptr);
        if (a_bSync) { fflush(stderr); }
        break;
    }  //  switch (a_type) {
    return nRet;
}


static void CinternalLoggerTlsClean(void* a_data)
{
    char* pcData = CPPUTILS_STATIC_CAST(char*,a_data);
    free(pcData);
}


static void cinternal_core_logger_clean(void) CPPUTILS_NOEXCEPT {
    CinternalCleanAllLoggersInline();
    CinternalTlsDelete(s_loggerData.tlsData);
    CInternalRWLockClean(&(s_loggerData.rwLock))
}


CPPUTILS_C_CODE_INITIALIZER(cinternal_core_logger_init) {
    s_loggerData.pFirstLogger = CPPUTILS_NULL;
    s_loggerData.logLevel = 0;
    s_loggerData.filesDeepness = 1;
    CInternalRWLockInit(&(s_loggerData.rwLock));
    CinternalTlsAlloc(&(s_loggerData.tlsData), &CinternalLoggerTlsClean);
    atexit(&cinternal_core_logger_clean);
}


CPPUTILS_END_C
