#ifndef __SORT_H__
#define __SORT_H__

#include "graph.h"

void bubble_sort(int *a, unsigned int size);
void insert_sort(int *a, unsigned int size);
void merge_sort_rec(int *a, unsigned int size);
void merge_sort_notrec(int *a, unsigned int size);
void quick_sort_rec(int *a, unsigned int size);
void quick_sort_notrec(int *a, unsigned int size);
int topo_sort(graph_t *g, char **lable_list, unsigned int size);

#endif