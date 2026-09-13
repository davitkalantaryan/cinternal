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
#include <signal.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#define CinternalInterruptArgType1                                  ULONG_PTR
#define CinternalSignalForNetworkingFailedPipe                      SIGSEGV
#define CinternalSignalToSendUsr1                                   1980
#define CinternalSignalToSendUsr2                                   1981
#define CinternalSleepInterruptableMs(_x)                           SleepEx(CPPUTILS_STATIC_CAST(DWORD,_x),TRUE)
#define CinternalInterruptThread(_thrHandle,_signal,_intrptFnc)     QueueUserAPC((_intrptFnc),(HANDLE)(_thrHandle),(ULONG_PTR)(_signal))
#else
#include <unistd.h>
#include <pthread.h>
#define CinternalInterruptArgType1                                  int
#define CinternalSignalForNetworkingFailedPipe                      SIGPIPE
#define CinternalSignalToSendUsr1                                   SIGUSR1
#define CinternalSignalToSendUsr2                                   SIGUSR2
#define CinternalSleepInterruptableMs(_x)                           sleep(CPPUTILS_STATIC_CAST(unsigned int,(_x)/1000));usleep(CPPUTILS_STATIC_CAST(useconds_t,1000*((_x)%1000)))
#define CinternalInterruptThread(_thrHandle,_signal,_intrptFnc)     (void)(_intrptFnc);pthread_kill((pthread_t)(_thrHandle),(_signal))
#endif
#include <cinternal/undisable_compiler_warnings.h>

typedef void (*CinternalSimpleSignalHandlerPointer)(int);

#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_SIGNALS_H
