#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

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

	graph_matrix_t *g2 = init_graph_matrix(5);
	int ** linked_matrix;
	int i;
	
	g2->add_vertex(g2, "A");
	g2->add_vertex(g2, "B");
	g2->add_vertex(g2, "C");
	g2->add_vertex(g2, "D");
	g2->add_vertex(g2, "E");
	g2->add_edge(g2, "B", "A", 1);
	g2->add_edge(g2, "A", "C", 1);
	g2->add_edge(g2, "B", "E", 1);
	g2->add_edge(g2, "E", "C", 1);
	g2->add_edge(g2, "D", "E", 1);

	linked_matrix = (int**) malloc(g2->num_vertex*sizeof(int*));
	for (i=0; i<g2->num_vertex; i++)
		linked_matrix[i] = (int*) calloc(0, g2->num_vertex*sizeof(int));
	g2->warshall(g2, linked_matrix, g2->num_vertex);
	g2->print_neighbor_matrix(g2);
	print_linked_matrix(g2, linked_matrix);
		
	return 0;
}

