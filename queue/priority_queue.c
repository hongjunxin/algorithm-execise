#include <stdlib.h>
#include <stdio.h>

typedef struct prio_q_element {
	void *value;
	int priority;
} prio_q_element_t;

typedef struct prio_queue {
	int size;
	int items;
	prio_q_element_t **e;	/* point to element array */
} prio_queue_t;

prio_queue_t *init_prio_queue(int initsize);
int enqueue(prio_queue_t *queue, prio_q_element_t *element);
prio_q_element_t *dequeue(prio_queue_t *queue);


prio_queue_t *init_prio_queue(int initsize)
{
	prio_queue_t *q;
	
	q = (prio_queue_t*) malloc(sizeof(prio_queue_t));
	if (!q)
		return NULL;
	q->size = initsize;
	q->items = 0;
	q->e = malloc(sizeof(prio_q_element_t*)*initsize);
	return q;
}

int enqueue(prio_queue_t *queue, prio_q_element_t *element)
{	
	int i, p;
	prio_q_element_t *tmp;
	
	if (queue->size == queue->items) {
		tmp = queue->e;
		queue->e = (prio_q_element_t*) realloc(queue->e, queue->size*2);
		if (!queue->e) {
			queue->e = tmp;
			return -1;
		}
		queue->size *= 2;
	}
	
	queue->e[queue->items++] = element;
	i = queue->items - 1;
	while ((i-1)/2 >= 0) {
		p = (i-1)/2;
		if (queue->e[i]->priority > queue->e[p]->priority) {
			tmp = queue->e[i];
			queue->e[i] = queue->e[p];
			queue->e[p] = tmp;
			i = p;
		} else {
			break;
		}
	}
	return 0;
}

prio_q_element_t *dequeue(prio_queue_t *queue)
{
	int i, cl, cr;
	prio_q_element_t *tmp;
	int bigger;
	
	if (!queue->items)
		return NULL;
	
	prio_q_element_t *e = queue->e[0];
	i = 0;
	queue->e[0] = queue->e[--queue->items];
	while ((2*i+1) < queue->items) {
		cl = 2*i+1;
		cr = 2*i+2;
		tmp = queue->e[i];
		if (queue->e[i]->priority < queue->e[cl]->priority)
			bigger = cl;
		else
			bigger = i;
		/* cr not always existing */
		if ((cr <= queue->items-1) &&
		    (queue->e[bigger]->priority < queue->e[cr]->priority))
			bigger = cr;
		if (i==bigger)
			break;
		queue->e[i] = queue->e[bigger];
		queue->e[bigger] = tmp;
		i = bigger;
	}
	return e;
}


/* Test Code */

static void show_queue(prio_queue_t *q)
{
	prio_q_element_t **e = q->e;
	int i;
	
	for (i=0; ; i++) {
		if (e[i])
			printf("%d ", (int) e[i]->value);
		else
			break;
	}	
	printf("\n");
}

#define INIT_E(prio, val) \
	e = (prio_queue_t*) malloc(sizeof(prio_q_element_t)); \
	e->priority = prio; \
	e->value = val; \
	enqueue(q, e);

int main(int argc, char **argv)
{
	prio_queue_t *q = init_prio_queue(10);
	prio_q_element_t *e;
	int i;

	INIT_E(1, 1);
	INIT_E(3, 3);
	INIT_E(10, 10);
	INIT_E(7, 7);
	INIT_E(9, 9);
	INIT_E(4, 4);
	INIT_E(6, 6);
	INIT_E(5, 5);
	INIT_E(8, 8);
	INIT_E(2, 2);
	show_queue(q);

	for (i=0; ; i++) {
		if (e=dequeue(q))
			printf("dequeue->%d\n", (int) e->value);
		else
			break;
	}	
	return 0;
}

#undef INIT_E