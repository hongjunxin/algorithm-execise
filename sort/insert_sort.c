#include "sort.h"

void insert_sort(int *a, unsigned int size)
{
	int i, j, cur;

	for (i=1; i<size; i++) {
		cur = a[i];
		j = i;
		while (j-- && cur<a[j])
			a[j+1] = a[j];
		a[j+1] = cur;
	}
}

