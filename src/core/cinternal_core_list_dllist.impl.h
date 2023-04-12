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

#include <cinternal/common_data01.h>
#include <cinternal/common_data02.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//#define CInternalListItemToIter(_item_ptr)		CPPUTILS_REINTERPRET_CAST(struct SCinternalIterator*,_item_ptr)
#define CInternalItemToIterator(_item_ptr)			(&((_item_ptr)->itr))

#ifdef _MSC_VER

#pragma warning (disable:5039)

#elif defined(__GNUC__) 

#pragma GCC diagnostic ignored "-Wattributes"

#endif


CPPUTILS_BEGIN_C


static void CinternalDefaultDataCleaner(void* a_pData) CPPUTILS_NOEXCEPT  {
	CPPUTILS_STATIC_CAST(void, a_pData);
}


struct CPPUTILS_DLL_PRIVATE SCinternalDLList {
	TypeCinternalAllocator			allocator;
	TypeCinternalDeallocator		deallocator;
	struct SCinternalIterator		*first, *last;
	size_t							m_size;
};


static inline void CInternalDLListInitializeInline(CinternalDLList_t a_list, TypeCinternalAllocator CPPUTILS_ARG_NO_NULL a_allocator, TypeCinternalDeallocator a_deallocator) CPPUTILS_NOEXCEPT  {
	a_list->allocator = a_allocator;
	a_list->deallocator = a_deallocator ? a_deallocator : (&free);
	a_list->last = a_list->first = CPPUTILS_NULL;
	a_list->m_size = 0;
}


static inline void CInternalDLListDestroyExInline(CinternalDLList_t a_list, TypeCinternalDeallocator a_remainingDataCleaner) CPPUTILS_NOEXCEPT {
	struct SCinternalIterator *pItemTmp, *pItem = a_list->first;
	a_remainingDataCleaner = a_remainingDataCleaner ? a_remainingDataCleaner : (&CinternalDefaultDataCleaner); // if null, then data should not be cleaned
	while (pItem) {
		pItemTmp = pItem->next;
		(*a_remainingDataCleaner)(CInternalDataFromIterator(pItem));
		(*(a_list->deallocator))(pItem);
		pItem = pItemTmp;
	}
	(*(a_list->deallocator))(a_list);
}


static inline CinternalIterator_t CInternalDLListAddDataBeforeIteratorInline(CinternalDLList_t a_list, CinternalIterator_t a_iter, const void* a_data) CPPUTILS_NOEXCEPT  {
	struct SCinternalIteratorWithData*const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalIteratorWithData*, (*(a_list->allocator))(sizeof(struct SCinternalIteratorWithData)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);

	if(a_iter){
		struct SCinternalIterator* const pIterInp = CPPUTILS_CONST_CAST(struct SCinternalIterator*, a_iter);
		pNewItem->itr.next = pIterInp;
		pNewItem->itr.prev = pIterInp->prev;
		if (pIterInp->prev) {
			pIterInp->prev->next = CInternalItemToIterator(pNewItem);
		}

		if (pIterInp == a_list->first) {
			a_list->first = CInternalItemToIterator(pNewItem);
		}

	}
	else {
		pNewItem->itr.next = a_list->first;
		pNewItem->itr.prev = CPPUTILS_NULL;
		if (a_list->first) {
			a_list->first->prev = CInternalItemToIterator(pNewItem);
		}
		else {
			a_list->last = CInternalItemToIterator(pNewItem);
		}
		a_list->first = CInternalItemToIterator(pNewItem);
	}
	
	++(a_list->m_size);

	return CInternalItemToIterator(pNewItem);
}


static inline CinternalIterator_t CInternalDLListAddDataAfterIteratorInline(CinternalDLList_t a_list, CinternalIterator_t a_iter, const void* a_data) CPPUTILS_NOEXCEPT  {
	struct SCinternalIteratorWithData* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalIteratorWithData*, (*(a_list->allocator))(sizeof(struct SCinternalIteratorWithData)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);

	if (a_iter) {
		struct SCinternalIterator* const pIterInp = CPPUTILS_CONST_CAST(struct SCinternalIterator*, a_iter);
		pNewItem->itr.prev = pIterInp;
		pNewItem->itr.next = pIterInp->prev;
		if (pIterInp->next) {
			pIterInp->next->prev = CInternalItemToIterator(pNewItem);
		}

		if (pIterInp == a_list->last) {
			a_list->last = CInternalItemToIterator(pNewItem);
		}

	}
	else {
		pNewItem->itr.prev = a_list->last;
		pNewItem->itr.next = CPPUTILS_NULL;
		if (a_list->last) {
			a_list->last->next = CInternalItemToIterator(pNewItem);
		}
		else {
			a_list->first = CInternalItemToIterator(pNewItem);
		}
		a_list->last = CInternalItemToIterator(pNewItem);
	}

	++(a_list->m_size);

	return CInternalItemToIterator(pNewItem);
}


static inline void CInternalDLListRemoveDataInline(CinternalDLList_t a_list, CinternalIterator_t a_iterator) CPPUTILS_NOEXCEPT {
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

	(*(a_list->deallocator))(CPPUTILS_REINTERPRET_CAST(struct SCinternalIteratorWithData*,CPPUTILS_CONST_CAST(struct SCinternalIterator*, a_iterator)));
}


CPPUTILS_END_C


#endif  //  #ifdef CINTERNAL_SRC_CORE_CINTERNAL_CORE_LIST_DLLIST_IMPL_H_NEEDED
#endif  //  #ifndef CINTERNAL_SRC_CORE_CINTERNAL_CORE_LIST_DLLIST_IMPL_H
