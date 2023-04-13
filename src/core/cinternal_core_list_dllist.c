//
// file:            cinternal_core_list_dllist.c
// path:			src/core/cinternal_core_list_dllist.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// explanation:		Double Linked List
//


#include <cinternal/list/dllist.h>
#define CINTERNAL_SRC_CORE_CINTERNAL_CORE_LIST_DLLIST_IMPL_H_NEEDED
#include "cinternal_core_list_dllist.impl.h"


CPPUTILS_BEGIN_C



CINTERNAL_EXPORT CinternalDLList_t CInternalDLListCreateEx(TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	CinternalDLList_t pRet;
	a_allocator = a_allocator ? a_allocator : (&malloc);
	pRet = CPPUTILS_STATIC_CAST(CinternalDLList_t, (*a_allocator)(sizeof(struct SCinternalDLList)));
	if (!pRet) {
		return CPPUTILS_NULL;
	}
	CInternalDLListInitializeInline(pRet, a_allocator, a_deallocator);
	return pRet;
}


CINTERNAL_EXPORT void CInternalDLListDestroyEx(CinternalDLList_t a_list, TypeCinternalDeallocator a_remainingDataCleaner)
{
	CInternalDLListDestroyExInline(a_list, a_remainingDataCleaner);
}


CINTERNAL_EXPORT CinternalListIterator_t CInternalDLListAddDataBeforeIterator(CinternalDLList_t a_list, CinternalListIterator_t a_iter, const void* a_data)
{
	return CInternalDLListAddDataBeforeIteratorInline(a_list, a_iter, a_data);
}


CINTERNAL_EXPORT CinternalListIterator_t CInternalDLListAddDataAfterIterator(CinternalDLList_t a_list, CinternalListIterator_t a_iter, const void* a_data)
{
	return CInternalDLListAddDataAfterIteratorInline(a_list, a_iter, a_data);
}


CINTERNAL_EXPORT CinternalListIterator_t CInternalDLListFirstItem(ConstCinternalDLList_t a_list)
{
	return a_list->first;
}


CINTERNAL_EXPORT CinternalListIterator_t CInternalDLListLastItem(ConstCinternalDLList_t a_list)
{
	return a_list->last;
}


CINTERNAL_EXPORT void CInternalDLListRemoveData(CinternalDLList_t a_list, CinternalListIterator_t a_iterator)
{
	CInternalDLListRemoveDataInline(a_list, a_iterator);
}


CINTERNAL_EXPORT size_t CInternalDLListSize(ConstCinternalDLList_t a_list)
{
	return a_list->m_size;
}


CPPUTILS_END_C
