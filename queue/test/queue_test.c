#include "../queue.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main(int argc, char **argv)
{
	int i;
	queue_t *q;

	q = init_queue();
	for (i=0; i<SIZE; i++)
		q->enqueue(q, i);
	if (q->total != SIZE) {
		printf("Test FAIL\n");
		exit(-1);
	}
	for (i=0; i<SIZE; i++)
		if (q->dequeue(q) != i) {
			printf("Test FAIL\n");
			exit(-1);
		}
	if (!q->empty(q)) {
		printf("Test FAIL\n");
		exit(-1);
	}
	printf("Test PASSED\n");
	return 0;
}
