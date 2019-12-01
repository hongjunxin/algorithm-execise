#include <stdlib.h>
#include "sort.h"

static void merge(int *a, int begin, int mid, int end)
{
	int *workspace;
	int i, j, k;

	workspace = (int*) malloc(sizeof(int)*(end-begin+1));
	i = begin;
	j = mid + 1;
	k = 0;
	while (i<=mid && j<=end) {
		if (a[i] < a[j])
			workspace[k++] = a[i++];
		else
			workspace[k++] = a[j++];
	}
	while (i<=mid)
		workspace[k++] = a[i++];
	while (j<=end)
		workspace[k++] = a[j++];
	for (i=0; i<k; i++)
		a[begin++] = workspace[i];
	free(workspace);
}

static void sort_rec(int *a, int begin, int end)
{
	int mid;

	if (begin >= end)
		return;
	mid = (begin+end)/2;
	sort_rec(a, begin, mid);
	sort_rec(a, mid+1, end);
	merge(a, begin, mid, end);
}

void merge_sort_rec(int *a, unsigned int size)
{
	sort_rec(a, 0, size-1);
}