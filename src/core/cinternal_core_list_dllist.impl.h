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

//#define CInternalListItemToIter(_item_ptr)		CPPUTILS_REINTERPRET_CAST(struct SCinternalListIterator*,_item_ptr)
#define CInternalItemToIterator(_item_ptr)			(&((_item_ptr)->itr))

#ifdef CINTERNAL_INLINE2
#undef CINTERNAL_INLINE2
#endif

#define CINTERNAL_INLINE2

#ifdef _MSC_VER
#pragma warning (disable:5039)
#elif defined(__GNUC__) 
#pragma GCC diagnostic ignored "-Wattributes"
#endif


CPPUTILS_BEGIN_C

typedef void (*TypeCinternalListItemExtraCleaner)(CinternalDLList_t a_list, struct SCinternalListIterator* a_iter);


static void CinternalDefaultDataCleaner(void* a_pData) CPPUTILS_NOEXCEPT  {
	CPPUTILS_STATIC_CAST(void, a_pData);
}


struct CPPUTILS_DLL_PRIVATE SCinternalDLList {
	TypeCinternalAllocator			allocator;
	TypeCinternalDeallocator		deallocator;
	struct SCinternalListIterator	*first, *last;
	size_t							m_size;
};


static CINTERNAL_INLINE2 void CInternalDLListInitializeInline(CinternalDLList_t a_list, TypeCinternalAllocator CPPUTILS_ARG_NO_NULL a_allocator, TypeCinternalDeallocator a_deallocator) CPPUTILS_NOEXCEPT  {
	a_list->allocator = a_allocator;
	a_list->deallocator = a_deallocator ? a_deallocator : (&free);
	a_list->last = a_list->first = CPPUTILS_NULL;
	a_list->m_size = 0;
}


static CINTERNAL_INLINE2 void CInternalListCleanInline(CinternalDLList_t a_list, TypeCinternalDeallocator a_remainingDataCleaner, TypeCinternalListItemExtraCleaner a_extraCleaner) CPPUTILS_NOEXCEPT {
	struct SCinternalListIterator *pItemTmp, *pItem = a_list->first;
	a_remainingDataCleaner = a_remainingDataCleaner ? a_remainingDataCleaner : (&CinternalDefaultDataCleaner); // if null, then data should not be cleaned
	while (pItem) {
		pItemTmp = pItem->next;
		(*a_remainingDataCleaner)(CInternalDataFromListIterator(pItem));
		(*a_extraCleaner)(a_list, pItem);
		(*(a_list->deallocator))(pItem);
		pItem = pItemTmp;
	}
}


static CINTERNAL_INLINE2 void CInternalDLListAddCreatedIteratorBeforeIteratorInline(CinternalDLList_t a_list, CinternalListIterator_t a_iter, struct SCinternalListIterator* a_pNewIter) CPPUTILS_NOEXCEPT  {
	if(a_iter){
		struct SCinternalListIterator* const pIterInp = CPPUTILS_CONST_CAST(struct SCinternalListIterator*, a_iter);
		a_pNewIter->next = pIterInp;
		a_pNewIter->prev = pIterInp->prev;
		if (pIterInp->prev) {
			pIterInp->prev->next = a_pNewIter;
		}

		if (pIterInp == a_list->first) {
			a_list->first = a_pNewIter;
		}

	}
	else {
		a_pNewIter->next = a_list->first;
		a_pNewIter->prev = CPPUTILS_NULL;
		if (a_list->first) {
			a_list->first->prev = a_pNewIter;
		}
		else {
			a_list->last = a_pNewIter;
		}
		a_list->first = a_pNewIter;
	}
	
	++(a_list->m_size);
}


static CINTERNAL_INLINE2 void CInternalDLListAddCreatedIteratorAfterIteratorInline(CinternalDLList_t a_list, CinternalListIterator_t a_iter, struct SCinternalListIterator* a_pNewIter) CPPUTILS_NOEXCEPT  {
	if (a_iter) {
		struct SCinternalListIterator* const pIterInp = CPPUTILS_CONST_CAST(struct SCinternalListIterator*, a_iter);
		a_pNewIter->prev = pIterInp;
		a_pNewIter->next = pIterInp->prev;
		if (pIterInp->next) {
			pIterInp->next->prev = a_pNewIter;
		}

		if (pIterInp == a_list->last) {
			a_list->last = a_pNewIter;
		}

	}
	else {
		a_pNewIter->prev = a_list->last;
		a_pNewIter->next = CPPUTILS_NULL;
		if (a_list->last) {
			a_list->last->next = a_pNewIter;
		}
		else {
			a_list->first = a_pNewIter;
		}
		a_list->last = a_pNewIter;
	}

	++(a_list->m_size);
}


static CINTERNAL_INLINE2 void CInternalDLListRemoveDataNoFreeInline(CinternalDLList_t a_list, CinternalListIterator_t a_iterator) CPPUTILS_NOEXCEPT {
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
}


CPPUTILS_END_C


#endif  //  #ifdef CINTERNAL_SRC_CORE_CINTERNAL_CORE_LIST_DLLIST_IMPL_H_NEEDED
#endif  //  #ifndef CINTERNAL_SRC_CORE_CINTERNAL_CORE_LIST_DLLIST_IMPL_H
