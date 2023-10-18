//
// repo:            cinternal
// file:			cinternal_unit_test_0009_hash_vhash.c
// path:			src/tests/unit_test/cinternal_unit_test_0009_hash_vhash.c
// created on:		2023 Oct 18
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test.h>
#include <cinternal/hash/vhash.h>
#include <stdlib.h>

#define CINTR_TEST_HASH_DATA1		2
#define CINTR_TEST_HASH_DATA2		4


static void TestHash(CinternalVHash_t a_hash, const void* a_key1, size_t keySize1, const void* a_key2, size_t keySize2);


CPPUTILS_UTEST_AFTER_MAIN(f_0009_hash_vhash, t_0001) {

	const int key1 = 1;
	const int key2 = 2;
	CinternalVHash_t aHash;
	CinternalVHashItem_t pItem;

	aHash = CInternalVHashCreateRawMem(1024);
	CinternalUnitTestCheckOpt(aHash);
	//if (!aHash) {
	//	exit(1);
	//}

	CInternalVHashAddDataToEndEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	pItem = CInternalVHashFind(aHash, &key1, sizeof(int));
	CinternalUnitTestAssertCheckSrc(pItem);
	CInternalVHashRemoveDataEx(aHash, pItem);

	CInternalVHashAddDataToEndEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	CInternalVHashAddDataToEndEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA2, &key2, sizeof(int));
	TestHash(aHash, &key1, sizeof(int), &key2, sizeof(int));
	CInternalVHashDestroy(aHash);


	aHash = CInternalVHashCreateSmlInt(1024);
	CinternalUnitTestCheckOpt(aHash);
	//if (!aHash) {
	//	exit(1);
	//}

	CInternalVHashAddDataToEndEvenIfExistSmlInt(aHash, (void*)CINTR_TEST_HASH_DATA1, 1);
	CInternalVHashAddDataToEndEvenIfExistSmlInt(aHash, (void*)CINTR_TEST_HASH_DATA2, 2);
	TestHash(aHash, CInternalSmallIntHPairFn(1), CInternalSmallIntHPairFn(2));
	CInternalVHashDestroy(aHash);

}


static void TestHash(CinternalVHash_t a_hash, const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2)
{
	CinternalVHashItem_t pItem;
	int nNumber;
	size_t i;
	struct SCinternalVHashItem** ppVector;
	const size_t cunNumber = CInternalVHashSize(a_hash);

	CinternalUnitTestAssertCheckSrc(cunNumber == 2);

	ppVector = CInternalVHashVector(a_hash);
	CinternalUnitTestAssertCheckSrc(ppVector);

	nNumber = 0;
	for (i = 0; i < cunNumber; ++i) {
		++nNumber;
		pItem = ppVector[i];
		CinternalUnitTestAssertCheckSrc(pItem);
	}

	CinternalUnitTestAssertCheckSrc(nNumber == 2);

	pItem = CInternalVHashFind(a_hash, a_key1, a_keySize1);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)(pItem->hit.data)) == CINTR_TEST_HASH_DATA1);

	pItem = CInternalVHashFind(a_hash, a_key2, a_keySize2);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)(pItem->hit.data)) == CINTR_TEST_HASH_DATA2);
}

