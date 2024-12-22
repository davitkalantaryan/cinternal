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

#define CINTERNAL_COLLECTION_RESIZE_STEP    1024


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

struct CInternalTypeinfoStructParseItem {
    CinternalConstCharPtr   name;
    size_t                  offset;
};


struct CInternalTypeinfoStructNames {
    CinternalConstCharPtr*  pNames;
    size_t                  tableSize;
};


struct CInternalTypeinfoCollectionEnumNames {
    struct CInternalTypeinfoEnumNames**     pNames;
    size_t                                  currentSize;
};


struct CInternalTypeinfoCollectionStructNames {
    struct CInternalTypeinfoStructNames**   pNames;
    size_t                                  currentSize;
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


static inline void CInternalTypeinfoCleanEnumNamesInline(struct CInternalTypeinfoEnumNames* a_enumNames) CPPUTILS_NOEXCEPT {
    if (a_enumNames) {
        size_t i;
        for (i = 0; i < a_enumNames->tableSize; ++i) {
            free(a_enumNames->pNames[i]);
        }  //  for (i = 0; i < a_number; ++i) {
        free(a_enumNames->pNames);
        free(a_enumNames);
    }  //  if (a_enumNames) {
}


static inline struct CInternalTypeinfoEnumNames* CInternalTypeinfoCreateEnumNamesInline(int a_number, va_list a_argList) CPPUTILS_NOEXCEPT {
    const char* nextArg;
    int i, minVal = 0, maxVal = 0, defaultValue = 0;
    size_t index;
    struct CInternalTypeinfoEnumNames* pRetStr;
    struct CInternalTypeinfoEnumParseItem* pInputData;

    pInputData = (struct CInternalTypeinfoEnumParseItem*)calloc((size_t)a_number, sizeof(struct CInternalTypeinfoEnumParseItem));
    if (!pInputData) {
        return CPPUTILS_NULL;
    }

    for (i = 0; i < a_number; ++i) {
        nextArg = va_arg(a_argList, const char*);
        if (CInternalTypeinfoEnumParseSingleInliine(defaultValue, nextArg, &pInputData[i])) {
            CInternalTypeinfoEnumCleanInputDataInline(pInputData, i);
            return CPPUTILS_NULL;
        }  //  if (CInternalTypeinfoEnumParseSingleInliine(defaultValue, nextArg, &pInputData[i])) {
        if (pInputData[i].value > maxVal) {
            maxVal = pInputData[i].value;
        }
        if (pInputData[i].value < minVal) {
            minVal = pInputData[i].value;
        }
    }  //  for (i=0; i < a_number; ++i) {

    pRetStr = (struct CInternalTypeinfoEnumNames*)calloc(1, sizeof(struct CInternalTypeinfoEnumNames));
    if (!pRetStr) {
        CInternalTypeinfoEnumCleanInputDataInline(pInputData, a_number);
        return CPPUTILS_NULL;
    }

    pRetStr->minVal = minVal;
    pRetStr->maxVal = maxVal;
    pRetStr->tableSize = (size_t)(maxVal - minVal + 1);
    pRetStr->pNames = (char**)calloc(pRetStr->tableSize, sizeof(char*));
    if (!(pRetStr->pNames)) {
        CInternalTypeinfoEnumCleanInputDataInline(pInputData, a_number);
        free(pRetStr);
        return CPPUTILS_NULL;
    }

    for (i = 0; i < a_number; ++i) {
        index = (size_t)((pInputData[i].value) - minVal);
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


static inline void CInternalTypeinfoCleanStructNamesInline(struct CInternalTypeinfoStructNames* a_structNames) CPPUTILS_NOEXCEPT {
    if (a_structNames) {
        free((char**)(a_structNames->pNames));
        free(a_structNames);
    }  //  if (a_structNames) {
}


static inline struct CInternalTypeinfoStructNames* CInternalTypeinfoCreateStructNamesInline(int a_number, va_list a_argList) CPPUTILS_NOEXCEPT {
    int i;
    size_t index;
    struct CInternalTypeinfoStructNames* pRetStr;
    struct CInternalTypeinfoStructParseItem* pInputData;
    size_t maxValue = 0;

    pInputData = (struct CInternalTypeinfoStructParseItem*)calloc((size_t)a_number, sizeof(struct CInternalTypeinfoStructParseItem));
    if (!pInputData) {
        return CPPUTILS_NULL;
    }

    for (i = 0; i < a_number; ++i) {
        pInputData[i].name = va_arg(a_argList, const char*);
    }  //  for (i=0; i < a_number; ++i) {
    for (i = 0; i < a_number; ++i) {
        pInputData[i].offset = (size_t)va_arg(a_argList, int);
        if ((pInputData[i].offset) > maxValue) {
            maxValue = pInputData[i].offset;
        }  //  if ((pInputData[i].offset) > maxValue) {
    }  //  for (i=0; i < a_number; ++i) {

    pRetStr = (struct CInternalTypeinfoStructNames*)calloc(1, sizeof(struct CInternalTypeinfoStructNames));
    if (!pRetStr) {
        free(pInputData);
        return CPPUTILS_NULL;
    }
    pRetStr->tableSize = (size_t)(maxValue + 1);
    pRetStr->pNames = (CinternalConstCharPtr*)calloc(pRetStr->tableSize, sizeof(CinternalConstCharPtr));
    if (!(pRetStr->pNames)) {
        free(pInputData);
        free(pRetStr);
        return CPPUTILS_NULL;
    }

    for (i = 0; i < a_number; ++i) {
        index = (size_t)(pInputData[i].offset);
        assert(index < (pRetStr->tableSize));
        pRetStr->pNames[index] = pInputData[i].name;
    }  //  for (i = 0; i < a_number; ++i) {

    free(pInputData);
    return pRetStr;
}


static inline const char* CInternalTypeinfoGetEnumNameInline(const struct CInternalTypeinfoEnumNames* CPPUTILS_ARG_NN a_enumNames, int a_value) CPPUTILS_NOEXCEPT {
    const size_t cunIndex = (size_t)(a_value - (a_enumNames->minVal));
    if ((a_value < (a_enumNames->minVal)) || (a_value > (a_enumNames->maxVal))) {
        return CINTERNAL_TYPEINFO_NAME_MEMORY_PROBLEM;
    }

    if (a_enumNames->pNames[cunIndex]) {
        return a_enumNames->pNames[cunIndex];
    }

    return CINTERNAL_TYPEINFO_NAME_NON_EXIST;
}



static inline const char* CInternalTypeinfoGetStructNameInline(const struct CInternalTypeinfoStructNames* CPPUTILS_ARG_NN a_structNames, size_t a_offset) CPPUTILS_NOEXCEPT {
    if (a_offset > (a_structNames->tableSize)) {
        return CINTERNAL_TYPEINFO_NAME_MEMORY_PROBLEM;
    }

    if (a_structNames->pNames[a_offset]) {
        return a_structNames->pNames[a_offset];
    }

    return CINTERNAL_TYPEINFO_NAME_NON_EXIST;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


CINTERNAL_EXPORT struct CInternalTypeinfoEnumNames* CInternalTypeinfoCreateEnumNames(int a_number, ...) CPPUTILS_NOEXCEPT
{
    va_list argList;
    struct CInternalTypeinfoEnumNames* pRetStr;
    va_start(argList, a_number);
    pRetStr = CInternalTypeinfoCreateEnumNamesInline(a_number, argList);
    va_end(argList);
    return pRetStr;
}


CINTERNAL_EXPORT void CInternalTypeinfoCleanEnumNames(struct CInternalTypeinfoEnumNames* a_enumNames) CPPUTILS_NOEXCEPT
{
    CInternalTypeinfoCleanEnumNamesInline(a_enumNames);
}


CINTERNAL_EXPORT struct CInternalTypeinfoStructNames* CInternalTypeinfoCreateStructNames(int a_number, ...) CPPUTILS_NOEXCEPT
{
    va_list argList;
    struct CInternalTypeinfoStructNames* pRetStr;
    va_start(argList, a_number);
    pRetStr = CInternalTypeinfoCreateStructNamesInline(a_number, argList);
    va_end(argList);
    return pRetStr;
}


CINTERNAL_EXPORT void CInternalTypeinfoCleanStructNames(struct CInternalTypeinfoStructNames* a_structNames) CPPUTILS_NOEXCEPT
{
    CInternalTypeinfoCleanStructNamesInline(a_structNames);
}


CINTERNAL_EXPORT const char* CInternalTypeinfoGetEnumName(const struct CInternalTypeinfoEnumNames* CPPUTILS_ARG_NN a_enumNames, int a_value) CPPUTILS_NOEXCEPT
{
    return CInternalTypeinfoGetEnumNameInline(a_enumNames, a_value);
}



CINTERNAL_EXPORT const char* CInternalTypeinfoGetStructName(const struct CInternalTypeinfoStructNames* CPPUTILS_ARG_NN a_structNames, size_t a_offset) CPPUTILS_NOEXCEPT
{
    return CInternalTypeinfoGetStructNameInline(a_structNames, a_offset);
}


CINTERNAL_EXPORT struct CInternalTypeinfoCollectionEnumNames* CInternalTypeinfoCreateCollectionEnumNames(void) CPPUTILS_NOEXCEPT
{
    struct CInternalTypeinfoCollectionEnumNames* const pRetStr = (struct CInternalTypeinfoCollectionEnumNames*)calloc(1, sizeof(struct CInternalTypeinfoCollectionEnumNames));
    return pRetStr;
}


CINTERNAL_EXPORT struct CInternalTypeinfoCollectionStructNames* CInternalTypeinfoCreateCollectionStructNames(void) CPPUTILS_NOEXCEPT
{
    struct CInternalTypeinfoCollectionStructNames* const pRetStr = (struct CInternalTypeinfoCollectionStructNames*)calloc(1, sizeof(struct CInternalTypeinfoCollectionStructNames));
    return pRetStr;
}


CINTERNAL_EXPORT void CInternalTypeinfoCleanCollectionEnumNames(struct CInternalTypeinfoCollectionEnumNames* a_collection) CPPUTILS_NOEXCEPT
{
    if (a_collection) {
        size_t i;
        for (i = 0; i < (a_collection->currentSize); ++i) {
            CInternalTypeinfoCleanEnumNamesInline(a_collection->pNames[i]);
        }  //  for (i = 0; i < (a_collection->currentSize); ++i) {
        free(a_collection);
    }  //  if (a_collection) {
}


CINTERNAL_EXPORT void CInternalTypeinfoCleanCollectionStructNames(struct CInternalTypeinfoCollectionStructNames* a_collection) CPPUTILS_NOEXCEPT
{
    if (a_collection) {
        size_t i;
        for (i = 0; i < (a_collection->currentSize); ++i) {
            CInternalTypeinfoCleanStructNamesInline(a_collection->pNames[i]);
        }  //  for (i = 0; i < (a_collection->currentSize); ++i) {
        free(a_collection);
    }  //  if (a_collection) {
}


CINTERNAL_EXPORT struct CInternalTypeinfoEnumNames* CInternalTypeinfoSetEnumNamesToCollection(struct CInternalTypeinfoCollectionEnumNames* CPPUTILS_ARG_NN a_collection, size_t a_index, int a_number, ...) CPPUTILS_NOEXCEPT
{
    va_list argList;
    struct CInternalTypeinfoEnumNames** pNamesTmp;
    size_t newSize;
    while (a_index >= (a_collection->currentSize)) {
        newSize = (a_collection->currentSize) + CINTERNAL_COLLECTION_RESIZE_STEP;
        pNamesTmp = (struct CInternalTypeinfoEnumNames**)realloc(a_collection->pNames, newSize * sizeof(struct CInternalTypeinfoEnumNames*));
        if (!pNamesTmp) {
            return CPPUTILS_NULL;
        }  //  if (!pNamesTmp) {
        memset(((char*)pNamesTmp) + a_collection->currentSize, 0, CINTERNAL_COLLECTION_RESIZE_STEP * sizeof(struct CInternalTypeinfoEnumNames*));
        a_collection->pNames = pNamesTmp;
        a_collection->currentSize = newSize;
    }  //  while (a_index >= (a_collection->currentSize)) {
    
    // let's free old, if any
    CInternalTypeinfoCleanEnumNamesInline(a_collection->pNames[a_index]);

    va_start(argList, a_number);
    a_collection->pNames[a_index] = CInternalTypeinfoCreateEnumNamesInline(a_number, argList);
    va_end(argList);
    return a_collection->pNames[a_index];
}


CINTERNAL_EXPORT struct CInternalTypeinfoStructNames* CInternalTypeinfoSetStructNamesToCollection(struct CInternalTypeinfoCollectionStructNames* CPPUTILS_ARG_NN a_collection, size_t a_index, int a_number, ...) CPPUTILS_NOEXCEPT
{
    va_list argList;
    struct CInternalTypeinfoStructNames** pNamesTmp;
    size_t newSize;
    while (a_index >= (a_collection->currentSize)) {
        newSize = (a_collection->currentSize) + CINTERNAL_COLLECTION_RESIZE_STEP;
        pNamesTmp = (struct CInternalTypeinfoStructNames**)realloc(a_collection->pNames, newSize * sizeof(struct CInternalTypeinfoStructNames*));
        if (!pNamesTmp) {
            return CPPUTILS_NULL;
        }  //  if (!pNamesTmp) {
        memset(((char*)pNamesTmp) + a_collection->currentSize, 0, CINTERNAL_COLLECTION_RESIZE_STEP * sizeof(struct CInternalTypeinfoStructNames*));
        a_collection->pNames = pNamesTmp;
        a_collection->currentSize = newSize;
    }  //  while (a_index >= (a_collection->currentSize)) {

    // let's free old, if any
    CInternalTypeinfoCleanStructNamesInline(a_collection->pNames[a_index]);

    va_start(argList, a_number);
    a_collection->pNames[a_index] = CInternalTypeinfoCreateStructNamesInline(a_number, argList);
    va_end(argList);
    return a_collection->pNames[a_index];
}


CINTERNAL_EXPORT const char* CInternalTypeinfoGetEnumNameFromCollection(const struct CInternalTypeinfoCollectionEnumNames* CPPUTILS_ARG_NN a_collection, size_t a_index, int a_value) CPPUTILS_NOEXCEPT
{
    if (a_index >= (a_collection->currentSize)) {
        return CINTERNAL_TYPEINFO_NAME_MEMORY_PROBLEM;
    }

    if (!(a_collection->pNames[a_index])) {
        return CINTERNAL_TYPEINFO_NAME_NON_EXIST;
    }

    return CInternalTypeinfoGetEnumNameInline(a_collection->pNames[a_index], a_value);
}


CINTERNAL_EXPORT const char* CInternalTypeinfoGetStructNameFromCollection(const struct CInternalTypeinfoCollectionStructNames* CPPUTILS_ARG_NN a_collection, size_t a_index, size_t a_offset) CPPUTILS_NOEXCEPT
{
    if (a_index >= (a_collection->currentSize)) {
        return CINTERNAL_TYPEINFO_NAME_MEMORY_PROBLEM;
    }

    if (!(a_collection->pNames[a_index])) {
        return CINTERNAL_TYPEINFO_NAME_NON_EXIST;
    }

    return CInternalTypeinfoGetStructNameInline(a_collection->pNames[a_index],a_offset);
}


CPPUTILS_END_C
