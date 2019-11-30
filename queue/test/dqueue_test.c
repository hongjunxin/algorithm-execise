#include <stdio.h>
#include <stdlib.h>
#include "../queue.h"

void print_deque(deque_t *deque)
{
	dqueue_elememt_t *e = deque->head->next;
	for (; e->val; e=e->next)
		printf("%d ", *(int*) e->val);
	printf("[total=%d]\n", deque->total);
}

int main(int arc, char *argv)
{
	int counter = 10;
	int i;
	deque_t *deque = init_deque();
	
	int *a = (int*) malloc(sizeof(int)*counter);
	for (i=0; i<counter; i++)
		a[i] = i+1;
	for (i=0; i<counter; i++)
		deque->head_in(deque, &a[i]);
	print_deque(deque);
	for (i=0; i<counter/2; i++)
		deque->head_out(deque);
	print_deque(deque);
	for (i=0; i<counter/2; i++)
		deque->tail_in(deque, &a[i]);
	print_deque(deque);
	for (i=0; i<counter/2; i++)
		deque->tail_out(deque);
	print_deque(deque);
	
	return 0;
}
