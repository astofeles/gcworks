#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "maze.h"

#ifdef _MAZE_H

void say_hello() {
    printf("Hello, I'm compiling\n");
}

/* Defines the structure of a graph edge
 *
 * @attr "from" the node of one edge end
 * @attr "dest" the other node
 * @attr "weight" the edge weight
 */
struct _edge  {
    int from, dest, weight;
};

/* Build a vector list of the edges of a simple graph given by its
 * adjacence matrix representation
 *
 * @param "graph" An integer matrix of NxN dimension representing the
 *                adjacence matrix of the graph
 *
 *      @note The matrix is suposed to be symetric
 *
 * @param "n" The number of nodes in the graph (or the dimension of the
 *            matrix
 * 
 * @param "edge_list" An array of edges with enough space to store the
 *                    the edges that will be sorted put (by its weigth)
 *                    
 * @return the number of edges in the graph
 */ 
int fill_sorted_edges(int **graph, int n, edge_t *edge_list) { 
    int i, j, k, l;
    edge_t e; l = 0;
    /* iterate trhough the supreior triangle of the matrix */
    for (i = 0; i < n; i++) {
        for (j = i+1; j < n; j++) {
            /* if there is an weighted edge there */
            if (graph[i][j] > 0) {
                e.from = i;
                e.dest = j;
                e.weight = graph[i][j];
                /* inserts the edge "e" in the list, sorted by its weigth */
                k = l;
                while (k > 0 && e.weight <= edge_list[k-1].weight) {
                    edge_list[k] = edge_list[k-1];
                    --k;
                }
                edge_list[k] = e;
                ++l;
            }
        }
    }
    /* return the final list length */
    return l;
}

/* Checks is the addition of an edge will close a cycle in the
 * graph.
 *
 * @param "graph" An integer matrix of NxN dimension representing the
 *                adjacence matrix of the graph
 *
 * @param "n" The number of nodes in the graph (or the dimension of the
 *            matrix
 *
 * @param "from" The first node of the edge to be verified
 *
 * @param "dest" The other node of the edge to be verified
 *
 */
int closes_cycle(int **graph, int n, int from, int to) {
    // TODO: implement this
    return 0;
}

/* Uses Kruskal algorithm to create the minimum spanning tree in a
 * graph given by its adjacence matrix.
 *
 * @param "graph" An integer matrix of NxN dimension representing the
 *                adjacence matrix of the graph
 *
 * @param "n" The number of nodes in the graph (or the dimension of the
 *            matrix
 *
 * @param "span" The adjacence matrix that the spanning tree will be
 *               stored
 */
void kruskal(int **graph, int n, int **span)  {
    int l, i, j;
    edge_t edge_list[N * N], e;
    /* fill spanning tree matrix with zeros */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            span[i][j] = 0;
    /* fill the edge sorted list with the edges of the graph */
    l = fill_sorted_edges(graph, n, edge_list);
    while (l > 0) {
        e = edge_list[i++];
        if ( ! closes_cycle(span, n, e.from, e.dest)) {
            span[e.from][e.dest] = 1;
            span[e.dest][e.from] = 1;
        }
        --l;
    }
}

void create_maze(int **graph, int n) {

}


#endif
