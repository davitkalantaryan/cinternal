//
// file:            cinternal_core_hash_dllhash.c
// path:			src/core/cinternal_core_hash_dllhash.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/hash/dllhash.h>
#define CINTERNAL_SRC_CORE_CINTERNAL_CORE_LIST_DLLIST_IMPL_H_NEEDED
#include "cinternal_core_list_dllist.impl.h"
#include <string.h>

#define CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS	4096

static size_t cinternal_hash1_raw_mem(const void* a_pKey, size_t a_unKeySize) CPPUTILS_NOEXCEPT;


CPPUTILS_BEGIN_C


struct CPPUTILS_DLL_PRIVATE SCinternalLHash {
	struct SCinternalDLList				lst;
	
	struct SCinternalListIterator**		ppTable;
	size_t								numberOfBaskets;
	TypeCinternalHasher					hasher;
	TypeCinternalIsMemoriesIdentical	isEq;
	TypeCinternalStoreKey				keyStore;
	TypeCinternalUnstoreKey				keyUnstore;
};

#define CInternalDLLHashFromDLLList(_list_ptr)			cpputils_container_of(_list_ptr,struct SCinternalLHash,lst)
#define CInternalHashItemFromTableIterator(_iter_ptr)	cpputils_container_of(_iter_ptr,struct SCinternalLHashItem,tbl)


static size_t cinternal_hash1_small_int(const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_keySize);
	return CPPUTILS_REINTERPRET_CAST(size_t, a_key);
}


static bool CinternalIsMemoriesIdenticalRawMemory(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT
{
	return (a_keySize1 == a_keySize2) && (memcmp(a_key1, a_key2, a_keySize1) == 0);
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
	*a_pKeyStore = CPPUTILS_CONST_CAST(void*,a_key);
	return true;
}


static void CinternalUnstoreKeySmallInt(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_deallocator);
	CPPUTILS_STATIC_CAST(void, a_key);
	CPPUTILS_STATIC_CAST(void, a_keySize);
}


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NONULL a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NONULL a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NONULL a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NONULL a_keyUnstore,
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
	CInternalDLListInitializeInline(&(pRet->lst), a_allocator, a_deallocator);

	pRet->numberOfBaskets = a_numberOfBaskets ? a_numberOfBaskets : CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS;

	tableMemorySize = pRet->numberOfBaskets * sizeof(struct SCinternalListIterator*);
	pRet->ppTable = CPPUTILS_STATIC_CAST(struct SCinternalListIterator**, (*a_allocator)(tableMemorySize));
	if (!(pRet->ppTable)) {
		(*(pRet->lst.deallocator))(pRet);
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


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalLHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_raw_mem), a_isEq ? a_isEq :(&CinternalIsMemoriesIdenticalRawMemory),
		a_keyStore ? a_keyStore : (&CinternalStoreKeyRawMemory), a_keyUnstore ? a_keyUnstore :(&CinternalUnstoreKeyRawMemory),
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


static void CinternalDLListItemExtraCleaner(CinternalDLList_t a_list, struct SCinternalListIterator* a_iter, TypeCinternalDeallocator a_remainingDataCleaner)
{
	(*a_remainingDataCleaner)(CInternalDLLHashItemFromListIterator(a_iter)->lst.data);
	(*(CInternalDLLHashFromDLLList(a_list)->keyUnstore))(a_list->deallocator, 
		CInternalDLLHashItemFromListIterator(a_iter)->key, CInternalDLLHashItemFromListIterator(a_iter)->keySize);
}


CINTERNAL_EXPORT void CInternalLHashDestroyEx(CinternalLHash_t a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner)
{
	CInternalListCleanInline(&(a_hashTbl->lst), a_remainingDataCleaner, &CinternalDLListItemExtraCleaner);
	(*(a_hashTbl->lst.deallocator))(a_hashTbl->ppTable);
	(*(a_hashTbl->lst.deallocator))(a_hashTbl);
}


CINTERNAL_EXPORT CinternalListIterator_t CInternalLHashAddDataEvenIfExistBeforeIterator(CinternalLHash_t a_hashTbl, CinternalListIterator_t a_iter, const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	return CInternalLHashAddDataWithKnownHashBeforeIterator(a_hashTbl, a_iter, a_data, a_key, a_keySize, hash);
}


static inline struct SCinternalListIterator* CInternalHashFindItemInline(ConstCinternalLHash_t a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NO_NULL a_pHash) {
	struct SCinternalListIterator* pItem;
	*a_pHash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	pItem = a_hashTbl->ppTable[*a_pHash];
	while (pItem) {
		// todo: delete below line
		const size_t cunOffset = cpputils_offsetof(const struct SCinternalLHashItem, tbl);
		const struct SCinternalLHashItem* pItemC = CInternalHashItemFromTableIterator(pItem);
		(void)pItemC;
		(void)cunOffset;
		if ((*(a_hashTbl->isEq))(CInternalHashItemFromTableIterator(pItem)->key, CInternalHashItemFromTableIterator(pItem)->keySize, a_key, a_keySize)) {
			return &(CInternalHashItemFromTableIterator(pItem)->lst.itr);
		}
		pItem = pItem->next;
	}
	return CPPUTILS_NULL;
}


CINTERNAL_EXPORT CinternalListIterator_t CInternalLHashAddDataIfNotExistsBeforeIterator(CinternalLHash_t a_hashTbl, CinternalListIterator_t a_iter, const void* a_data, const void* a_key, size_t a_keySize)
{
	size_t hash;
	if (CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize,&hash)) {
		return CPPUTILS_NULL;
	}
	return CInternalLHashAddDataWithKnownHashBeforeIterator(a_hashTbl, a_iter,a_data, a_key, a_keySize, hash);
}


CINTERNAL_EXPORT CinternalListIterator_t CInternalLHashAddDataEvenIfExistAfterIterator(CinternalLHash_t a_hashTbl, CinternalListIterator_t CPPUTILS_ARG_NO_NULL a_iter, const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	return CInternalLHashAddDataWithKnownHashAfterIterator(a_hashTbl, a_iter, a_data, a_key, a_keySize, hash);
}


CINTERNAL_EXPORT CinternalListIterator_t CInternalLHashAddDataIfNotExistsAfterIterator(CinternalLHash_t a_hashTbl, CinternalListIterator_t CPPUTILS_ARG_NO_NULL a_iter, const void* a_data, const void* a_key, size_t a_keySize)
{
	size_t hash;
	if (CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, &hash)) {
		return CPPUTILS_NULL;
	}
	return CInternalLHashAddDataWithKnownHashAfterIterator(a_hashTbl, a_iter, a_data, a_key, a_keySize, hash);
}


CINTERNAL_EXPORT CinternalListIterator_t CInternalLHashAddDataWithKnownHashAfterIterator(CinternalLHash_t a_hashTbl, CinternalListIterator_t CPPUTILS_ARG_NO_NULL a_iter, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	return CInternalLHashAddDataWithKnownHashBeforeIterator(a_hashTbl, a_iter->next, a_data, a_key,a_keySize,a_hash);
}


CINTERNAL_EXPORT CinternalListIterator_t CInternalLHashAddDataWithKnownHashBeforeIterator(CinternalLHash_t a_hashTbl, CinternalListIterator_t a_iter, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	struct SCinternalLHashItem*const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalLHashItem*, (*(a_hashTbl->lst.allocator))(sizeof(struct SCinternalLHashItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	if (!(*(a_hashTbl->keyStore))(a_hashTbl->lst.allocator, &(pNewItem->key), &(pNewItem->keySize), a_key, a_keySize)) {
		(*(a_hashTbl->lst.deallocator))(pNewItem);
		return CPPUTILS_NULL;
	}

	// list related part
	pNewItem->lst.data = CPPUTILS_CONST_CAST(void*, a_data);
	CInternalDLListAddCreatedIteratorBeforeIteratorInline(&(a_hashTbl->lst), a_iter, &(pNewItem->lst.itr));
	// end list related part

	pNewItem->tbl.prev = CPPUTILS_NULL;
	pNewItem->hash = a_hash;

	pNewItem->tbl.next = a_hashTbl->ppTable[a_hash];
	if (a_hashTbl->ppTable[a_hash]) {
		a_hashTbl->ppTable[a_hash]->prev = &(pNewItem->tbl);
	}
	a_hashTbl->ppTable[a_hash] = &(pNewItem->tbl);

	return &(pNewItem->lst.itr);
}


CINTERNAL_EXPORT CinternalListIterator_t CInternalLHashFindEx(ConstCinternalLHash_t a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NO_NULL a_pHash)
{
	return CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, a_pHash);
}


CINTERNAL_EXPORT CinternalListIterator_t CInternalLHashFind(ConstCinternalLHash_t a_hashTbl, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	return CInternalLHashFindEx(a_hashTbl,a_key,a_keySize,&unHash);
}


CINTERNAL_EXPORT CinternalListIterator_t CInternalLHashFirstItem(ConstCinternalLHash_t a_hashTbl)
{
	return a_hashTbl->lst.first;
}


CINTERNAL_EXPORT bool CInternalLHashRemoveData(CinternalLHash_t a_hashTbl, const void* a_key, size_t a_keySize)
{
	CinternalListIterator_t pIterator = CInternalLHashFind(a_hashTbl, a_key, a_keySize);
	if (pIterator) {
		CInternalLHashRemoveDataEx(a_hashTbl, pIterator);
		return true;
	}
	return false;
}


CINTERNAL_EXPORT void CInternalLHashRemoveDataEx(CinternalLHash_t a_hashTbl, CinternalListIterator_t a_iter)
{
	CInternalListRemoveItertaorInline(&(a_hashTbl->ppTable[CInternalDLLHashItemFromListIterator(a_iter)->hash]), &(CInternalDLLHashItemFromListIterator(a_iter)->tbl));
	CInternalDLListRemoveDataNoFreeInline(&(a_hashTbl->lst), a_iter);

	(*(a_hashTbl->keyUnstore))(a_hashTbl->lst.deallocator, CInternalDLLHashItemFromListIterator(a_iter)->key, CInternalDLLHashItemFromListIterator(a_iter)->keySize);
	(*(a_hashTbl->lst.deallocator))(CPPUTILS_CONST_CAST(struct SCinternalLHashItem*, CInternalDLLHashItemFromListIterator(a_iter)));
}


CINTERNAL_EXPORT size_t CInternalLHashSize(ConstCinternalLHash_t a_hashTbl)
{
	return a_hashTbl->lst.m_size;
}


CINTERNAL_EXPORT void* CInternalLHashGetDefaultFunctions(int a_function)
{
	switch (a_function) {
	case CINTERNAL_HASH_DEFAULT_FUNC_MMEM_HASH:
		return (void*)(&cinternal_hash1_raw_mem);
	case CINTERNAL_HASH_DEFAULT_FUNC_SML_INT_HASH:
		return (void*)(&cinternal_hash1_small_int);
	default:
		return CPPUTILS_NULL;
	}  //  switch (a_function) {
}


CPPUTILS_END_C




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
