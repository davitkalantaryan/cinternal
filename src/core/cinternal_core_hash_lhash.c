//
// repo:			cinternal
// file:            cinternal_core_shash.c
// path:			src/core/cinternal_core_shash.c
// created on:		2023 Oct 11
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/hash/lhash.h>
#define cinternal_hash1_small_int_needed
#define CinternalIsMemoriesIdenticalSmallInt_needed
#define CinternalStoreKeySmallInt_needed
#define CinternalUnstoreKeySmallInt_needed
#define CinternalStoreKeyRawMemory_needed
#define CinternalUnstoreKeyRawMemory_needed
#define CinternalIsMemoriesIdenticalRawMemory_needed
#define DefaultRemainingCleaner_needed
#define cinternal_hash1_raw_mem_needed
#include <cinternal/hash/functions.h>
#include <stdlib.h>


#define CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS	4096


CPPUTILS_BEGIN_C


struct SCinternalLHash {
	TypeCinternalAllocator				allocator;
	TypeCinternalDeallocator			deallocator;
	struct SCinternalLHashItem			*first, *last;
	size_t								m_size;

	struct SCinternalLHashItem**		ppTable;
	size_t								numberOfBaskets;
	TypeCinternalHasher					hasher;
	TypeCinternalIsMemoriesIdentical	isEq;
	TypeCinternalStoreKey				keyStore;
	TypeCinternalUnstoreKey				keyUnstore;
};


static inline struct SCinternalLHashItem* CInternalHashFindItemInline(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash) {
	struct SCinternalLHashItem* pItem;
	*a_pHash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	pItem = a_hashTbl->ppTable[*a_pHash];
	while (pItem) {
		if ((*(a_hashTbl->isEq))(pItem->key,pItem->keySize, a_key, a_keySize)) {
			return pItem;
		}
		pItem = pItem->next;
	}
	return CPPUTILS_NULL;
}


static inline CinternalSHashItem_t CInternalLHashAddFirstDataWithKnownHashInline(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	struct SCinternalLHashItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalLHashItem*, (*(a_hashTbl->allocator))(sizeof(struct SCinternalLHashItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	if (!(*(a_hashTbl->keyStore))(a_hashTbl->allocator, &(pNewItem->key), &(pNewItem->keySize), a_key, a_keySize)) {
		(*(a_hashTbl->deallocator))(pNewItem);
		return CPPUTILS_NULL;
	}

	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);
	pNewItem->hash = a_hash;
	pNewItem->prev = CPPUTILS_NULL;
	pNewItem->next = CPPUTILS_NULL;
	a_hashTbl->last = a_hashTbl->first = pNewItem;
	//
	pNewItem->prevInTheBucket = CPPUTILS_NULL;
	pNewItem->nextInTheBucket = CPPUTILS_NULL;
	a_hashTbl->ppTable[a_hash] = pNewItem;

	a_hashTbl->m_size = 1;

	return pNewItem;
}


CINTERNAL_EXPORT CinternalSHash_t CInternalLHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	CinternalSHash_t pRet;
	size_t tableMemorySize;

	a_allocator = a_allocator ? a_allocator : (&malloc);

	pRet = CPPUTILS_STATIC_CAST(CinternalSHash_t, (*a_allocator)(sizeof(struct SCinternalLHash)));
	if (!pRet) {
		return CPPUTILS_NULL;
	}

	// init the list
	//CInternalDLListInitializeInline(&(pRet->lst), a_allocator, a_deallocator);
	pRet->allocator = a_allocator;
	pRet->deallocator = a_deallocator ? a_deallocator : (&free);
	pRet->last = pRet->first = CPPUTILS_NULL;
	pRet->m_size = 0;

	pRet->numberOfBaskets = (a_numberOfBaskets>0) ? a_numberOfBaskets : CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS;

	tableMemorySize = pRet->numberOfBaskets * sizeof(struct SCinternalLHashItem*);
	pRet->ppTable = CPPUTILS_STATIC_CAST(struct SCinternalLHashItem**, (*a_allocator)(tableMemorySize));
	if (!(pRet->ppTable)) {
		(*(pRet->deallocator))(pRet);
		return CPPUTILS_NULL;
	}
	memset(pRet->ppTable, 0, tableMemorySize);

	//pRet->hasher = a_hasher ? a_hasher : (&cinternal_hash1_);
	//pRet->isEq = a_isEq ? a_isEq : (&CinternaldefaultIsMemoriesIdentical);
	pRet->hasher = a_hasher;
	pRet->isEq = a_isEq;

	pRet->keyStore = a_keyStore;
	pRet->keyUnstore = a_keyUnstore;

	return pRet;
}


CINTERNAL_EXPORT CinternalSHash_t CInternalLHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalLHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_raw_mem), a_isEq ? a_isEq : (&CinternalIsMemoriesIdenticalRawMemory),
		a_keyStore ? a_keyStore : (&CinternalStoreKeyRawMemory), a_keyUnstore ? a_keyUnstore : (&CinternalUnstoreKeyRawMemory),
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT CinternalSHash_t CInternalLHashCreateExAnyDefSmlInt(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalLHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_small_int), a_isEq ? a_isEq : (&CinternalIsMemoriesIdenticalSmallInt),
		a_keyStore ? a_keyStore : (&CinternalStoreKeySmallInt), a_keyUnstore ? a_keyUnstore : (&CinternalUnstoreKeySmallInt),
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT CinternalSHash_t CInternalLHashCreateExRawMem(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalLHashCreateExAny(a_numberOfBaskets,
		&cinternal_hash1_raw_mem, &CinternalIsMemoriesIdenticalRawMemory,
		&CinternalStoreKeyRawMemory, &CinternalUnstoreKeyRawMemory,
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT CinternalSHash_t CInternalLHashCreateExSmlInt(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalLHashCreateExAny(a_numberOfBaskets,
		&cinternal_hash1_small_int, &CinternalIsMemoriesIdenticalSmallInt,
		&CinternalStoreKeySmallInt, &CinternalUnstoreKeySmallInt,
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT void CInternalLHashDestroyEx(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner)
{
	struct SCinternalLHashItem *pItemTmp, *pItem = a_hashTbl->first;
	a_remainingDataCleaner = a_remainingDataCleaner ? a_remainingDataCleaner : &DefaultRemainingCleaner;
	while (pItem) {
		pItemTmp = pItem->next;
		(*a_remainingDataCleaner)(pItem->data);
		(*(a_hashTbl->deallocator))(pItem);
		pItem = pItemTmp;
	}

	(*(a_hashTbl->deallocator))(a_hashTbl->ppTable);
	(*(a_hashTbl->deallocator))(a_hashTbl);
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataAfterWithKnownHash(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	struct SCinternalLHashItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalLHashItem*, (*(a_hashTbl->allocator))(sizeof(struct SCinternalLHashItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	if (!(*(a_hashTbl->keyStore))(a_hashTbl->allocator, &(pNewItem->key), &(pNewItem->keySize), a_key, a_keySize)) {
		(*(a_hashTbl->deallocator))(pNewItem);
		return CPPUTILS_NULL;
	}

	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);
	pNewItem->hash = a_hash;
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
	pNewItem->prevInTheBucket = CPPUTILS_NULL;
	pNewItem->nextInTheBucket = a_hashTbl->ppTable[a_hash];
	if (a_hashTbl->ppTable[a_hash]) { a_hashTbl->ppTable[a_hash]->prevInTheBucket = pNewItem; }
	a_hashTbl->ppTable[a_hash] = pNewItem;

	++(a_hashTbl->m_size);

	return pNewItem;
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataAfterIfNotExists(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	if (CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, &unHash)) {
		return CPPUTILS_NULL;
	}
	return CInternalLHashAddDataAfterWithKnownHash(a_hashTbl, a_itemBefore,a_data, a_key, a_keySize, unHash);
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataAfterEvenIfExist(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	return CInternalLHashAddDataAfterWithKnownHash(a_hashTbl, a_itemBefore,a_data, a_key, a_keySize, hash);
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataBeforeWithKnownHash(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	struct SCinternalLHashItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalLHashItem*, (*(a_hashTbl->allocator))(sizeof(struct SCinternalLHashItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	if (!(*(a_hashTbl->keyStore))(a_hashTbl->allocator, &(pNewItem->key), &(pNewItem->keySize), a_key, a_keySize)) {
		(*(a_hashTbl->deallocator))(pNewItem);
		return CPPUTILS_NULL;
	}

	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);
	pNewItem->hash = a_hash;
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
	pNewItem->prevInTheBucket = CPPUTILS_NULL;
	pNewItem->nextInTheBucket = a_hashTbl->ppTable[a_hash];
	if (a_hashTbl->ppTable[a_hash]) { a_hashTbl->ppTable[a_hash]->prevInTheBucket = pNewItem; }
	a_hashTbl->ppTable[a_hash] = pNewItem;

	++(a_hashTbl->m_size);

	return pNewItem;
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataBeforeIfNotExists(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	if (CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, &unHash)) {
		return CPPUTILS_NULL;
	}
	return CInternalLHashAddDataBeforeWithKnownHash(a_hashTbl, a_itemAfter, a_data, a_key, a_keySize, unHash);
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataBeforeEvenIfExist(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	return CInternalLHashAddDataBeforeWithKnownHash(a_hashTbl, a_itemAfter, a_data, a_key, a_keySize, hash);
}



CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataToBegWithKnownHash(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	if (a_hashTbl->first) {
		return CInternalLHashAddDataBeforeWithKnownHash(a_hashTbl, a_hashTbl->first, a_data, a_key, a_keySize, a_hash);
	}

	return CInternalLHashAddFirstDataWithKnownHashInline(a_hashTbl, a_data, a_key, a_keySize, a_hash);
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataToBegIfNotExists(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	if (CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, &unHash)) {
		return CPPUTILS_NULL;
	}
	return CInternalLHashAddDataToBegWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, unHash);
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataToBegEvenIfExist(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	return CInternalLHashAddDataToBegWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, hash);
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataToEndWithKnownHash(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	if (a_hashTbl->last) {
		return CInternalLHashAddDataAfterWithKnownHash(a_hashTbl, a_hashTbl->last, a_data, a_key, a_keySize, a_hash);
	}

	return CInternalLHashAddFirstDataWithKnownHashInline(a_hashTbl, a_data, a_key, a_keySize, a_hash);
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataToEndIfNotExists(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	if (CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, &unHash)) {
		return CPPUTILS_NULL;
	}
	return CInternalLHashAddDataToEndWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, unHash);
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataToEndEvenIfExist(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	return CInternalLHashAddDataToEndWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, hash);
}


CINTERNAL_EXPORT bool CInternalLHashRemoveData(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	struct SCinternalLHashItem* pIterator = CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, &unHash);
	if (pIterator) {
		CInternalLHashRemoveDataEx(a_hashTbl, pIterator);
		return true;
	}
	return false;
}


CINTERNAL_EXPORT void CInternalLHashRemoveDataEx(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, CinternalSHashItem_t CPPUTILS_ARG_NN a_iter)
{
	if (a_iter->prev) { a_iter->prev->next = a_iter->next; }
	if (a_iter->next) { a_iter->next->prev = a_iter->prev; }
	if (a_iter == (a_hashTbl->first)) { a_hashTbl->first = a_iter->next; }
	if (a_iter == (a_hashTbl->last)) { a_hashTbl->last = a_iter->prev; }
	if (a_iter->prevInTheBucket) { a_iter->prevInTheBucket->nextInTheBucket = a_iter->nextInTheBucket; }
	if (a_iter->nextInTheBucket) { a_iter->nextInTheBucket->prevInTheBucket = a_iter->prevInTheBucket; }
	if (a_iter == (a_hashTbl->ppTable[a_iter->hash])) { a_hashTbl->ppTable[a_iter->hash] = a_iter->nextInTheBucket; }

	(*(a_hashTbl->keyUnstore))(a_hashTbl->deallocator, a_iter->key, a_iter->keySize);
	(*(a_hashTbl->deallocator))(a_iter);
	--(a_hashTbl->m_size);
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashFindEx(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash)
{
	return CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, a_pHash);
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashFind(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	return CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, &unHash);
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashFirstItem(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return a_hashTbl->first;
}


CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashLastItem(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return a_hashTbl->last;
}


CINTERNAL_EXPORT size_t CInternalLHashSize(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return a_hashTbl->m_size;
}


CPPUTILS_END_C
