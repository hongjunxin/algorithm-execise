#include <stdio.h>
#include "../sort.h"

static void show_array(int *a, unsigned int size, char *msg)
{
	int i;
	printf("%s ", msg);
    for (i=0; i<size; i++)
        printf("%d ", a[i]);
    printf("\n");
}

static void copy_array(int *dst, int *src, int size)
{
	int i;
	for(i=0; i<size; i++)
		dst[i] = src[i];
}

int main(void)
{
    int a[] = {1,6,2,3,8,4,5,10,9,7};
	int b[] = {1,6,2,3,8,4,5,10,9,7};
	int *tmp = (int*) malloc(sizeof(int)*(sizeof(b)/sizeof(b[0])));
    int i;

	printf("Test recursive\n");
	show_array(a, sizeof(a)/sizeof(a[0]), "Before:");
    merge_sort_rec(a, sizeof(a)/sizeof(a[0]));
	show_array(a, sizeof(a)/sizeof(a[0]), "After:");
	printf("\n");

	printf("Test not recursive\n");
	for (i=1; i<=sizeof(b)/sizeof(b[0]); i++) {
		copy_array(tmp, b, i);
		show_array(tmp, i, "Before:");
	    merge_sort_notrec(tmp, i);
		show_array(tmp, i, "After:");		
	}

    return 0;
}
