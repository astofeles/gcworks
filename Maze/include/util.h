#include <stdio.h>
#include <stdlib.h>

#ifndef _MAZE_UTIL
#define _MAZE_UTIL

/* Defines the structure of a graph edge */
struct _edge;
typedef struct _edge edge_t;

/* Build a vector list of the edges of a simple graph given by its
 * adjacence matrix representation */
int fill_sorted_edges(int **graph, int n, edge_t *edge_list);
/* Uses Kruskal algorithm to create the minimum spanning tree in a
 * graph given by its adjacence matrix. */
void kruskal(int **graph, int n, int **span);
/* Checks is the addition of an edge will close a cycle in the
 * graph. */
int check_cycle(int **graph, int n, int from, int to);

#endif
