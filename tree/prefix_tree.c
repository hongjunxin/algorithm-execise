#include <stdlib.h>
#include <string.h>
#include "tree.h"

typedef int bool;
#define false 0
#define true 1

typedef struct Trie {
    struct Trie *child[26];
    int end;
} Trie;


/** Initialize your data structure here. */

Trie* trieCreate() {
    Trie *t = (Trie*) malloc(sizeof(Trie));
    memset(t, 0, sizeof(Trie));
    return t;
}

/** Inserts a word into the trie. */
void trieInsert(Trie *obj, char *word)
{ 
    while (*word) {
		if (!obj->child[*word-'a'])
			obj->child[*word-'a'] = trieCreate();
		/* if insert "app" -> "apple", app(1) should not be changed to app(0)
		   when insert "apple" */
		if (!obj->child[*word-'a']->end)
			obj->child[*word-'a']->end = (word[1]=='\0') ? 1 : 0;
		obj = obj->child[*word-'a'];
		++word;
    }    
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

void trieFree(Trie *obj) {
    int i;

    if (!obj)
        return;
    for (i=0; i<26; i++) {
        if (obj->child[i])
            trieFree(obj->child[i]);
    }
    free(obj);
}

int main(void)
{
	char *word = "hello";
	char *prefix = "he";
	
	Trie* obj = trieCreate();
	trieInsert(obj, word);
	bool param_2 = trieSearch(obj, "app");
	bool param_3 = trieStartsWith(obj, prefix);
	printf("param_2=%d, param_3=%d\n", param_2, param_3);
	trieFree(obj);
	return 0;
}

