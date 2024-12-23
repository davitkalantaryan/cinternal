//
// repo:			cinternal
// file:			logger.h
// path:			src/include/cinternal/logger.h
// created on:		2023 Mar 30
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_LOGGER_H
#define CINTERNAL_INCLUDE_CINTERNAL_LOGGER_H

#include <cinternal/export_symbols.h>
#include <cinternal/macroses.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stddef.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C

#define CinternalLogIntToEnum(_int)                 CPPUTILS_STATIC_CAST(enum CinternalLogType,_int)
#define CinternalLogEnumToInt(_enum)                CPPUTILS_STATIC_CAST(unsigned int,_enum)
#define CinternalLogEnumConcatToInt(...)            CPPUTILS_VAR_MACRO_APPY_OP(CinternalLogEnumToInt, | ,__VA_ARGS__)
#define CinternalLogEnumConcat(...)                 CinternalLogIntToEnum( CinternalLogEnumConcatToInt(__VA_ARGS__) )
#define CINTERNALLOGGER_TIME_BUFF_MIN_SIZE          256

struct CinternalLoggerItem;

enum CinternalLogType { 
    CinternalLogTypeNone = 0, 
    CinternalLogTypeCategory = 1,
    CinternalLogTypeTime = 2, 
    CinternalLogTypeFile = 4,
    CinternalLogTypeLine = 8,
    CinternalLogTypeFunction = 16,
    CinternalLogTypeMainText = 32,
    CinternalLogTypeFinalize = 64, 
    CinternalLogTypeCategoryWithTime = CinternalLogEnumConcatToInt(CinternalLogTypeCategory,CinternalLogTypeTime),
    CinternalLogTypePlace = CinternalLogEnumConcatToInt(CinternalLogTypeFile,CinternalLogTypeLine),
    CinternalLogTypePlaceWithFunc = CinternalLogEnumConcatToInt(CinternalLogTypePlace,CinternalLogTypeFunction),
    CinternalLogTypeStart = CinternalLogEnumConcatToInt(CinternalLogTypeCategoryWithTime,CinternalLogTypePlace),
    CinternalLogTypeStartWithFunc = CinternalLogEnumConcatToInt(CinternalLogTypeStart,CinternalLogTypeFunction),
    CinternalLogTypeStartAndText = CinternalLogEnumConcatToInt(CinternalLogTypeStart,CinternalLogTypeMainText),
    CinternalLogTypeStartAndTextWithFunc = CinternalLogEnumConcatToInt(CinternalLogTypeStartAndText,CinternalLogTypeFunction),
    CinternalLogTypeCompleteLogging = CinternalLogEnumConcatToInt(CinternalLogTypeCategoryWithTime,CinternalLogTypeMainText,CinternalLogTypeFinalize),
    CinternalLogTypeCompleteLoggingWithPlace = CinternalLogEnumConcatToInt(CinternalLogTypeCompleteLogging,CinternalLogTypePlace),
    CinternalLogTypeCompleteLoggingWithPlaceAndFunc = CinternalLogEnumConcatToInt(CinternalLogTypeCompleteLoggingWithPlace,CinternalLogTypeFunction)
};

enum CinternalLogCategory {
    CinternalLogCategoryNone,
    CinternalLogCategoryFatal,
    CinternalLogCategorySystem = CinternalLogCategoryFatal,
    CinternalLogCategoryCritical,
    CinternalLogCategoryError = CinternalLogCategoryCritical,
    CinternalLogCategoryWarning,
    CinternalLogCategoryInfo,
    CinternalLogCategoryDebug
};


typedef void (*TypeCinternalLogger)(void* a_userData, enum CinternalLogCategory a_categoryEnm, const char* CPPUTILS_ARG_NN a_categoryStr, char* CPPUTILS_ARG_NN a_log, size_t a_logStrLen);
typedef int (*TypeCinternalLoggerIterator)(void* a_userData, struct CinternalLoggerItem* CPPUTILS_ARG_NN);  // ret != 0 stops iteration

struct CinternalLoggerItem {
    TypeCinternalLogger     fnc;
    void*                   userData;
};


CINTERNAL_EXPORT void CinternalLoggerRemoveDefaultlyAddedLogger(void) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT const char* CinternalLoggerCreateTimeLog(char* CPPUTILS_ARG_NN a_pEnoughBigBuffer) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT struct CinternalLoggerItem* CinternalLoggerGetDefaultlyAddedLogger(void) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT struct CinternalLoggerItem* CinternalLoggerAddLogger(TypeCinternalLogger a_fnc, void* a_userData, const char* a_endStr) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT struct CinternalLoggerItem* CinternalLoggerAddDefaultLogger(void) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CinternalLoggerRemoveLogger(struct CinternalLoggerItem* a_logger) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CinternalLoggerCleanAllLoggers(void) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CinternalLoggerIterateOverAllLoggers(TypeCinternalLoggerIterator CPPUTILS_ARG_NN a_iterator, void* a_clbkData) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CinternalLoggerSetCurrentLogLevel(int a_newLogLevel) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT int  CinternalLoggerGetCurrentLogLevel(void) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CinternalLoggerSetCurrentFilesDeepness(int a_filesDeepness) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT int  CinternalLoggerGetCurrentFilesDeepness(void) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT const char* CinternalLoggerGetEndString(const struct CinternalLoggerItem* CPPUTILS_ARG_NN a_logger) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT int  CinternalLoggerSetEndString(struct CinternalLoggerItem* CPPUTILS_ARG_NN a_logger, const char* a_endStr) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT size_t  CinternalLoggerGetLogSize(void) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT int  CinternalLoggerMakeLog(int a_logLevel, const char* a_categoryStr, const char* CPPUTILS_ARG_NN a_file, int a_line, const char* CPPUTILS_ARG_NN a_function,
                                             enum CinternalLogType a_type, enum CinternalLogCategory a_categoryEnm, const char* CPPUTILS_ARG_NN a_fmtStr, ...) CPPUTILS_NOEXCEPT;


#define CInternalLogFatal(...)		            CinternalLoggerMakeLog(0,"fatal",__FILE__,__LINE__,__FUNCTION__,CinternalLogTypeCompleteLoggingWithPlaceAndFunc,CinternalLogCategoryFatal,__VA_ARGS__)
#define CInternalLogCritical(...)		        CinternalLoggerMakeLog(0,"critical",__FILE__,__LINE__,__FUNCTION__,CinternalLogTypeCompleteLoggingWithPlaceAndFunc,CinternalLogCategoryCritical,__VA_ARGS__)
#define CInternalLogError(...)		            CinternalLoggerMakeLog(0,"error",__FILE__,__LINE__,__FUNCTION__,CinternalLogTypeCompleteLoggingWithPlace,CinternalLogCategoryError,__VA_ARGS__)
#define CInternalLogWarning(...)	            CinternalLoggerMakeLog(0,"warning",__FILE__,__LINE__,__FUNCTION__,CinternalLogTypeCompleteLoggingWithPlace,CinternalLogCategoryWarning,__VA_ARGS__)
#define CInternalLogInfo(...)		            CinternalLoggerMakeLog(0,"info",__FILE__,__LINE__,__FUNCTION__,CinternalLogTypeCompleteLogging,CinternalLogCategoryInfo,__VA_ARGS__)
#define CInternalLogDebug(...)		            CinternalLoggerMakeLog(0,"debug",__FILE__,__LINE__,__FUNCTION__,CinternalLogTypeCompleteLoggingWithPlaceAndFunc,CinternalLogCategoryDebug,__VA_ARGS__)
#define CInternalLogDebugLogLvl(_logLevel,...)  CinternalLoggerMakeLog(_logLevel,"debug",__FILE__,__LINE__,__FUNCTION__,CinternalLogTypeCompleteLoggingWithPlaceAndFunc,CinternalLogCategoryDebug,__VA_ARGS__)


#define CinternalLoggerMakeLogOnlyText(_logLevel,...)   CinternalLoggerMakeLog(_logLevel,"","",0,"",CinternalLogTypeMainText,CinternalLogCategoryNone,__VA_ARGS__)

CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_LOGGER_H
