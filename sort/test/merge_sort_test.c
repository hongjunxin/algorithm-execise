#include <stdio.h>
#include "../sort.h"

int main(void)
{
	int a[10] = {1,51,2,36,8,4,23,10,9,7};
	int size = sizeof(a)/sizeof(a[0]);
	int i;

	merge_sort_rec(a, size);
	for (i=0; i<size; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;

}
