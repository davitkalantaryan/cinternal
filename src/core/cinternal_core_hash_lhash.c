//
// repo:			cinternal
// file:            cinternal_core_lhash.c
// path:			src/core/cinternal_core_lhash.c
// created on:		2023 Oct 11
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// comment:			list hash
//


#include <cinternal/hash/lhash.h>
#define CInternalHashAddFirstDataWithKnownHashInline_needed		1
#define CInternalHashFindItemInline_needed						1
#define cinternal_hash1_small_int_needed						1
#define CinternalIsMemoriesIdenticalSmallInt_needed				1
#define CinternalStoreKeySmallInt_needed						1
#define CinternalUnstoreKeySmallInt_needed						1
#define CinternalStoreKeyRawMemory_needed						1
#define CinternalUnstoreKeyRawMemory_needed						1
#define CinternalIsMemoriesIdenticalRawMemory_needed			1
#define DefaultRemainingCleaner_needed							1
#define cinternal_hash1_raw_mem_needed							1
#include <cinternal/hash/functions.h>
#include <stdlib.h>

#ifdef _MSC_VER
#pragma warning(disable:5039)
#endif


#define CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS	4096
#define CinternalHashToLHash(_hash)					CPPUTILS_STATIC_CAST(struct SCinternalLHash*,CPPUTILS_STATIC_CAST(void*,_hash))
#define CinternalHashItemToLHashItem(_hashItem)		CPPUTILS_STATIC_CAST(struct SCinternalLHashItem*,CPPUTILS_STATIC_CAST(void*,_hashItem))


CPPUTILS_BEGIN_C


struct SCinternalLHash {
	struct SCinternalHash				hash;
	struct SCinternalLHashItem			*first, *last;
};


static inline void CInternalLHashClearExInline(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner)
{
	struct SCinternalLHashItem* pItemTmp, * pItem = a_hashTbl->first;
	a_remainingDataCleaner = a_remainingDataCleaner ? a_remainingDataCleaner : &DefaultRemainingCleaner;
	while (pItem) {
		pItemTmp = pItem->next;
		a_hashTbl->hash.ppTable[pItem->hit.hash] = CPPUTILS_NULL;
		(*a_remainingDataCleaner)(pItem->hit.data);
		(*(a_hashTbl->hash.deallocator))(pItem);
		pItem = pItemTmp;
	}	
}


static inline CinternalLHashItem_t CInternalLHashAddFirstDataWithKnownHashInline(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	struct SCinternalLHashItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalLHashItem*, (*(a_hashTbl->hash.allocator))(sizeof(struct SCinternalLHashItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	if (!CInternalHashAddFirstDataWithKnownHashInline(&(a_hashTbl->hash), &(pNewItem->hit), a_data, a_key, a_keySize, a_hash)) {
		(*(a_hashTbl->hash.deallocator))(pNewItem);
		return CPPUTILS_NULL;
	}

	pNewItem->prev = CPPUTILS_NULL;
	pNewItem->next = CPPUTILS_NULL;
	a_hashTbl->last = a_hashTbl->first = pNewItem;
	//

	return pNewItem;
}


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	CinternalLHash_t pRet;
	size_t tableMemorySize;

	a_allocator = a_allocator ? a_allocator : (&malloc);

	pRet = CPPUTILS_STATIC_CAST(CinternalLHash_t, (*a_allocator)(sizeof(struct SCinternalLHash)));
	if (!pRet) {
		return CPPUTILS_NULL;
	}

	// init the list
	//CInternalDLListInitializeInline(&(pRet->lst), a_allocator, a_deallocator);
	pRet->hash.allocator = a_allocator;
	pRet->hash.deallocator = a_deallocator ? a_deallocator : (&free);
	pRet->hash.m_size = 0;
	pRet->hash.numberOfBaskets = (a_numberOfBaskets > 0) ? a_numberOfBaskets : CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS;
	pRet->last = pRet->first = CPPUTILS_NULL;

	tableMemorySize = pRet->hash.numberOfBaskets * sizeof(struct SCinternalLHashItem*);
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


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalLHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_raw_mem), a_isEq ? a_isEq : (&CinternalIsMemoriesIdenticalRawMemory),
		a_keyStore ? a_keyStore : (&CinternalStoreKeyRawMemory), a_keyUnstore ? a_keyUnstore : (&CinternalUnstoreKeyRawMemory),
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExAnyDefSmlInt(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalLHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_small_int), a_isEq ? a_isEq : (&CinternalIsMemoriesIdenticalSmallInt),
		a_keyStore ? a_keyStore : (&CinternalStoreKeySmallInt), a_keyUnstore ? a_keyUnstore : (&CinternalUnstoreKeySmallInt),
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExRawMem(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalLHashCreateExAny(a_numberOfBaskets,
		&cinternal_hash1_raw_mem, &CinternalIsMemoriesIdenticalRawMemory,
		&CinternalStoreKeyRawMemory, &CinternalUnstoreKeyRawMemory,
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExSmlInt(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalLHashCreateExAny(a_numberOfBaskets,
		&cinternal_hash1_small_int, &CinternalIsMemoriesIdenticalSmallInt,
		&CinternalStoreKeySmallInt, &CinternalUnstoreKeySmallInt,
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT void CInternalLHashDestroyEx(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner)
{
	CInternalLHashClearExInline(a_hashTbl, a_remainingDataCleaner);
	(*(a_hashTbl->hash.deallocator))(a_hashTbl->hash.ppTable);
	(*(a_hashTbl->hash.deallocator))(a_hashTbl);
}


CINTERNAL_EXPORT void CInternalLHashClearEx(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner)
{
	//const size_t tableMemorySize = a_hashTbl->hash.numberOfBaskets * sizeof(struct SCinternalLHashItem*);
	CInternalLHashClearExInline(a_hashTbl, a_remainingDataCleaner);
	//memset(a_hashTbl->hash.ppTable,0, tableMemorySize);
	a_hashTbl->hash.m_size = 0;
}


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataAfterWithKnownHash(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalLHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	struct SCinternalLHashItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalLHashItem*, (*(a_hashTbl->hash.allocator))(sizeof(struct SCinternalLHashItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	if (!(*(a_hashTbl->hash.keyStore))(a_hashTbl->hash.allocator, &(pNewItem->hit.key), &(pNewItem->hit.keySize), a_key, a_keySize)) {
		(*(a_hashTbl->hash.deallocator))(pNewItem);
		return CPPUTILS_NULL;
	}

	pNewItem->prev = a_itemBefore;
	pNewItem->next = a_itemBefore->next;
	if (a_itemBefore->next) { a_itemBefore->next->prev = pNewItem;}
	else { 
		a_hashTbl->last = pNewItem;
		if (!(a_hashTbl->first)) {
			a_hashTbl->first = pNewItem;
		}
	}
	a_itemBefore->next = pNewItem;
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


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataAfterIfNotExists(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalLHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	if (CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, &unHash)) {
		return CPPUTILS_NULL;
	}
	return CInternalLHashAddDataAfterWithKnownHash(a_hashTbl, a_itemBefore,a_data, a_key, a_keySize, unHash);
}


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataAfterEvenIfExist(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalLHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hash.hasher))(a_key, a_keySize)) % (a_hashTbl->hash.numberOfBaskets);
	return CInternalLHashAddDataAfterWithKnownHash(a_hashTbl, a_itemBefore,a_data, a_key, a_keySize, hash);
}


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataBeforeWithKnownHash(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalLHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	struct SCinternalLHashItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalLHashItem*, (*(a_hashTbl->hash.allocator))(sizeof(struct SCinternalLHashItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	if (!(*(a_hashTbl->hash.keyStore))(a_hashTbl->hash.allocator, &(pNewItem->hit.key), &(pNewItem->hit.keySize), a_key, a_keySize)) {
		(*(a_hashTbl->hash.deallocator))(pNewItem);
		return CPPUTILS_NULL;
	}

	pNewItem->prev = a_itemAfter->prev;
	pNewItem->next = a_itemAfter;
	if (a_itemAfter->prev) { a_itemAfter->prev->next = pNewItem; }
	else {
		a_hashTbl->first = pNewItem; 
		if (!(a_hashTbl->last)) {
			a_hashTbl->last = pNewItem;
		}
	}
	a_itemAfter->prev = pNewItem;
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


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataBeforeIfNotExists(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalLHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	if (CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, &unHash)) {
		return CPPUTILS_NULL;
	}
	return CInternalLHashAddDataBeforeWithKnownHash(a_hashTbl, a_itemAfter, a_data, a_key, a_keySize, unHash);
}


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataBeforeEvenIfExist(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalLHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hash.hasher))(a_key, a_keySize)) % (a_hashTbl->hash.numberOfBaskets);
	return CInternalLHashAddDataBeforeWithKnownHash(a_hashTbl, a_itemAfter, a_data, a_key, a_keySize, hash);
}



CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataToBegWithKnownHash(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	if (a_hashTbl->first) {
		return CInternalLHashAddDataBeforeWithKnownHash(a_hashTbl, a_hashTbl->first, a_data, a_key, a_keySize, a_hash);
	}

	return CInternalLHashAddFirstDataWithKnownHashInline(a_hashTbl, a_data, a_key, a_keySize, a_hash);
}


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataToBegIfNotExists(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	if (CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, &unHash)) {
		return CPPUTILS_NULL;
	}
	return CInternalLHashAddDataToBegWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, unHash);
}


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataToBegEvenIfExist(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hash.hasher))(a_key, a_keySize)) % (a_hashTbl->hash.numberOfBaskets);
	return CInternalLHashAddDataToBegWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, hash);
}


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataToEndWithKnownHash(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	if (a_hashTbl->last) {
		return CInternalLHashAddDataAfterWithKnownHash(a_hashTbl, a_hashTbl->last, a_data, a_key, a_keySize, a_hash);
	}

	return CInternalLHashAddFirstDataWithKnownHashInline(a_hashTbl, a_data, a_key, a_keySize, a_hash);
}


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataToEndIfNotExists(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	if (CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, &unHash)) {
		return CPPUTILS_NULL;
	}
	return CInternalLHashAddDataToEndWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, unHash);
}


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataToEndEvenIfExist(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hash.hasher))(a_key, a_keySize)) % (a_hashTbl->hash.numberOfBaskets);
	return CInternalLHashAddDataToEndWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, hash);
}


CINTERNAL_EXPORT bool CInternalLHashRemoveData(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	struct SCinternalLHashItem* const pIterator = CinternalHashItemToLHashItem(CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, &unHash));
	if (pIterator) {
		CInternalLHashRemoveDataEx(a_hashTbl, pIterator);
		return true;
	}
	return false;
}


CINTERNAL_EXPORT void CInternalLHashRemoveDataEx(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, CinternalLHashItem_t CPPUTILS_ARG_NN a_iter)
{
	if (a_iter->prev) { a_iter->prev->next = a_iter->next; }
	if (a_iter->next) { a_iter->next->prev = a_iter->prev; }
	if (a_iter == (a_hashTbl->first)) { a_hashTbl->first = a_iter->next; }
	if (a_iter == (a_hashTbl->last)) { a_hashTbl->last = a_iter->prev; }
	if (a_iter->hit.prevInTheBucket) { a_iter->hit.prevInTheBucket->nextInTheBucket = a_iter->hit.nextInTheBucket; }
	if (a_iter->hit.nextInTheBucket) { a_iter->hit.nextInTheBucket->prevInTheBucket = a_iter->hit.prevInTheBucket; }
	if (a_iter == CinternalHashItemToLHashItem(a_hashTbl->hash.ppTable[a_iter->hit.hash])) { a_hashTbl->hash.ppTable[a_iter->hit.hash] = a_iter->hit.nextInTheBucket; }

	(*(a_hashTbl->hash.keyUnstore))(a_hashTbl->hash.deallocator, a_iter->hit.key, a_iter->hit.keySize);
	(*(a_hashTbl->hash.deallocator))(a_iter);
	--(a_hashTbl->hash.m_size);
}


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashFindEx(ConstCinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash)
{
	return CinternalHashItemToLHashItem(CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, a_pHash));
}


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashFind(ConstCinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	return CinternalHashItemToLHashItem(CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, &unHash));
}


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashFirstItem(ConstCinternalLHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return a_hashTbl->first;
}


CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashLastItem(ConstCinternalLHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return a_hashTbl->last;
}


CINTERNAL_EXPORT size_t CInternalLHashSize(ConstCinternalLHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return a_hashTbl->hash.m_size;
}


CPPUTILS_END_C
