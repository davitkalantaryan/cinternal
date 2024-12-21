//
// repo:            cinternal
// file:			macroses03.h
// path:			include/cinternal/macroses03.h
// created on:		2021 Apr 11
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_MACROSES_VARIADIC_H
#define CINTERNAL_INCLUDE_CINTERNAL_MACROSES_VARIADIC_H

#include <cinternal/internal_header.h>
#include <cinternal/macroses_base.h>


#define CPPUTILS_NARGS_IMPL(_1,   _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9		\
		,_10, _11, _12, _13, _14, _15, _16, _17, _18, _19					\
		,_20, _21, _22, _23, _24, _25, _26, _27, _28, _29					\
		,_30, _31, _32, _33, _34, _35, _36, _37, _38, _39					\
		,_40, _41, _42, _43, _44, _45, _46, _47, _48, _49					\
		,_50, _51, _52, _53, _54, _55, _56, _57, _58, _59					\
		,_60, _61, _62, _63, _64, _65, _66, _67, _68, _69					\
		,_70, _71, _72, _73, _74, _75, _76, _77, _78, _79					\
		,_80, _81, _82, _83, _84, _85, _86, _87, _88, _89					\
		,_90, _91, _92, _93, _94, _95, _96, _97, _98, _99, N, ...			\
	) N


#define CPPUTILS_NARGS(...) CPPUTILS_ID( CPPUTILS_NARGS_IMPL(__VA_ARGS__,	\
		99, 98, 97, 96, 95, 94, 93, 92, 91, 90,								\
		89, 88, 87, 86, 85, 84, 83, 82, 81, 80,								\
		79, 78, 77, 76, 75, 74, 73, 72, 71, 70,								\
		69, 68, 67, 66, 65, 64, 63, 62, 61, 60,								\
		59, 58, 57, 56, 55, 54, 53, 52, 51, 50,								\
		49, 48, 47, 46, 45, 44, 43, 42, 41, 40,								\
		39, 38, 37, 36, 35, 34, 33, 32, 31, 30,								\
		29, 28, 27, 26, 25, 24, 23, 22, 21, 20,								\
		19, 18, 17, 16, 15, 14, 13, 12, 11, 10,								\
		 9,  8,  7,  6,  5,  4,  3,  2,  1									\
	))


#define CPPUTILS_VAR_MACRO_A1(_macrou,_macrob,_uop,_bop,_x)		    _macrou(_uop,_x)
#define CPPUTILS_VAR_MACRO_A2(_macrou,_macrob,_uop,_bop,_x,...)	    _macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A1(_macrou,_macrob,_uop,_bop,__VA_ARGS__)))
#define CPPUTILS_VAR_MACRO_A3(_macrou,_macrob,_uop,_bop,_x,...)	    _macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A2(_macrou,_macrob,_uop,_bop,__VA_ARGS__)))
#define CPPUTILS_VAR_MACRO_A4(_macrou,_macrob,_uop,_bop,_x,...)	    _macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A3(_macrou,_macrob,_uop,_bop,__VA_ARGS__)))
#define CPPUTILS_VAR_MACRO_A5(_macrou,_macrob,_uop,_bop,_x,...)	    _macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A4(_macrou,_macrob,_uop,_bop,__VA_ARGS__)))
#define CPPUTILS_VAR_MACRO_A6(_macrou,_macrob,_uop,_bop,_x,...)	    _macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A5(_macrou,_macrob,_uop,_bop,__VA_ARGS__)))
#define CPPUTILS_VAR_MACRO_A7(_macrou,_macrob,_uop,_bop,_x,...)	    _macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A6(_macrou,_macrob,_uop,_bop,__VA_ARGS__)))
#define CPPUTILS_VAR_MACRO_A8(_macrou,_macrob,_uop,_bop,_x,...)	    _macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A7(_macrou,_macrob,_uop,_bop,__VA_ARGS__)))
#define CPPUTILS_VAR_MACRO_A9(_macrou,_macrob,_uop,_bop,_x,...)	    _macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A8(_macrou,_macrob,_uop,_bop,__VA_ARGS__)))
#define CPPUTILS_VAR_MACRO_A10(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A9(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A11(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A10(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A12(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A11(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A13(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A12(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A14(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A13(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A15(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A14(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A16(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A15(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A17(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A16(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A18(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A17(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A19(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A18(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A20(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A19(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A21(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A20(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A22(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A21(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A23(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A22(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A24(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A23(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A25(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A24(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A26(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A25(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A27(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A26(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A28(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A27(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A29(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A28(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A30(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A29(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A31(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A30(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A32(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A31(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A33(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A32(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A34(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A33(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A35(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A34(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A36(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A35(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A37(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A36(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A38(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A37(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A39(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A38(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A40(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A39(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A41(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A40(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A42(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A41(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A43(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A42(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A44(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A43(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A45(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A44(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A46(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A45(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A47(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A46(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A48(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A47(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A49(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A48(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A50(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A49(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A51(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A50(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A52(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A51(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A53(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A52(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A54(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A53(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A55(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A54(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A56(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A55(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A57(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A56(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A58(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A57(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A59(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A58(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A60(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A59(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A61(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A60(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A62(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A61(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A63(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A62(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A64(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A63(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A65(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A64(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A66(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A65(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A67(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A66(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A68(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A67(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A69(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A68(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A70(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A69(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A71(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A70(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A72(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A71(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A73(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A72(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A74(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A73(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A75(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A74(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A76(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A75(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A77(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A76(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A78(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A77(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A79(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A78(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A80(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A79(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A81(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A80(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A82(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A81(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A83(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A82(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A84(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A83(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A85(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A84(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A86(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A85(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A87(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A86(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A88(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A87(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A89(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A88(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A90(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A89(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A91(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A90(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A92(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A91(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A93(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A92(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A94(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A93(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A95(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A94(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A96(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A95(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A97(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A96(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A98(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A97(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)
#define CPPUTILS_VAR_MACRO_A99(_macrou,_macrob,_uop,_bop,_x,...)		_macrob(_macrou(_uop,_x),_bop,CPPUTILS_ID(CPPUTILS_VAR_MACRO_A98(_macrou,_macrob,_uop,_bop,__VA_ARGS__)),_bop)


#define CPPUTILS_VAR_MACRO_COUNT(_count)			        CPPUTILS_VAR_MACRO_A ## _count


#define CPPUTILS_VAR_MACRO_APPY_GEN_GEN(_macro01,_macro02,_uop,_bop, ...) \
    CPPUTILS_ID( \
        CPPUTILS_VAR_MACRO_APPLY_IMPL( \
            CPPUTILS_VAR_MACRO_COUNT, \
            CPPUTILS_NARGS(__VA_ARGS__)) \
			(CPPUTILS_ID(_macro01),CPPUTILS_ID(_macro02),CPPUTILS_ID(_uop),CPPUTILS_ID(_bop),__VA_ARGS__))

#define CPPUTILS_VAR_MACRO_HELPER01a(_macro01a,_x)            CPPUTILS_VAR_MACRO_APPLY_IMPL(CPPUTILS_ID(_macro01a),_x)
#define CPPUTILS_VAR_MACRO_APPY_GEN(_macro01,_macro02,_bop, ...) CPPUTILS_VAR_MACRO_APPY_GEN_GEN(CPPUTILS_VAR_MACRO_HELPER01a,_macro02,_macro01,_bop,__VA_ARGS__)


#define CPPUTILS_VAR_MACRO_HELPER01(_x1,_bop,_x2)            CPPUTILS_ID(_x1) CPPUTILS_ID(_bop) CPPUTILS_ID(_x2)
#define CPPUTILS_VAR_MACRO_APPY_OP(_macro01,_bop, ...)       CPPUTILS_VAR_MACRO_APPY_GEN(CPPUTILS_ID(_macro01),CPPUTILS_VAR_MACRO_HELPER01,_bop,__VA_ARGS__)

#define CPPUTILS_VAR_MACRO_HELPER02(_x1,_bop,_x2)            CPPUTILS_ID(_x1) , CPPUTILS_ID(_x2)
#define CPPUTILS_VAR_MACRO_APPY_COMMA(_macro01, ...)         CPPUTILS_VAR_MACRO_APPY_GEN(CPPUTILS_ID(_macro01),CPPUTILS_VAR_MACRO_HELPER02, _macro01,__VA_ARGS__)



#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_MACROSES_VARIADIC_H
