#include <stdio.h>
#include "../sort.h"

int main(void)
{
    int a[10] = {1,5,2,6,18,4,3,210,9,7};
	int b[10] = {1,51,2,36,8,4,23,10,9,7};
    int i;

    quick_sort_rec(a, sizeof(a)/sizeof(a[0]));
    for (i=0; i<sizeof(a)/sizeof(a[0]); i++)
        printf("%d ", a[i]);
    printf("\n");

    quick_sort_notrec(b, sizeof(b)/sizeof(b[0]));
    for (i=0; i<sizeof(b)/sizeof(b[0]); i++)
        printf("%d ", b[i]);
    printf("\n");

    return 0;
}

