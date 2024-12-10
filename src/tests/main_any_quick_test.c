//
// file:            main_any_quick_test.c
// path:			src/tests/main_any_quick_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/hash.h>
#include <cinternal/unit_test_only_checks.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdlib.h>
#include <cinternal/undisable_compiler_warnings.h>

#define CINTR_TEST_HASH_DATA1		2
#define CINTR_TEST_HASH_DATA2		4

static void TestHash(ConstCinternalHash_t a_hash, const void* a_key1, size_t keySize1, const void* a_key2, size_t keySize2);


int main(void)
{
    const int key1 = 1;
    const int key2 = 2;
    ConstCinternalHash_t aHash;
    CinternalHashItem_t pItem;

    aHash = CInternalHashCreateRawMem(1024);
    if (!aHash) {
        perror("\n");
        return 1;
    }

    CInternalHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
    pItem = CInternalHashFind(aHash, &key1, sizeof(int));
    CinternalUnitTestAssertCheckSrc(pItem);
    CInternalHashRemoveDataEx(aHash, pItem);

    CInternalHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
    CInternalHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA2, &key2, sizeof(int));
    TestHash(aHash, &key1, sizeof(int), &key2, sizeof(int));
    CInternalHashDestroy(aHash);


    aHash = CInternalHashCreateSmlInt(1024);
    if (!aHash) {
        perror("\n");
        return 1;
    }
    CInternalHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, CInternalSmallIntHPairFn(1));
    CInternalHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA2, CInternalSmallIntHPairFn(2));
    TestHash(aHash, CInternalSmallIntHPairFn(1), CInternalSmallIntHPairFn(2));
    CInternalHashDestroy(aHash);

	return 0;
}


static bool HashIterStatic(void* a_pData, CinternalHashItem_t a_item)
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
    CInternalHashIterate(a_hash, &HashIterStatic, &nNumber);
    CinternalUnitTestAssertCheckSrc(nNumber == 2);

    pItem = CInternalHashFind(a_hash, a_key1, a_keySize1);
    CinternalUnitTestAssertCheckSrc(pItem);
    CinternalUnitTestAssertCheckSrc(((size_t)(pItem->data)) == CINTR_TEST_HASH_DATA1);

    pItem = CInternalHashFind(a_hash, a_key2, a_keySize2);
    CinternalUnitTestAssertCheckSrc(pItem);
    CinternalUnitTestAssertCheckSrc(((size_t)(pItem->data)) == CINTR_TEST_HASH_DATA2);
}
