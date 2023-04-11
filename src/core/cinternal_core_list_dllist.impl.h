//
// file:            cinternal_core_list_dllist.impl.h
// path:			src/core/cinternal_core_list_dllist.impl.h
// created on:		2023 Apr 11
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#ifndef CINTERNAL_SRC_CORE_CINTERNAL_CORE_LIST_DLLIST_IMPL_H
#define CINTERNAL_SRC_CORE_CINTERNAL_CORE_LIST_DLLIST_IMPL_H

#include <cinternal/internal_header.h>

#ifdef CINTERNAL_SRC_CORE_CINTERNAL_CORE_LIST_DLLIST_IMPL_H_NEEDED

#include <cinternal/list/llist.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define CInternalListItemToIter3(_item_ptr)		CPPUTILS_REINTERPRET_CAST(struct SCinternalLListItemIter*,_item_ptr)

#ifdef _MSC_VER

#elif defined(__GNUC__) 

#pragma GCC diagnostic ignored "-Wattributes"

#endif


CPPUTILS_BEGIN_C


static void CinternalDefaultDataCleaner(void* a_pData) {
	CPPUTILS_STATIC_CAST(void, a_pData);
}


struct CPPUTILS_DLL_PRIVATE SCinternalLList {
	TypeCinternalAllocator			allocator;
	TypeCinternalDeallocator		deallocator;
	struct SCinternalLListItemIter	*first, *last;
	size_t							m_size;
};


static inline void CInternalDLListInitializeInline(CinternalLList_t a_list, TypeCinternalAllocator CPPUTILS_ARG_NO_NULL a_allocator, TypeCinternalDeallocator a_deallocator) {
	a_list->allocator = a_allocator;
	a_list->deallocator = a_deallocator ? a_deallocator : (&free);
	a_list->last = a_list->first = CPPUTILS_NULL;
	a_list->m_size = 0;
}


static inline void CInternalDLListDestroyExInline(CinternalLList_t a_list, TypeCinternalDeallocator a_remainingDataCleaner){
	struct SCinternalLListItemIter* pItemTmp, * pItem = a_list->first;
	a_remainingDataCleaner = a_remainingDataCleaner ? a_remainingDataCleaner : (&CinternalDefaultDataCleaner); // if null, then data should not be cleaned
	while (pItem) {
		pItemTmp = pItem->next;
		(*a_remainingDataCleaner)(CInternalListDataFromIter(pItem));
		(*(a_list->deallocator))(pItem);
		pItem = pItemTmp;
	}
	(*(a_list->deallocator))(a_list);
}


static inline CInternalLListIterator CInternalDLListAddDataBeforeIteratorInline(CinternalLList_t a_list, CInternalLListIterator a_iter, const void* a_data){
	struct SCinternalLListItem*const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalLListItem*, (*(a_list->allocator))(sizeof(struct SCinternalLListItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);

	if(a_iter){
		struct SCinternalLListItemIter* const pIterInp = CPPUTILS_CONST_CAST(struct SCinternalLListItemIter*, a_iter);
		pNewItem->itr.next = pIterInp;
		pNewItem->itr.prev = pIterInp->prev;
		if (pIterInp->prev) {
			pIterInp->prev->next = CInternalListItemToIter3(pNewItem);
		}

		if (pIterInp == a_list->first) {
			a_list->first = CInternalListItemToIter3(pNewItem);
		}

	}
	else {
		pNewItem->itr.next = a_list->first;
		pNewItem->itr.prev = CPPUTILS_NULL;
		if (a_list->first) {
			a_list->first->prev = CInternalListItemToIter3(pNewItem);
		}
		else {
			a_list->last = CInternalListItemToIter3(pNewItem);
		}
		a_list->first = CInternalListItemToIter3(pNewItem);
	}
	
	++(a_list->m_size);

	return CInternalListItemToIter3(pNewItem);
}


static inline CInternalLListIterator CInternalDLListAddDataAfterIteratorInline(CinternalLList_t a_list, CInternalLListIterator a_iter, const void* a_data){
	struct SCinternalLListItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalLListItem*, (*(a_list->allocator))(sizeof(struct SCinternalLListItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);

	if (a_iter) {
		struct SCinternalLListItemIter* const pIterInp = CPPUTILS_CONST_CAST(struct SCinternalLListItemIter*, a_iter);
		pNewItem->itr.prev = pIterInp;
		pNewItem->itr.next = pIterInp->prev;
		if (pIterInp->next) {
			pIterInp->next->prev = CInternalListItemToIter3(pNewItem);
		}

		if (pIterInp == a_list->last) {
			a_list->last = CInternalListItemToIter3(pNewItem);
		}

	}
	else {
		pNewItem->itr.prev = a_list->last;
		pNewItem->itr.next = CPPUTILS_NULL;
		if (a_list->last) {
			a_list->last->next = CInternalListItemToIter3(pNewItem);
		}
		else {
			a_list->first = CInternalListItemToIter3(pNewItem);
		}
		a_list->last = CInternalListItemToIter3(pNewItem);
	}

	++(a_list->m_size);

	return CInternalListItemToIter3(pNewItem);
}


static inline void CInternalDLListRemoveDataInline(CinternalLList_t a_list, CInternalLListIterator a_iterator){
	if (a_iterator->prev) {
		a_iterator->prev->next = a_iterator->next;
	}

	if (a_iterator->next) {
		a_iterator->next->prev = a_iterator->prev;
	}

	if (a_iterator == a_list->first) {
		a_list->first = a_iterator->next;
	}

	if (a_iterator == a_list->last) {
		a_list->last = a_iterator->prev;
	}

	--(a_list->m_size);

	(*(a_list->deallocator))(CPPUTILS_REINTERPRET_CAST(struct SCinternalLListItem*,CPPUTILS_CONST_CAST(struct SCinternalLListItemIter*, a_iterator)));
}


CPPUTILS_END_C


#endif  //  #ifdef CINTERNAL_SRC_CORE_CINTERNAL_CORE_LIST_DLLIST_IMPL_H_NEEDED
#endif  //  #ifndef CINTERNAL_SRC_CORE_CINTERNAL_CORE_LIST_DLLIST_IMPL_H
