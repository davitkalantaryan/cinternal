//
// repo:			cinternal
// file:            shash.h
// path:			include/cinternal/shash.h
// created on:		2023 Oct 12
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#ifndef CINTERNAL_INCLUDE_CINTERNAL_SHASH_H
#define CINTERNAL_INCLUDE_CINTERNAL_SHASH_H

#include <cinternal/export_symbols.h>
#include <cinternal/common_data01.h>
#include <stdbool.h>

CPPUTILS_BEGIN_C

struct SCinternalSHash;

struct SCinternalSHashItem {
	struct SCinternalSHashItem	*prev, *next, *prevInTheBucket, *nextInTheBucket;
	void*						data;
	void*						key;
	size_t						keySize;
	size_t						hash;
};

typedef struct SCinternalSHashItem* CinternalSHashItem_t;
typedef struct SCinternalSHash* CinternalSHash_t;
typedef const struct SCinternalSHash* ConstCinternalSHash_t;


CINTERNAL_EXPORT CinternalSHash_t CInternalSHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalSHash_t CInternalSHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalSHash_t CInternalSHashCreateExAnyDefSmlInt(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalSHash_t CInternalSHashCreateExRawMem(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalSHash_t CInternalSHashCreateExSmlInt(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);;
CINTERNAL_EXPORT void	CInternalSHashDestroyEx(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashAddDataAfterWithKnownHash(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, 
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashAddDataAfterIfNotExists(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, 
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashAddDataAfterEvenIfExist(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, 
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemBefore, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashAddDataBeforeWithKnownHash(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashAddDataBeforeIfNotExists(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashAddDataBeforeEvenIfExist(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	CinternalSHashItem_t CPPUTILS_ARG_NN a_itemAfter, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashAddDataToBegWithKnownHash(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashAddDataToBegIfNotExists(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashAddDataToBegEvenIfExist(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashAddDataToEndWithKnownHash(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashAddDataToEndIfNotExists(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashAddDataToEndEvenIfExist(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);

CINTERNAL_EXPORT void	CInternalSHashRemoveDataEx(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, CinternalSHashItem_t CPPUTILS_ARG_NN a_iterator);
CINTERNAL_EXPORT bool	CInternalSHashRemoveData(CinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize);

CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashFindEx(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashFind(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashFirstItem(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl);
CINTERNAL_EXPORT CinternalSHashItem_t CInternalSHashLastItem(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl);
CINTERNAL_EXPORT size_t CInternalSHashSize(ConstCinternalSHash_t CPPUTILS_ARG_NN a_hashTbl);


CPPUTILS_END_C


#define CInternalSHashCreateRawMem(_size)											CInternalSHashCreateExRawMem(_size,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalSHashCreateSmlInt(_size)											CInternalSHashCreateExSmlInt(_size,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalSHashDestroy(_hashTbl)												CInternalSHashDestroyEx(_hashTbl,CPPUTILS_NULL)
#define CInternalSHashAddDataToBegIfNotExistsSmlInt(_hashTbl,_data,_key)			CInternalSHashAddDataToBegIfNotExists(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalSHashAddDataToBegEvenIfExistSmlInt(_hashTbl,_data,_key)			CInternalSHashAddDataToBegEvenIfExist(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalSHashAddDataToBegWithKnownHashSmlInt(_hashTbl,_data,_key,_hash)	CInternalSHashAddDataToBegWithKnownHash(_hashTbl,_data,((void*)((size_t)(_key))),0,_hash)
#define CInternalSHashAddDataToEndIfNotExistsSmlInt(_hashTbl,_data,_key)			CInternalSHashAddDataToEndIfNotExists(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalSHashAddDataToEndEvenIfExistSmlInt(_hashTbl,_data,_key)			CInternalSHashAddDataToEndEvenIfExist(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalSHashAddDataToEndWithKnownHashSmlInt(_hashTbl,_data,_key,_hash)	CInternalSHashAddDataToEndWithKnownHash(_hashTbl,_data,((void*)((size_t)(_key))),0,_hash)


#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_SHASH_H
