//
// repo:            cinternal
// file:			cinternal_unit_test_0008_hash_phash.c
// path:			src/tests/unit_test/cinternal_unit_test_0008_hash_phash.c
// created on:		2023 Oct 18
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test.h>
#include <cinternal/hash/phash.h>
#include <stdlib.h>

#define CINTR_TEST_HASH_DATA1		2
#define CINTR_TEST_HASH_DATA2		4


static void TestHash(CinternalPHash_t a_hash, const void* a_key1, size_t keySize1, const void* a_key2, size_t keySize2);


CPPUTILS_UTEST_AFTER_MAIN(f_0008_hash_phash, t_0001) {

	const int key1 = 1;
	const int key2 = 2;
	CinternalPHash_t aHash;
	CinternalPHashItem_t pItem;

	aHash = CInternalPHashCreateRawMem(1024);
	CinternalUnitTestCheckOpt(aHash);
	//if (!aHash) {
	//	exit(1);
	//}

	CInternalPHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	pItem = CInternalPHashFind(aHash, &key1, sizeof(int));
	CinternalUnitTestAssertCheckSrc(pItem);
	CInternalPHashRemoveDataEx(aHash, pItem);

	CInternalPHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	CInternalPHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA2, &key2, sizeof(int));
	TestHash(aHash, &key1, sizeof(int), &key2, sizeof(int));
	CInternalPHashDestroy(aHash);


	aHash = CInternalPHashCreateSmlInt(1024);
	CinternalUnitTestCheckOpt(aHash);
	//if (!aHash) {
	//	exit(1);
	//}

	CInternalPHashAddDataEvenIfExistSmlInt(aHash, (void*)CINTR_TEST_HASH_DATA1, 1);
	CInternalPHashAddDataEvenIfExistSmlInt(aHash, (void*)CINTR_TEST_HASH_DATA2, 2);
	TestHash(aHash, CInternalSmallIntHPairFn(1), CInternalSmallIntHPairFn(2));
	CInternalPHashDestroy(aHash);

}


static void TestHash(CinternalPHash_t a_hash, const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2)
{
	CinternalPHashItem_t pItem;

	CinternalUnitTestAssertCheckSrc(CInternalPHashSize(a_hash) == 2);

	//nNumber = 0;
	//pItem = CInternalPHashFirstItem(a_hash);
	//while (pItem) {
	//	++nNumber;
	//	pItem = pItem->next;
	//}
	//CinternalUnitTestAssertCheckSrc(nNumber == 2);

	pItem = CInternalPHashFind(a_hash, a_key1, a_keySize1);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)(pItem->hit.data)) == CINTR_TEST_HASH_DATA1);

	pItem = CInternalPHashFind(a_hash, a_key2, a_keySize2);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)(pItem->hit.data)) == CINTR_TEST_HASH_DATA2);
}

