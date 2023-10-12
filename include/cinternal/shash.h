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
#include <stddef.h>

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


CPPUTILS_END_C


#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_SHASH_H
