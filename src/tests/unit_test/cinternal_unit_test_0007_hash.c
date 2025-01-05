//
// repo:            cinternal
// file:			cinternal_unit_test_0007_hash_lhash.c
// path:			src/tests/unit_test/cinternal_unit_test_0007_hash_lhash.c
// created on:		2023 Oct 15
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test.h>
#include <cinternal/hash.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdlib.h>
#include <stdio.h>
#include <cinternal/undisable_compiler_warnings.h>

#define CINTR_TEST_HASH_DATA1		2
#define CINTR_TEST_HASH_DATA2		4
#define USE_RAW_MEM                 0


static void TestHash(ConstCinternalHash_t a_hash, const void* a_key1, size_t keySize1, const void* a_key2, size_t keySize2);


CPPUTILS_UTEST_AFTER_MAIN(f_0007_hash_lhash, t_0001) {

	const int key1 = 1;
	const int key2 = 2;
	ConstCinternalHash_t aHash;
	CinternalHashItem_t pItem;

	aHash = CInternalHashCreateRawMem(1024);
	CinternalUnitTestCheckOpt(aHash);
	//if (!aHash) {
	//	exit(1);
	//}

	CInternalHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	pItem = CInternalHashFind(aHash, &key1, sizeof(int));
	CinternalUnitTestAssertCheckSrc(pItem);
	CInternalHashRemoveDataEx(aHash, pItem);

	CInternalHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	CInternalHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA2, &key2, sizeof(int));
	TestHash(aHash, &key1, sizeof(int), &key2, sizeof(int));
	CInternalHashDestroy(aHash);


	aHash = CInternalHashCreateSmlInt(1024);
	CinternalUnitTestCheckOpt(aHash);
	//if (!aHash) {
	//	exit(1);
	//}

	CInternalHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, CInternalSmallIntHPairFn(1));
    CInternalHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA2, CInternalSmallIntHPairFn(2));
	TestHash(aHash, CInternalSmallIntHPairFn(1), CInternalSmallIntHPairFn(2));
	CInternalHashDestroy(aHash);

}


static bool HashIterStatic1(void* a_pData, CinternalHashItem_t a_item)
{
    int* const pnNumber = (int*)a_pData;
    (void)a_item;
    ++(*pnNumber);
    return true;
}


static void TestHash(ConstCinternalHash_t a_hash, const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2)
{
	CinternalHashItem_t pItem;
	int nNumber;

	CinternalUnitTestAssertCheckSrc(a_hash->count == 2);

    nNumber = 0;
    CInternalHashIterate(a_hash, &HashIterStatic1, &nNumber);
    CinternalUnitTestAssertCheckSrc(nNumber == 2);

	pItem = CInternalHashFind(a_hash, a_key1, a_keySize1);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)(pItem->data)) == CINTR_TEST_HASH_DATA1);

	pItem = CInternalHashFind(a_hash, a_key2, a_keySize2);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)(pItem->data)) == CINTR_TEST_HASH_DATA2);
}


static void WholeTestOfHash(int a_nMinChecks, int a_nMaxChecks, int a_nMinItemsCount, int a_nMaxItemsCount);


CPPUTILS_UTEST_AFTER_MAIN(f_0007_hash_lhash, t_0002) {
    int nMinItemsCount = 10, nMaxItemsCount = 20;
    int nMinChecks = 10, nMaxChecks = 600;
    CinternalUnitTestCheckOpt(true);
    WholeTestOfHash(nMinChecks, nMaxChecks, nMinItemsCount, nMaxItemsCount);
}



struct SCinternalHashSnglKey {
    struct SCinternalHashSnglKey* next;
    CinternalHashItem_t             pItem;
    void* data;
    size_t  keySize;
    int     keyInt;
    int     reserved01;
};

struct SCinternalHashAllKeys {
    size_t                          count;
    struct SCinternalHashSnglKey* firstKey;
};


static inline int GenerateNumberInTheRangeInline(int a_min, int a_max) {
    int nActualValue;
    CinternalUnitTestAssertCheckSrc(a_max > a_min);
    nActualValue = rand();
    nActualValue %= (a_max - a_min);
    nActualValue += a_min;
    return nActualValue;
}


static inline ConstCinternalHash_t CreateHashInline(int* CPPUTILS_ARG_NN a_pnCase) {
    *a_pnCase = rand() % 2;
    switch (*a_pnCase) {
    case USE_RAW_MEM:
        printf("hashType: RawMem, remove: Raw");
        return CInternalHashCreateRawMem(1024);
    default:
        break;
    }  //  switch (cnCase) {
    printf("hashType: SmallInt, remove: byKey");
    return CInternalHashCreateSmlInt(1024);
}


static inline void CheckKeyConsistencyInline(int a_nCase, const void* a_key1, int a_key2) {
    int nKey1;
    switch (a_nCase) {
    case USE_RAW_MEM: {
        nKey1 = *((const int*)a_key1);
    }break;
    default: {
        nKey1 = (int)((size_t)a_key1);
    }break;
    }  //  switch (a_nCase) {
    CinternalUnitTestAssertCheckSrc(nKey1 == a_key2);
}


static inline void CheckKeySizeConsistencyInline(int a_nCase, size_t a_key1Size, size_t a_key2Size) {
    switch (a_nCase) {
    case USE_RAW_MEM:
        CinternalUnitTestAssertCheckSrc(a_key1Size == a_key2Size);
        break;
    default:
        break;
    }  //  switch (a_nCase) {
}


static inline void AddDataToHashInline(ConstCinternalHash_t CPPUTILS_ARG_NN a_hash, int a_nCase, struct SCinternalHashAllKeys* CPPUTILS_ARG_NN a_allKeys_p) {
    void* pKey;
    struct SCinternalHashSnglKey* const pNextEntry = (struct SCinternalHashSnglKey*)malloc(sizeof(struct SCinternalHashSnglKey));
    CinternalUnitTestAssertCheckSrc(pNextEntry);
    pNextEntry->keyInt = rand();
    pNextEntry->data = (void*)((size_t)rand());
    pNextEntry->next = CPPUTILS_NULL;
    switch (a_nCase) {
    case USE_RAW_MEM:
        pKey = &(pNextEntry->keyInt);
        pNextEntry->keySize = sizeof(int);
        break;
    default:
        pKey = CInternalSmallIntHKey(pNextEntry->keyInt);
        break;
    }  //  switch (cnCase) {
    pNextEntry->pItem = CInternalHashAddDataEvenIfExist(a_hash, pNextEntry->data, pKey, pNextEntry->keySize);
    CinternalUnitTestAssertCheckSrc(pNextEntry->pItem);
    CinternalUnitTestAssertCheckSrc((pNextEntry->pItem->data) == (pNextEntry->data));
    CheckKeyConsistencyInline(a_nCase, pNextEntry->pItem->key, pNextEntry->keyInt);
    CheckKeySizeConsistencyInline(a_nCase, pNextEntry->pItem->keySize, pNextEntry->keySize);
    pNextEntry->next = a_allKeys_p->firstKey;
    a_allKeys_p->firstKey = pNextEntry;
}


static void SingleTestOfHashAndCleanData(ConstCinternalHash_t CPPUTILS_ARG_NN a_hash, struct SCinternalHashAllKeys* CPPUTILS_ARG_NN a_allKeys_p, int a_nCase);


static void WholeTestOfHash(int a_nMinChecks, int a_nMaxChecks, int a_nMinItemsCount, int a_nMaxItemsCount)
{
    ConstCinternalHash_t aHash;
    struct SCinternalHashAllKeys allKeys;
    size_t j;
    int i, nCase;
    const int nActualCheck = GenerateNumberInTheRangeInline(a_nMinChecks, a_nMaxChecks);

    fprintf(stdout, "------------------------------------\npossible checks count: [%d,%d], actualChecksNumber is %d\n", a_nMinChecks, a_nMaxChecks, nActualCheck);

    for (i = 0; i < nActualCheck; ++i) {
        allKeys.firstKey = CPPUTILS_NULL;
        allKeys.count = (size_t)GenerateNumberInTheRangeInline(a_nMinItemsCount, a_nMaxItemsCount);
        printf("  ----- iteration: %.2d -> itemsCount: %d, ", i, (int)allKeys.count);
        aHash = CreateHashInline(&nCase);
        printf("\n");
        CinternalUnitTestAssertCheckSrc(aHash);

        for (j = 0; j < allKeys.count; ++j) {
            AddDataToHashInline(aHash, nCase, &allKeys);
        }  //  for (j = 0; j < allKeys.count; ++j) {

        SingleTestOfHashAndCleanData(aHash, &allKeys, nCase);
        CInternalHashDestroy(aHash);
    }  //  for (i = 0; i < nActualCheck; ++i) {
}


static bool HashIterStatic2(void* a_pData, CinternalHashItem_t a_item)
{
    size_t* const pnNumber = (size_t*)a_pData;
    (void)a_item;
    ++(*pnNumber);
    return true;
}


static inline const void* GetHashKeyInline(const struct SCinternalHashSnglKey* CPPUTILS_ARG_NN a_pSnglData, int a_nCase) {
    switch (a_nCase) {
    case USE_RAW_MEM:
        return &(a_pSnglData->keyInt);
    default:
        break;
    }  //  switch (a_nCase) {
    return CInternalSmallIntHKey(a_pSnglData->keyInt);
}


static void SingleTestOfHashAndCleanData(ConstCinternalHash_t CPPUTILS_ARG_NN a_hash, struct SCinternalHashAllKeys* CPPUTILS_ARG_NN a_allKeys_p, int a_nCase)
{
    CinternalHashItem_t pItem;
    size_t nNumber;
    bool removeResult;
    struct SCinternalHashSnglKey* pSnglData, * pSnglDataNext;

    CinternalUnitTestAssertCheckSrc(a_hash->count == a_allKeys_p->count);

    nNumber = 0;
    CInternalHashIterate(a_hash, &HashIterStatic2, &nNumber);
    CinternalUnitTestAssertCheckSrc(nNumber == a_allKeys_p->count);

    pSnglData = a_allKeys_p->firstKey;
    while (pSnglData) {
        pSnglDataNext = pSnglData->next;
        pItem = CInternalHashFind(a_hash, GetHashKeyInline(pSnglData, a_nCase), pSnglData->keySize);
        CinternalUnitTestAssertCheckSrc(pItem);
        CinternalUnitTestAssertCheckSrc(pItem == (pSnglData->pItem));
        CinternalUnitTestAssertCheckSrc((pItem->data) == (pSnglData->data));
        switch (a_nCase) {
        case USE_RAW_MEM:
            CInternalHashRemoveDataEx(a_hash, pItem);
            break;
        default:
            removeResult = CInternalHashRemoveData(a_hash, GetHashKeyInline(pSnglData, a_nCase), pSnglData->keySize);
            CinternalUnitTestAssertCheckSrc(removeResult);
            break;
        }  //  switch (a_nCase) {

        free(pSnglData);

        pSnglData = pSnglDataNext;
    }  //  while (pSnglData) {

    nNumber = 0;
    CInternalHashIterate(a_hash, &HashIterStatic2, &nNumber);
    CinternalUnitTestAssertCheckSrc(nNumber == 0);

}
