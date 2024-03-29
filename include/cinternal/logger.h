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
#include <stdarg.h>
#include <stdbool.h>


CPPUTILS_BEGIN_C

enum CinternalLogTypes { CinternalLogTypeError, CinternalLogTypeWarning, CinternalLogTypeInfo, CinternalLogTypeDebug };
typedef int (*TypeCinternalLogger)(void* a_userData, enum CinternalLogTypes a_type, bool a_bSync, const char* a_fmtStr, va_list alist);

#ifndef CPPUTILS_CONDITIONAL_WEAKNESS
#define CPPUTILS_CONDITIONAL_WEAKNESS		CPPUTILS_ONLY_GCCLIKE_ATTR_STRONG
#endif
CPPUTILS_CONDITIONAL_WEAKNESS int CinternalDefaultLoggerFunction(void* a_userData, enum CinternalLogTypes a_type, bool a_bSync, const char* a_fmtStr, va_list a_argptr);

CINTERNAL_EXPORT void CinternalInstallLogger(void* a_userData, TypeCinternalLogger a_clbk);
CINTERNAL_EXPORT void CinternalGetLogger(void** a_pUserData, TypeCinternalLogger* a_pClbk);
CINTERNAL_EXPORT void CinternalMakeLog(const char* a_src, int a_line, enum CinternalLogTypes a_type, const char* a_fmtStr, ...);
CINTERNAL_EXPORT int  CinternalMakeLogNoExtraData(enum CinternalLogTypes a_type, bool a_bSync, const char* a_fmtStr, ...);
CINTERNAL_EXPORT void CinternalLogPrintDateAndTime(enum CinternalLogTypes a_type, bool a_bSync);


#define CInternalLogError(...)		CinternalMakeLog(__FILE__,__LINE__,CinternalLogTypeError,__VA_ARGS__)
#define CInternalLogWarning(...)	CinternalMakeLog(__FILE__,__LINE__,CinternalLogTypeWarning,__VA_ARGS__)
#define CInternalLogInfo(...)		CinternalMakeLog(__FILE__,__LINE__,CinternalLogTypeInfo,__VA_ARGS__)
#if defined(NDEBUG) || defined(CUTILS_NO_DEBUG_LOGS)
#define CInternalLogDebug(...)
#else
#define CInternalLogDebug(...)		CinternalMakeLog(__FILE__,__LINE__,CinternalLogTypeDebug,__VA_ARGS__)
#endif


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_LOGGER_H
