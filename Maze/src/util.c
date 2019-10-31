#include "util.h"

#ifdef  _MAZE_UTIL

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"
#include "config.h"

/* Algorithm reference: https://en.wikipedia.org/wiki/Maze_generation_algorithm#Recursive_backtracker
 * 
 * Note that north, south, east, and west defintion follow the convension, see 'graphical.h'
 */
void backgen(int map[complexity][complexity], int n) {
    // the 5th bit
    const int visited = 0x10;
    int i, j, top = 0, length = 0, chosen, oposite[9], unvisited = n * n;
    struct node {
       int i, j, dir;
    } stack[complexity * complexity], list[4], pop;
    oposite[NORTH] = SOUTH;
    oposite[SOUTH] = NORTH;
    oposite[EAST] = WEST;
    oposite[WEST] = EAST;
    // put wall on everywhere
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            map[i][j] = ~0 & 0xf;
    i = rand() % n;
    j = rand() & n;
    map[i][j] |= visited;
    unvisited--;
    // while there are was visited
    while (unvisited > 0) {
        // list the neighbors not visited
        length = 0;
        if (i > 0 && !(map[i-1][j] & visited)) list[length++] = (struct node) {i-1, j, SOUTH};
        if (j > 0 && !(map[i][j-1] & visited)) list[length++] = (struct node) {i, j-1, WEST};
        if (i < n-1 && !(map[i+1][j] & visited)) list[length++] = (struct node) {i+1, j, NORTH};
        if (j < n-1 && !(map[i][j+1] & visited)) list[length++] = (struct node) {i, j+1, EAST};
        // if there is neighbor not visited
        if (length > 0) {
            // choose randomally a neighbor not viseted
            chosen = rand() % length;
            // push current node if has more then one neighbor
            if (length > 1) stack[top++] = (struct node) {i, j};
            // remove the wall between the current cell and chosen neighbor
            map[i][j] &= ~list[chosen].dir;
            map[list[chosen].i][list[chosen].j] &= ~oposite[list[chosen].dir];
            // make the chosen cell the current cell and mark as visited
            i = list[chosen].i;
            j = list[chosen].j;
            map[i][j] |= visited;
            unvisited--;
        // else if the stack is not empty
        } else if (top > 0) {
            // pop a cell from the stack while the stack is not empty and the popped cell has no unvisited neighbors
            do {
                pop = stack[--top];
                // list the 'pop' neighbors not visited
                length = 0;
                if (pop.i > 0 && !(map[pop.i-1][pop.j] & visited)) list[length++] = (struct node) {pop.i-1, pop.j, NORTH};
                if (pop.j > 0 && !(map[pop.i][pop.j-1] & visited)) list[length++] = (struct node) {pop.i, pop.j-1, WEST};
                if (pop.i < n && !(map[pop.i+1][pop.j] & visited)) list[length++] = (struct node) {pop.i+1, pop.j, SOUTH};
                if (pop.j < n && !(map[pop.i][pop.j+1] & visited)) list[length++] = (struct node) {pop.i, pop.j+1, EAST};
            } while (top > 0 && length == 0);
            // make it the current cell
            i = pop.i;
            j = pop.j;
        }
    }
}

/* DEPRECEATED SECTION */

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
int check_cycle(int **graph, int n, int from, int to) {
    // TODO: rebuild this in a correct way
    int color[n], i, stack[n], top = 0, node, cycle = 0;
    /* set all nodes' color to zero */
    for (i = 0; i < n; i++) color[i] = 0;
    /* search in depth first */
    color[from]++;
    /* push the "from" node */
    stack[top++] = from;
    node = to;
    color[node]++;
    /* repeat until find a cycle or the stack become empty */
    while (!cycle && top > 0) {
        /* iterates through the children nodes */
        for (i = 0; i < n; i++) {
            /* checks if node 'i' is child of n
             * and if its not the node considered
             * its parent. */
            if ((graph[node][i] > 0) && (i != stack[top-1])) {
                /* push "node" */
                stack[top++] = node;
                node = i;
                color[node]++;
            }
        }
    }
    return cycle;
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
    edge_t edge_list[n * n], e;
    /* fill spanning tree matrix with zeros */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            span[i][j] = 0;
    /* fill the edge sorted list with the edges of the graph */
    l = fill_sorted_edges(graph, n, edge_list);
    while (l > 0) {
        e = edge_list[i++];
        if ( ! check_cycle(span, n, e.from, e.dest)) {
            span[e.from][e.dest] = 1;
            span[e.dest][e.from] = 1;
        }
        --l;
    }
}

#endif
