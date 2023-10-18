//
// repo:			cinternal
// file:            phash.h
// path:			include/cinternal/hash/phash.h
// created on:		2023 Oct 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// comment:			pure hash
//


#ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_PHASH_H
#define CINTERNAL_INCLUDE_CINTERNAL_HASH_PHASH_H

#include <cinternal/export_symbols.h>
#include <cinternal/hash/data.h>
#include <stdbool.h>

CPPUTILS_BEGIN_C

struct SCinternalPHash;

struct SCinternalPHashItem {
	struct SCinternalHashItem	hit;
};

typedef struct SCinternalPHashItem* CinternalPHashItem_t;
typedef struct SCinternalPHash* CinternalPHash_t;
typedef const struct SCinternalPHash* ConstCinternalPHash_t;


CINTERNAL_EXPORT CinternalPHash_t CInternalPHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalPHash_t CInternalPHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalPHash_t CInternalPHashCreateExAnyDefSmlInt(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalPHash_t CInternalPHashCreateExRawMem(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalPHash_t CInternalPHashCreateExSmlInt(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT void	CInternalPHashDestroyEx(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner);
CINTERNAL_EXPORT void	CInternalPHashClearEx(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner);
CINTERNAL_EXPORT CinternalPHashItem_t CInternalPHashAddDataWithKnownHash(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalPHashItem_t CInternalPHashAddDataIfNotExists(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalPHashItem_t CInternalPHashAddDataEvenIfExist(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl,
	const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT void	CInternalPHashRemoveDataEx(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl, CinternalPHashItem_t CPPUTILS_ARG_NN a_iterator);
CINTERNAL_EXPORT bool	CInternalPHashRemoveData(CinternalPHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize);

CINTERNAL_EXPORT CinternalPHashItem_t CInternalPHashFindEx(ConstCinternalPHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash);
CINTERNAL_EXPORT CinternalPHashItem_t CInternalPHashFind(ConstCinternalPHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT size_t CInternalPHashSize(ConstCinternalPHash_t CPPUTILS_ARG_NN a_hashTbl);


CPPUTILS_END_C


#define CInternalPHashCreateRawMem(_size)											CInternalPHashCreateExRawMem(_size,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalPHashCreateSmlInt(_size)											CInternalPHashCreateExSmlInt(_size,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalPHashDestroy(_hashTbl)												CInternalPHashDestroyEx(_hashTbl,CPPUTILS_NULL)
#define CInternalPHashClear(_hashTbl)												CInternalPHashClearEx(_hashTbl,CPPUTILS_NULL)
#define CInternalPHashAddDataIfNotExistsSmlInt(_hashTbl,_data,_key)					CInternalPHashAddDataIfNotExists(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalPHashAddDataEvenIfExistSmlInt(_hashTbl,_data,_key)					CInternalPHashAddDataEvenIfExist(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalPHashAddDataWithKnownHashSmlInt(_hashTbl,_data,_key,_hash)			CInternalPHashAddDataWithKnownHash(_hashTbl,_data,((void*)((size_t)(_key))),0,_hash)


#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_PHASH_H
