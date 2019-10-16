#include <stdlib.h>
#include <stdio.h>

#ifndef _MAZE_H
#define _MAZE_H

#define N 32

struct _edge;
typedef struct _edge edge_t;

void create_maze(int **graph, int n);
/* Build a vector list of the edges of a simple graph given by its
 * adjacence matrix representation */
int fill_sorted_edges(int **graph, int n, edge_t *edge_list);
/* Uses Kruskal algorithm to create the minimum spanning tree in a
 * graph given by its adjacence matrix. */
void kruskal(int **graph, int n, int **span);
/* Checks is the addition of an edge will close a cycle in the
 * graph. */
int closes_cycle(int **graph, int n, int from, int to);

#endif
