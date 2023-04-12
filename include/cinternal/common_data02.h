//
// file:            common_data02.h
// path:			include/cinternal/common_data02.h
// created on:		2023 Apr 12
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_COMMON_DATA02_H
#define CINTERNAL_INCLUDE_CINTERNAL_COMMON_DATA02_H

#include <cinternal/export_symbols.h>


CPPUTILS_BEGIN_C

struct SCinternalIterator {
	struct SCinternalIterator	*prev, *next;
};

struct SCinternalIteratorWithData {
	struct SCinternalIterator		itr;
	void*							data;
};

struct SCinternalDLList;


typedef struct SCinternalDLList* CinternalDLList_t;
typedef const struct SCinternalDLList* ConstCinternalDLList_t;
typedef const struct SCinternalIterator* CinternalIterator_t;

CPPUTILS_END_C


#define CInternalDataFromIterator(_iter_ptr)	CPPUTILS_REINTERPRET_CAST(const struct SCinternalIteratorWithData*,_iter_ptr)->data


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_COMMON_DATA02_H
