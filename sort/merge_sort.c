#include <stdlib.h>
#include "../stack/stack.h"
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

void merge_sort_notrec(int *a, unsigned int size)
{
	stack_t *s = init_stack();
	int pre_begin = -1;
	int pre_end = -1;
	int begin = 0;
	int end = size - 1;
	int mid;

	s->push(s, 0);
	s->push(s, size-1);
	while (!s->empty(s)) {
		end = s->pop(s);
		begin = s->pop(s);
		mid = (begin+end)/2;

		if (begin >= end)
			continue;
		if ((end-begin == 1) ||
				(begin<=pre_begin && pre_end<=end)) {
			merge(a, begin, mid, end);
			pre_begin = begin;
			pre_end = end;
		} else {
			s->push(s, begin);
			s->push(s, end);
			s->push(s, begin);
			s->push(s, mid);
			s->push(s, mid+1);
			s->push(s, end);
			pre_begin = pre_end = -1;
		}
	}
}