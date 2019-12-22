#include <stdio.h>
#include "../graph.h"

int main(int argc, char **argv)
{
	graph_t *g = init_graph();

	g->add_vertex(g, "A");
	g->add_vertex(g, "B");
	g->add_vertex(g, "C");
	g->add_vertex(g, "D");
	g->add_vertex(g, "E");
	g->add_vertex(g, "F");

	g->add_edge(g, "A", "B");
	g->add_edge(g, "A", "C");
	g->add_edge(g, "B", "C");
	g->add_edge(g, "B", "D");
	g->add_edge(g, "C", "D");
	g->add_edge(g, "C", "E");
	g->add_edge(g, "D", "E");
	g->add_edge(g, "D", "F");

	g->dfs(g, "F");
	g->bfs(g, "A");

	return 0;
}
