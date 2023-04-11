//
// file:            cinternal_core_list_llist.c
// path:			src/core/cinternal_core_list_llist.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/internal_header.h>
#define CINTERNAL_SRC_CORE_CINTERNAL_CORE_LIST_DLLIST_IMPL_H_NEEDED
#include "cinternal_core_list_dllist.impl.h"


CPPUTILS_BEGIN_C



CINTERNAL_EXPORT CinternalLList_t CInternalLListCreateEx(TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	CinternalLList_t pRet;
	a_allocator = a_allocator ? a_allocator : (&malloc);
	pRet = CPPUTILS_STATIC_CAST(CinternalLList_t, (*a_allocator)(sizeof(struct SCinternalLList)));
	if (!pRet) {
		return CPPUTILS_NULL;
	}
	CInternalDLListInitializeInline(pRet, a_allocator, a_deallocator);
	return pRet;
}


CINTERNAL_EXPORT void CInternalLListDestroyEx(CinternalLList_t a_list, TypeCinternalDeallocator a_remainingDataCleaner)
{
	CInternalDLListDestroyExInline(a_list, a_remainingDataCleaner);
}


CINTERNAL_EXPORT CInternalLListIterator CInternalLListAddDataBeforeIterator(CinternalLList_t a_list, CInternalLListIterator a_iter, const void* a_data)
{
	return CInternalDLListAddDataBeforeIteratorInline(a_list, a_iter, a_data);
}


CINTERNAL_EXPORT CInternalLListIterator CInternalLListAddDataAfterIterator(CinternalLList_t a_list, CInternalLListIterator a_iter, const void* a_data)
{
	return CInternalDLListAddDataAfterIteratorInline(a_list, a_iter, a_data);
}


CINTERNAL_EXPORT CInternalLListIterator CInternalLListFirstItem(ConstCinternalLList_t a_list)
{
	return a_list->first;
}


CINTERNAL_EXPORT CInternalLListIterator CInternalLListLastItem(ConstCinternalLList_t a_list)
{
	return a_list->last;
}


CINTERNAL_EXPORT void CInternalLListRemoveData(CinternalLList_t a_list, CInternalLListIterator a_iterator)
{
	CInternalDLListRemoveDataInline(a_list, a_iterator);
}


CINTERNAL_EXPORT size_t CInternalLListSize(ConstCinternalLList_t a_list)
{
	return a_list->m_size;
}


CPPUTILS_END_C
