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
void backgen() {
    // the 5th bit
    const int visited = 0x10;
    int i, j, top = 0, length = 0, chosen, oposite[9], unvisited = complexity * complexity, max = 0;
    struct node {
       int i, j, dir;
    } stack[maxcomplexity * maxcomplexity], list[4], pop;
    oposite[NORTH] = SOUTH;
    oposite[SOUTH] = NORTH;
    oposite[EAST] = WEST;
    oposite[WEST] = EAST;
    // put wall on everywhere
    for (i = 0; i < complexity; i++)
        for (j = 0; j < complexity; j++)
            maze.map[i][j] = ~0 & 0xf;
    i = rand() % complexity;
    j = rand() % complexity;
    // set initials position
    maze.start_i = i;
    maze.start_j = j;
    // set as visited
    maze.map[i][j] |= visited;
    unvisited--;
    // while there are was visited
    while (unvisited > 0) {
        // list the neighbors not visited
        length = 0;
        if (i > 0 && !(maze.map[i-1][j] & visited)) list[length++] = (struct node) {i-1, j, SOUTH};
        if (j > 0 && !(maze.map[i][j-1] & visited)) list[length++] = (struct node) {i, j-1, WEST};
        if (i < complexity-1 && !(maze.map[i+1][j] & visited)) list[length++] = (struct node) {i+1, j, NORTH};
        if (j < complexity-1 && !(maze.map[i][j+1] & visited)) list[length++] = (struct node) {i, j+1, EAST};
        // if there is neighbor not visited
        if (length > 0) {
            // choose randomally a neighbor not viseted
            chosen = rand() % length;
            // push current node if has more then one neighbor
            if (length > 1) stack[top++] = (struct node) {i, j};
            // sets the ends positions as the most mess
            if (top > max) {
                max = top;
                maze.end_i = i;
                maze.end_j = j;
            }
            // remove the wall between the current cell and chosen neighbor
            maze.map[i][j] &= ~list[chosen].dir;
            maze.map[list[chosen].i][list[chosen].j] &= ~oposite[list[chosen].dir];
            // make the chosen cell the current cell and mark as visited
            i = list[chosen].i;
            j = list[chosen].j;
            maze.map[i][j] |= visited;
            unvisited--;
        // else if the stack is not empty
        } else if (top > 0) {
            // pop a cell from the stack while the stack is not empty and the popped cell has no unvisited neighbors
            do {
                pop = stack[--top];
                // list the 'pop' neighbors not visited
                length = 0;
                if (pop.i > 0 && !(maze.map[pop.i-1][pop.j] & visited)) list[length++] = (struct node) {pop.i-1, pop.j, NORTH};
                if (pop.j > 0 && !(maze.map[pop.i][pop.j-1] & visited)) list[length++] = (struct node) {pop.i, pop.j-1, WEST};
                if (pop.i < complexity && !(maze.map[pop.i+1][pop.j] & visited)) list[length++] = (struct node) {pop.i+1, pop.j, SOUTH};
                if (pop.j < complexity && !(maze.map[pop.i][pop.j+1] & visited)) list[length++] = (struct node) {pop.i, pop.j+1, EAST};
            } while (top > 0 && length == 0);
            // make it the current cell
            i = pop.i;
            j = pop.j;
        }
    }
}

void error(char const * file, int line, char const * msg) {
        fprintf(stderr, "Error! See file %s: line %d: %s.\n", file, line, msg);
}
#endif
