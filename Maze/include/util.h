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

#endif
