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


CPPUTILS_BEGIN_C

#define CinternalLogIntToEnum(_int)                 CPPUTILS_STATIC_CAST(enum CinternalLogType,_int)
#define CinternalLogEnumToInt(_enum)                CPPUTILS_STATIC_CAST(unsigned int,_enum)
#define CINTERNALLOGGER_TIME_BUFF_MIN_SIZE          256

struct CinternalLoggerItem;

enum CinternalLogType { 
    CinternalLogTypeNone = 0, 
    CinternalLogTypeTime = 1, 
    CinternalLogTypeFileAndLine = 2,
    CinternalLogTypeMainText = 4,
    CinternalLogTypeEnding = 8, 
    CinternalLogTypeStart = CinternalLogIntToEnum(CinternalLogEnumToInt(CinternalLogTypeTime) | CinternalLogEnumToInt(CinternalLogTypeFileAndLine)),
    CinternalLogTypeStartAndText = CinternalLogIntToEnum(CinternalLogEnumToInt(CinternalLogTypeStart) | CinternalLogEnumToInt(CinternalLogTypeMainText)),
    CinternalLogTypeCompleteLogging = CinternalLogIntToEnum(CinternalLogEnumToInt(CinternalLogTypeStartAndText) | CinternalLogEnumToInt(CinternalLogTypeEnding))
};

enum CinternalLogCategory {
    CinternalLogCategoryNone,
    CinternalLogCategoryError,
    CinternalLogCategoryWarning,
    CinternalLogCategoryInfo,
    CinternalLogCategoryDebug
};


typedef int (*TypeCinternalLogger)(void* a_userData, enum CinternalLogType a_type, enum CinternalLogCategory a_category, const char* a_textToLog);
typedef int (*TypeCinternalLoggerIterator)(void* a_userData, struct CinternalLoggerItem* CPPUTILS_ARG_NN);  // ret != 0 stops iteration

struct CinternalLoggerItem {
    TypeCinternalLogger     fnc;
    void*                   userData;
};


CINTERNAL_EXPORT const char* CinternalLoggerCreateTimeLog(char* CPPUTILS_ARG_NN a_pEnoughBigBuffer) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT struct CinternalLoggerItem* CinternalLoggerAddLogger(TypeCinternalLogger a_fnc, void* a_userData) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT struct CinternalLoggerItem* CinternalLoggerAddDefaultLogger(void) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CinternalLoggerRemoveLogger(struct CinternalLoggerItem* a_logger) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CinternalLoggerCleanAllLoggers(void) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CinternalLoggerIterateOverAllLoggers(TypeCinternalLoggerIterator CPPUTILS_ARG_NN a_iterator, void* a_clbkData) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CinternalLoggerSetCurrentLogLevel(int a_newLogLevel) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT int  CinternalLoggerGetCurrentLogLevel(void) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CinternalLoggerSetCurrentFilesDeepness(int a_filesDeepness) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT int  CinternalLoggerGetCurrentFilesDeepness(void) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CinternalLoggerMakeLog(int a_logLevel, const char* CPPUTILS_ARG_NN a_file, int a_line, 
                                             enum CinternalLogType a_type, enum CinternalLogCategory a_category, const char* CPPUTILS_ARG_NN a_fmtStr, ...) CPPUTILS_NOEXCEPT;


#define CInternalLogError(...)		            CinternalLoggerMakeLog(0,__FILE__,__LINE__,CinternalLogCategoryError,__VA_ARGS__)
#define CInternalLogWarning(...)	            CinternalLoggerMakeLog(0,__FILE__,__LINE__,CinternalLogCategoryWarning,__VA_ARGS__)
#define CInternalLogInfo(...)		            CinternalLoggerMakeLog(0,__FILE__,__LINE__,CinternalLogCategoryInfo,__VA_ARGS__)
#define CInternalLogDebug(...)		            CinternalLoggerMakeLog(0,__FILE__,__LINE__,CinternalLogCategoryDebug,__VA_ARGS__)
#define CInternalLogDebugLogLvl(_logLevel,...)  CinternalLoggerMakeLog(_logLevel,__FILE__,__LINE__,CinternalLogCategoryDebug,__VA_ARGS__)


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_LOGGER_H
