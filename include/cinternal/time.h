//
// repo:			cinternal
// file:            time.h
// path:			include/cinternal/time.h
// created on:		2023 Jul 26
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_TIME_H
#define CINTERNAL_INCLUDE_CINTERNAL_TIME_H

#include <cinternal/internal_header.h>
#include <cinternal/disable_compiler_warnings.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#else
#include <sys/time.h>
#endif
#include <time.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define CINTERNAL_DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define CINTERNAL_DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif


#ifdef _WIN32

#if !defined(_MSC_VER) || (_MSC_VER>=1400)
#define CINTERNAL_WIN_TZ_NEW_VERSION	1
#endif

#ifndef cinternal_timezone_defined
#define cinternal_timezone_defined
struct timezone{
	int tz_minuteswest;		/* Minutes west of GMT.  */
	int tz_dsttime;		/* Nonzero if DST is ever in effect.  */
};
#endif

#ifdef cinternal_gettimeofday_needed
#undef cinternal_gettimeofday_needed
static inline int cinternal_gettimeofday_inline(struct timeval* a_tv, struct timezone* a_tz) CPPUTILS_NOEXCEPT
{
	static void* spPointer = NULL;
	unsigned __int64 tmpres = 0;
#ifdef CINTERNAL_WIN_TZ_NEW_VERSION
	long lnTzTemp;
	int nldTemp;
#endif

	if (a_tv){
		FILETIME ft;
		GetSystemTimeAsFileTime(&ft);

		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;

		tmpres /= 10;  /*convert into microseconds*/
		/*converting file time to unix epoch*/
		tmpres -= CINTERNAL_DELTA_EPOCH_IN_MICROSECS;
		a_tv->tv_sec = (long)(tmpres / 1000000UL);
		a_tv->tv_usec = (long)(tmpres % 1000000UL);
	}

	if (a_tz){
		// (setting timezone environmental variable) once
		if (InterlockedCompareExchangePointer(&spPointer, (void*)1, NULL) == NULL){
			_tzset();
		}

#ifdef CINTERNAL_WIN_TZ_NEW_VERSION
		_get_timezone(&lnTzTemp);
		a_tz->tz_minuteswest = lnTzTemp / 60;
		_get_daylight(&nldTemp);
		a_tz->tz_dsttime = nldTemp;
#else
		a_tz->tz_minuteswest = _timezone / 60;
		a_tz->tz_dsttime = _daylight;
#endif
	}

	return 0;
}
#endif  //  #ifdef cinternal_gettimeofday_needed
#define		cinternal_gettimeofday	cinternal_gettimeofday_inline

#else   //  #ifdef _WIN32

#define		cinternal_gettimeofday	gettimeofday

#endif  // #ifdef _WIN32


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_TIME_H
