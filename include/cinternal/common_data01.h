//
// repo:			cinternal
// file:            common_data01.h
// path:			include/cinternal/common_data01.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_COMMON_DATA01_H
#define CINTERNAL_INCLUDE_CINTERNAL_COMMON_DATA01_H

#include <cinternal/internal_header.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stddef.h>
#include <stdbool.h>
#include <cinternal/undisable_compiler_warnings.h>

CPPUTILS_BEGIN_C


typedef void(*TypeCinternalDeallocator)(void*);
typedef void* (*TypeCinternalAllocator)(size_t);
typedef void* (*TypeCinternalReallocator)(void*,size_t);
typedef size_t(*TypeCinternalHasher)(const void* key, size_t keySize);
typedef bool(*TypeCinternalIsMemoriesIdentical)(const void* key1, size_t keySize1, const void* key2, size_t keySize2);
typedef bool(*TypeCinternalStoreKey)(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* key, size_t keySize);
typedef void(*TypeCinternalUnstoreKey)(TypeCinternalDeallocator a_deallocator, void* key, size_t keySize);


CPPUTILS_END_C



#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_COMMON_DATA01_H
