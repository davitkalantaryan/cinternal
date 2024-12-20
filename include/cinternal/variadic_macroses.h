//
// repo:            cinternal
// file:			macroses03.h
// path:			include/cinternal/macroses03.h
// created on:		2021 Apr 11
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_VARIADIC_MACROSES_H
#define CINTERNAL_INCLUDE_CINTERNAL_VARIADIC_MACROSES_H

#include <cinternal/internal_header.h>
#include <cinternal/macroses.h>

#define CPPUTILS_VAR_MACRO_A01(_macro01,_macro02,_op,_x)			_macro01(_x)
#define CPPUTILS_VAR_MACRO_A02(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A01(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A03(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A02(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A04(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A03(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A05(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A04(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A06(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A05(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A07(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A06(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A08(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A07(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A09(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A08(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A10(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A09(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A11(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A10(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A12(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A11(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A13(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A12(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A14(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A13(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A15(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A14(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A16(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A15(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A17(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A16(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A18(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A17(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A19(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A18(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A20(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A19(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A21(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A20(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A22(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A21(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A23(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A22(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A24(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A23(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A25(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A24(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A26(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A25(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A27(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A26(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A28(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A27(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A29(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A28(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A30(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A29(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A31(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A30(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A32(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A31(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A33(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A32(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A34(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A33(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A35(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A34(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A36(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A35(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A37(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A36(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A38(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A37(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A39(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A38(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A40(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A39(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A41(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A40(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A42(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A41(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A43(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A42(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A44(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A43(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A45(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A44(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A46(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A45(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A47(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A46(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A48(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A47(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A49(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A48(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A50(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A49(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A51(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A50(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A52(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A51(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A53(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A52(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A54(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A53(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A55(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A54(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A56(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A55(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A57(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A56(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A58(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A57(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A59(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A58(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A60(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A59(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A61(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A60(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A62(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A61(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A63(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A62(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A64(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A63(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A65(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A64(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A66(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A65(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A67(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A66(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A68(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A67(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A69(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A68(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A70(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A69(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A71(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A70(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A72(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A71(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A73(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A72(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A74(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A73(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A75(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A74(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A76(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A75(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A77(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A76(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A78(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A77(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A79(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A78(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A80(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A79(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A81(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A80(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A82(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A81(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A83(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A82(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A84(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A83(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A85(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A84(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A86(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A85(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A87(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A86(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A88(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A87(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A89(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A88(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A90(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A89(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A91(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A90(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A92(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A91(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A93(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A92(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A94(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A93(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A95(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A94(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A96(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A95(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A97(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A96(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A98(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A97(_macro01,_macro02,_op,__VA_ARGS__)),_op)
#define CPPUTILS_VAR_MACRO_A99(_macro01,_macro02,_op,_x,...)		_macro02(_macro01(_x),CPPUTILS_ID(CPPUTILS_VAR_MACRO_A98(_macro01,_macro02,_op,__VA_ARGS__)),_op)


#define CPPUTILS_VAR_MACRO_COUNT(_count)			        CPPUTILS_VAR_MACRO_A ## _count
#define CPPUTILS_VAR_MACRO_APPLY_IMPL(_macroAnyMacro, ...)	CPPUTILS_ID(_macroAnyMacro(__VA_ARGS__))

#define CPPUTILS_VAR_MACRO_APPY_GEN(_macro01,_macro02,_op, ...) \
    CPPUTILS_ID( \
        CPPUTILS_VAR_MACRO_APPLY_IMPL( \
            CPPUTILS_VAR_MACRO_COUNT, \
            CPPUTILS_NARGS(__VA_ARGS__)) \
			(CPPUTILS_ID(_macro01),CPPUTILS_ID(_macro02),CPPUTILS_ID(_op),__VA_ARGS__))


#define CPPUTILS_VAR_MACRO_HELPER01(_x1,_x2,_op)            CPPUTILS_ID(_x1) CPPUTILS_ID(_op) CPPUTILS_ID(_x2)
#define CPPUTILS_VAR_MACRO_APPY_OP(_macro01,_op, ...)       CPPUTILS_VAR_MACRO_APPY_GEN(CPPUTILS_ID(_macro01),CPPUTILS_VAR_MACRO_HELPER01,_op,__VA_ARGS__)

#define CPPUTILS_VAR_MACRO_HELPER02(_x1,_x2,_op)            CPPUTILS_ID(_x1) , CPPUTILS_ID(_x2)
#define CPPUTILS_VAR_MACRO_APPY_COMMA(_macro01, ...)        CPPUTILS_VAR_MACRO_APPY_GEN(CPPUTILS_ID(_macro01),CPPUTILS_VAR_MACRO_HELPER02, ,__VA_ARGS__)



#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_VARIADIC_MACROSES_H
