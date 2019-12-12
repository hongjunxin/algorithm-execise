#ifndef __TREE_H__
#define __TREE_H__

typedef int bool;
#define false 0
#define true 1

typedef struct Trie {
	/* assume all input characters are in [a,z] */
    struct Trie *child[26];
    int end;
} Trie;

Trie* trieCreate(void);
void trieInsert(Trie *obj, char *word);
bool trieSearch(Trie *obj, char *word);
bool trieStartsWith(Trie *obj, char *prefix);
void trieFree(Trie *obj);
void trieFree_notrec(Trie *obj);

#endif