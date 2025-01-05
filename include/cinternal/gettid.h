//
// repo:			cinternal
// file:            gettid.h
// path:			include/cinternal/gettid.h
// created on:		2024 Nov 28
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_GETTID_H
#define CINTERNAL_INCLUDE_CINTERNAL_GETTID_H

#include <cinternal/internal_header.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdint.h>
#include <cinternal/undisable_compiler_warnings.h>

#ifdef cinternal_gettid_needed

#include <cinternal/disable_compiler_warnings.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#define CinternalGetCurrentTid()     CPPUTILS_STATIC_CAST(int64_t,GetCurrentThreadId())
#elif defined(__APPLE__)
#include <pthread.h>
static inline int64_t CinternalGetCurrentTid(void) CPPUTILS_NOEXCEPT  {
    uint64_t ullnTid;
    pthread_threadid_np(pthread_self(),&ullnTid);
    return CPPUTILS_STATIC_CAST(int64_t,ullnTid);
}
#else
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#define CinternalGetCurrentTid()     CPPUTILS_STATIC_CAST(int64_t,syscall(SYS_gettid))
#endif
#include <cinternal/undisable_compiler_warnings.h>


#endif  //  #ifdef cinternal_gettid_needed


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_GETTID_H
