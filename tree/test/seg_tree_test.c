#include "../tree.h"

int main(int argc, char **argv)
{
	int a[] = {1, 3, 5, 7, 9, 11};
	seg_tree_t *seg_tree;

	seg_tree = init_seg_tree(a, sizeof(a)/sizeof(a[0]));
	seg_tree->print(seg_tree);

	printf("[3,5]=%d\n", seg_tree->query(seg_tree, 3, 5));
	printf("[2,5]=%d\n", seg_tree->query(seg_tree, 2, 5));
	return 0;
}

