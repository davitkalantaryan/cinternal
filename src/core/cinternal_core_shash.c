//
// repo:			cinternal
// file:            cinternal_core_shash.c
// path:			src/core/cinternal_core_shash.c
// created on:		2023 Oct 11
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/hash/lhash.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS	4096


static size_t cinternal_hash1_small_int(const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static bool CinternalIsMemoriesIdenticalSmallInt(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT;
static bool CinternalStoreKeySmallInt(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static void CinternalUnstoreKeySmallInt(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static size_t cinternal_hash1_raw_mem(const void* a_pKey, size_t a_unKeySize) CPPUTILS_NOEXCEPT;
static bool CinternalIsMemoriesIdenticalRawMemory(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT;
static bool CinternalStoreKeyRawMemory(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static void CinternalUnstoreKeyRawMemory(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static void DefaultRemainingCleaner(void* a_pData);

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


static size_t cinternal_hash1_small_int(const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_keySize);
	return CPPUTILS_REINTERPRET_CAST(size_t, a_key);
}


static bool CinternalIsMemoriesIdenticalSmallInt(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_keySize1);
	CPPUTILS_STATIC_CAST(void, a_keySize2);
	return (a_key1 == a_key2);
}


static bool CinternalStoreKeySmallInt(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_allocator);
	CPPUTILS_STATIC_CAST(void, a_keySize);
	CPPUTILS_STATIC_CAST(void, a_pKeySizeStore);
	*a_pKeyStore = CPPUTILS_CONST_CAST(void*, a_key);
	return true;
}


static void CinternalUnstoreKeySmallInt(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_deallocator);
	CPPUTILS_STATIC_CAST(void, a_key);
	CPPUTILS_STATIC_CAST(void, a_keySize);
}


static bool CinternalStoreKeyRawMemory(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
	*a_pKeyStore = (*a_allocator)(a_keySize);
	if (!(*a_pKeyStore)) {
		return false;
	}
	memcpy(*a_pKeyStore, a_key, a_keySize);
	*a_pKeySizeStore = a_keySize;
	return true;
}


static void CinternalUnstoreKeyRawMemory(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_keySize);
	(*a_deallocator)(a_key);
}


static bool CinternalIsMemoriesIdenticalRawMemory(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT
{
	return (a_keySize1 == a_keySize2) && (memcmp(a_key1, a_key2, a_keySize1) == 0);
}


static void DefaultRemainingCleaner(void* a_pData)
{
	CPPUTILS_STATIC_CAST(void, a_pData);
}


/* The mixing step */
#define mix2(a,b,c) \
{ \
  a=a-b;  a=a-c;  a=a^(c>>13); \
  b=b-c;  b=b-a;  b=b^(a<<8);  \
  c=c-a;  c=c-b;  c=c^(b>>13); \
  a=a-b;  a=a-c;  a=a^(c>>12); \
  b=b-c;  b=b-a;  b=b^(a<<16); \
  c=c-a;  c=c-b;  c=c^(b>>5);  \
  a=a-b;  a=a-c;  a=a^(c>>3);  \
  b=b-c;  b=b-a;  b=b^(a<<10); \
  c=c-a;  c=c-b;  c=c^(b>>15); \
}

static size_t cinternal_hash1_raw_mem(const void* a_pKey, size_t a_unKeySize) CPPUTILS_NOEXCEPT
{
	const uint32_t unKeySize = CPPUTILS_STATIC_CAST(uint32_t, a_unKeySize);
	CPPUTILS_REGISTER const uint8_t* k = CPPUTILS_STATIC_CAST(const uint8_t*, a_pKey);
	CPPUTILS_REGISTER uint32_t a, b, c;  /* the internal state */

	uint32_t          len;    /* how many key bytes still need mixing */

	/* Set up the internal state */
	len = unKeySize;
	a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
	c = 13;         /* variable initialization of internal state */

	/*---------------------------------------- handle most of the key */
	while (len >= 12) {
		a = a + (k[0] + (CPPUTILS_STATIC_CAST(uint32_t, k[1]) << 8) + (CPPUTILS_STATIC_CAST(uint32_t, k[2]) << 16) + (CPPUTILS_STATIC_CAST(uint32_t, k[3]) << 24));
		b = b + (k[4] + (CPPUTILS_STATIC_CAST(uint32_t, k[5]) << 8) + (CPPUTILS_STATIC_CAST(uint32_t, k[6]) << 16) + (CPPUTILS_STATIC_CAST(uint32_t, k[7]) << 24));
		c = c + (k[8] + (CPPUTILS_STATIC_CAST(uint32_t, k[9]) << 8) + (CPPUTILS_STATIC_CAST(uint32_t, k[10]) << 16) + (CPPUTILS_STATIC_CAST(uint32_t, k[11]) << 24));
		mix2(a, b, c);
		k = k + 12; len = len - 12;
	}

	/*------------------------------------- handle the last 11 bytes */
	c = c + unKeySize;

	/* all the case statements fall through */
	switch (len) {
	case 11: c = c + (CPPUTILS_STATIC_CAST(uint32_t, k[10]) << 24); CPPUTILS_FALLTHROUGH
	case 10: c = c + (CPPUTILS_STATIC_CAST(uint32_t, k[9]) << 16); CPPUTILS_FALLTHROUGH
	case 9: c = c + (CPPUTILS_STATIC_CAST(uint32_t, k[8]) << 8); CPPUTILS_FALLTHROUGH

		/* the first byte of c is reserved for the length */
	case 8: b = b + (CPPUTILS_STATIC_CAST(uint32_t, k[7]) << 24); CPPUTILS_FALLTHROUGH
	case 7: b = b + (CPPUTILS_STATIC_CAST(uint32_t, k[6]) << 16); CPPUTILS_FALLTHROUGH
	case 6: b = b + (CPPUTILS_STATIC_CAST(uint32_t, k[5]) << 8); CPPUTILS_FALLTHROUGH
	case 5: b = b + k[4]; CPPUTILS_FALLTHROUGH
	case 4: a = a + (CPPUTILS_STATIC_CAST(uint32_t, k[3]) << 24); CPPUTILS_FALLTHROUGH
	case 3: a = a + (CPPUTILS_STATIC_CAST(uint32_t, k[2]) << 16); CPPUTILS_FALLTHROUGH
	case 2: a = a + (CPPUTILS_STATIC_CAST(uint32_t, k[1]) << 8); CPPUTILS_FALLTHROUGH
	case 1: a = a + k[0];
		/* case 0: nothing left to add */
	}
	mix2(a, b, c);
	/*-------------------------------------------- report the result */

	return CPPUTILS_STATIC_CAST(size_t, c);
}
