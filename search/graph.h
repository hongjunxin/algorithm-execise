#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "list.h"

typedef struct vertex {
	char *lable;
	unsigned short visited;  /* 0--unvisited, 1--visited */
	struct vertex *(*get_unvisited_neighbor) (struct vertex *self);
	/* the following fields is for graph_t */
	struct vertex *next;
	list_t *neighbor;
} vertex_t;

/* using neighbor list */
typedef struct graph {
	vertex_t *head;  /* save vertexs */
	unsigned int num_vertex;
	int (*add_vertex) (struct graph *self, char *lable);
	int (*add_edge) (struct graph *self, char *lable_a, char *lable_b, int has_direction);
	int (*dfs) (struct graph *self, char *lable);
	int (*bfs) (struct graph *self, char *lable);
} graph_t;

graph_t *init_graph(void);

/* using neighbor matrix */
typedef struct graph_matrix {
	int **neighbor_matrix;
	unsigned int num_vertex;
	unsigned int capacity;
	vertex_t **vertex_array;
	int (*add_vertex) (struct graph_matrix *self, char *lable);
	int (*add_edge) (struct graph_matrix *self, char *lable_a, char *lable_b, int has_direction);
	int (*dfs) (struct graph_matrix *self, char *lable);
	int (*bfs) (struct graph_matrix *self, char *lable);
} graph_matrix_t;

graph_matrix_t *init_graph_matrix(unsigned int init_capacity);

#endif
