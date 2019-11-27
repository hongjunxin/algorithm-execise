#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

typedef struct elememt {
	void *val;
	struct elememt *pre;
	struct elememt *next;
} elememt_t;

typedef struct deque {
	int total;  /* number of elememts exclude head/tail */
	elememt_t *head;  /* dummy head, always be head */
	elememt_t *tail;  /* dummy tail, always be tail */
} deque_t;

deque_t *init_deque(void);

// return 0 -- success, -1 -- failed
int head_in(deque_t *deque, void *value);

void *head_out(deque_t *deque);

// return 0 -- success, -1 -- failed
int tail_in(deque_t *deque, void *value);

void *tail_out(deque_t *deque);

deque_t *init_deque(void)
{
	deque_t *deque = (deque_t*) malloc(sizeof(deque_t));
	elememt_t *head = (elememt_t*) malloc(sizeof(elememt_t));
	elememt_t *tail = (elememt_t*) malloc(sizeof(elememt_t));
	
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
	
	return deque;
}

int head_in(deque_t *deque, void *value)
{
	elememt_t *e = (elememt_t*) malloc(sizeof(elememt_t));
	
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

void *head_out(deque_t *deque)
{
	void *value = NULL;
	elememt_t *e = deque->head->next;
	value = e->val;
	
	if (!deque->total)
		return NULL;
	e->next->pre = e->pre;
	e->pre->next = e->next;
	deque->total--;
	free(e);
	return value;
}

int tail_in(deque_t *deque, void *value)
{
	elememt_t *e = (elememt_t*) malloc(sizeof(elememt_t));
	
	if (!e || (deque->total >= INT_MAX))
		return -1;
	e->val = value;
	e->next = deque->tail;
	e->pre = deque->tail->pre;
	deque->tail->pre->next = e;
	deque->tail->pre = e;
	deque->total++;
	return 0;
}

void *tail_out(deque_t *deque)
{
	void *value = NULL;
	elememt_t *e = deque->tail->pre;
	value = e->val;
	
	if (!deque->total)
		return NULL;
	e->pre->next = e->next;
	e->next->pre = e->pre;
	deque->total--;
	free(e);
	return value;
}

/* Test Code */

void print_deque(deque_t *deque)
{
	elememt_t *e = deque->head->next;
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
		head_in(deque, &a[i]);
	print_deque(deque);
	for (i=0; i<counter/2; i++)
		head_out(deque);
	print_deque(deque);
	for (i=0; i<counter/2; i++)
		tail_in(deque, &a[i]);
	print_deque(deque);
	for (i=0; i<counter/2; i++)
		tail_out(deque);
	print_deque(deque);
	
	return 0;
}
