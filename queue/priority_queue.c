#include <unistd.h>
#include <stdlib.h>
#include "queue.h"

static int enqueue(prio_queue_t *queue, prio_q_element_t *element)
{	
	int i, p;
	prio_q_element_t *tmp;
	prio_q_element_t **element_array;

	if (queue->size == queue->items) {
		element_array = queue->e;
		queue->e = (prio_q_element_t**) realloc(queue->e, queue->size*2);
		if (!queue->e) {
			queue->e = element_array;
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

static prio_q_element_t *dequeue(prio_queue_t *queue)
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

static int empty(prio_queue_t *q)
{
	return (q->items == 0);
}

prio_queue_t *init_prio_queue(int initsize)
{
	prio_queue_t *q;
	
	q = (prio_queue_t*) malloc(sizeof(prio_queue_t));
	if (!q)
		return NULL;
	q->size = initsize;
	q->items = 0;
	q->e = (prio_q_element_t**) malloc(sizeof(prio_q_element_t*)*initsize);
	q->enqueue = enqueue;
	q->dequeue = dequeue;
	q->empty = empty;
	
	return q;
}
