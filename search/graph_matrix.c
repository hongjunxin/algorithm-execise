#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "graph.h"

static int resize_graph(graph_matrix_t *g)
{
	int **neighbor_matrix;
	int *neighbors;
	vertex_t **vertex_array;
	unsigned int i;

	neighbor_matrix = g->neighbor_matrix;
	g->neighbor_matrix = (int**) realloc(g->neighbor_matrix, g->capacity*2*sizeof(int*));
	if (!g->neighbor_matrix) {
		g->neighbor_matrix = neighbor_matrix;
		return -1;
	}
	for (i=g->num_vertex; i<g->capacity*2; i++)
		g->neighbor_matrix[i] = NULL;
	for (i=0; i<g->capacity*2; i++) {
		neighbors = g->neighbor_matrix[i];
		g->neighbor_matrix[i] = (int*) realloc(g->neighbor_matrix[i], g->capacity*2*sizeof(int));
		if (!g->neighbor_matrix[i]) {
			g->neighbor_matrix[i] = neighbors;
			return -1;
		}
		if (neighbors)
			memset(&(g->neighbor_matrix[i][g->num_vertex]), 0, g->capacity*sizeof(int));
		else
			memset(g->neighbor_matrix[i], 0, g->capacity*2*sizeof(int));
	}
	vertex_array = g->vertex_array;
	g->vertex_array = (vertex_t**) realloc(g->vertex_array, g->capacity*2*sizeof(vertex_t*));
	if (!g->vertex_array) {
		g->vertex_array = vertex_array;
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

static int get_vertex_index(graph_matrix_t *g, char *lable)
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
	a = get_vertex_index(self, lable_a);
	b = get_vertex_index(self, lable_b);
	if (a == -1 || b == -1)
		return -1;
	self->neighbor_matrix[a][b] = 1;  /* means a has a neighbor named b */
	if (!has_direction)
		self->neighbor_matrix[b][a] = 1;

	return 0;
}

static vertex_t *get_unvisited_neighbor(graph_matrix_t *g, vertex_t *v)
{
	int v_index, i;

	v_index = get_vertex_index(g, v->lable);
	for (i=0; i<g->num_vertex; i++)
		if (g->neighbor_matrix[v_index][i] && !g->vertex_array[i]->visited)
			return g->vertex_array[i];
	return NULL;
}

static int dfs(graph_matrix_t *self, char *lable)
{
	stack_t *stack;
	vertex_t *v = NULL, *v_unvisited = NULL;
	int v_index, i;

	stack = init_stack();
	v_index = get_vertex_index(self, lable);
	if (v_index == -1) {
		free(stack);
		return -1;
	}
	v = self->vertex_array[v_index];
	v->visited = 1;
	printf("%s", v->lable);
	stack->push(stack, v);
	while (!stack->empty(stack)) {
		v = stack->peek(stack);
		v_unvisited = get_unvisited_neighbor(self, v);
		if (v_unvisited) {
			v_unvisited->visited = 1;
			printf("%s", v_unvisited->lable);
			stack->push(stack, v_unvisited);
		} else {
			stack->pop(stack);
		}
	}
	printf("\n");
	for (i=0; i<self->num_vertex; i++)
		self->vertex_array[i]->visited = 0;

	free(stack);
	return 0;
}

static int bfs(graph_matrix_t *self, char *lable)
{
	queue_t *queue;
	int v_index, i;
	vertex_t *v;

	queue = init_queue();
	v_index = get_vertex_index(self, lable);
	if (v_index == -1) {
		free(queue);
		return -1;
	}
	v = self->vertex_array[v_index];
	v->visited = 1;
	printf("%s", v->lable);
	queue->enqueue(queue, v);
	while (!queue->empty(queue)) {
		v = queue->dequeue(queue);
		v_index = get_vertex_index(self, v->lable);
		for (i=0; i<self->num_vertex; i++)
			if (self->neighbor_matrix[v_index][i] && !self->vertex_array[i]->visited) {
				self->vertex_array[i]->visited = 1;
				printf("%s", self->vertex_array[i]->lable);
				queue->enqueue(queue, self->vertex_array[i]);
			}
	}
	printf("\n");
	for (i=0; i<self->num_vertex; i++)
		self->vertex_array[i]->visited = 0;

	free(queue);
	return 0;
}

static int warshall(struct graph_matrix *self, int **linked_matrix, unsigned int size)
{
	int i, j, k;
	
	if (!linked_matrix || !size)
		return -1;

	/* copy neighbor_matrix to linked_matrix */
	for (i=0; i<size; i++)
		for (j=0; j<size; j++)
			linked_matrix[i][j] = self->neighbor_matrix[i][j];

	/* Warshall */
	for (i=0; i<size; i++)
		for (j=0; j<size; j++)
			if (self->neighbor_matrix[i][j] == 1)
				for (k=0; k<size; k++)
					if (self->neighbor_matrix[j][k] == 1)
						linked_matrix[i][k] = 1;
	return 0;
}

graph_matrix_t *init_graph_matrix(unsigned int init_capacity)
{
	int i, j;
	graph_matrix_t *g;

	g = (graph_matrix_t*) malloc(sizeof(graph_matrix_t));
	if (!g)
		goto error_free;
	g->neighbor_matrix = (int**) malloc(sizeof(int*)*init_capacity);
	if (!g->neighbor_matrix) 
		goto error_free;
	for (i=0; i<init_capacity; i++) {
		g->neighbor_matrix[i] = (int*) calloc(0, sizeof(int)*init_capacity);
		if (!g->neighbor_matrix[i])
			goto error_free;
	}
	g->vertex_array = (vertex_t**) malloc(sizeof(vertex_t*)*init_capacity);
	if (!g->vertex_array)
		goto error_free;
	g->add_vertex = add_vertex;
	g->add_edge = add_edge;
	g->dfs = dfs;
	g->bfs = bfs;
	g->warshall = warshall;
	g->capacity = init_capacity;
	g->num_vertex = 0;

	return g;

error_free:
	if (g) {
		if (g->neighbor_matrix) {
			for (i=0; i<init_capacity; i++)
				if (g->neighbor_matrix[i])
					free(g->neighbor_matrix[i]);
			free(g->neighbor_matrix);	
		}
		if (!g->vertex_array)
			free(g->vertex_array);
		free(g);
	}
	return NULL;
}

