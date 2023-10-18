//
// repo:            cinternal
// file:			cinternal_unit_test_0007_hash_lhash.c
// path:			src/tests/unit_test/cinternal_unit_test_0007_hash_lhash.c
// created on:		2023 Oct 15
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test.h>
#include <cinternal/hash/lhash.h>
#include <stdlib.h>

#define CINTR_TEST_HASH_DATA1		2
#define CINTR_TEST_HASH_DATA2		4


static void TestHash(CinternalLHash_t a_hash, const void* a_key1, size_t keySize1, const void* a_key2, size_t keySize2);


CPPUTILS_UTEST_AFTER_MAIN(f_0007_hash_lhash, t_0001) {

	const int key1 = 1;
	const int key2 = 2;
	CinternalLHash_t aHash;
	CinternalLHashItem_t pItem;

	aHash = CInternalLHashCreateRawMem(1024);
	CinternalUnitTestCheckOpt(aHash);
	//if (!aHash) {
	//	exit(1);
	//}

	CInternalLHashAddDataToBegEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	pItem = CInternalLHashFind(aHash, &key1, sizeof(int));
	CinternalUnitTestAssertCheckSrc(pItem);
	CInternalLHashRemoveDataEx(aHash, pItem);

	CInternalLHashAddDataToBegEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	CInternalLHashAddDataToBegEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA2, &key2, sizeof(int));
	TestHash(aHash, &key1, sizeof(int), &key2, sizeof(int));
	CInternalLHashDestroy(aHash);


	aHash = CInternalLHashCreateSmlInt(1024);
	CinternalUnitTestCheckOpt(aHash);
	//if (!aHash) {
	//	exit(1);
	//}

	CInternalLHashAddDataToEndEvenIfExistSmlInt(aHash, (void*)CINTR_TEST_HASH_DATA1, 1);
	CInternalLHashAddDataToEndEvenIfExistSmlInt(aHash, (void*)CINTR_TEST_HASH_DATA2, 2);
	TestHash(aHash, CInternalSmallIntHPairFn(1), CInternalSmallIntHPairFn(2));
	CInternalLHashDestroy(aHash);

}


static void TestHash(CinternalLHash_t a_hash, const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2)
{
	CinternalLHashItem_t pItem;
	int nNumber;

	CinternalUnitTestAssertCheckSrc(CInternalLHashSize(a_hash) == 2);

	nNumber = 0;
	pItem = CInternalLHashFirstItem(a_hash);
	while (pItem) {
		++nNumber;
		pItem = pItem->next;
	}

	CinternalUnitTestAssertCheckSrc(nNumber == 2);

	pItem = CInternalLHashFind(a_hash, a_key1, a_keySize1);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)(pItem->hit.data)) == CINTR_TEST_HASH_DATA1);

	pItem = CInternalLHashFind(a_hash, a_key2, a_keySize2);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)(pItem->hit.data)) == CINTR_TEST_HASH_DATA2);
}

