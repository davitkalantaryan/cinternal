//
// repo:            cinternal
// file:			cinternal_core_typeinfo.c
// path:			src/core/cinternal_core_typeinfo.c
// created on:		2023 Mar 30
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cinternal/typeinfo.h>
#include <cinternal/wrapper.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C


struct CInternalTypeinfoEnumParseItem {
    char*                   name;
    int                     value;
    int                     reserved01;
};


struct CInternalTypeinfoEnumNames {
    char**                  pNames;
    size_t                  tableSize;
    int                     minVal;
    int                     maxVal;
};


static inline int CInternalTypeinfoEnumParseSingleInliine(int a_defaultValue, const char* CPPUTILS_ARG_NN a_input, struct CInternalTypeinfoEnumParseItem* CPPUTILS_ARG_NN a_pItem) CPPUTILS_NOEXCEPT  {
    const char* pcTerm = strchr(a_input, '=');
    if (pcTerm) {
        const size_t tokenLen = (size_t)(pcTerm - a_input);
        a_pItem->name = (char*)malloc(tokenLen + 1);
        if (!(a_pItem->name)) {
            return 1;
        }
        CinternalWrapperMemcpy(a_pItem->name, a_input, tokenLen);
        a_pItem->name[tokenLen] = 0;
        a_pItem->value = atoi(++pcTerm);
    }
    else {
        a_pItem->name = CinternalWrapperStrdup(a_input);
        if (!(a_pItem->name)) {
            return 1;
        }
        a_pItem->value = a_defaultValue;
    }
    return 0;
}


static inline void CInternalTypeinfoEnumCleanInputDataInline(struct CInternalTypeinfoEnumParseItem* CPPUTILS_ARG_NN a_pInputData, int a_count) CPPUTILS_NOEXCEPT  {
    int j;
    for (j = 0; j < a_count; ++j) {
        free(a_pInputData[j].name);
    }  //  for (j = 0; j < i; ++j) {
    free(a_pInputData);
}


CINTERNAL_EXPORT struct CInternalTypeinfoEnumNames* CInternalTypeinfoCreateEnumNames(int a_number, ...) CPPUTILS_NOEXCEPT
{
    const char* nextArg;
    int i, minVal=0, maxVal = 0, defaultValue=0;
    size_t index;
    va_list argList;
    struct CInternalTypeinfoEnumNames* pRetStr;
    struct CInternalTypeinfoEnumParseItem* pInputData;

    pInputData = (struct CInternalTypeinfoEnumParseItem*)calloc((size_t)a_number, sizeof(struct CInternalTypeinfoEnumParseItem));
    if (!pInputData) {
        return CPPUTILS_NULL;
    }

    va_start(argList, a_number);
    for (i=0; i < a_number; ++i) {
        nextArg = va_arg(argList, const char*);
        if (CInternalTypeinfoEnumParseSingleInliine(defaultValue, nextArg, &pInputData[i])) {
            CInternalTypeinfoEnumCleanInputDataInline(pInputData,i);
            va_end(argList);
            return CPPUTILS_NULL;
        }  //  if (CInternalTypeinfoEnumParseSingleInliine(defaultValue, nextArg, &pInputData[i])) {
        if (pInputData[i].value > maxVal) {
            maxVal = pInputData[i].value;
        }
        if (pInputData[i].value < minVal) {
            minVal = pInputData[i].value;
        }
    }  //  for (i=0; i < a_number; ++i) {
    va_end(argList);

    pRetStr = (struct CInternalTypeinfoEnumNames*)calloc(1, sizeof(struct CInternalTypeinfoEnumNames));
    if (!pRetStr) {
        CInternalTypeinfoEnumCleanInputDataInline(pInputData, a_number);
        return CPPUTILS_NULL;
    }

    pRetStr->minVal = minVal;
    pRetStr->maxVal = maxVal;
    pRetStr->tableSize = (size_t)(maxVal - minVal);
    pRetStr->pNames = (char**)calloc(pRetStr->tableSize, sizeof(char*));
    if (!(pRetStr->pNames)) {
        CInternalTypeinfoEnumCleanInputDataInline(pInputData, a_number);
        free(pRetStr);
        return CPPUTILS_NULL;
    }

    for (i = 0; i < a_number; ++i) {
        index = (size_t)((pInputData[i].value)-minVal);
        assert(index < (pRetStr->tableSize));
        if (pRetStr->pNames[index]) {
            free(pRetStr->pNames[index]);
        }
        pRetStr->pNames[index] = pInputData[i].name;
        pInputData[i].name = CPPUTILS_NULL;
    }  //  for (i = 0; i < a_number; ++i) {

    CInternalTypeinfoEnumCleanInputDataInline(pInputData, a_number);

    return pRetStr;

}


CINTERNAL_EXPORT struct CInternalTypeinfoStructNames* CInternalTypeinfoCreateStructNames(int a_number, ...) CPPUTILS_NOEXCEPT
{
    (void)a_number;
    return CPPUTILS_NULL;
}

CPPUTILS_END_C
