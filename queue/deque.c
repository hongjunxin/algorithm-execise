#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "queue.h"

static int head_in(deque_t *deque, void *value)
{
	dqueue_elememt_t *e = (dqueue_elememt_t*) malloc(sizeof(dqueue_elememt_t));
	
	if (!e || (deque->total >= INT_MAX))
		return -1;
	e->val = value;
	e->pre = deque->head;
	e->next = deque->head->next;	
	deque->head->next->pre = e;
	deque->head->next = e;
	deque->total++;
	return 0;
}

static void *head_out(deque_t *deque)
{
	void *value = NULL;
	dqueue_elememt_t *e = deque->head->next;
	value = e->val;
	
	if (!deque->total)
		return NULL;
	e->next->pre = e->pre;
	e->pre->next = e->next;
	deque->total--;
	free(e);
	return value;
}

static int tail_in(deque_t *deque, void *value)
{
	dqueue_elememt_t *e = (dqueue_elememt_t*) malloc(sizeof(dqueue_elememt_t));
	
	if (!e || (deque->total >= UINT_MAX))
		return -1;
	e->val = value;
	e->next = deque->tail;
	e->pre = deque->tail->pre;
	deque->tail->pre->next = e;
	deque->tail->pre = e;
	deque->total++;
	return 0;
}

static void *tail_out(deque_t *deque)
{
	void *value = NULL;
	dqueue_elememt_t *e = deque->tail->pre;
	value = e->val;
	
	if (!deque->total)
		return NULL;
	e->pre->next = e->next;
	e->next->pre = e->pre;
	deque->total--;
	free(e);
	return value;
}

deque_t *init_deque(void)
{
	deque_t *deque = (deque_t*) malloc(sizeof(deque_t));
	dqueue_elememt_t *head = (dqueue_elememt_t*) malloc(sizeof(dqueue_elememt_t));
	dqueue_elememt_t *tail = (dqueue_elememt_t*) malloc(sizeof(dqueue_elememt_t));
	
	if (!deque || !head || !tail)
		return NULL;
	
	head->pre = NULL;
	head->next = tail;
	head->val = NULL;
	tail->pre = head;
	tail->next = NULL;
	tail->val = NULL;
	deque->head = head;
	deque->tail = tail;
	deque->total = 0; /* exclude dummy head and dummy tail */
	deque->head_in = head_in;
	deque->head_out = head_out;
	deque->tail_in = tail_in;
	deque->tail_out = tail_out;
	
	return deque;
}
