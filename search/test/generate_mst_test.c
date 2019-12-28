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

	g->add_edge_with_weight(g, "A", "B", 0, 6);
	g->add_edge_with_weight(g, "A", "D", 0, 4);
	g->add_edge_with_weight(g, "D", "B", 0, 7);
	g->add_edge_with_weight(g, "B", "C", 0, 10);
	g->add_edge_with_weight(g, "D", "E", 0, 12);
	g->add_edge_with_weight(g, "B", "E", 0, 7);
	g->add_edge_with_weight(g, "D", "C", 0, 8);
	g->add_edge_with_weight(g, "C", "E", 0, 5);
	g->add_edge_with_weight(g, "C", "F", 0, 6);
	g->add_edge_with_weight(g, "E", "F", 0, 7);

	g->generate_weight_mst(g, "A");

	return 0;
}	

