#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* using neighbor matrix */
typedef struct graph_matrix {
	int **neighbor_matrix;
	unsigned int nvertex;
	unsigned int capacity;
	int (*add_vertex) (struct graph_matrix *self, char *lable);
	int (*add_edge) (struct graph_matrix *self, char *lable_a, char *lable_b, int has_direction);
	int (*dfs) (struct graph_matrix *self, char *lable);
	int (*bfs) (struct graph_matrix *self, char *lable);
} graph_matrix_t;


graph_matrix_t *init_graph_matrix(unsigned int init_capacity)
{
	int i;
	graph_matrix_t *g;

	g = (graph_matrix_t*) malloc(sizeof(graph_matrix_t));
	g->neighbor_matrix = (int**) malloc(sizeof(int*)*init_capacity);
	if (!g)
		return NULL;
	for (i=0; i<init_capacity; i++) {
		g->neighbor_matrix[i] = (int*) malloc(sizeof(int)*init_capacity);
		if (!g->neighbor_matrix[i])
			return NULL;
	}
	g->capacity = init_capacity;
	g->nvertex = 0;

	return g;
}

int main(int argc, char **argv)
{
	int i, j;
	graph_matrix_t *g = init_graph_matrix(4);

	if (!g) {
		printf("init graph failed\n");
		exit(-1);
	}
	
	for (i=0; i<g->capacity; i++)
		for (j=0; j<g->capacity; j++)
			g->neighbor_matrix[i][j] = j;

	for (i=0; i<g->capacity; i++)
		for (j=0; j<g->capacity; j++) {
			printf("%d ", g->neighbor_matrix[i][j]);
			if (j == g->capacity-1)
				printf("\n");
		}
	printf("\n");
	return 0;
}
