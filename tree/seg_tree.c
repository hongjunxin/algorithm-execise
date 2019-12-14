#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "tree.h"

static int create(struct seg_tree *tree, int node_idx, int begin, int end)
{
	int mid, left_sum, right_sum;

	if (begin == end) {
		return (tree->seg_arr[node_idx] = tree->ori_arr[begin]);
	} else {
		mid = (begin+end)/2;
		left_sum = create(tree, 2*node_idx+1, begin, mid);
		right_sum = create(tree, 2*node_idx+2, mid+1, end);
		return (tree->seg_arr[node_idx] = left_sum+right_sum);
	}
}

static int base_query(struct seg_tree *tree, int node_idx, int begin, int end, int q_begin, int q_end)
{
	int mid, left_sum, right_sum;

	if (q_end < begin || q_begin > end)
		return 0;
	else if (q_begin <= begin && end <= q_end)
		return tree->seg_arr[node_idx];
	else if (begin == end)
		return tree->ori_arr[begin];
	else {
		mid = (begin+end)/2;
		left_sum = base_query(tree, 2*node_idx+1, begin, mid, q_begin, q_end);
		right_sum = base_query(tree, 2*node_idx+2, mid+1, end, q_begin, q_end);
		return (left_sum + right_sum);
	}
}

static int query(struct seg_tree *tree, int q_begin, int q_end)
{
	return base_query(tree, 0, 0, tree->ori_size-1, q_begin, q_end);
}

static void base_update(struct seg_tree *tree, int index, int del, int node_idx, int begin, int end)
{
	int mid;

	if (index < begin || end < index)
		return;
	else if (begin == end)
		tree->seg_arr[node_idx] += del;
	else {
		tree->seg_arr[node_idx] += del;
		mid = (begin+end)/2;
		base_update(tree, index, del, 2*node_idx+1, begin, mid);
		base_update(tree, index, del, 2*node_idx+2, mid+1, end);
	}
}

/*
 * index -- origin array index
 */
static int update(struct seg_tree *tree, int index, int newvalue)
{
	if (index < 0 || index > tree->ori_size-1 || !tree)
		return -1;
	base_update(tree, index, newvalue-tree->ori_arr[index], 0, 0, tree->ori_size-1);
	tree->ori_arr[index] = newvalue;
	return 0;
}

static void print(struct seg_tree *tree)
{
	int i;

	for (i=0; i<tree->seg_size; i++)
		printf("%d ", tree->seg_arr[i]);
	printf("\n");
}

static int get_seg_arr_size(int ori_arr_size)
{
	double t;
	t = log(ori_arr_size)/log(2);
	t = ceil(t) + 1;
	return (int) pow(2, t);
}

seg_tree_t *init_seg_tree(int *array, int size)
{
	seg_tree_t *tree;
	
	if (!array || size <= 0)
		return NULL;
	tree = (seg_tree_t*) malloc(sizeof(seg_tree_t));
	tree->ori_arr = array;
	tree->ori_size = size;
	tree->seg_size = get_seg_arr_size(size);
	tree->seg_arr = (int*) malloc(sizeof(int) * tree->seg_size);
	tree->query = query;
	tree->update = update;
	tree->print = print;
	create(tree, 0, 0, size-1);
	
	return tree;
}

