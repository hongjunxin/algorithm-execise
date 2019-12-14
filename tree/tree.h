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

typedef struct seg_tree {
	int *ori_arr;   /* origin array */
	int ori_size;  /* origin array size */
	int *seg_arr; 	/* store segment tree nodes */
	int seg_size;	/* seg_arr size, increase it as not big enough */
	int (*query) (struct seg_tree *tree, int q_begin, int q_end);
	int (*update) (struct seg_tree *tree, int index, int newvalue);
	void (*print) (struct seg_tree *tree);  /* for debug */
} seg_tree_t;

seg_tree_t *init_seg_tree(int *array, int size);

#endif