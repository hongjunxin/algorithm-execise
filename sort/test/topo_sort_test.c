#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "graph.h"


int main(int argc, char **argv)
{
	graph_t *g = init_graph();
	char **lable_list;
	int i;
	
	g->add_vertex(g, "A");
	g->add_vertex(g, "B");
	g->add_vertex(g, "C");
	g->add_vertex(g, "D");
	g->add_vertex(g, "E");
	g->add_vertex(g, "F");
	g->add_vertex(g, "G");
	g->add_vertex(g, "H");

	lable_list = (char**) malloc(g->nvertex*sizeof(char*));

	g->add_edge(g, "A", "D", 1);
	g->add_edge(g, "A", "E", 1);
	g->add_edge(g, "D", "G", 1);
	g->add_edge(g, "E", "G", 1);
	g->add_edge(g, "B", "E", 1);
	g->add_edge(g, "G", "H", 1);
	g->add_edge(g, "C", "F", 1);
	g->add_edge(g, "F", "H", 1);

	if (!topo_sort(g, lable_list, g->nvertex)) {
		for (i=0; i<g->nvertex; i++)
			printf("%s", lable_list[i]);
		printf("\n");
		return 0;
	} 
	return -1;
 }
