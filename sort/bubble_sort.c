#include "sort.h"

void bubble_sort(int *a, unsigned int size)
{
	int i, j;
	int tmp;
	
	for (i=0; i<size; i++)
		for (j=0; j<size-i-1; j++) {
			if (a[j] > a[j+1]) {
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
}
