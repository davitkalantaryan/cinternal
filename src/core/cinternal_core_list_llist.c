//
// file:            cinternal_core_list_llist.c
// path:			src/core/cinternal_core_list_llist.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/list/llist.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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
	struct SCinternalLListItem*		first;
	size_t							m_size;
};


CINTERNAL_EXPORT CinternalLList_t CInternalLListCreateEx(TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	CinternalLList_t pRet;

	a_allocator = a_allocator ? a_allocator : (&malloc);

	pRet = CPPUTILS_STATIC_CAST(CinternalLList_t, (*a_allocator)(sizeof(struct SCinternalLList)));
	if (!pRet) {
		return CPPUTILS_NULL;
	}

	pRet->allocator = a_allocator;
	pRet->deallocator = a_deallocator ? a_deallocator : (&free);
	pRet->first = CPPUTILS_NULL;
	pRet->m_size = 0;

	return pRet;
}


CINTERNAL_EXPORT void	CInternalLListDestroyEx(CinternalLList_t a_list, TypeCinternalDeallocator a_remainingDataCleaner)
{
	struct SCinternalLListItem* pItemTmp, * pItem = a_list->first;

	a_remainingDataCleaner = a_remainingDataCleaner ? a_remainingDataCleaner : (&CinternalDefaultDataCleaner); // if null, then data should not be cleaned

	while (pItem) {
		pItemTmp = pItem->nextInList;
		(*a_remainingDataCleaner)(pItem->data);
		(*(a_list->deallocator))(pItem);
		pItem = pItemTmp;
	}

	(*(a_list->deallocator))(a_list);
}


CINTERNAL_EXPORT CInternalLListIterator CInternalLListAddDataBeforeIterator(CinternalLList_t a_list, CInternalLListIterator a_iter, const void* a_data)
{
	struct SCinternalLListItem* const pIterInp = a_iter?CPPUTILS_CONST_CAST(struct SCinternalLListItem*, a_iter):(a_list->first);
	struct SCinternalLListItem*const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalLListItem*, (*(a_list->allocator))(sizeof(struct SCinternalLListItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	pNewItem->nextInList = pIterInp;
	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);

	if(pIterInp){
		pNewItem->prevInList = pIterInp->prevInList;
		if (pIterInp->prevInList) {
			pIterInp->prevInList->nextInList = pNewItem;
		}

		if (pIterInp == a_list->first) {
			a_list->first = pNewItem;
		}

	}
	else {
		pNewItem->prevInList = CPPUTILS_NULL;
		a_list->first = pNewItem;
	}
	
	++(a_list->m_size);

	return pNewItem;
}


CINTERNAL_EXPORT CInternalLListIterator CInternalLListAddDataAfterIterator(CinternalLList_t a_list, CInternalLListIterator CPPUTILS_ARG_NO_NULL a_iter, const void* a_data)
{
	return CInternalLListAddDataBeforeIterator(a_list, a_iter->nextInList, a_data);
}


CINTERNAL_EXPORT CInternalLListIterator CInternalLListFirstItem(ConstCinternalLList_t a_list)
{
	return a_list->first;
}


CINTERNAL_EXPORT void CInternalLListRemoveData(CinternalLList_t a_list, CInternalLListIterator a_iterator)
{
	if (a_iterator->prevInList) {
		a_iterator->prevInList->nextInList = a_iterator->nextInList;
	}

	if (a_iterator->nextInList) {
		a_iterator->nextInList->prevInList = a_iterator->prevInList;
	}

	if (a_iterator == a_list->first) {
		a_list->first = a_iterator->nextInList;
	}

	--(a_list->m_size);

	(*(a_list->deallocator))(CPPUTILS_CONST_CAST(struct SCinternalLListItem*, a_iterator));
}


CINTERNAL_EXPORT size_t CInternalLListSize(ConstCinternalLList_t a_list)
{
	return a_list->m_size;
}


CPPUTILS_END_C
