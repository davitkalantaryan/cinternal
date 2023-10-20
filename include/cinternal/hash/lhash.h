//
// repo:			cinternal
// file:            lhash.h
// path:			include/cinternal/hash/lhash.h
// created on:		2023 Oct 12
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_LHASH_H
#define CINTERNAL_INCLUDE_CINTERNAL_HASH_LHASH_H

#include <cinternal/export_symbols.h>
#include <cinternal/hash/data.h>
#include <stdbool.h>

CPPUTILS_BEGIN_C

struct SCinternalLHash;

struct SCinternalLHashItem {
	struct SCinternalHashItem	hit;
	struct SCinternalLHashItem	*prev, *next;
};

typedef struct SCinternalLHashItem* CinternalLHashItem_t;
typedef struct SCinternalLHash* CinternalLHash_t;
typedef const struct SCinternalLHash* ConstCinternalLHash_t;


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExAnyDefSmlInt(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExRawMem(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExSmlInt(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT void	CInternalLHashDestroyEx(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner);
CINTERNAL_EXPORT void	CInternalLHashClearEx(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataAfterWithKnownHash(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, 
	CinternalLHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataAfterIfNotExists(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, 
	CinternalLHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataAfterEvenIfExist(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, 
	CinternalLHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataBeforeWithKnownHash(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalLHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataBeforeIfNotExists(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalLHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataBeforeEvenIfExist(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalLHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataToBegWithKnownHash(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataToBegIfNotExists(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataToBegEvenIfExist(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataToEndWithKnownHash(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataToEndIfNotExists(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashAddDataToEndEvenIfExist(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);

CINTERNAL_EXPORT void	CInternalLHashRemoveDataEx(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, CinternalLHashItem_t CPPUTILS_ARG_NN a_iterator);
CINTERNAL_EXPORT bool	CInternalLHashRemoveData(CinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize);

CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashFindEx(ConstCinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashFind(ConstCinternalLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashFirstItem(ConstCinternalLHash_t CPPUTILS_ARG_NN a_hashTbl);
CINTERNAL_EXPORT CinternalLHashItem_t CInternalLHashLastItem(ConstCinternalLHash_t CPPUTILS_ARG_NN a_hashTbl);
CINTERNAL_EXPORT size_t CInternalLHashSize(ConstCinternalLHash_t CPPUTILS_ARG_NN a_hashTbl);


CPPUTILS_END_C


#define CInternalLHashCreateRawMem(_size)											CInternalLHashCreateExRawMem(_size,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalLHashCreateSmlInt(_size)											CInternalLHashCreateExSmlInt(_size,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalLHashDestroy(_hashTbl)												CInternalLHashDestroyEx(_hashTbl,CPPUTILS_NULL)
#define CInternalLHashClear(_hashTbl)												CInternalLHashClearEx(_hashTbl,CPPUTILS_NULL)
#define CInternalLHashAddDataToBegIfNotExistsSmlInt(_hashTbl,_data,_key)			CInternalLHashAddDataToBegIfNotExists(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalLHashAddDataToBegEvenIfExistSmlInt(_hashTbl,_data,_key)			CInternalLHashAddDataToBegEvenIfExist(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalLHashAddDataToBegWithKnownHashSmlInt(_hashTbl,_data,_key,_hash)	CInternalLHashAddDataToBegWithKnownHash(_hashTbl,_data,((void*)((size_t)(_key))),0,_hash)
#define CInternalLHashAddDataToEndIfNotExistsSmlInt(_hashTbl,_data,_key)			CInternalLHashAddDataToEndIfNotExists(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalLHashAddDataToEndEvenIfExistSmlInt(_hashTbl,_data,_key)			CInternalLHashAddDataToEndEvenIfExist(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalLHashAddDataToEndWithKnownHashSmlInt(_hashTbl,_data,_key,_hash)	CInternalLHashAddDataToEndWithKnownHash(_hashTbl,_data,((void*)((size_t)(_key))),0,_hash)


#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_LHASH_H
