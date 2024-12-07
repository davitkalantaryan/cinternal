//
// repo:            cinternal
// file:            signals.h
// path:			include/cinternal/signals.h
// created on:		2024 Dec 07
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_SIGNALS_H
#define CINTERNAL_INCLUDE_CINTERNAL_SIGNALS_H

#include <cinternal/internal_header.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdint.h>

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#define CinternalSleepInterruptableMs(_x)     SleepEx(CPPUTILS_STATIC_CAST(DWORD,_x),TRUE)
#else
#include <unistd.h>
#define CinternalSleepInterruptableMs(_x)     usleep(CPPUTILS_STATIC_CAST(useconds_t,1000*(_x)))
#endif
#include <cinternal/undisable_compiler_warnings.h>


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_SIGNALS_H
