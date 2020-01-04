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
	v->index = self->num_vertex;
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

static int add_edge_with_weight(graph_matrix_t *self, char *lable_a, char *lable_b, 
		int has_direction, int weight)
{
	int a, b;

	if (!self || !lable_a || !lable_b || !strcmp(lable_a, lable_b))
		return -1;
	a = get_vertex_index(self, lable_a);
	b = get_vertex_index(self, lable_b);
	if (a == -1 || b == -1)
		return -1;
	self->neighbor_matrix[a][b] = weight;
	if (!has_direction)
		self->neighbor_matrix[b][a] = weight;

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

static void print_mst(struct graph_matrix *g)
{
	edge_t *edge;
	int total_weight = 0;
	
	while (!g->mst->empty(g->mst)) {
		edge = (edge_t*) g->mst->dequeue(g->mst);
		printf("%s%s(%d) ", edge->a->lable, edge->b->lable, edge->weight);
		total_weight += edge->weight;
	}
	printf("\ntotal weight: %d\n", total_weight);
}

static void enqueue_unvisited_neighbor(struct graph_matrix *g, vertex_t *v, prio_queue_t *prio_q)
{
	vertex_t *unvisited_neighbor;
	edge_t *edge;
	prio_q_element_t *prio_q_element;
	int weight, v_index, i;

	v_index = get_vertex_index(g, v->lable);
	for (i=0; i<g->num_vertex; i++) {
		if (g->neighbor_matrix[v_index][i] && !g->vertex_array[i]->visited) {
			unvisited_neighbor =  g->vertex_array[i];
			weight = g->neighbor_matrix[v->index][unvisited_neighbor->index];
			edge = (edge_t*) malloc(sizeof(edge_t));
			edge->weight = weight;
			edge->a = v;
			edge->b = unvisited_neighbor;
			prio_q_element = (prio_q_element_t*) malloc(sizeof(prio_q_element_t));
			/* So far the implement of prio_queue_t is that the top priority element 
			   has the biggest priority value */
			prio_q_element->priority = -weight;
			prio_q_element->value = (void*) edge; 
			prio_q->enqueue(prio_q, prio_q_element);
		}	
	}
}

static int generate_weight_mst(struct graph_matrix *self, char *begin_lable)
{
	int v_index;
	vertex_t *v;
	edge_t *edge;
	prio_queue_t *prio_q;
	prio_q_element_t *prio_q_element;

	v_index = get_vertex_index(self, begin_lable);
	if (v_index == -1)
		return -1;
	self->mst = init_queue();
	prio_q = init_prio_queue(20);
	v = self->vertex_array[v_index];
	v->visited = 1;
	enqueue_unvisited_neighbor(self, v, prio_q);
	while (!prio_q->empty(prio_q)) {
		prio_q_element = (prio_q_element_t*) prio_q->dequeue(prio_q);
		edge = (edge_t*) prio_q_element->value;
		if (!edge->a->visited) {
			printf("graph vertex info error\n");
			exit(-1);
		}
		if (edge->b->visited) {
			continue;
		} else {
			edge->b->visited = 1;
			enqueue_unvisited_neighbor(self, edge->b, prio_q);
		}
		self->mst->enqueue(self->mst, (void*) edge);
		free(prio_q_element);
	}
	
	print_mst(self);
	return 0;
}

static void print_neighbor_matrix(graph_matrix_t *self)
{
	int i, j;

	printf("[neighbor matrix]\n");
	printf("   ");
	for (i=0; i<self->num_vertex; i++)
		printf("%s\t", self->vertex_array[i]->lable);
	printf("\n");
	for (i=0; i<self->num_vertex; i++) {
		printf("%s: ", self->vertex_array[i]->lable);
		for (j=0; j<self->num_vertex; j++) {
			printf("%d\t", self->neighbor_matrix[i][j]);
			if (j==self->num_vertex-1)
				printf("\n");
		}
	}
	printf("\n");
}

int dijkstra(struct graph_matrix *self, char *begin_lable, dijkstra_path_info_t *ret)
{
	int begin_index, i, weight, weight_tmp;
	vertex_t *vertex_tmp;
	prio_queue_t *prio_q;
	prio_q_element_t *prio_q_e;
	
	if (!self || !begin_lable || !ret)
		return -1;
	begin_index = get_vertex_index(self, begin_lable);
	if (begin_index == -1)
		return -1;
	prio_q = init_prio_queue(20);
	for (i=0; i<self->num_vertex; i++) {
		ret[i].weight = self->neighbor_matrix[begin_index][i];
		ret[i].vertex = self->vertex_array[i];
	}

	self->vertex_array[begin_index]->visited = 1;	
	for (i=0; i<self->num_vertex; i++) {
		if (ret[i].weight) {
			ret[i].pre_vertex = self->vertex_array[begin_index];
			prio_q_e = (prio_q_element_t*) malloc(sizeof(prio_q_element_t));
			prio_q_e->priority = -ret[i].weight;
			prio_q_e->value = (void*) self->vertex_array[i];
			prio_q->enqueue(prio_q, prio_q_e);
		}
	}
	while (!prio_q->empty(prio_q)) {
		prio_q_e = (prio_q_element_t*) prio_q->dequeue(prio_q);
		vertex_tmp = (vertex_t*) prio_q_e->value;
		free(prio_q_e);
		if (vertex_tmp->visited)
			continue;
		vertex_tmp->visited = 1;
		for (i=0; i<self->num_vertex; i++) {
			if ((weight=self->neighbor_matrix[vertex_tmp->index][i]) > 0 &&
				 		!self->vertex_array[i]->visited) {	
				 weight_tmp = ret[vertex_tmp->index].weight + weight;
				 /* if A can't go to B at beginning we set weight to 0 */
				 if (weight_tmp < ret[i].weight || ret[i].weight == 0) {
					ret[i].weight = weight_tmp;
				 	ret[i].pre_vertex = vertex_tmp;
				 	prio_q_e = (prio_q_element_t*) malloc(sizeof(prio_q_element_t));
					prio_q_e->priority = -weight_tmp;
					prio_q_e->value = (void*)self->vertex_array[i];
					prio_q->enqueue(prio_q, prio_q_e);
				 }
			}
		}
	}

	for (i=0; i<self->num_vertex; i++)
		self->vertex_array[i]->visited = 0;
	free(prio_q);
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
	g->add_edge_with_weight = add_edge_with_weight;
	g->add_edge = add_edge;
	g->dfs = dfs;
	g->bfs = bfs;
	g->warshall = warshall;
	g->generate_weight_mst = generate_weight_mst;
	g->print_neighbor_matrix = print_neighbor_matrix;
	g->dijkstra = dijkstra;
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

