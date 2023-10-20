//
// repo:			cinternal
// file:            vhash.h
// path:			include/cinternal/hash/vhash.h
// created on:		2023 Oct 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// comment:			vector hash
//


#ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_VHASH_H
#define CINTERNAL_INCLUDE_CINTERNAL_HASH_VHASH_H

#include <cinternal/export_symbols.h>
#include <cinternal/hash/data.h>
#include <stdbool.h>

CPPUTILS_BEGIN_C

struct SCinternalVHash;

struct SCinternalVHashItem {
	struct SCinternalHashItem	hit;
	size_t						index;
};

typedef struct SCinternalVHashItem* CinternalVHashItem_t;
typedef struct SCinternalVHash* CinternalVHash_t;
typedef const struct SCinternalVHash* ConstCinternalVHash_t;


CINTERNAL_EXPORT CinternalVHash_t CInternalVHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator, TypeCinternalReallocator a_reallocator);
CINTERNAL_EXPORT CinternalVHash_t CInternalVHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator, TypeCinternalReallocator a_reallocator);
CINTERNAL_EXPORT CinternalVHash_t CInternalVHashCreateExAnyDefSmlInt(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator, TypeCinternalReallocator a_reallocator);
CINTERNAL_EXPORT CinternalVHash_t CInternalVHashCreateExRawMem(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator, TypeCinternalReallocator a_reallocator);
CINTERNAL_EXPORT CinternalVHash_t CInternalVHashCreateExSmlInt(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator, TypeCinternalReallocator a_reallocator);
CINTERNAL_EXPORT void	CInternalVHashDestroyEx(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner);
CINTERNAL_EXPORT void	CInternalVHashClearEx(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner);
CINTERNAL_EXPORT CinternalVHashItem_t CInternalVHashAddDataToEndWithKnownHash(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalVHashItem_t CInternalVHashAddDataToEndIfNotExists(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalVHashItem_t CInternalVHashAddDataToEndEvenIfExist(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT void	CInternalVHashRemoveDataEx(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl, CinternalVHashItem_t CPPUTILS_ARG_NN a_iterator);
CINTERNAL_EXPORT bool	CInternalVHashRemoveData(CinternalVHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalVHashItem_t CInternalVHashFindEx(ConstCinternalVHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash);
CINTERNAL_EXPORT CinternalVHashItem_t CInternalVHashFind(ConstCinternalVHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalVHashItem_t CInternalVHashFirstItem(ConstCinternalVHash_t CPPUTILS_ARG_NN a_hashTbl);
CINTERNAL_EXPORT CinternalVHashItem_t CInternalVHashLastItem(ConstCinternalVHash_t CPPUTILS_ARG_NN a_hashTbl);
CINTERNAL_EXPORT size_t CInternalVHashSize(ConstCinternalVHash_t CPPUTILS_ARG_NN a_hashTbl);
CINTERNAL_EXPORT struct SCinternalVHashItem** CInternalVHashVector(ConstCinternalVHash_t CPPUTILS_ARG_NN a_hashTbl);



CPPUTILS_END_C


#define CInternalVHashCreateRawMem(_size)											CInternalVHashCreateExRawMem(_size,CPPUTILS_NULL,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalVHashCreateSmlInt(_size)											CInternalVHashCreateExSmlInt(_size,CPPUTILS_NULL,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalVHashDestroy(_hashTbl)												CInternalVHashDestroyEx(_hashTbl,CPPUTILS_NULL)
#define CInternalVHashAddDataToEndIfNotExistsSmlInt(_hashTbl,_data,_key)			CInternalVHashAddDataToEndIfNotExists(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalVHashAddDataToEndEvenIfExistSmlInt(_hashTbl,_data,_key)			CInternalVHashAddDataToEndEvenIfExist(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalVHashAddDataToEndWithKnownHashSmlInt(_hashTbl,_data,_key,_hash)	CInternalVHashAddDataToEndWithKnownHash(_hashTbl,_data,((void*)((size_t)(_key))),0,_hash)


#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_VHASH_H
