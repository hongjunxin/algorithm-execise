#include <stdio.h>
#include <stdlib.h>
#include "../tree.h"

static int test_query(seg_tree_t *tree, int q_begin, int q_end)
{
	int i, sum = 0;

	for (i=q_begin; i<=q_end; i++)
		sum += tree->ori_arr[i];
	if (tree->query(tree, q_begin, q_end) == sum)
		return 0;
	else
		return -1;
}

int main(int argc, char **argv)
{
	int a[] = {1, 3, 5, 7, 9, 11};
	seg_tree_t *seg_tree;

	seg_tree = init_seg_tree(a, sizeof(a)/sizeof(a[0]));
	seg_tree->print(seg_tree);

	if (test_query(seg_tree, 3, 5) != 0 ||
			test_query(seg_tree, 2, 5) != 0 ||
		    test_query(seg_tree, 1, 4) != 0) {
		printf("Test FAIL\n");
		return -1;
	} 

	seg_tree->update(seg_tree, 2, seg_tree->ori_arr[2]+1);
	seg_tree->print(seg_tree);
	if (test_query(seg_tree, 0, seg_tree->ori_size-1) != 0) {
		printf("Test FAIL\n");
		return -1;
	}

	printf("Test PASSED\n");
	return 0;
}

