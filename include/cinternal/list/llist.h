//
// file:            llist.h
// path:			include/cinternal/list/llist.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_LIST_LLIST_H
#define CINTERNAL_INCLUDE_CINTERNAL_LIST_LLIST_H

#include <cinternal/export_symbols.h>
#include <cinternal/common_data01.h>


CPPUTILS_BEGIN_C

struct SCinternalLListItem {
	struct SCinternalLListItem *prevInList, *nextInList;
	void*				data;
	void*				reserved01;
};

typedef const struct SCinternalLListItem* CInternalLListIterator;
typedef struct SCinternalLList* CinternalLList_t;
typedef const struct SCinternalLList* ConstCinternalLList_t;


CINTERNAL_EXPORT CinternalLList_t CInternalLListCreateEx(TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT void	CInternalLListDestroyEx(CinternalLList_t a_list, TypeCinternalDeallocator a_remainingDataCleaner);
CINTERNAL_EXPORT CInternalLListIterator CInternalLListFirstItem(ConstCinternalLList_t a_list);
CINTERNAL_EXPORT void	CInternalLListRemoveData(CinternalLList_t a_list, CInternalLListIterator a_iterator);
CINTERNAL_EXPORT size_t CInternalLListSize(ConstCinternalLList_t a_list);
CINTERNAL_EXPORT CInternalLListIterator CInternalLListAddDataBeforeIterator(CinternalLList_t a_list, CInternalLListIterator a_iter, const void* a_data);
CINTERNAL_EXPORT CInternalLListIterator CInternalLListAddDataAfterIterator(CinternalLList_t a_list, CInternalLListIterator CPPUTILS_ARG_NO_NULL a_iter, const void* a_data);


CPPUTILS_END_C

#define CInternalLListCreate()						CInternalLListCreateEx(CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalLListDestroy(_hashTbl)				CInternalLListDestroyEx(_hashTbl,CPPUTILS_NULL)
#define CInternalLListAddDataToFront(_list, _data)	CInternalLListAddDataBeforeIterator(_list,CInternalLListFirstItem(_list),_data)


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_LIST_LLIST_H
