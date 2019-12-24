#include <stdio.h>
#include "graph.h"

int main(int argc, char **argv)
{
	graph_t *g = init_graph();

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

	g->dfs(g, "F");
	g->bfs(g, "A");

	return 0;
}
