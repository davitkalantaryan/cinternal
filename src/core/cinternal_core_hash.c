//
// repo:			cinternal
// file:            cinternal_core_hash.c
// path:			src/core/cinternal_core_hash.c
// created on:		2024 Dec 10
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// comment:			pure hash
//


#ifndef cinternal_hash1_raw_mem_inline_needed
#define cinternal_hash1_raw_mem_inline_needed
#endif

#include <cinternal/hash.h>
#include <cinternal/hash_functions.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C


#define CinternalHashItemFromPublPtr(_publPtr)      CPPUTILS_REINTERPRET_CAST(struct SCinternalHashItemPrivateFull*,CPPUTILS_CONST_CAST(struct SCinternalHashItem*,_publPtr))
#define CinternalHashItemFromPrvtPtr(_prvtPtr)      CPPUTILS_REINTERPRET_CAST(struct SCinternalHashItem*,_prvtPtr)


#define CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS	4096

struct SCinternalHashItemPrivate SCinternalHashItemBase(size_t, void*);


struct SCinternalHashItemPrivateFull {
    struct SCinternalHashItemPrivate        publ;
    struct SCinternalHashItemPrivateFull    *prev, * next;
};


struct SCinternalHashFull {
    struct SCinternalHash                   publ;
    struct SCinternalHashItemPrivateFull**  ppTable;
};


static bool CinternalIsMemoriesIdenticalRawMemory(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT;
static bool CinternalStoreKeyRawMemory(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static void CinternalUnstoreKeyRawMemory(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static size_t cinternal_hash1_small_int(const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static bool CinternalIsMemoriesIdenticalSmallInt(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT;
static bool CinternalStoreKeySmallInt(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static void CinternalUnstoreKeySmallInt(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static size_t cinternal_hash1_raw_mem(const void* a_pKey, size_t a_unKeySize) CPPUTILS_NOEXCEPT;

static inline struct SCinternalHashItemPrivateFull* CInternalHashFindItemInlineRaw(const struct SCinternalHashFull* CPPUTILS_ARG_NN a_hashTbl, struct SCinternalHashItemPrivateFull* a_pItem, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT  {
    struct SCinternalHashItemPrivateFull* pItem = a_pItem;
    while (pItem) {
        if ((*(a_hashTbl->publ.isEq))(pItem->publ.key, pItem->publ.keySize, a_key, a_keySize)) {
            return pItem;
        }
        pItem = pItem->next;
    }
    return CPPUTILS_NULL;
}


static inline struct SCinternalHashItemPrivateFull* CInternalHashFindItemInline(const struct SCinternalHashFull* CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash) CPPUTILS_NOEXCEPT  {
    struct SCinternalHashItemPrivateFull* pItem;
    *a_pHash = ((*(a_hashTbl->publ.hasher))(a_key, a_keySize)) % (a_hashTbl->publ.numberOfBaskets);
    pItem = a_hashTbl->ppTable[*a_pHash];
    return CInternalHashFindItemInlineRaw(a_hashTbl,pItem,a_key, a_keySize);
}


static inline void CInternalHashRemoveDataExInline(struct SCinternalHashFull* CPPUTILS_ARG_NN a_pHashTable, struct SCinternalHashItemPrivateFull* CPPUTILS_ARG_NN a_pItem) CPPUTILS_NOEXCEPT {
    if (a_pItem->next) { a_pItem->next->prev = a_pItem->prev; }
    if (a_pItem->prev) { a_pItem->prev->next = a_pItem->next; }
    else {
        a_pHashTable->ppTable[a_pItem->publ.hash] = a_pItem->next;
    }

    (*(a_pHashTable->publ.keyUnstore))(a_pHashTable->publ.deallocator, a_pItem->publ.key, a_pItem->publ.keySize);
    (*(a_pHashTable->publ.deallocator))(a_pItem);
    --(a_pHashTable->publ.count);
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

CINTERNAL_EXPORT CinternalHash_t CInternalHashCreateAnyEx(size_t a_numberOfBaskets,
    TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
    TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
    TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator) CPPUTILS_NOEXCEPT
{
    struct SCinternalHashFull* pRet;
    size_t tableMemorySize;

    a_allocator = a_allocator ? a_allocator : (&malloc);

    pRet = CPPUTILS_STATIC_CAST(struct SCinternalHashFull*, (*a_allocator)(sizeof(struct SCinternalHashFull)));
    if (!pRet) {
        return CPPUTILS_NULL;
    }

    pRet->publ.allocator = a_allocator;
    pRet->publ.deallocator = a_deallocator ? a_deallocator : (&free);
    pRet->publ.count = 0;
    pRet->publ.numberOfBaskets = (a_numberOfBaskets > 0) ? a_numberOfBaskets : CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS;

    tableMemorySize = pRet->publ.numberOfBaskets * sizeof(struct SCinternalHashItemPrivateFull*);
    pRet->ppTable = CPPUTILS_STATIC_CAST(struct SCinternalHashItemPrivateFull**, (*a_allocator)(tableMemorySize));
    if (!(pRet->ppTable)) {
        (*(pRet->publ.deallocator))(pRet);
        return CPPUTILS_NULL;
    }
    memset(pRet->ppTable, 0, tableMemorySize);

    pRet->publ.hasher = a_hasher;
    pRet->publ.isEq = a_isEq;
    pRet->publ.keyStore = a_keyStore;
    pRet->publ.keyUnstore = a_keyUnstore;

    return pRet;
}


CINTERNAL_EXPORT CinternalHash_t CInternalHashCreateRawMemEx(size_t a_numberOfBaskets,
    TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator) CPPUTILS_NOEXCEPT
{
    return CInternalHashCreateAnyEx(a_numberOfBaskets,
        &cinternal_hash1_raw_mem, &CinternalIsMemoriesIdenticalRawMemory,
        &CinternalStoreKeyRawMemory, &CinternalUnstoreKeyRawMemory,
        a_allocator, a_deallocator);
}


CINTERNAL_EXPORT CinternalHash_t CInternalHashCreateSmlIntEx(size_t a_numberOfBaskets,
    TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator) CPPUTILS_NOEXCEPT
{
    return CInternalHashCreateAnyEx(a_numberOfBaskets,
        &cinternal_hash1_small_int, &CinternalIsMemoriesIdenticalSmallInt,
        &CinternalStoreKeySmallInt, &CinternalUnstoreKeySmallInt,
        a_allocator, a_deallocator);
}


CINTERNAL_EXPORT CinternalHashConstBasic_t CinternalHashGetBasic(CinternalHashConst_t CPPUTILS_ARG_NN a_hashTbl) CPPUTILS_NOEXCEPT
{
    return &(a_hashTbl->publ);
}


CINTERNAL_EXPORT void CInternalHashDestroy(CinternalHash_t CPPUTILS_ARG_NN a_hashTbl) CPPUTILS_NOEXCEPT
{
    (*(a_hashTbl->publ.deallocator))(a_hashTbl->ppTable);
    (*(a_hashTbl->publ.deallocator))(a_hashTbl);
}


CINTERNAL_EXPORT void CInternalHashIterate(CinternalHashConst_t CPPUTILS_ARG_NN a_hashTbl, CinternalHashTypeIter CPPUTILS_ARG_NN a_iter, void* a_clbkData) CPPUTILS_NOEXCEPT
{
    size_t basketIndex, countFound=0;
    bool bIterate = true;
    const size_t cunCount = a_hashTbl->publ.count;
    struct SCinternalHashItemPrivateFull *pItemNext, *pItem;

    for (basketIndex = 0; (countFound< cunCount) && (basketIndex < a_hashTbl->publ.numberOfBaskets) && bIterate; ++basketIndex) {
        pItem = a_hashTbl->ppTable[basketIndex];
        while (pItem && bIterate) {
            pItemNext = pItem->next;
            bIterate = (*a_iter)(a_clbkData, CinternalHashItemFromPrvtPtr (&(pItem->publ)));
            pItem = pItemNext;
            ++countFound;
        }  //  while (pItem) {
    }  //  for (basketIndex = 0; (countFound< cunCount) && (basketIndex < pHashTable->publ.numberOfBaskets); ++basketIndex) {
}


CINTERNAL_EXPORT CinternalHashItem_t CInternalHashAddDataWithKnownHash(CinternalHash_t CPPUTILS_ARG_NN a_hashTbl,
    const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash) CPPUTILS_NOEXCEPT
{
    struct SCinternalHashItemPrivateFull* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalHashItemPrivateFull*, (*(a_hashTbl->publ.allocator))(sizeof(struct SCinternalHashItemPrivateFull)));
    if (!pNewItem) {
        return CPPUTILS_NULL;
    }

    if (!(*(a_hashTbl->publ.keyStore))(a_hashTbl->publ.allocator, &(pNewItem->publ.key), &(pNewItem->publ.keySize), a_key, a_keySize)) {
        (*(a_hashTbl->publ.deallocator))(pNewItem);
        return CPPUTILS_NULL;
    }

    //
    pNewItem->publ.data = CPPUTILS_CONST_CAST(void*, a_data);
    pNewItem->publ.hash = a_hash;
    pNewItem->prev = CPPUTILS_NULL;
    pNewItem->next = a_hashTbl->ppTable[a_hash];
    if (a_hashTbl->ppTable[a_hash]) {
        a_hashTbl->ppTable[a_hash]->prev = pNewItem;
    }
    a_hashTbl->ppTable[a_hash] = pNewItem;

    ++(a_hashTbl->publ.count);

    return CinternalHashItemFromPrvtPtr(&(pNewItem->publ));
}


CINTERNAL_EXPORT CinternalHashItem_t CInternalHashAddDataEvenIfExist(CinternalHash_t CPPUTILS_ARG_NN a_hashTbl,
    const void* a_data, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
    const size_t hash = ((*(a_hashTbl->publ.hasher))(a_key, a_keySize)) % (a_hashTbl->publ.numberOfBaskets);
    return CInternalHashAddDataWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, hash);
}


CINTERNAL_EXPORT CinternalHashItem_t CInternalHashAddDataIfNotExists(CinternalHash_t CPPUTILS_ARG_NN a_hashTbl,
    const void* a_data, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
    size_t unHash;
    if (CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, &unHash)) {
        return CPPUTILS_NULL;
    }
    return CInternalHashAddDataWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, unHash);
}


CINTERNAL_EXPORT void CInternalHashRemoveDataEx(CinternalHash_t CPPUTILS_ARG_NN a_hashTbl, CinternalHashItem_t CPPUTILS_ARG_NN a_iter) CPPUTILS_NOEXCEPT
{
    struct SCinternalHashItemPrivateFull* const pItem = CinternalHashItemFromPublPtr(a_iter);
    CInternalHashRemoveDataExInline(a_hashTbl, pItem);
}


CINTERNAL_EXPORT bool CInternalHashRemoveData(CinternalHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
    size_t unHash;
    struct SCinternalHashItemPrivateFull* const pIterator = CInternalHashFindItemInline(a_hashTbl,a_key,a_keySize,&unHash);
    if (pIterator) {
        CInternalHashRemoveDataExInline(a_hashTbl, pIterator);
        return true;
    }
    return false;
}


CINTERNAL_EXPORT CinternalHashItem_t CInternalHashFindEx(CinternalHashConst_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash) CPPUTILS_NOEXCEPT
{
    struct SCinternalHashItemPrivateFull* const pIterator = CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, a_pHash);
    if (pIterator) {
        return CinternalHashItemFromPrvtPtr(&(pIterator->publ));
    }
    return CPPUTILS_NULL;
}


CINTERNAL_EXPORT CinternalHashItem_t CInternalHashFind(CinternalHashConst_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
    size_t unHash;
    struct SCinternalHashItemPrivateFull* const pIterator = CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, &unHash);
    if (pIterator) {
        return CinternalHashItemFromPrvtPtr(&(pIterator->publ));
    }
    return CPPUTILS_NULL;
}


CINTERNAL_EXPORT CinternalHashItem_t CInternalHashFindNextTheSame(CinternalHashConst_t CPPUTILS_ARG_NN a_hashTbl, CinternalHashItem_t CPPUTILS_ARG_NN a_prev) CPPUTILS_NOEXCEPT
{
    //const struct SCinternalHashFull* const pHashTable = CinternalHashFromPublPtr(a_hashTbl);
    struct SCinternalHashItemPrivateFull* const pItem = CinternalHashItemFromPublPtr(a_prev);
    struct SCinternalHashItemPrivateFull* const pIterator = CInternalHashFindItemInlineRaw(a_hashTbl,pItem->next,a_prev->key,a_prev->keySize);
    if (pIterator) {
        return CinternalHashItemFromPrvtPtr(&(pIterator->publ));
    }
    return CPPUTILS_NULL;
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

static size_t cinternal_hash1_raw_mem(const void* a_pKey, size_t a_unKeySize) CPPUTILS_NOEXCEPT
{
    return cinternal_hash1_raw_mem_inline(a_pKey, a_unKeySize);
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


CPPUTILS_END_C
