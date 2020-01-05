#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

static void print_path(char *begin_lable, dijkstra_path_info_t *ret, int size)
{
	int i;
	
	printf("from %s: ", begin_lable);
	for (i=0; i<size; i++)
		if (ret[i].weight)
			printf("%s=%d(%s) ", ret[i].vertex->lable, ret[i].weight, ret[i].pre_vertex->lable);
	printf("\n");
}

int main(int argc, char **argv)
{
	dijkstra_path_info_t *ret;
	int size = 5;
	graph_matrix_t *g = init_graph_matrix(size);

	g->add_vertex(g, "A");
	g->add_vertex(g, "B");
	g->add_vertex(g, "C");
	g->add_vertex(g, "D");
	g->add_vertex(g, "E");

	g->add_edge_with_weight(g, "A", "B", 1, 50);
	g->add_edge_with_weight(g, "A", "D", 1, 80);
	g->add_edge_with_weight(g, "B", "D", 1, 90);
	g->add_edge_with_weight(g, "B", "C", 1, 60);
	g->add_edge_with_weight(g, "C", "E", 1, 40);
	g->add_edge_with_weight(g, "D", "E", 1, 70);
	g->add_edge_with_weight(g, "D", "C", 1, 20);
	g->add_edge_with_weight(g, "E", "B", 1, 50);

	ret = (dijkstra_path_info_t*) malloc(sizeof(dijkstra_path_info_t)*size);
	g->dijkstra(g, "A", ret);
	print_path("A", ret, size);

	memset(ret, 0, sizeof(dijkstra_path_info_t)*size);
	g->dijkstra(g, "B", ret);
	print_path("B", ret, size);
	
	memset(ret, 0, sizeof(dijkstra_path_info_t)*size);
	g->dijkstra(g, "C", ret);
	print_path("C", ret, size);

	memset(ret, 0, sizeof(dijkstra_path_info_t)*size);
	g->dijkstra(g, "D", ret);
	print_path("D", ret, size);
	
	memset(ret, 0, sizeof(dijkstra_path_info_t)*size);
	g->dijkstra(g, "E", ret);
	print_path("E", ret, size);

	return 0;
}
