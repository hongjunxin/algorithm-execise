#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "list.h"
#include "queue.h"

typedef struct vertex {
	char *lable;
	unsigned short visited;  /* 0--unvisited, 1--visited */
	unsigned int index;  /* used for graph_matrix_t */
	/* the following fields is for graph_t */
	struct vertex *next;
	list_t *neighbor;
	struct vertex *(*get_unvisited_neighbor) (struct vertex *self);
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
	queue_t *mst;
	int (*add_vertex) (struct graph_matrix *self, char *lable);
	int (*add_edge) (struct graph_matrix *self, char *lable_a, char *lable_b, int has_direction);
	int (*add_edge_with_weight) (struct graph_matrix *self, char *lable_a, char *lable_b, 
			int has_direction, int weight);
	int (*dfs) (struct graph_matrix *self, char *lable);
	int (*bfs) (struct graph_matrix *self, char *lable);
	int (*warshall) (struct graph_matrix *self, int **linked_matrix, unsigned int size);
	/* mst -- minimun spanning tree */
	int (*generate_weight_mst) (struct graph_matrix *self, char *begin_lable);
	void (*print_neighbor_matrix) (struct graph_matrix *self);  /* for debug */
} graph_matrix_t;

graph_matrix_t *init_graph_matrix(unsigned int init_capacity);

/* for Minimum Spanning Tree with weight */
typedef struct edge {
	vertex_t *a;
	vertex_t *b;
	int weight;
} edge_t; 

#endif
