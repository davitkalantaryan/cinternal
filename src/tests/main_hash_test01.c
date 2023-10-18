//
// repo:			cinternal
// file:            main_hash_test01.c
// path:			src/tests/main_hash_test01.c
// created on:		2023 Oct 11
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cinternal/hash/lhash.h>
#include <cinternal/unit_test_only_checks.h>
#include <stdio.h>

#define CINTR_TEST_HASH_DATA1		2
#define CINTR_TEST_HASH_DATA2		4


static void TestHash(CinternalSHash_t a_hash, const void* a_key1, size_t keySize1, const void* a_key2, size_t keySize2);

int main(void)
{
	const int key1 = 1;
	const int key2 = 2;
	CinternalSHash_t aHash;
	CinternalSHashItem_t pItem;

	aHash = CInternalLHashCreateRawMem(1024);
	if (!aHash) {
		perror("\n");
		return 1;
	}

	CInternalLHashAddDataToBegEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	pItem = CInternalLHashFind(aHash, &key1, sizeof(int));
	CinternalUnitTestAssertCheckSrc(pItem);
	CInternalLHashRemoveDataEx(aHash, pItem);

	CInternalLHashAddDataToBegEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	CInternalLHashAddDataToBegEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA2, &key2, sizeof(int));
	TestHash(aHash, &key1, sizeof(int), &key2, sizeof(int));
	CInternalLHashDestroy(aHash);


	aHash = CInternalLHashCreateSmlInt(1024);
	if (!aHash) {
		perror("\n");
		return 1;
	}
	CInternalLHashAddDataToEndEvenIfExistSmlInt(aHash, (void*)CINTR_TEST_HASH_DATA1, 1);
	CInternalLHashAddDataToEndEvenIfExistSmlInt(aHash, (void*)CINTR_TEST_HASH_DATA2, 2);
	TestHash(aHash, CInternalSmallIntHPairFn(1), CInternalSmallIntHPairFn(2));
	CInternalLHashDestroy(aHash);

	return 0;
}


static void TestHash(CinternalSHash_t a_hash, const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2)
{
	CinternalSHashItem_t pItem;
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
	CinternalUnitTestAssertCheckSrc(((size_t)(pItem->data)) == CINTR_TEST_HASH_DATA1);

	pItem = CInternalLHashFind(a_hash, a_key2, a_keySize2);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)(pItem->data)) == CINTR_TEST_HASH_DATA2);
}
