//
// repo:			cinternal
// file:            cinternal_core_vhash.c
// path:			src/core/cinternal_core_vhash.c
// created on:		2023 Oct 11
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// comment:			vector hash
//


#include <cinternal/hash/vhash.h>
//#define CInternalHashAddFirstDataWithKnownHashInline_needed		1
#define CInternalHashFindItemInline_needed						1
#define cinternal_hash1_small_int_needed						1
#define CinternalIsMemoriesIdenticalSmallInt_needed				1
#define CinternalStoreKeySmallInt_needed						1
#define CinternalUnstoreKeySmallInt_needed						1
#define CinternalStoreKeyRawMemory_needed						1
#define CinternalUnstoreKeyRawMemory_needed						1
#define CinternalIsMemoriesIdenticalRawMemory_needed			1
//#define DefaultRemainingCleaner_needed							1
#define cinternal_hash1_raw_mem_needed							1
#include <cinternal/hash/functions.h>
#include <stdlib.h>

#ifdef _MSC_VER
#pragma warning(disable:5039)
#endif


#define CINTERNAL_VECTOR_RESIZE_SIZE				1024
#define CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS	4096
#define CinternalHashToVHash(_hash)					CPPUTILS_STATIC_CAST(struct SCinternalVHash*,CPPUTILS_STATIC_CAST(void*,_hash))
#define CinternalHashItemToVHashItem(_hashItem)		CPPUTILS_STATIC_CAST(struct SCinternalVHashItem*,CPPUTILS_STATIC_CAST(void*,_hashItem))


CPPUTILS_BEGIN_C


struct SCinternalVHash {
	struct SCinternalHash				hash;
	TypeCinternalReallocator			reallocator;
	struct SCinternalVHashItem**		ppVector;
};


static inline void CInternalVHashClearExInline(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner)
{
	size_t i;
	for (i = 0; i < a_hashTbl->hash.m_size; ++i) {
		a_hashTbl->hash.ppTable[a_hashTbl->ppVector[i]->hit.hash] = CPPUTILS_NULL;
		(*a_remainingDataCleaner)(a_hashTbl->ppVector[i]->hit.data);
		(*(a_hashTbl->hash.deallocator))(a_hashTbl->ppVector[i]);
	}

	(*(a_hashTbl->hash.deallocator))(a_hashTbl->ppVector);
	//a_hashTbl->ppVector = CPPUTILS_NULL;
	//a_hashTbl->hash.m_size = 0;
}


//static inline CinternalLHashItem_t CInternalLHashAddFirstDataWithKnownHashInline(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
//	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
//{
//	struct SCinternalLHashItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalLHashItem*, (*(a_hashTbl->hash.allocator))(sizeof(struct SCinternalLHashItem)));
//	if (!pNewItem) {
//		return CPPUTILS_NULL;
//	}
//
//	if (!CInternalHashAddFirstDataWithKnownHashInline(&(a_hashTbl->hash), &(pNewItem->hit), a_data, a_key, a_keySize, a_hash)) {
//		(*(a_hashTbl->hash.deallocator))(pNewItem);
//		return CPPUTILS_NULL;
//	}
//
//	pNewItem->prev = CPPUTILS_NULL;
//	pNewItem->next = CPPUTILS_NULL;
//	a_hashTbl->last = a_hashTbl->first = pNewItem;
//	//
//
//	return pNewItem;
//}


CINTERNAL_EXPORT CinternalVHash_t CInternalVHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator, TypeCinternalReallocator a_reallocator)
{
	CinternalVHash_t pRet;
	size_t tableMemorySize;

	a_allocator = a_allocator ? a_allocator : (&malloc);

	pRet = CPPUTILS_STATIC_CAST(CinternalVHash_t, (*a_allocator)(sizeof(struct SCinternalVHash)));
	if (!pRet) {
		return CPPUTILS_NULL;
	}

	// init the list
	//CInternalDLListInitializeInline(&(pRet->lst), a_allocator, a_deallocator);
	pRet->reallocator = a_reallocator ? a_reallocator : (&realloc);
	pRet->hash.allocator = a_allocator;
	pRet->hash.deallocator = a_deallocator ? a_deallocator : (&free);
	pRet->hash.m_size = 0;
	pRet->hash.numberOfBaskets = (a_numberOfBaskets > 0) ? a_numberOfBaskets : CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS;
	pRet->ppVector = CPPUTILS_NULL;

	tableMemorySize = pRet->hash.numberOfBaskets * sizeof(struct SCinternalVHashItem*);
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


CINTERNAL_EXPORT CinternalVHash_t CInternalVHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator, TypeCinternalReallocator a_reallocator)
{
	return CInternalVHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_raw_mem), a_isEq ? a_isEq : (&CinternalIsMemoriesIdenticalRawMemory),
		a_keyStore ? a_keyStore : (&CinternalStoreKeyRawMemory), a_keyUnstore ? a_keyUnstore : (&CinternalUnstoreKeyRawMemory),
		a_allocator, a_deallocator, a_reallocator);
}


CINTERNAL_EXPORT CinternalVHash_t CInternalVHashCreateExAnyDefSmlInt(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator, TypeCinternalReallocator a_reallocator)
{
	return CInternalVHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_small_int), a_isEq ? a_isEq : (&CinternalIsMemoriesIdenticalSmallInt),
		a_keyStore ? a_keyStore : (&CinternalStoreKeySmallInt), a_keyUnstore ? a_keyUnstore : (&CinternalUnstoreKeySmallInt),
		a_allocator, a_deallocator, a_reallocator);
}


CINTERNAL_EXPORT CinternalVHash_t CInternalVHashCreateExRawMem(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator, TypeCinternalReallocator a_reallocator)
{
	return CInternalVHashCreateExAny(a_numberOfBaskets,
		&cinternal_hash1_raw_mem, &CinternalIsMemoriesIdenticalRawMemory,
		&CinternalStoreKeyRawMemory, &CinternalUnstoreKeyRawMemory,
		a_allocator, a_deallocator, a_reallocator);
}


CINTERNAL_EXPORT CinternalVHash_t CInternalVHashCreateExSmlInt(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator, TypeCinternalReallocator a_reallocator)
{
	return CInternalVHashCreateExAny(a_numberOfBaskets,
		&cinternal_hash1_small_int, &CinternalIsMemoriesIdenticalSmallInt,
		&CinternalStoreKeySmallInt, &CinternalUnstoreKeySmallInt,
		a_allocator, a_deallocator, a_reallocator);
}


CINTERNAL_EXPORT void CInternalVHashDestroyEx(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner)
{
	CInternalVHashClearExInline(a_hashTbl, a_remainingDataCleaner);
	(*(a_hashTbl->hash.deallocator))(a_hashTbl->hash.ppTable);
	(*(a_hashTbl->hash.deallocator))(a_hashTbl);
}


CINTERNAL_EXPORT void CInternalVHashClearEx(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner)
{
	CInternalVHashClearExInline(a_hashTbl, a_remainingDataCleaner);
	a_hashTbl->ppVector = CPPUTILS_NULL;
	a_hashTbl->hash.m_size = 0;
}


CINTERNAL_EXPORT CinternalVHashItem_t CInternalVHashAddDataToEndWithKnownHash(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	struct SCinternalVHashItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalVHashItem*, (*(a_hashTbl->hash.allocator))(sizeof(struct SCinternalVHashItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	if (!(*(a_hashTbl->hash.keyStore))(a_hashTbl->hash.allocator, &(pNewItem->hit.key), &(pNewItem->hit.keySize), a_key, a_keySize)) {
		(*(a_hashTbl->hash.deallocator))(pNewItem);
		return CPPUTILS_NULL;
	}

	pNewItem->index = a_hashTbl->hash.m_size;
	//
	pNewItem->hit.data = CPPUTILS_CONST_CAST(void*, a_data);
	pNewItem->hit.hash = a_hash;
	pNewItem->hit.prevInTheBucket = CPPUTILS_NULL;
	pNewItem->hit.nextInTheBucket = a_hashTbl->hash.ppTable[a_hash];
	if (a_hashTbl->hash.ppTable[a_hash]) { a_hashTbl->hash.ppTable[a_hash]->prevInTheBucket = &(pNewItem->hit); }
	a_hashTbl->hash.ppTable[a_hash] = &(pNewItem->hit);

	//++(a_hashTbl->hash.m_size);
	if (((a_hashTbl->hash.m_size) % CINTERNAL_VECTOR_RESIZE_SIZE) == 0) {
		const size_t cunNewSize = a_hashTbl->hash.m_size + CINTERNAL_VECTOR_RESIZE_SIZE;
		struct SCinternalVHashItem** ppVectorTmp = (struct SCinternalVHashItem**)((*a_hashTbl->reallocator)(a_hashTbl->ppVector, cunNewSize * sizeof(struct SCinternalVHashItem*)));
		if (!ppVectorTmp) {
			return CPPUTILS_NULL;
		}
		a_hashTbl->ppVector = ppVectorTmp;
	}
	a_hashTbl->ppVector[(a_hashTbl->hash.m_size)++] = pNewItem;

	return pNewItem;
}


CINTERNAL_EXPORT CinternalVHashItem_t CInternalVHashAddDataToEndIfNotExists(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	if (CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, &unHash)) {
		return CPPUTILS_NULL;
	}
	return CInternalVHashAddDataToEndWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, unHash);
}


CINTERNAL_EXPORT CinternalVHashItem_t CInternalVHashAddDataToEndEvenIfExist(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hash.hasher))(a_key, a_keySize)) % (a_hashTbl->hash.numberOfBaskets);
	return CInternalVHashAddDataToEndWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, hash);
}


CINTERNAL_EXPORT void CInternalVHashRemoveDataEx(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl, CinternalVHashItem_t CPPUTILS_ARG_NN a_iter)
{
	size_t unIndex1 = a_iter->index;
	size_t unIndex2 = a_iter->index+1;

	for (; unIndex2 < a_hashTbl->hash.m_size; ++unIndex1,++unIndex2) {
		++((a_hashTbl->ppVector)[unIndex2]->index);
		(a_hashTbl->ppVector)[unIndex1] = (a_hashTbl->ppVector)[unIndex2];
	}

	if (a_iter->hit.prevInTheBucket) { a_iter->hit.prevInTheBucket->nextInTheBucket = a_iter->hit.nextInTheBucket; }
	if (a_iter->hit.nextInTheBucket) { a_iter->hit.nextInTheBucket->prevInTheBucket = a_iter->hit.prevInTheBucket; }
	if (a_iter == CinternalHashItemToVHashItem(a_hashTbl->hash.ppTable[a_iter->hit.hash])) { a_hashTbl->hash.ppTable[a_iter->hit.hash] = a_iter->hit.nextInTheBucket; }

	(*(a_hashTbl->hash.keyUnstore))(a_hashTbl->hash.deallocator, a_iter->hit.key, a_iter->hit.keySize);
	(*(a_hashTbl->hash.deallocator))(a_iter);
	--(a_hashTbl->hash.m_size);
}


CINTERNAL_EXPORT bool CInternalVHashRemoveData(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	struct SCinternalVHashItem* const pIterator = CinternalHashItemToVHashItem(CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, &unHash));
	if (pIterator) {
		CInternalVHashRemoveDataEx(a_hashTbl, pIterator);
		return true;
	}
	return false;
}


CINTERNAL_EXPORT CinternalVHashItem_t CInternalVHashFindEx(ConstCinternalVHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash)
{
	return CinternalHashItemToVHashItem(CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, a_pHash));
}


CINTERNAL_EXPORT CinternalVHashItem_t CInternalVHashFind(ConstCinternalVHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	return CinternalHashItemToVHashItem(CInternalHashFindItemInline(&(a_hashTbl->hash), a_key, a_keySize, &unHash));
}


CINTERNAL_EXPORT CinternalVHashItem_t CInternalVHashFirstItem(ConstCinternalVHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return a_hashTbl->ppVector[0];
}


CINTERNAL_EXPORT CinternalVHashItem_t CInternalVHashLastItem(ConstCinternalVHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return a_hashTbl->ppVector[a_hashTbl->hash.m_size-1];
}


CINTERNAL_EXPORT size_t CInternalVHashSize(ConstCinternalVHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return a_hashTbl->hash.m_size;
}


CINTERNAL_EXPORT struct SCinternalVHashItem** CInternalVHashVector(ConstCinternalVHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return a_hashTbl->ppVector;
}


CPPUTILS_END_C
