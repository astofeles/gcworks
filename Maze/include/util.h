#ifndef _MAZE_UTIL
#define _MAZE_UTIL

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

/* Defines the structure of a graph edge */
struct _edge;
typedef struct _edge edge_t;

/* Generates the maze map with backtrack algorithm */
extern void backgen(int[complexity][complexity] , int);

/* DEPRECEATED SECTION */

/* Build a vector list of the edges of a simple graph given by its
 * adjacence matrix representation */
int fill_sorted_edges(int **graph, int n, edge_t *edge_list);
/* Uses Kruskal algorithm to create the minimum spanning tree in a
 * graph given by its adjacence matrix. */
void kruskal(int **graph, int n, int **span);
/* Checks is the addition of an edge will close a cycle in the
 * graph. */
int check_cycle(int **graph, int n, int from, int to);
/* Genrate a graph for the maze of N squared nodes */
void gen_graph(int **gen, int n);


#endif
