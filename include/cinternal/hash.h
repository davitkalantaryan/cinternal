//
// repo:			cinternal
// file:            hash.h
// path:			include/cinternal/hash.h
// created on:		2024 Dec 10
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// comment:			pure hash
//


#ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_H
#define CINTERNAL_INCLUDE_CINTERNAL_HASH_H

#include <cinternal/export_symbols.h>
#include <cinternal/common_data01.h>
#ifdef CPPUTILS_CPP_11_DEFINED
#ifdef _MSC_VER
#pragma warning(disable:4623)
#pragma warning(disable:4626)
#pragma warning(disable:5027)
#endif
#endif
#include <cinternal/disable_compiler_warnings.h>
#include <stddef.h>
#include <stdbool.h>
#include <cinternal/undisable_compiler_warnings.h>

CPPUTILS_BEGIN_C


#define SCinternalHashItemBase(_typeSize, _typeKey){    \
    void*       data;  \
    _typeKey    key; \
    _typeSize           keySize;    \
    _typeSize           hash;       \
}

typedef struct SCinternalHashFull*          CinternalHash_t;
typedef const struct SCinternalHashFull*    CinternalHashConst_t;
typedef const struct SCinternalHash*        CinternalHashConstBasic_t;
typedef struct SCinternalHashItem*          CinternalHashItem_t;

struct SCinternalHash {
    size_t                                  numberOfBaskets;
    size_t                                  count;
    TypeCinternalAllocator				    allocator;
    TypeCinternalDeallocator			    deallocator;
    TypeCinternalHasher					    hasher;
    TypeCinternalIsMemoriesIdentical	    isEq;
    TypeCinternalStoreKey				    keyStore;
    TypeCinternalUnstoreKey				    keyUnstore;
};

struct SCinternalHashItem SCinternalHashItemBase(const size_t, const void* const);

typedef bool (*CinternalHashTypeIter)(void*, CinternalHashItem_t);

CINTERNAL_EXPORT CinternalHash_t CInternalHashCreateAnyEx(size_t a_numberOfBaskets,
    TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
    TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
    TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT CinternalHash_t CInternalHashCreateRawMemEx(size_t a_numberOfBaskets,
    TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT CinternalHash_t CInternalHashCreateSmlIntEx(size_t a_numberOfBaskets,
    TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT CinternalHashConstBasic_t CinternalHashGetBasic(CinternalHashConst_t CPPUTILS_ARG_NN a_hashTbl) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CInternalHashDestroy(CinternalHash_t CPPUTILS_ARG_NN a_hashTbl) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CInternalHashIterate(CinternalHashConst_t CPPUTILS_ARG_NN a_hashTbl, CinternalHashTypeIter CPPUTILS_ARG_NN a_iter, void* a_clbkData) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT CinternalHashItem_t CInternalHashAddDataWithKnownHash(CinternalHash_t CPPUTILS_ARG_NN a_hashTbl,
    const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT CinternalHashItem_t CInternalHashAddDataEvenIfExist(CinternalHash_t CPPUTILS_ARG_NN a_hashTbl,
    const void* a_data, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT CinternalHashItem_t CInternalHashAddDataIfNotExists(CinternalHash_t CPPUTILS_ARG_NN a_hashTbl,
    const void* a_data, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT void CInternalHashRemoveDataEx(CinternalHash_t CPPUTILS_ARG_NN a_hashTbl, CinternalHashItem_t CPPUTILS_ARG_NN a_iterator) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT bool CInternalHashRemoveData(CinternalHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT CinternalHashItem_t CInternalHashFindEx(CinternalHashConst_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash) CPPUTILS_NOEXCEPT;
CINTERNAL_EXPORT CinternalHashItem_t CInternalHashFind(CinternalHashConst_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;

// Functions added on 2025 May 02
CINTERNAL_EXPORT CinternalHashItem_t CInternalHashFindNextTheSame(CinternalHashConst_t CPPUTILS_ARG_NN a_hashTbl, CinternalHashItem_t CPPUTILS_ARG_NN a_prev) CPPUTILS_NOEXCEPT;

CPPUTILS_END_C

#define CInternalSmallIntHKey(_key)             CPPUTILS_REINTERPRET_CAST(void*,CPPUTILS_STATIC_CAST(size_t,_key))
#define CInternalStrHKeyLenFromStrLen(_strLn)   CPPUTILS_STATIC_CAST(size_t,(_strLn)+1)
#define CInternalSmallIntHPairFn(_key)		    CInternalSmallIntHKey(_key), 0
#define CInternalStrHKeyPairFn(_str)			(_str),CInternalStrHKeyLenFromStrLen(strlen(_str))  // to use this string.h should be included

#define CInternalHashCreateAny(_numOfBaskets,_hasher,_isEq,_keyStore,_keyUnstore)       CInternalHashCreateAnyEx(_numOfBaskets,_hasher,_isEq,_keyStore,_keyUnstore,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalHashCreateRawMem(_numOfBaskets)                                        CInternalHashCreateRawMemEx(_numOfBaskets,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalHashCreateSmlInt(_numOfBaskets)                                        CInternalHashCreateSmlIntEx(_numOfBaskets,CPPUTILS_NULL,CPPUTILS_NULL)



#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_H
