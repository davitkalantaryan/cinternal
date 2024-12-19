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

#define CPPUTILS_VAR_MACRO_A1(_macro,_op,_x)			_macro(_x)
#define CPPUTILS_VAR_MACRO_A2(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A1 (_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A3(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A2 (_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A4(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A3 (_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A5(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A4 (_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A6(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A5 (_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A7(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A6 (_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A8(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A7 (_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A9(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A8 (_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A10(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A9 (_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A11(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A10(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A12(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A11(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A13(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A12(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A14(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A13(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A15(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A14(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A16(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A15(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A17(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A16(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A18(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A17(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A19(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A18(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A20(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A19(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A21(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A20(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A22(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A21(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A23(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A22(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A24(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A23(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A25(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A24(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A26(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A25(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A27(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A26(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A28(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A27(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A29(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A28(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A30(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A29(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A31(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A30(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A32(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A31(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A33(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A32(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A34(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A33(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A35(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A34(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A36(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A35(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A37(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A36(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A38(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A37(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A39(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A38(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A40(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A39(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A41(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A40(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A42(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A41(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A43(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A42(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A44(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A43(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A45(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A44(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A46(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A45(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A47(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A46(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A48(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A47(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A49(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A48(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A50(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A49(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A51(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A50(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A52(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A51(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A53(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A52(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A54(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A53(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A55(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A54(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A56(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A55(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A57(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A56(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A58(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A57(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A59(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A58(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A60(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A59(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A61(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A60(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A62(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A61(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A63(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A62(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A64(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A63(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A65(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A64(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A66(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A65(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A67(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A66(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A68(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A67(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A69(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A68(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A70(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A69(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A71(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A70(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A72(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A71(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A73(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A72(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A74(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A73(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A75(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A74(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A76(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A75(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A77(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A76(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A78(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A77(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A79(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A78(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A80(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A79(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A81(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A80(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A82(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A81(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A83(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A82(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A84(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A83(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A85(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A84(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A86(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A85(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A87(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A86(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A88(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A87(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A89(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A88(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A90(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A89(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A91(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A90(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A92(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A91(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A93(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A92(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A94(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A93(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A95(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A94(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A96(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A95(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A97(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A96(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A98(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A97(_macro,CPPUTILS_ID(_op),__VA_ARGS__))
#define CPPUTILS_VAR_MACRO_A99(_macro,_op,_x,...)		_macro(_x) CPPUTILS_ID(_op) CPPUTILS_ID(CPPUTILS_VAR_MACRO_A98(_macro,CPPUTILS_ID(_op),__VA_ARGS__))


#define CPPUTILS_VAR_MACRO_COUNT(_count)			CPPUTILS_VAR_MACRO_A ## _count
#define CPPUTILS_VAR_MACRO_APPLY_IMPL(_macro, ...)	CPPUTILS_ID(_macro(__VA_ARGS__))

#define CPPUTILS_VAR_MACRO_APPY(_macro,_op, ...) \
    CPPUTILS_ID( \
        CPPUTILS_VAR_MACRO_APPLY_IMPL( \
            CPPUTILS_VAR_MACRO_COUNT, \
            CPPUTILS_NARGS(__VA_ARGS__)) \
			(_macro,CPPUTILS_ID(_op),__VA_ARGS__))



#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_VARIADIC_MACROSES_H
