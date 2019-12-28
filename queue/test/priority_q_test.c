#include <stdio.h>
#include <stdlib.h>
#include "../queue.h"

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
    e = (prio_q_element_t*) malloc(sizeof(prio_q_element_t)); \
    e->priority = prio; \
    e->value = (void*) val; \
    q->enqueue(q, e);

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
        if (e=q->dequeue(q))
            printf("dequeue->%d\n", (int) e->value);
        else
            break;
    }    
    return 0;
}
#undef INIT_E
