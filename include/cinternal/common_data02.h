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

struct SCinternalListIterator {
	struct SCinternalListIterator	*prev, *next;
};

struct SCinternalListIteratorWithData {
	struct SCinternalListIterator	itr;
	void*							data;
};

struct SCinternalDLList;
typedef struct SCinternalDLList* CinternalDLList_t;
typedef const struct SCinternalDLList* ConstCinternalDLList_t;

typedef const struct SCinternalListIterator* CinternalListIterator_t;

#define CInternalDataFromListIterator(_iter_ptr)	CPPUTILS_REINTERPRET_CAST(const struct SCinternalListIteratorWithData*,_iter_ptr)->data

CPPUTILS_END_C



#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_COMMON_DATA02_H
