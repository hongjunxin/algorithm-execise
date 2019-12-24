#include <stdlib.h>
#include <stdio.h>
#include "sort.h"
#include "graph.h"

int topo_sort(graph_t *g)
{
	vertex_t *v = NULL;
	unsigned int n_visited = 0;
	
	if (!g)
		return -1;
	for (v=g->head; v; v=v->next)
		if (!v->get_unvisited_neighbor(v))
			break;
	if (!v) {
		printf("Error: the graph has loop. Quit!\n");
		return -1;
	}

	printf("%s", v->lable);
	v->visited = 1;
	n_visited++;
	while (v) {
		for (v=g->head; v; v=v->next) {
			if (!v->visited && !v->get_unvisited_neighbor(v)) {
				printf("%s", v->lable);
				v->visited = 1;
				n_visited++;
				break;
			}
		}
	}
	printf("\n");
	if (n_visited != g->nvertex) {
		printf("Error: the graph has loop. Quit!\n");
		exit(-1);
	}

	for (v=g->head; v; v=v->next)
		v->visited = 0;
	return 0;
}

