//
// repo:			cinternal
// file:            shash.h
// path:			include/cinternal/hash/lhash.h
// created on:		2023 Oct 12
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_LHASH_H
#define CINTERNAL_INCLUDE_CINTERNAL_HASH_LHASH_H

#include <cinternal/export_symbols.h>
#include <cinternal/common_data01.h>
#include <stdbool.h>

CPPUTILS_BEGIN_C

struct SCinternalLHash;

struct SCinternalLHashItem {
	struct SCinternalLHashItem	*prev, *next, *prevInTheBucket, *nextInTheBucket;
	void*						data;
	void*						key;
	size_t						keySize;
	size_t						hash;
};

typedef struct SCinternalLHashItem* CinternalSHashItem_t;
typedef struct SCinternalLHash* CinternalSHash_t;
typedef const struct SCinternalLHash* ConstCinternalSHash_t;


CINTERNAL_EXPORT CinternalSHash_t CInternalLHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalSHash_t CInternalLHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalSHash_t CInternalLHashCreateExAnyDefSmlInt(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalSHash_t CInternalLHashCreateExRawMem(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalSHash_t CInternalLHashCreateExSmlInt(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);;
CINTERNAL_EXPORT void	CInternalLHashDestroyEx(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataAfterWithKnownHash(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, 
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataAfterIfNotExists(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, 
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataAfterEvenIfExist(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, 
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataBeforeWithKnownHash(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataBeforeIfNotExists(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataBeforeEvenIfExist(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataToBegWithKnownHash(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataToBegIfNotExists(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataToBegEvenIfExist(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataToEndWithKnownHash(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataToEndIfNotExists(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashAddDataToEndEvenIfExist(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);

CINTERNAL_EXPORT void	CInternalLHashRemoveDataEx(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, CinternalSHashItem_t CPPUTILS_ARG_NN a_iterator);
CINTERNAL_EXPORT bool	CInternalLHashRemoveData(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize);

CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashFindEx(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashFind(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashFirstItem(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalLHashLastItem(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl);
CINTERNAL_EXPORT size_t CInternalLHashSize(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl);


CPPUTILS_END_C


#define CInternalLHashCreateRawMem(_size)											CInternalLHashCreateExRawMem(_size,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalLHashCreateSmlInt(_size)											CInternalLHashCreateExSmlInt(_size,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalLHashDestroy(_hashTbl)												CInternalLHashDestroyEx(_hashTbl,CPPUTILS_NULL)
#define CInternalLHashAddDataToBegIfNotExistsSmlInt(_hashTbl,_data,_key)			CInternalLHashAddDataToBegIfNotExists(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalLHashAddDataToBegEvenIfExistSmlInt(_hashTbl,_data,_key)			CInternalLHashAddDataToBegEvenIfExist(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalLHashAddDataToBegWithKnownHashSmlInt(_hashTbl,_data,_key,_hash)	CInternalLHashAddDataToBegWithKnownHash(_hashTbl,_data,((void*)((size_t)(_key))),0,_hash)
#define CInternalLHashAddDataToEndIfNotExistsSmlInt(_hashTbl,_data,_key)			CInternalLHashAddDataToEndIfNotExists(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalLHashAddDataToEndEvenIfExistSmlInt(_hashTbl,_data,_key)			CInternalLHashAddDataToEndEvenIfExist(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalLHashAddDataToEndWithKnownHashSmlInt(_hashTbl,_data,_key,_hash)	CInternalLHashAddDataToEndWithKnownHash(_hashTbl,_data,((void*)((size_t)(_key))),0,_hash)


#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_LHASH_H
