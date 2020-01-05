#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char **argv)
{
	graph_matrix_t *g = init_graph_matrix(6);

	g->add_vertex(g, "A");
	g->add_vertex(g, "B");
	g->add_vertex(g, "C");
	g->add_vertex(g, "D");
	g->add_vertex(g, "E");
	g->add_vertex(g, "F");

	g->add_edge(g, "A", "B", 0);
	g->add_edge(g, "A", "C", 0);
	g->add_edge(g, "B", "C", 0);
	g->add_edge(g, "B", "D", 0);
	g->add_edge(g, "C", "D", 0);
	g->add_edge(g, "C", "E", 0);
	g->add_edge(g, "D", "E", 0);
	g->add_edge(g, "D", "F", 0);

	g->add_vertex(g, "H");
	g->add_edge(g, "E", "H", 0);

	printf("DFS from F: ");
	g->dfs(g, "F");
	printf("BFS from A: ");
	g->bfs(g, "A");
	printf("\n");
		
	return 0;
}

