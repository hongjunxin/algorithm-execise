#include <stdio.h>
#include "../stack.h"

int main(void)
{
	stack_t *s;
	int i;

	s = init_stack();
	for (i=0; i<10; i++)
		s->push(s, (void*)i);
	for (i=0; i<10; i++)
		printf("%d ", (int)s->pop(s));
	for (i=0; i<10; i++)
		printf("%d ", (int)s->pop(s));
	printf("\n");
	return 0;
}
