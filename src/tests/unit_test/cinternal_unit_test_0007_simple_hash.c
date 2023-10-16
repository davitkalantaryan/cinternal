//
// repo:            cinternal
// file:			cinternal_unit_test_0007_simple_hash.c
// path:			src/tests/unit_test/cinternal_unit_test_0007_simple_hash.c
// created on:		2023 Oct 15
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test.h>
#include <cinternal/shash.h>
#include <stdlib.h>

#define CINTR_TEST_HASH_DATA1		2
#define CINTR_TEST_HASH_DATA2		4


static void TestHash(CinternalSHash_t a_hash, const void* a_key1, size_t keySize1, const void* a_key2, size_t keySize2);


CPPUTILS_UTEST_AFTER_MAIN(f_0007_simple_hash, t_0001) {

	const int key1 = 1;
	const int key2 = 2;
	CinternalSHash_t aHash;
	CinternalSHashItem_t pItem;

	aHash = CInternalSHashCreateRawMem(1024);
	CinternalUnitTestCheckOpt(aHash);
	//if (!aHash) {
	//	exit(1);
	//}

	CInternalSHashAddDataToBegEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	pItem = CInternalSHashFind(aHash, &key1, sizeof(int));
	CinternalUnitTestAssertCheckSrc(pItem);
	CInternalSHashRemoveDataEx(aHash, pItem);

	CInternalSHashAddDataToBegEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	CInternalSHashAddDataToBegEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA2, &key2, sizeof(int));
	TestHash(aHash, &key1, sizeof(int), &key2, sizeof(int));
	CInternalSHashDestroy(aHash);


	aHash = CInternalSHashCreateSmlInt(1024);
	CinternalUnitTestCheckOpt(aHash);
	//if (!aHash) {
	//	exit(1);
	//}

	CInternalSHashAddDataToEndEvenIfExistSmlInt(aHash, (void*)CINTR_TEST_HASH_DATA1, 1);
	CInternalSHashAddDataToEndEvenIfExistSmlInt(aHash, (void*)CINTR_TEST_HASH_DATA2, 2);
	TestHash(aHash, CInternalSmallIntHPairFn(1), CInternalSmallIntHPairFn(2));
	CInternalSHashDestroy(aHash);

}


static void TestHash(CinternalSHash_t a_hash, const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2)
{
	CinternalSHashItem_t pItem;
	int nNumber;

	CinternalUnitTestAssertCheckSrc(CInternalSHashSize(a_hash) == 2);

	nNumber = 0;
	pItem = CInternalSHashFirstItem(a_hash);
	while (pItem) {
		++nNumber;
		pItem = pItem->next;
	}

	CinternalUnitTestAssertCheckSrc(nNumber == 2);

	pItem = CInternalSHashFind(a_hash, a_key1, a_keySize1);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)(pItem->data)) == CINTR_TEST_HASH_DATA1);

	pItem = CInternalSHashFind(a_hash, a_key2, a_keySize2);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)(pItem->data)) == CINTR_TEST_HASH_DATA2);
}

