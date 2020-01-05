#include "graph.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

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
			if (linked_matrix[i][j] == INT_MAX)
				printf("--\t");
			else
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

	g->add_edge_with_weight(g, "A", "B", 1, 50);
	g->add_edge_with_weight(g, "A", "D", 1, 80);
	g->add_edge_with_weight(g, "B", "D", 1, 90);
	g->add_edge_with_weight(g, "B", "C", 1, 60);
	g->add_edge_with_weight(g, "C", "E", 1, 40);
	g->add_edge_with_weight(g, "D", "E", 1, 70);
	g->add_edge_with_weight(g, "D", "C", 1, 20);
	g->add_edge_with_weight(g, "E", "B", 1, 50);

	linked_matrix = (int**) malloc(g->num_vertex*sizeof(int*));
	for (i=0; i<g->num_vertex; i++)
		linked_matrix[i] = (int*) calloc(0, g->num_vertex*sizeof(int));
	g->floyd(g, linked_matrix, g->num_vertex);
	g->print_neighbor_matrix(g);
	print_linked_matrix(g, linked_matrix);

	return 0;
}
