//
// file:			main_cinternal_unit_test.c
// path:			src/tools/cinternal_unit_test/main_cinternal_unit_test.c
// created on:		2023 May 18
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#include <cinternal/list/dllist.h>
#include <stdlib.h>

typedef void (*TypeFunction)(void);

static CinternalDLList_t	s_listOfFunctions = CPPUTILS_NULL;

int main(void)
{
	if (s_listOfFunctions) {
		TypeFunction aFunction;
		CinternalDLListItem_t pItem = CInternalDLListFirstItem(s_listOfFunctions);
		while (pItem) {
			aFunction = CPPUTILS_REINTERPRET_CAST(TypeFunction, pItem->data);
			(*aFunction)();
			pItem = CInternalDLListItemFromDLListIterator(CInternalDLListIteratorFromDLListItem(pItem)->next);
		}
	}
	return 0;
}


CPPUTILS_EXTERN_C CPPUTILS_DLL_PRIVATE void CinternalAddUnitTestFunction(void (*a_function)(void))
{
	if (!s_listOfFunctions) {
		s_listOfFunctions = CInternalDLListCreate();
		if (!s_listOfFunctions) {
			exit(1);
		}
	}

	CInternalDLListAddDataToFront(s_listOfFunctions, a_function);
}
