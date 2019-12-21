#include <stdlib.h>
#include <string.h>
#include "queue.h"

static int enqueue(struct queue *q, void *value)
{
	q_element_t *e;

	if (!q)
		return -1;
	e = (q_element_t*) malloc(sizeof(q_element_t));
	if (!e)
		return -1;
	e->value = value;
	q->tail->pre->next = e;
	e->pre = q->tail->pre;
	e->next = q->tail;
	q->tail->pre = e;
	q->total++;

	return 0;
}

static void *dequeue(struct queue *q)
{
	void *value;
	q_element_t *e;

	if (!q || q->head->next == q->tail)
		return NULL;
	e = q->head->next;
	value = e->value;
	q->head->next = e->next;
	e->next->pre = q->head;
	q->total--;
	free(e);
	
	return value;
}

static int empty(struct queue* q)
{
	return (q->total == 0);
}

queue_t *init_queue(void)
{
	queue_t *q = (queue_t*) malloc(sizeof(queue_t));
	q->head = (q_element_t*) malloc(sizeof(q_element_t));
	q->tail = (q_element_t*) malloc(sizeof(q_element_t));
	memset(q->head, 0, sizeof(q_element_t));
	memset(q->tail, 0, sizeof(q_element_t));
	q->head->next = q->tail;
	q->tail->pre = q->head;
	q->enqueue = enqueue;
	q->dequeue = dequeue;
	q->empty = empty;
	q->total = 0;
	
	return q;
}
