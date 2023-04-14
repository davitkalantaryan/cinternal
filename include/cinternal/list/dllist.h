//
// file:            dllist.h
// path:			include/cinternal/list/dllist.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// explanation:		Double Linked List
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_LIST_LLIST_H
#define CINTERNAL_INCLUDE_CINTERNAL_LIST_LLIST_H

#include <cinternal/export_symbols.h>
#include <cinternal/common_data01.h>
#include <cinternal/common_data02.h>


CPPUTILS_BEGIN_C

#define CInternalDataFromDLListIterator(_iter_ptr)	CPPUTILS_REINTERPRET_CAST(const struct SCinternalListIteratorWithData*,_iter_ptr)->data

CINTERNAL_EXPORT CinternalDLList_t CInternalDLListCreateEx(TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT void	CInternalDLListDestroyEx(CinternalDLList_t a_list, TypeCinternalDeallocator a_remainingDataCleaner);
CINTERNAL_EXPORT CinternalListIterator_t CInternalDLListFirstItem(ConstCinternalDLList_t a_list);
CINTERNAL_EXPORT CinternalListIterator_t CInternalDLListLastItem(ConstCinternalDLList_t a_list);
CINTERNAL_EXPORT void	CInternalDLListRemoveData(CinternalDLList_t a_list, CinternalListIterator_t a_iterator);
CINTERNAL_EXPORT size_t CInternalDLListSize(ConstCinternalDLList_t a_list);
CINTERNAL_EXPORT CinternalListIterator_t CInternalDLListAddDataBeforeIterator(CinternalDLList_t a_list, CinternalListIterator_t a_iter, const void* a_data);
CINTERNAL_EXPORT CinternalListIterator_t CInternalDLListAddDataAfterIterator(CinternalDLList_t a_list, CinternalListIterator_t a_iter, const void* a_data);


CPPUTILS_END_C

#define CInternalDLListCreate()						CInternalDLListCreateEx(CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalDLListDestroy(_hashTbl)			CInternalDLListDestroyEx(_hashTbl,CPPUTILS_NULL)
#define CInternalDLListAddDataToFront(_list, _data)	CInternalDLListAddDataBeforeIterator(_list,CPPUTILS_NULL,_data)
#define CInternalDLListAddDataToBack(_list, _data)	CInternalDLListAddDataAfterIterator(_list,CPPUTILS_NULL,_data)


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_LIST_LLIST_H
