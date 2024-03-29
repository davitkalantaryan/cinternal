//
// repo:            cinternal
// file:			cinternal_core_logger.c
// path:			src/core/cinternal_core_logger.c
// created on:		2023 Mar 30
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cinternal/internal_header.h>
#define CPPUTILS_CONDITIONAL_WEAKNESS		CPPUTILS_ONLY_GCCLIKE_ATTR_WEAK
#include <cinternal/logger.h>
#define FileNameFromPossiblePathInline_needed
#include <cinternal/fs.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


CPPUTILS_BEGIN_C


#ifdef _MSC_VER
#define URL_CAPT_API_FILE_DELIMER0	'\\'
#define URL_CAPT_API_FILE_DELIMER1	'/'
#else
#define URL_CAPT_API_FILE_DELIMER0	'/'
#define URL_CAPT_API_FILE_DELIMER1	'\\'
#endif

#ifdef _MSC_VER
#pragma warning (disable:4061)
#endif

#ifdef _WIN32
#define ctime_s_t(_timep,_buffer,_numberOfElements)     ctime_s(_buffer,_numberOfElements,_timep)
#else
#define ctime_s_t(_timep,_buffer,_numberOfElements)     CPPUTILS_STATIC_CAST(void,_numberOfElements);ctime_r(_timep,_buffer)
#endif


static void*                    s_userData = CPPUTILS_NULL;
static TypeCinternalLogger      s_loggerClbk = &CinternalDefaultLoggerFunction;


CPPUTILS_CONDITIONAL_WEAKNESS int CinternalDefaultLoggerFunction(void* a_userData, enum CinternalLogTypes a_type, bool a_bSync, const char* a_fmtStr, va_list a_argptr)
{
    int nRet = 0;
    CPPUTILS_STATIC_CAST(void, a_userData);
    switch (a_type) {
    case CinternalLogTypeInfo:
        nRet = vprintf(a_fmtStr, a_argptr);
        if(a_bSync){fflush(stdout);}
        break;
    case CinternalLogTypeDebug:
#if defined(NDEBUG) || (defined(CUTILS_NO_DEBUG_LOGS) && defined(CUTILS_NO_DEBUG_LOGS_FOR_LIB))
        CPPUTILS_STATIC_CAST(void, a_userData);
#else
        nRet = vprintf(a_fmtStr, a_argptr);
        if(a_bSync){fflush(stdout);}
#endif
        break;
    default:
        nRet = vfprintf(stderr, a_fmtStr, a_argptr);
        if(a_bSync){fflush(stderr);}
        break;
    }  //  switch (a_type) {
    return nRet;
}


static inline int CinternalMakeLogPrivateInlineV(enum CinternalLogTypes a_type, bool a_bSync, const char* a_fmtStr, va_list* a_argptr_p){
    return (*s_loggerClbk)(s_userData, a_type,a_bSync,a_fmtStr, *a_argptr_p);
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


CPPUTILS_CODE_INITIALIZER(cinternal_core_logger_initialize) {

    s_userData = CPPUTILS_NULL;
    s_loggerClbk = &CinternalDefaultLoggerFunction;
}


CPPUTILS_END_C
