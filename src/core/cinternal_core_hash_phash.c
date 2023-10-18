//
// repo:			cinternal
// file:            cinternal_core_phash.c
// path:			src/core/cinternal_core_phash.c
// created on:		2023 Oct 11
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// comment:			pure hash
//


#include <cinternal/hash/phash.h>
//#define CInternalHashAddFirstDataWithKnownHashInline_needed		1
#define CInternalHashFindItemInline_needed				1
#define cinternal_hash1_small_int_needed						1
#define CinternalIsMemoriesIdenticalSmallInt_needed				1
#define CinternalStoreKeySmallInt_needed						1
#define CinternalUnstoreKeySmallInt_needed						1
#define CinternalStoreKeyRawMemory_needed						1
#define CinternalUnstoreKeyRawMemory_needed						1
#define CinternalIsMemoriesIdenticalRawMemory_needed			1
//#define DefaultRemainingCleaner_needed					1
#define cinternal_hash1_raw_mem_needed							1
#include <cinternal/hash/functions.h>
#include <stdlib.h>

#ifdef _MSC_VER
#pragma warning(disable:5039)
#endif


#define CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS	4096
#define CinternalHashToPHash(_hash)					CPPUTILS_STATIC_CAST(struct SCinternalPHash*,CPPUTILS_STATIC_CAST(void*,_hash))
#define CinternalHashItemToPHashItem(_hashItem)		CPPUTILS_STATIC_CAST(struct SCinternalPHashItem*,CPPUTILS_STATIC_CAST(void*,_hashItem))


CPPUTILS_BEGIN_C


struct SCinternalPHash {
	struct SCinternalHash				hash;
};


static inline void CInternalPHashClearExInline(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner)
{
	size_t i;
	struct SCinternalHashItem* pItemTmp, * pItem;

	for (i = 0; i < a_hashTbl->hash.numberOfBaskets; ++i) {
		pItem = a_hashTbl->hash.ppTable[i];
		while (pItem) {
			pItemTmp = pItem->nextInTheBucket;
			(*a_remainingDataCleaner)(pItem->data);
			(*(a_hashTbl->hash.deallocator))(pItem);
			pItem = pItemTmp;
		}
		a_hashTbl->hash.ppTable[i] = CPPUTILS_NULL;
	}
}


//static inline CinternalPHashItem_t CInternalPHashAddFirstDataWithKnownHashInline(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl,
//	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
//{
//	struct SCinternalPHashItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalPHashItem*, (*(a_hashTbl->hash.allocator))(sizeof(struct SCinternalPHashItem)));
//	if (!pNewItem) {
//		return CPPUTILS_NULL;
//	}
//
//	if (!CInternalHashAddFirstDataWithKnownHashInline(&(a_hashTbl->hash), &(pNewItem->hit), a_data, a_key, a_keySize, a_hash)) {
//		(*(a_hashTbl->hash.deallocator))(pNewItem);
//		return CPPUTILS_NULL;
//	}
//
//	return pNewItem;
//}


CINTERNAL_EXPORT CinternalPHash_t CInternalPHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	CinternalPHash_t pRet;
	size_t tableMemorySize;

	a_allocator = a_allocator ? a_allocator : (&malloc);

	pRet = CPPUTILS_STATIC_CAST(CinternalPHash_t, (*a_allocator)(sizeof(struct SCinternalPHash)));
	if (!pRet) {
		return CPPUTILS_NULL;
	}

	// init the list
	//CInternalDLListInitializeInline(&(pRet->lst), a_allocator, a_deallocator);
	pRet->hash.allocator = a_allocator;
	pRet->hash.deallocator = a_deallocator ? a_deallocator : (&free);
	pRet->hash.m_size = 0;
	pRet->hash.numberOfBaskets = (a_numberOfBaskets > 0) ? a_numberOfBaskets : CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS;

	tableMemorySize = pRet->hash.numberOfBaskets * sizeof(struct SCinternalPHashItem*);
	pRet->hash.ppTable = CPPUTILS_STATIC_CAST(struct SCinternalHashItem**, (*a_allocator)(tableMemorySize));
	if (!(pRet->hash.ppTable)) {
		(*(pRet->hash.deallocator))(pRet);
		return CPPUTILS_NULL;
	}
	memset(pRet->hash.ppTable, 0, tableMemorySize);

	//pRet->hasher = a_hasher ? a_hasher : (&cinternal_hash1_);
	//pRet->isEq = a_isEq ? a_isEq : (&CinternaldefaultIsMemoriesIdentical);
	pRet->hash.hasher = a_hasher;
	pRet->hash.isEq = a_isEq;
	pRet->hash.keyStore = a_keyStore;
	pRet->hash.keyUnstore = a_keyUnstore;

	return pRet;
}


CINTERNAL_EXPORT CinternalPHash_t CInternalPHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalPHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_raw_mem), a_isEq ? a_isEq : (&CinternalIsMemoriesIdenticalRawMemory),
		a_keyStore ? a_keyStore : (&CinternalStoreKeyRawMemory), a_keyUnstore ? a_keyUnstore : (&CinternalUnstoreKeyRawMemory),
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT CinternalPHash_t CInternalPHashCreateExAnyDefSmlInt(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalPHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_small_int), a_isEq ? a_isEq : (&CinternalIsMemoriesIdenticalSmallInt),
		a_keyStore ? a_keyStore : (&CinternalStoreKeySmallInt), a_keyUnstore ? a_keyUnstore : (&CinternalUnstoreKeySmallInt),
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT CinternalPHash_t CInternalPHashCreateExRawMem(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalPHashCreateExAny(a_numberOfBaskets,
		&cinternal_hash1_raw_mem, &CinternalIsMemoriesIdenticalRawMemory,
		&CinternalStoreKeyRawMemory, &CinternalUnstoreKeyRawMemory,
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT CinternalPHash_t CInternalPHashCreateExSmlInt(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalPHashCreateExAny(a_numberOfBaskets,
		&cinternal_hash1_small_int, &CinternalIsMemoriesIdenticalSmallInt,
		&CinternalStoreKeySmallInt, &CinternalUnstoreKeySmallInt,
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT void CInternalPHashDestroyEx(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner)
{
	CInternalPHashClearExInline(a_hashTbl,a_remainingDataCleaner);
	(*(a_hashTbl->hash.deallocator))(a_hashTbl->hash.ppTable);
	(*(a_hashTbl->hash.deallocator))(a_hashTbl);
}


CINTERNAL_EXPORT void CInternalPHashClearEx(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner)
{
	CInternalPHashClearExInline(a_hashTbl, a_remainingDataCleaner);
	a_hashTbl->hash.m_size = 0;
}


CINTERNAL_EXPORT CinternalPHashItem_t CInternalPHashAddDataWithKnownHash(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	struct SCinternalPHashItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalPHashItem*, (*(a_hashTbl->hash.allocator))(sizeof(struct SCinternalPHashItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	if (!(*(a_hashTbl->hash.keyStore))(a_hashTbl->hash.allocator, &(pNewItem->hit.key), &(pNewItem->hit.keySize), a_key, a_keySize)) {
		(*(a_hashTbl->hash.deallocator))(pNewItem);
		return CPPUTILS_NULL;
	}

	//
	pNewItem->hit.data = CPPUTILS_CONST_CAST(void*, a_data);
	pNewItem->hit.hash = a_hash;
	pNewItem->hit.prevInTheBucket = CPPUTILS_NULL;
	pNewItem->hit.nextInTheBucket = a_hashTbl->hash.ppTable[a_hash];
	if (a_hashTbl->hash.ppTable[a_hash]) { a_hashTbl->hash.ppTable[a_hash]->prevInTheBucket = &(pNewItem->hit); }
	a_hashTbl->hash.ppTable[a_hash] = &(pNewItem->hit);

	++(a_hashTbl->hash.m_size);

	return pNewItem;
}


CINTERNAL_EXPORT CinternalPHashItem_t CInternalPHashAddDataIfNotExists(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	if (CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, &unHash)) {
		return CPPUTILS_NULL;
	}
	return CInternalPHashAddDataWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, unHash);
}


CINTERNAL_EXPORT CinternalPHashItem_t CInternalPHashAddDataEvenIfExist(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hash.hasher))(a_key, a_keySize)) % (a_hashTbl->hash.numberOfBaskets);
	return CInternalPHashAddDataWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, hash);
}


CINTERNAL_EXPORT void CInternalPHashRemoveDataEx(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl, CinternalPHashItem_t CPPUTILS_ARG_NN a_iter)
{
	if (a_iter->hit.prevInTheBucket) { a_iter->hit.prevInTheBucket->nextInTheBucket = a_iter->hit.nextInTheBucket; }
	if (a_iter->hit.nextInTheBucket) { a_iter->hit.nextInTheBucket->prevInTheBucket = a_iter->hit.prevInTheBucket; }
	if (a_iter == CinternalHashItemToPHashItem(a_hashTbl->hash.ppTable[a_iter->hit.hash])) { a_hashTbl->hash.ppTable[a_iter->hit.hash] = a_iter->hit.nextInTheBucket; }

	(*(a_hashTbl->hash.keyUnstore))(a_hashTbl->hash.deallocator, a_iter->hit.key, a_iter->hit.keySize);
	(*(a_hashTbl->hash.deallocator))(a_iter);
	--(a_hashTbl->hash.m_size);
}


CINTERNAL_EXPORT bool CInternalPHashRemoveData(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	struct SCinternalPHashItem* const pIterator = CinternalHashItemToPHashItem(CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, &unHash));
	if (pIterator) {
		CInternalPHashRemoveDataEx(a_hashTbl, pIterator);
		return true;
	}
	return false;
}


CINTERNAL_EXPORT CinternalPHashItem_t CInternalPHashFindEx(ConstCinternalPHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash)
{
	return CinternalHashItemToPHashItem(CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, a_pHash));
}


CINTERNAL_EXPORT CinternalPHashItem_t CInternalPHashFind(ConstCinternalPHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	return CinternalHashItemToPHashItem(CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, &unHash));
}


CINTERNAL_EXPORT size_t CInternalPHashSize(ConstCinternalPHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return a_hashTbl->hash.m_size;
}


CPPUTILS_END_C
