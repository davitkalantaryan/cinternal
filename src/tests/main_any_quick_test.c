//
// file:            main_any_quick_test.c
// path:			src/tests/main_any_quick_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/export_symbols.h>
#include <cinternal/hash/lhash.h>
#include <stdio.h>
#include <assert.h>

#define CINTERNALS_GLB_CONS_DSGN_VAL	1

static int s_nData = 0;

CPPUTILS_C_CODE_INITIALIZER(code_init) {
	s_nData = CINTERNALS_GLB_CONS_DSGN_VAL;
}

int main(void)
{
	const int key1 = 1;
	const int key2 = 2;
	int nNumber;
	CInternalLHashIterator pItem;
	CinternalLHash_t aHash = CInternalLHashCreate(1024);

	printf("s_nData = %d\n", s_nData);
	assert(s_nData == CINTERNALS_GLB_CONS_DSGN_VAL);

	if (!aHash) {
		perror("\n");
		return 1;
	}

	CInternalLHashAddDataEvenIfExist(aHash, (void*)2, &key1, sizeof(int));
	CInternalLHashAddDataEvenIfExist(aHash, (void*)4, &key2, sizeof(int));

	nNumber = 0;
	pItem = CInternalLHashFirstItem(aHash);
	while (pItem) {
		++nNumber;
		pItem = pItem->nextInList;
	}

	assert(nNumber==2);
	
	pItem = CInternalLHashFind(aHash, &key1, sizeof(int));
	assert(pItem);
	assert(((size_t)pItem->data)==2);

	pItem = CInternalLHashFind(aHash, &key2, sizeof(int));
	assert(pItem);
	assert(((size_t)pItem->data) == 4);

	CInternalLHashDestroy(aHash);

	return 0;
}
