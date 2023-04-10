//
// file:            lhash.h
// path:			include/cinternal/hash/lhash.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_LHASH_H
#define CINTERNAL_INCLUDE_CINTERNAL_HASH_LHASH_H

#include <cinternal/export_symbols.h>
#include <cinternal/common_data01.h>
#include <stdbool.h>


CPPUTILS_BEGIN_C

#define CINTERNAL_HASH_DEFAULT_FUNC_MMEM_HASH		1
#define CINTERNAL_HASH_DEFAULT_FUNC_SML_INT_HASH	2

struct SCinternalLHashItem {
	struct SCinternalLHashItem* prevInTbl, * nextInTbl, * prevInList, * nextInList;
	void*				data;
	void*				key;
	size_t				keySize;
	size_t				hash;
};

typedef const struct SCinternalLHashItem* CInternalLHashIterator;
typedef struct SCinternalLHash* CinternalLHash_t;
typedef const struct SCinternalLHash* ConstCinternalLHash_t;


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExAny(size_t a_numberOfBaskets, 
	TypeCinternalHasher CPPUTILS_ARG_NONULL a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NONULL a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NONULL a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NONULL a_keyUnstore,
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
CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExSmlInt(size_t a_numberOfBaskets,TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT void	CInternalLHashDestroyEx(CinternalLHash_t a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashAddDataEvenIfExistBeforeIterator(CinternalLHash_t a_hashTbl, CInternalLHashIterator a_iter, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashAddDataIfNotExistsBeforeIterator(CinternalLHash_t a_hashTbl, CInternalLHashIterator a_iter, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashAddDataWithKnownHashBeforeIterator(CinternalLHash_t a_hashTbl, CInternalLHashIterator a_iter, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashAddDataEvenIfExistAfterIterator(CinternalLHash_t a_hashTbl, CInternalLHashIterator CPPUTILS_ARG_NO_NULL a_iter, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashAddDataIfNotExistsAfterIterator(CinternalLHash_t a_hashTbl, CInternalLHashIterator CPPUTILS_ARG_NO_NULL a_iter, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashAddDataWithKnownHashAfterIterator(CinternalLHash_t a_hashTbl, CInternalLHashIterator CPPUTILS_ARG_NO_NULL a_iter, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashFindEx(ConstCinternalLHash_t a_hashTbl, const void* a_key, size_t a_keySize,size_t* CPPUTILS_ARG_NO_NULL a_pHash);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashFind(ConstCinternalLHash_t a_hashTbl, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashFirstItem(ConstCinternalLHash_t a_hashTbl);
CINTERNAL_EXPORT void	CInternalLHashRemoveDataEx(CinternalLHash_t a_hashTbl, CInternalLHashIterator a_iterator);
CINTERNAL_EXPORT bool	CInternalLHashRemoveData(CinternalLHash_t a_hashTbl, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT size_t CInternalLHashSize(ConstCinternalLHash_t a_hashTbl);


CINTERNAL_EXPORT void* CInternalLHashGetDefaultFunctions(int a_function);


CPPUTILS_END_C

#define CInternalLHashCreateRawMem(_size)	CInternalLHashCreateExRawMem(_size,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalLHashCreateSmlInt(_size)	CInternalLHashCreateExSmlInt(_size,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalLHashDestroy(_hashTbl)		CInternalLHashDestroyEx(_hashTbl,CPPUTILS_NULL)
#define CInternalStrKeyPairFn(_str)			(_str),strlen(_str)  // to use this string.h should be included
#define CInternalSmallIntHPairFn(_data)		((void*)((size_t)(_data))), 0

#define CInternalLHashAddDataWithKnownHash(_hashTbl, _data, _key, _keySize, _hash)	\
	CInternalLHashAddDataWithKnownHashBeforeIterator(_hashTbl, CPPUTILS_NULL,_data, _key, _keySize, _hash)

#define CInternalLHashAddDataIfNotExists(_hashTbl,_data,_key,_keySize)					CInternalLHashAddDataIfNotExistsBeforeIterator(_hashTbl,CPPUTILS_NULL,_data,_key,_keySize)
#define CInternalLHashAddDataIfNotExistsBeforeIteratorSmlInt(_hashTbl,_iter,_data,_key)	CInternalLHashAddDataIfNotExistsBeforeIterator(_hashTbl,_iter,_data,((void*)((size_t)(_key))),0)
#define CInternalLHashAddDataIfNotExistsSmlInt(_hashTbl,_data,_key)						CInternalLHashAddDataIfNotExistsBeforeIteratorSmlInt(_hashTbl,CPPUTILS_NULL,_data,_key)
#define CInternalLHashAddDataIfNotExistsBeforeIteratorStr(_hashTbl,_iter,_data,_str)	CInternalLHashAddDataIfNotExistsBeforeIterator(_hashTbl,_iter,_data,(_str),strlen(_str))
#define CInternalLHashAddDataIfNotExistsStr(_hashTbl,_data,_str)						CInternalLHashAddDataIfNotExistsBeforeIteratorStr(_hashTbl,CPPUTILS_NULL,_data,_str)

#define CInternalLHashAddDataEvenIfExist(_hashTbl,_data,_key,_keySize)					CInternalLHashAddDataEvenIfExistBeforeIterator(_hashTbl,CPPUTILS_NULL,_data,_key,_keySize)
#define CInternalLHashAddDataEvenIfExistBeforeIteratorSmlInt(_hashTbl,_iter,_data,_key)	CInternalLHashAddDataEvenIfExistBeforeIterator(_hashTbl,_iter,_data,((void*)((size_t)(_key))),0)
#define CInternalLHashAddDataEvenIfExistSmlInt(_hashTbl,_data,_key)						CInternalLHashAddDataEvenIfExistBeforeIteratorSmlInt(_hashTbl,CPPUTILS_NULL,_data,_key)
#define CInternalLHashAddDataEvenIfExistBeforeIteratorStr(_hashTbl,_iter,_data,_str)	CInternalLHashAddDataEvenIfExistBeforeIterator(_hashTbl,_iter,_data,(_str),strlen(_str))
#define CInternalLHashAddDataEvenIfExistStr(_hashTbl,_data,_str)						CInternalLHashAddDataEvenIfExistBeforeIteratorStr(_hashTbl,CPPUTILS_NULL,_data,_str)

#define CInternalLHashAddDataIfNotExistsAfterIteratorSmlInt(_hashTbl,_iter,_data,_key)	CInternalLHashAddDataIfNotExistsAfterIterator(_hashTbl,_iter,_data,((void*)((size_t)(_key))),0)
#define CInternalLHashAddDataIfNotExistsAfterIteratorStr(_hashTbl,_iter,_data,_str)		CInternalLHashAddDataIfNotExistsAfterIterator(_hashTbl,_iter,_data,(_str),strlen(_str))
#define CInternalLHashAddDataEvenIfExistAfterIteratorSmlInt(_hashTbl,_iter,_data,_key)	CInternalLHashAddDataEvenIfExistAfterIterator(_hashTbl,_iter,_data,((void*)((size_t)(_key))),0)
#define CInternalLHashAddDataEvenIfExistAfterIteratorStr(_hashTbl,_iter,_data,_str)		CInternalLHashAddDataEvenIfExistAfterIterator(_hashTbl,_iter,_data,(_str),strlen(_str))


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_LHASH_H
