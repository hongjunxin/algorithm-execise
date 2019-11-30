#include <unistd.h>
#include <stdlib.h>
#include "stack.h"

static int push(stack_t *s, void *value)
{
	stack_elememt_t *e, *tmp;

	e = (stack_elememt_t*) malloc(sizeof(stack_elememt_t));
	if (!e || !s)
		return -1;
	e->value = value;
	tmp = s->head;
	s->head = e;
	e->next = tmp;
	s->items++;
	return 0;
}

static void *pop(stack_t *s)
{
	stack_elememt_t *e;
	void *value;
	
	if (!s || !s->head)
		return NULL;
	e = s->head;
	value = e->value;
	s->head = s->head->next;
	s->items--;
	free(e);
	return value;
}

static int empty(stack_t *s)
{
	return (s->items == 0) ? 1 : 0;
}

stack_t *init_stack(void)
{
	stack_t *s = (stack_t*) malloc(sizeof(stack_t));

	if (!s)
		return NULL;
	s->items = 0;
	s->head = NULL;
	s->push = push;
	s->pop = pop;
	s->empty = empty;
	return s;
}
