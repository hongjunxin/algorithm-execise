#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct q_element {
	void *value;
	struct q_element *pre;  
	struct q_element *next;  
} q_element_t;

typedef struct queue {
	q_element_t *head;  /* dummy head, always be head */
	q_element_t *tail;  /* dummy tail, always be tail */
	unsigned int total;  /* number of elememts exclude head/tail */
	int (*enqueue) (struct queue *q, void *value);
	void *(*dequeue) (struct queue *q);
	int (*empty) (struct queue *q);
} queue_t;

queue_t *init_queue(void);

typedef struct prio_q_element {
	void *value;
	int priority;
} prio_q_element_t;

typedef struct prio_queue {
	int size;
	unsigned int items;
	prio_q_element_t **e;
	int (*enqueue) (struct prio_queue *queue, prio_q_element_t *element);
	prio_q_element_t *(*dequeue) (struct prio_queue *queue);
	int (*empty) (struct prio_queue *queue);
} prio_queue_t;

prio_queue_t *init_prio_queue(int initsize);

typedef struct dqueue_elememt {
	void *val;
	struct dqueue_elememt *pre;
	struct dqueue_elememt *next;
} dqueue_elememt_t;

typedef struct deque {
	unsigned int total;  /* number of elememts exclude head/tail */
	dqueue_elememt_t *head;  /* dummy head, always be head */
	dqueue_elememt_t *tail;  /* dummy tail, always be tail */
	int (*head_in) (struct deque *deque, void *value);
	void *(*head_out) (struct deque *deque);
	int (*tail_in) (struct deque *deque, void *value);
	void *(*tail_out) (struct deque *deque);
} deque_t;

deque_t *init_deque(void);

#endif
