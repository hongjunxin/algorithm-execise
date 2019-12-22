#ifndef __STACK_H__
#define __STACK_H__

typedef struct stack_elememt {
	void *value;
	struct stack_elememt *next;
} stack_elememt_t;

typedef struct stack {
	unsigned long items;
	stack_elememt_t *head;
	int (*push) (struct stack *s, void *value);
	void *(*peek) (struct stack *s);
	void *(*pop) (struct stack *s);
	int (*empty) (struct stack *s);
} stack_t;

stack_t* init_stack(void);

#endif