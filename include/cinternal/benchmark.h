//
// repo:			cinternal
// file:            benchmark.h
// path:			include/cinternal/benchmark.h
// created on:		2023 Jul 26
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_BENCHMARK_H
#define CINTERNAL_INCLUDE_CINTERNAL_BENCHMARK_H

#include <cinternal/internal_header.h>
#define cinternal_gettimeofday_needed
#include <cinternal/time.h>


CPPUTILS_BEGIN_C


#define CINTERNAL_BENCHMARK_DECL(_nm)	struct timeval	__benchmark_st_time_ ## _nm, __benchmark_end_time_ ## _nm, __benchmark_time_diff_ ## _nm
#define CINTERNAL_BENCHMARK_START(_nm)	cinternal_gettimeofday(&(__benchmark_st_time_ ## _nm),CPPUTILS_NULL)
#ifdef CINTERNAL_BENCHMARK_FIN_needed
#undef CINTERNAL_BENCHMARK_FIN_needed
static inline void CINTERNAL_BENCHMARK_FIN_inline(const struct timeval* a_pStart, struct timeval* a_pEnd, struct timeval* a_pDiff) CPPUTILS_NOEXCEPT {
	cinternal_gettimeofday(a_pEnd, CPPUTILS_NULL);
	if ((a_pEnd->tv_usec) >= (a_pStart->tv_usec)) {
		a_pDiff->tv_sec = a_pEnd->tv_sec - a_pStart->tv_sec;
		a_pDiff->tv_usec = a_pEnd->tv_usec - a_pStart->tv_usec;
	}
	else {
		--(a_pEnd->tv_sec);
		a_pEnd->tv_usec += 1000000;
		a_pDiff->tv_sec = a_pEnd->tv_sec - a_pStart->tv_sec;
		a_pDiff->tv_usec = a_pEnd->tv_usec - a_pStart->tv_usec;
	}
}
#endif  //  #ifdef CINTERNAL_BENCHMARK_FIN_needed
#define CINTERNAL_BENCHMARK_FIN(_nm)			CINTERNAL_BENCHMARK_FIN_inline(&(__benchmark_st_time_ ## _nm), &(__benchmark_end_time_ ## _nm), &(__benchmark_time_diff_ ## _nm))
#define CINTERNAL_BENCHMARK_TIME_DIFF(_nm)		(__benchmark_time_diff_ ## _nm)
#define CINTERNAL_BENCHMARK_ST_TIME(_nm)		(__benchmark_st_time_ ## _nm)
#define CINTERNAL_BENCHMARK_END_TIME(_nm)		(__benchmark_end_time_ ## _nm)
#define CINTERNAL_BENCHMARK_SECS_DBL_RAW(_timeval)	\
	( CPPUTILS_STATIC_CAST(double,(_timeval).tv_sec) + (CPPUTILS_STATIC_CAST(double,(_timeval).tv_usec)/1000000.) )
#define CINTERNAL_BENCHMARK_TIME_DIFF_SECS_DBL(_nm)	CINTERNAL_BENCHMARK_SECS_DBL_RAW(__benchmark_time_diff_ ## _nm)

CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_BENCHMARK_H
