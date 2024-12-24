//
// repo:            cinternal
// file:			cinternal_core_logger.c
// path:			src/core/cinternal_core_logger.c
// created on:		2023 Mar 30
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef FileNameFromPossiblePathInline_needed
#define FileNameFromPossiblePathInline_needed
#endif

#include <cinternal/logger.h>
#include <cinternal/thread_local_sys.h>
#include <cinternal/fs.h>
#include <cinternal/rwlock.h>
#include <cinternal/wrapper.h>
#include <cinternal/bistateflags.h>
#include <cinternal/disable_compiler_warnings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C

#define CINTERNALLOGGER_TIME_BUFF_MIN_SIZE_MIN1  (CINTERNALLOGGER_TIME_BUFF_MIN_SIZE  - 1)
#define CINTERNALLOGGER_TLS_BUF_SIZE_MIN4        (0xffffc)
#define CINTERNALLOGGER_TLS_BUF_SIZE             (CINTERNALLOGGER_TLS_BUF_SIZE_MIN4 + 4)

struct CinternalLoggerItemPrivate {
    struct CinternalLoggerItem          publ;
    struct CinternalLoggerItemPrivate   *prev, *next;
    char*                               endStr;
    size_t                              endStrLenPlus1;
};

struct SCInternalLoggerTlsData {
    char*                       pcBuffer;
    size_t                      unOffset;
    CPPUTILS_BISTATE_FLAGS_UN(
        hasCategory,
        hasTime,
        hasPlace
    )flags;
};


struct SCinternalLoggerData {
    struct CinternalLoggerItemPrivate*  pFirstLogger;
    struct CinternalLoggerItem*         pDefaultlyAddedLogger;
    CInternalRWLock                     rwLock;
    CinternalTlsData                    tlsData;
    int                                 logLevel;
    int                                 filesDeepness;
    int                                 reserved01;
};


static void CinternalDefaultLoggerFunction(void* a_userData, enum CinternalLogCategory a_categoryEnm, const char* CPPUTILS_ARG_NN a_categoryStr, char* CPPUTILS_ARG_NN a_log, size_t a_logStrLen) CPPUTILS_NOEXCEPT;
static void cinternal_core_logger_clean(void) CPPUTILS_NOEXCEPT;
static void CinternalLoggerTlsClean(void* a_data) CPPUTILS_NOEXCEPT;

static struct SCinternalLoggerData  s_loggerData;
static int s_isInited = 0;


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


static inline struct CinternalLoggerItem* CinternalLoggerAddLoggerNoInitInline(TypeCinternalLogger a_fnc, void* a_userData, const char* a_endStr) CPPUTILS_NOEXCEPT
{
    const char* const endStr = a_endStr ? a_endStr : "";
    struct CinternalLoggerItemPrivate* const pRetStr = (struct CinternalLoggerItemPrivate*)calloc(1, sizeof(struct CinternalLoggerItemPrivate));
    if (!pRetStr) {
        return CPPUTILS_NULL;
    }

    pRetStr->endStr = CinternalWrapperStrdup(endStr);
    if (!(pRetStr->endStr)) {
        free(pRetStr);
        return CPPUTILS_NULL;
    }

    pRetStr->endStrLenPlus1 = strlen(endStr) + 1;
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


static inline int CinternalInitLoggerInline(void) CPPUTILS_NOEXCEPT {
    if(s_isInited){
        return 0;
    }
    s_isInited = 1;
    s_loggerData.pFirstLogger = CPPUTILS_NULL;
    s_loggerData.logLevel = 0;
    s_loggerData.filesDeepness = 2;
    CInternalRWLockInitNoCheck(&(s_loggerData.rwLock));
    CinternalTlsAlloc(&(s_loggerData.tlsData), &CinternalLoggerTlsClean);
#ifdef CINTERNALLOGGER_NO_DEFAULT
    s_loggerData.pDefaultlyAddedLogger = CPPUTILS_NULL;
#else
    s_loggerData.pDefaultlyAddedLogger = CinternalLoggerAddLoggerNoInitInline(&CinternalDefaultLoggerFunction, CPPUTILS_NULL, "\n\r");
#endif
    atexit(&cinternal_core_logger_clean);
    return 0;
}


static inline struct CinternalLoggerItem* CinternalLoggerAddLoggerInline(TypeCinternalLogger a_fnc, void* a_userData, const char* a_endStr) CPPUTILS_NOEXCEPT
{
    CinternalInitLoggerInline();
    return CinternalLoggerAddLoggerNoInitInline(a_fnc,a_userData,a_endStr);
}


static inline size_t CinternalLoggerCreateTimeLogInline(char* CPPUTILS_ARG_NN a_pEnoughBigBuffer) CPPUTILS_NOEXCEPT {
    char* pcTemp;
    time_t currentTime;

    currentTime = time(&currentTime);
    CinternalWrapperCtime_s(&currentTime, a_pEnoughBigBuffer, CINTERNALLOGGER_TIME_BUFF_MIN_SIZE_MIN1);
    pcTemp = strchr(a_pEnoughBigBuffer, '\n');
    if (pcTemp) {
        const size_t retStrLen = CPPUTILS_STATIC_CAST(size_t,(pcTemp - a_pEnoughBigBuffer));
        (*pcTemp) = 0;
        return retStrLen;
    }
    return strlen(a_pEnoughBigBuffer);
}


static inline void CinternalLoggerSetFileInline(struct SCInternalLoggerTlsData* CPPUTILS_ARG_NN a_pTlsData, const char* CPPUTILS_ARG_NN a_file) CPPUTILS_NOEXCEPT {
    const char* cpcFileName = a_file;
    size_t unTemporar;

    if ((s_loggerData.filesDeepness) > 0) {
        cpcFileName = FileNameFromPossiblePathInline(a_file);
        if (cpcFileName != a_file) {
            int cnt = 1;
            cpcFileName -= 2;
            for (; cpcFileName != a_file; --cpcFileName) {
                if (((*cpcFileName) == CINTERNAL_FILE_DELIMER01) || ((*cpcFileName) == CINTERNAL_FILE_DELIMER02)) {
                    if ((++cnt) >= (s_loggerData.filesDeepness)) {
                        ++cpcFileName;
                        break;
                    }  //  if ((++cnt) >= (s_loggerData.filesDeepness)) {
                }  //  if (((*cpcFileName) == CINTERNAL_FILE_DELIMER01) || ((*cpcFileName) == CINTERNAL_FILE_DELIMER02)) {
            }  //  for (; (cnt < (s_loggerData.filesDeepness)) && (cpcFileName != a_file); ++cnt, --cpcFileName) {
        }  //  if (cpcFileName != a_file) {
    }  //  if ((s_loggerData.filesDeepness) > 0) {

    a_pTlsData->pcBuffer[a_pTlsData->unOffset++] = 'f';
    a_pTlsData->pcBuffer[a_pTlsData->unOffset++] = 'l';
    a_pTlsData->pcBuffer[a_pTlsData->unOffset++] = ':';
    a_pTlsData->pcBuffer[a_pTlsData->unOffset++] = '\"';
    unTemporar = strlen(cpcFileName);
    CinternalWrapperMemcpy((a_pTlsData->pcBuffer) + (a_pTlsData->unOffset), cpcFileName, unTemporar);
    a_pTlsData->unOffset += unTemporar;
    a_pTlsData->pcBuffer[a_pTlsData->unOffset++] = '\"';
}


static inline const char* CinternalLoggerGetCategoryStringInline(const char* a_categoryStr, enum CinternalLogCategory a_categoryEnm) CPPUTILS_NOEXCEPT {
    const char* categoryStr = "unknown";
    if (a_categoryStr && a_categoryStr[0]) {
        categoryStr = a_categoryStr;
    }
    else {
        switch (a_categoryEnm) {
        case CinternalLogCategoryFatal:
            categoryStr = "fatal";
            break;
        case CinternalLogCategoryCritical:
            categoryStr = "critical";
            break;
        case CinternalLogCategoryWarning:
            categoryStr = "warning";
            break;
        case CinternalLogCategoryInfo:
            categoryStr = "info";
            break;
        case CinternalLogCategoryDebug:
            categoryStr = "debug";
            break;
        default:
            break;
        }  //  switch (a_pTlsData->catEnm) {
    }  //  if (!categoryStr) {
    return categoryStr;
}


static inline int CinternalLoggerFinalizeLoggingInline(struct SCInternalLoggerTlsData* CPPUTILS_ARG_NN a_pTlsData, const char* CPPUTILS_ARG_NN a_categoryStr, enum CinternalLogCategory a_categoryEnm) CPPUTILS_NOEXCEPT {
    const struct CinternalLoggerItemPrivate *pLoggerNext, *pLogger;
    const size_t unOffset = a_pTlsData->unOffset;

    CInternalRWLockRdLock(&(s_loggerData.rwLock));
    pLogger = s_loggerData.pFirstLogger;
    while (pLogger) {
        pLoggerNext = pLogger->next;

        CinternalWrapperMemcpy((a_pTlsData->pcBuffer) + unOffset, pLogger->endStr, pLogger->endStrLenPlus1);
        //pTlsData->unOffset += unTemporar;

        (*(pLogger->publ.fnc))(pLogger->publ.userData, a_categoryEnm, a_categoryStr, a_pTlsData->pcBuffer, a_pTlsData->unOffset);

        pLogger = pLoggerNext;
    }  //  while (pLogger) {
    CInternalRWLockRdUnlock(&(s_loggerData.rwLock));

    a_pTlsData->unOffset = 0;
    a_pTlsData->flags.wr_all = CPPUTILS_BISTATE_MAKE_ALL_BITS_FALSE;
    return CPPUTILS_STATIC_CAST(int, unOffset);
}


static inline struct SCInternalLoggerTlsData* CinternalLoggerGetTlsDataInline(void) CPPUTILS_NOEXCEPT {
    struct SCInternalLoggerTlsData* pTlsData;
    pTlsData = (struct SCInternalLoggerTlsData*)CinternalTlsGetSpecific(s_loggerData.tlsData);
    if (pTlsData) {
        return pTlsData;
    }

    pTlsData = (struct SCInternalLoggerTlsData*)calloc(1, sizeof(struct SCInternalLoggerTlsData));
    if (!pTlsData) {
        return CPPUTILS_NULL;
    }

    pTlsData->pcBuffer = (char*)malloc(CINTERNALLOGGER_TLS_BUF_SIZE);
    if (!pTlsData->pcBuffer) {
        free(pTlsData);
        return CPPUTILS_NULL;
    }

    pTlsData->flags.wr_all = CPPUTILS_BISTATE_MAKE_ALL_BITS_FALSE;
    pTlsData->unOffset = 0;
    CinternalTlsSetSpecific(s_loggerData.tlsData, pTlsData);
    return pTlsData;
}


static inline void CinternalLoggerRemoveLoggerInline(struct CinternalLoggerItem* CPPUTILS_ARG_NN a_logger) CPPUTILS_NOEXCEPT {
    struct CinternalLoggerItemPrivate* const pRetStr = (struct CinternalLoggerItemPrivate*)a_logger;

    free(pRetStr->endStr);

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
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


CINTERNAL_EXPORT void CinternalLoggerRemoveDefaultlyAddedLogger(void) CPPUTILS_NOEXCEPT
{
    if (s_loggerData.pDefaultlyAddedLogger) {
        CinternalLoggerRemoveLoggerInline(s_loggerData.pDefaultlyAddedLogger);
        s_loggerData.pDefaultlyAddedLogger = CPPUTILS_NULL;
    }  //  if (a_logger) {
}


CINTERNAL_EXPORT const char* CinternalLoggerCreateTimeLog(char* CPPUTILS_ARG_NN a_pEnoughBigBuffer) CPPUTILS_NOEXCEPT
{
    CinternalLoggerCreateTimeLogInline(a_pEnoughBigBuffer);
    return a_pEnoughBigBuffer;
}


CINTERNAL_EXPORT struct CinternalLoggerItem* CinternalLoggerGetDefaultlyAddedLogger(void) CPPUTILS_NOEXCEPT
{
    return s_loggerData.pDefaultlyAddedLogger;
}


CINTERNAL_EXPORT struct CinternalLoggerItem* CinternalLoggerAddLogger(TypeCinternalLogger a_fnc, void* a_userData, const char* a_endStr) CPPUTILS_NOEXCEPT
{
    return CinternalLoggerAddLoggerInline(a_fnc,a_userData, a_endStr);
}


CINTERNAL_EXPORT struct CinternalLoggerItem* CinternalLoggerAddDefaultLogger(void) CPPUTILS_NOEXCEPT
{
    return CinternalLoggerAddLoggerInline(&CinternalDefaultLoggerFunction, CPPUTILS_NULL,"\n\r");
}


CINTERNAL_EXPORT void CinternalLoggerRemoveLogger(struct CinternalLoggerItem* a_logger) CPPUTILS_NOEXCEPT
{
    if (a_logger) {
        CinternalLoggerRemoveLoggerInline(a_logger);
        if (a_logger == (s_loggerData.pDefaultlyAddedLogger)) {
            s_loggerData.pDefaultlyAddedLogger = CPPUTILS_NULL;
        }
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


CINTERNAL_EXPORT const char* CinternalLoggerGetEndString(const struct CinternalLoggerItem* CPPUTILS_ARG_NN a_logger) CPPUTILS_NOEXCEPT
{
    return ((const struct CinternalLoggerItemPrivate*)a_logger)->endStr;
}


CINTERNAL_EXPORT int CinternalLoggerSetEndString(struct CinternalLoggerItem* CPPUTILS_ARG_NN a_logger, const char* a_endStr) CPPUTILS_NOEXCEPT
{
    const char* const endStr = a_endStr ? a_endStr : "";
    char* const pcNewEndStr = CinternalWrapperStrdup(endStr);
    if (pcNewEndStr) {
        struct CinternalLoggerItemPrivate* const pRetStr = (struct CinternalLoggerItemPrivate*)a_logger;
        free(pRetStr->endStr);
        pRetStr->endStr = pcNewEndStr;
        pRetStr->endStrLenPlus1 = strlen(endStr) + 1;
        return 0;
    }
    return 1;
}


CINTERNAL_EXPORT size_t CinternalLoggerGetLogSize(void) CPPUTILS_NOEXCEPT
{
    struct SCInternalLoggerTlsData* const pTlsData = CinternalLoggerGetTlsDataInline();

    if (pTlsData) {
        return pTlsData->unOffset;
    }

    return 0;
}


CINTERNAL_EXPORT int CinternalLoggerMakeLog(int a_logLevel, const char* a_categoryStr, const char* CPPUTILS_ARG_NN a_file, int a_line, const char* CPPUTILS_ARG_NN a_function,
                                            enum CinternalLogType a_type, enum CinternalLogCategory a_categoryEnm, const char* CPPUTILS_ARG_NN a_fmtStr, ...) CPPUTILS_NOEXCEPT
{
    const char* const categoryStr = CinternalLoggerGetCategoryStringInline(a_categoryStr,a_categoryEnm);
    const unsigned int logType = CinternalLogEnumToInt(a_type);
    const unsigned int hasPlace = (logType & CinternalLogEnumToInt(CinternalLogTypeFile)) || (logType & CinternalLogEnumToInt(CinternalLogTypeLine)) || (logType & CinternalLogEnumToInt(CinternalLogTypeFunction));
    struct SCInternalLoggerTlsData* const pTlsData = CinternalLoggerGetTlsDataInline();

    if (!pTlsData) {
        return -1;
    }

    if ((a_categoryEnm == CinternalLogCategoryDebug) && (a_logLevel > (s_loggerData.logLevel))) {
        return 0;
    }

    // 1. category
    if ((logType & CinternalLogEnumToInt(CinternalLogTypeCategory)) && (pTlsData->flags.rd.hasCategory_false)) {
        size_t unTemporar;

        unTemporar = strlen(categoryStr);
        CinternalWrapperMemcpy((pTlsData->pcBuffer) + (pTlsData->unOffset), categoryStr, unTemporar);
        pTlsData->unOffset += unTemporar;

        pTlsData->pcBuffer[pTlsData->unOffset++] = ' ';
        pTlsData->pcBuffer[pTlsData->unOffset++] = '=';
        pTlsData->pcBuffer[pTlsData->unOffset++] = '>';
        pTlsData->pcBuffer[pTlsData->unOffset++] = ' ';
        pTlsData->flags.wr.hasCategory = CPPUTILS_BISTATE_MAKE_BITS_TRUE;
    }  //  if (logType & CinternalLogEnumToInt(CinternalLogTypeTime)) {

    // 2. time
    if ((logType & CinternalLogEnumToInt(CinternalLogTypeTime)) && (pTlsData->flags.rd.hasTime_false)) {
        pTlsData->pcBuffer[pTlsData->unOffset++] = '[';
        pTlsData->unOffset += CinternalLoggerCreateTimeLogInline((pTlsData->pcBuffer) + (pTlsData->unOffset));
        pTlsData->pcBuffer[pTlsData->unOffset++] = ']';
        
        pTlsData->pcBuffer[pTlsData->unOffset++] = ' ';
        pTlsData->pcBuffer[pTlsData->unOffset++] = '=';
        pTlsData->pcBuffer[pTlsData->unOffset++] = '>';
        pTlsData->pcBuffer[pTlsData->unOffset++] = ' ';
        pTlsData->flags.wr.hasTime = CPPUTILS_BISTATE_MAKE_BITS_TRUE;
    }  //  if (logType & CinternalLogEnumToInt(CinternalLogTypeTime)) {

    // 3. position (file,line,function)
    if (hasPlace && (pTlsData->flags.rd.hasPlace_false)) {
        size_t unTemporar;
        int nSnprintfRet,hasSmth = 0;

        if (logType & CinternalLogEnumToInt(CinternalLogTypeFile)) {
            if (a_file && a_file[0]) {
                pTlsData->pcBuffer[pTlsData->unOffset++] = '[';
                CinternalLoggerSetFileInline(pTlsData, a_file);
                hasSmth = 1;
            }
        }

        if (logType & CinternalLogEnumToInt(CinternalLogTypeLine)) {
            if (a_line > 0) {
                if (hasSmth) {
                    pTlsData->pcBuffer[pTlsData->unOffset++] = ',';
                }
                else {
                    pTlsData->pcBuffer[pTlsData->unOffset++] = '[';
                    hasSmth = 1;
                }
                pTlsData->pcBuffer[pTlsData->unOffset++] = 'l';
                pTlsData->pcBuffer[pTlsData->unOffset++] = 'n';
                pTlsData->pcBuffer[pTlsData->unOffset++] = ':';
                unTemporar = (CINTERNALLOGGER_TLS_BUF_SIZE_MIN4 - (pTlsData->unOffset));
                nSnprintfRet = CinternalWrapperSnprintf((pTlsData->pcBuffer) + (pTlsData->unOffset), unTemporar, "%d", a_line);
                pTlsData->unOffset += CPPUTILS_STATIC_CAST(size_t, nSnprintfRet);
            }
        }

        if (logType & CinternalLogEnumToInt(CinternalLogTypeFunction)) {
            if (a_function && a_function[0]) {
                if (hasSmth) {
                    pTlsData->pcBuffer[pTlsData->unOffset++] = ',';
                }
                else {
                    pTlsData->pcBuffer[pTlsData->unOffset++] = '[';
                    hasSmth = 1;
                }
                pTlsData->pcBuffer[pTlsData->unOffset++] = 'f';
                pTlsData->pcBuffer[pTlsData->unOffset++] = 'n';
                pTlsData->pcBuffer[pTlsData->unOffset++] = ':';
                pTlsData->pcBuffer[pTlsData->unOffset++] = '`';
                unTemporar = strlen(a_function);
                CinternalWrapperMemcpy((pTlsData->pcBuffer) + (pTlsData->unOffset), a_function, unTemporar);
                pTlsData->unOffset += unTemporar;
                pTlsData->pcBuffer[pTlsData->unOffset++] = '`';
            }
        }  //  if (logType & CinternalLogEnumToInt(CinternalLogTypeFunction)) {

        if (hasSmth) {
            pTlsData->pcBuffer[pTlsData->unOffset++] = ']';

            pTlsData->pcBuffer[pTlsData->unOffset++] = ' ';
            pTlsData->pcBuffer[pTlsData->unOffset++] = '=';
            pTlsData->pcBuffer[pTlsData->unOffset++] = '>';
            pTlsData->pcBuffer[pTlsData->unOffset++] = ' ';
            pTlsData->flags.wr.hasPlace = CPPUTILS_BISTATE_MAKE_BITS_TRUE;
        }  //  if (hasSmth) {
    }  //  if (hasPlace && (pTlsData->flags.rd.hasPlace_false)) {

    // 4. text itself
    if (logType & CinternalLogEnumToInt(CinternalLogTypeMainText)) {
        va_list args;
        size_t unTemporar;
        int nSnprintfRet;

        unTemporar = (CINTERNALLOGGER_TLS_BUF_SIZE_MIN4 - (pTlsData->unOffset));
        va_start(args, a_fmtStr);
        nSnprintfRet = CinternalWrapperVsnprintf((pTlsData->pcBuffer) + (pTlsData->unOffset), unTemporar, a_fmtStr, args);
        va_end(args);
        pTlsData->unOffset += CPPUTILS_STATIC_CAST(size_t, nSnprintfRet);
    }  //  if (logType & CinternalLogEnumToInt(CinternalLogTypeMainText)) {

    // 5. finalize
    if (logType & CinternalLogEnumToInt(CinternalLogTypeFinalize)) {
        return CinternalLoggerFinalizeLoggingInline(pTlsData, categoryStr, a_categoryEnm);
    }

    return CPPUTILS_STATIC_CAST(int, pTlsData->unOffset);
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


static void CinternalDefaultLoggerFunction(void* a_userData, enum CinternalLogCategory a_categoryEnm, const char* CPPUTILS_ARG_NN a_categoryStr, char* CPPUTILS_ARG_NN a_log, size_t a_logStrLen) CPPUTILS_NOEXCEPT
{
    FILE* fpOut;
    CPPUTILS_STATIC_CAST(void, a_userData);
    CPPUTILS_STATIC_CAST(void, a_categoryStr);
    switch (a_categoryEnm) {
    case CinternalLogCategoryFatal:
    case CinternalLogCategoryCritical:
    case CinternalLogCategoryWarning:
        fpOut = stderr;
        break;
    default:
        fpOut = stdout;
        break;
    }  //  switch (a_categoryEnm) {
    fwrite(a_log, 1, (a_logStrLen+1), fpOut);
    fflush(fpOut);
}


static void CinternalLoggerTlsClean(void* a_data) CPPUTILS_NOEXCEPT
{
    struct SCInternalLoggerTlsData* const pTlsData = (struct SCInternalLoggerTlsData*)a_data;
    if (pTlsData) {
        free(pTlsData->pcBuffer);
        free(pTlsData);
    }
}


static void cinternal_core_logger_clean(void) CPPUTILS_NOEXCEPT {
    if(s_isInited){
        s_isInited = 0;
        CinternalCleanAllLoggersInline();
        CinternalTlsDelete(s_loggerData.tlsData);
        CInternalRWLockClean(&(s_loggerData.rwLock))
    }
}


CPPUTILS_C_CODE_INITIALIZER(cinternal_core_logger_init) {
    CinternalInitLoggerInline();
}


CPPUTILS_END_C
