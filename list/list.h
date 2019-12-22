#ifndef __LIST_H__
#define __LIST_H__

typedef struct list {
	void *value;
	struct list *next;
} list_t;

#endif