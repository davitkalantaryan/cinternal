//
// repo:			cinternal
// file:            data.h
// path:			include/cinternal/hash/data.h
// created on:		2023 Oct 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_DATA_H
#define CINTERNAL_INCLUDE_CINTERNAL_HASH_DATA_H

#include <cinternal/internal_header.h>
#include <cinternal/common_data01.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

CPPUTILS_BEGIN_C


struct SCinternalHashItem {
	struct SCinternalHashItem	*prevInTheBucket, *nextInTheBucket;
	void* data;
	void* key;
	size_t						keySize;
	size_t						hash;
};


struct SCinternalHash {
	TypeCinternalAllocator				allocator;
	TypeCinternalDeallocator			deallocator;
	size_t								m_size;
	struct SCinternalHashItem**			ppTable;
	size_t								numberOfBaskets;
	TypeCinternalHasher					hasher;
	TypeCinternalIsMemoriesIdentical	isEq;
	TypeCinternalStoreKey				keyStore;
	TypeCinternalUnstoreKey				keyUnstore;
};


CPPUTILS_END_C




#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_DATA_H
