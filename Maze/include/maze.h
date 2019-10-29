#include <stdlib.h>
#include <stdio.h>

#ifndef _MAZE_H
#define _MAZE_H

#define EAST    1
#define NORTH   2
#define WEST    4
#define SOUTH   8

#define N 32

typedef int * maze_field;

void create_maze(int **graph, int n);

#endif
