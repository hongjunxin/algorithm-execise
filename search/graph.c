#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "graph.h"

static vertex_t *get_unvisited_neighbor(vertex_t *self)
{
	list_t *neighbor;

	if (!self || !self->neighbor)
		return NULL;

	for (neighbor=self->neighbor; neighbor; neighbor=neighbor->next)
		if (!((vertex_t*) neighbor->value)->visited)
			return (vertex_t*) neighbor->value;
	return NULL;
}

static int add_vertex(struct graph *self, char *lable)
{
	vertex_t *v, *vtmp;

	if (!self || !lable)
		return -1;
	
	for (vtmp=self->head; vtmp; vtmp=vtmp->next)
		if (!strcmp(lable, vtmp->lable))
			return -1;

	v = (vertex_t*) malloc(sizeof(vertex_t));
	if (!v)
		return -1;
	v->lable = lable;
	v->visited = 0;
	v->next = self->head;
	self->head = v;
	v->neighbor = NULL;
	v->get_unvisited_neighbor = get_unvisited_neighbor;
	self->num_vertex++;

	return 0;
}

/* has_direction: 0--no direction. 1--has direction, lable_a to lable_b means a->b */
static int add_edge(struct graph *self, char *lable_a, char *lable_b, int has_direction)
{
	vertex_t *va = NULL, *vb = NULL, *vtmp = NULL;
	list_t *neighbor = NULL;

	if (!self || !lable_a || !lable_b || !strcmp(lable_a, lable_b))
		return -1;
	
	for (vtmp=self->head; vtmp; vtmp=vtmp->next) {
		if (!strcmp(vtmp->lable, lable_a))
			va = vtmp;
		else if (!strcmp(vtmp->lable, lable_b))
			vb = vtmp;
		if (va && vb)
			break;
	}
	if (!va || !vb)
		return -1;

	for (neighbor=va->neighbor; neighbor; neighbor=neighbor->next)
		if (neighbor->value == vb)
			return -1;
	if (!has_direction)
		for (neighbor=vb->neighbor; neighbor; neighbor=neighbor->next)
			if (neighbor->value == va)
				return -1;
	
	neighbor = (list_t*) malloc(sizeof(list_t));
	if (!neighbor)
		return -1;
	neighbor->value = (void*) vb;
	neighbor->next = va->neighbor;
	va->neighbor = neighbor;

	if (!has_direction) {
		neighbor = (list_t*) malloc(sizeof(list_t));
		if (!neighbor)
			return -1;
		neighbor->value = (void*) va;
		neighbor->next = vb->neighbor;
		vb->neighbor = neighbor;
	}

	return 0;
}

static int dfs(struct graph *self, char *lable)
{
	stack_t *stack = init_stack();
	vertex_t *v, *vtmp;

	if (!self || !lable)
		return -1;

	for (v=self->head; v; v=v->next)
		if (!strcmp(v->lable, lable))
			break;
	if (!v)
		return -1;
	
	stack->push(stack, (void*) v);
	while (!stack->empty(stack)) {
		v = (vertex_t*) stack->peek(stack);
		if (!v->visited) {
			v->visited = 1;
			printf("%s", v->lable);
		}
		vtmp = v->get_unvisited_neighbor(v);
		if (vtmp)
			stack->push(stack, vtmp);
		else
			stack->pop(stack);
	}

	for (v=self->head; v; v=v->next)
		v->visited = 0;
	free(stack);
	printf("\n");
	return 0;
}

static int bfs(struct graph *self, char *lable)
{
	queue_t *queue;
	list_t *neighbor = NULL;
	vertex_t *v = NULL, *vtmp = NULL;

	queue = init_queue();
	for (v=self->head; v; v=v->next)
		if (!strcmp(v->lable, lable))
			break;
	if (!v)
		return -1;

	v->visited = 1;
	printf("%s", v->lable);
	queue->enqueue(queue, v);
	while (!queue->empty(queue)) {
		v = queue->dequeue(queue);
		while (vtmp=v->get_unvisited_neighbor(v)) {
			vtmp->visited = 1;
			printf("%s", vtmp->lable);
			queue->enqueue(queue, (void*) vtmp);
		}
	}

	for (v=self->head; v; v=v->next)
		v->visited = 0;
	free(queue);
	printf("\n");
	return 0;
}

graph_t *init_graph(void)
{
	graph_t *g = (graph_t*) malloc(sizeof(graph_t));

	if (!g)
		return NULL;
	g->head = NULL;
	g->num_vertex = 0;
	g->add_vertex = add_vertex;
	g->add_edge = add_edge;
	g->dfs = dfs;
	g->bfs = bfs;

	return g;
}

