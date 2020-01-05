#include "graph.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void print_linked_matrix(graph_matrix_t *g, int **linked_matrix)
{
	int i, j;

	printf("[linked matrix]\n");
	printf("   ");
	for (i=0; i<g->num_vertex; i++)
		printf("%s\t", g->vertex_array[i]->lable);
	printf("\n");
	for (i=0; i<g->num_vertex; i++) {
		printf("%s: ", g->vertex_array[i]->lable);
		for (j=0; j<g->num_vertex; j++) {
			printf("%d\t", linked_matrix[i][j]);
			if (j==g->num_vertex-1)
				printf("\n");
		}
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	int size = 5;
	int ** linked_matrix;
	int i;
	graph_matrix_t *g = init_graph_matrix(size);

	g->add_vertex(g, "A");
	g->add_vertex(g, "B");
	g->add_vertex(g, "C");
	g->add_vertex(g, "D");
	g->add_vertex(g, "E");

	g->add_edge(g, "A", "B", 1);
	g->add_edge(g, "A", "D", 1);
	g->add_edge(g, "B", "D", 1);
	g->add_edge(g, "B", "C", 1);
	g->add_edge(g, "C", "E", 1);
	g->add_edge(g, "D", "E", 1);
	g->add_edge(g, "D", "C", 1);
	g->add_edge(g, "E", "B", 1);

	linked_matrix = (int**) malloc(g->num_vertex*sizeof(int*));
	for (i=0; i<g->num_vertex; i++)
		linked_matrix[i] = (int*) calloc(0, g->num_vertex*sizeof(int));
	g->warshall(g, linked_matrix, g->num_vertex);
	g->print_neighbor_matrix(g);
	print_linked_matrix(g, linked_matrix);

	return 0;
}

