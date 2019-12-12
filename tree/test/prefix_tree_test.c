#include <stdio.h>
#include <stdlib.h>
#include "../tree.h"

static void errExit(void)
{
	printf("Test Faild\n");
	exit(-1);
}

int main(void)
{
	Trie* obj = trieCreate();
	
	trieInsert(obj, "hello");
	trieInsert(obj, "app");
	trieInsert(obj, "apple");
	
	if (!trieSearch(obj, "app") || 
			!trieSearch(obj, "apple") ||
			!trieSearch(obj, "hello"))
		errExit();
	if (!trieStartsWith(obj, "app") ||
		!trieStartsWith(obj, "he"))
		errExit();
	trieFree_notrec(obj);

	printf("Test PASSED\n");
	return 0;
}

