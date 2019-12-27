#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "graph.h"

static int resize_graph(graph_matrix_t *g)
{
	vertex_t **neighbor_matrix;
	vertex_t *neighbors;
	unsigned int i;

	neighbor_matrix = g->neighbor_matrix;
	g->neighbor_matrix = (vertex_t**) realloc(sizeof(vertex_t*)*g->capacity*2);
	if (!g->neighbor_matrix) {
		g->neighbor_matrix = neighbor_matrix;
		return -1;
	}
	printf("old neighbor_matrix=%p\n", neighbor_matrix);
	printf("new neighbor_matrix=%p\n", g->neighbor_matrix);
	for (i=0; i<g->num_vertex; i++) {
		neighbors = g->neighbor_matrix[i];
		g->neighbor_matrix[i] = (vertex_t*) realloc(g->neighbor_matrix[i],
				sizeof(vertex_t)*g->capacity*2);
		if (!g->neighbor_matrix[i]) {
			g->neighbor_matrix[i] = neighbors;
			return -1;
		}
	}
	for (; i<g->capacity*2; i++) {
		g->neighbor_matrix[i] = (vertex_t*) malloc(sizeof(vertex_t)*g->capacity*2);
		if (!g->neighbor_matrix[i])
			return -1;
	}
	g->capacity *= 2;
	
	return 0;
}

static int add_vertex(graph_matrix_t *self, char *lable)
{
	vertex_t *v;
	int i;

	if (!self || !lable)
		return -1;
	for (i=0; i<self->num_vertex; i++)
		if (!strcmp(self->vertex_array[i]->lable, lable))
			return -1;
	if (self->num_vertex >= self->capacity)
		if (resize_graph(self) != 0)
			return -1;
	v = (vertex_t*) malloc(sizeof(vertex_t));
	if (!v) 
		return -1;
	v->lable = lable;
	v->visited = 0;
	self->vertex_array[self->num_vertex++] = v;
	return 0;
}

static int get_verter_index(graph_matrix_t *g, char *lable)
{
	int i;

	for (i=0; i<g->num_vertex; i++)
		if (!strcmp(g->vertex_array[i]->lable, lable))
			return i;
	return -1;
}

static int add_edge(graph_matrix_t *self, char *lable_a, char *lable_b, int has_direction)
{
	int a, b;
	
	if (!self || !lable_a || !lable_b || !strcmp(lable_a, lable_b))
		return -1;
	a = get_verter_index(self, lable_a);
	b = get_verter_index(self, lable_b);
	if (a == -1 || b == -1)
		return -1;
	self->neighbor_matrix[a][b] = 1;  /* means a has a neighbor named b */
	if (!has_direction)
		self->neighbor_matrix[b][a] = 1;

	return 0;
}

static vertex_t *get_unvisited_neighbor(vertex_t *self)
{}

static dfs(graph_matrix_t *self, char *lable)
{}

static bfs(graph_matrix_t *self, char *lable)
{}

graph_matrix_t *init_graph_matrix(unsigned int init_capacity)
{
	int i;
	graph_matrix_t *g;

	g = (graph_matrix_t*) malloc(sizeof(graph_matrix_t));
	if (!g)
		return NULL;
	g->neighbor_matrix = (int**) malloc(sizeof(int*)*init_capacity);
	if (!g->neighbor_matrix)
		return NULL;
	for (i=0; i<init_capacity; i++) {
		g->neighbor_matrix[i] = (int*) malloc(sizeof(int)*init_capacity);
		if (!g->neighbor_matrix[i])
			return NULL;
	}
	g->vertex_array = (vertex_t**) malloc(sizeof(vertex_t*)*init_capacity);
	if (!g->vertex_array)
		return NULL;
	g->add_vertex = add_vertex;
	g->add_edge = add_edge;
	g->dfs = dfs;
	g->bfs = bfs;
	g->capacity = init_capacity;
	g->num_vertex = 0;

	return g;
}

