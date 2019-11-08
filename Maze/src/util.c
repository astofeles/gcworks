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

void error(char const * file, int line) {
        fprintf(stderr, "Error! See file %s: line %d: command not found.\n", file, line);
}
#endif
