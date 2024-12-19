//
// repo:            cinternal
// file:            wrapper.h
// path:			include/cinternal/wrapper.h
// created on:		2024 Dec 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_WRAPPER_H
#define CINTERNAL_INCLUDE_CINTERNAL_WRAPPER_H

#include <cinternal/internal_header.h>


#ifdef _MSC_VER
#define CinternalWrapperCtime_s(_timep,_buffer,_numberOfElements)   ctime_s(_buffer,_numberOfElements,_timep)
#define CinternalWrapperSnprintf(_buffer,_count,...)                _snprintf_s(_buffer,_count, _count,__VA_ARGS__)
#define CinternalWrapperVsnprintf(_buffer,_count,_format,_argptr)   vsnprintf_s(_buffer,_count,_count,_format,_argptr)
#define CinternalWrapperMemcpy(_dest,_src,_count)                   memcpy_s(_dest,_count,_src,_count)
#define CinternalWrapperStrdup                                      _strdup
#else
#define CinternalWrapperCtime_s(_timep,_buffer,_numberOfElements)   CPPUTILS_STATIC_CAST(void,_numberOfElements);ctime_r(_timep,_buffer)
#define CinternalWrapperSnprintf                                    snprintf
#define CinternalWrapperVsnprintf                                   vsnprintf
#define CinternalWrapperMemcpy                                      memcpy
#define CinternalWrapperStrdup                                      strdup
#endif


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_WRAPPER_H
