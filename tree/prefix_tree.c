#include <string.h>
#include <stdlib.h>
#include "../stack/stack.h"
#include "tree.h"

/* From leetcode 208 */

/** Initialize your data structure here. */
Trie* trieCreate()
{
    Trie *t = (Trie*) malloc(sizeof(Trie));
    memset(t, 0, sizeof(Trie));
	t->end = 0;
    return t;
}

/** Inserts a word into the trie. */
void trieInsert(Trie *obj, char *word)
{ 
    while (*word) {
		if (!obj->child[*word-'a'])
			obj->child[*word-'a'] = trieCreate();
		obj = obj->child[*word-'a'];
		++word;
    }    
	obj->end = 1;
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie *obj, char *word)
{
    while (*word) {
		if (!obj->child[*word-'a'])
			return false;
		obj = obj->child[*word-'a'];
        word++;    
    }
    return (obj->end);
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie *obj, char *prefix) {
    while (*prefix) {
		if (!obj->child[*prefix-'a'])
			return false;
		obj = obj->child[*prefix-'a'];
        prefix++;    
    }
    return true;
}

void trieFree(Trie *obj)
{
    int i;

    if (!obj)
        return;
    for (i=0; i<26; i++) {
        if (obj->child[i])
            trieFree(obj->child[i]);
    }
    free(obj);
} 

void trieFree_notrec(Trie *obj) 
{
	int i;
	stack_t *stack;
	Trie *t;

	if (!obj)
		return;
	stack = init_stack();
	stack->push(stack, obj);
	while (!stack->empty(stack)) {
		t = (Trie*) stack->pop(stack);
		for (i=0; i<26; i++)
			if (t->child[i])
				stack->push(stack, t->child[i]);
		free(t);
	}
}

