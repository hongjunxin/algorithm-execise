#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "../list/list.h"

typedef struct vertex {
	char *lable;
	unsigned short visited;  /* 0--unvisited, 1--visited */
	struct vertex *next;
	list_t *neighbor;
	struct vertex *(*get_unvisited_neighbor) (struct vertex *self);
} vertex_t;

typedef struct graph {
	vertex_t *head;  /* save vertexs */
	int (*add_vertex) (struct graph *self, char *lable);
	int (*add_edge) (struct graph *self, char *lable_a, char *lable_b);
	int (*dfs) (struct graph *self, char *lable);
	int (*bfs) (struct graph *self, char *lable);
} graph_t;

graph_t *init_graph(void);

#endif
