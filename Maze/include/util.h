#ifndef _MAZE_UTIL
#define _MAZE_UTIL

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#define ERROR(m) (error(__FILE__,__LINE__, (m)))

/* Defines the structure of a graph edge */
struct _edge;
typedef struct _edge edge_t;

/* Generates the maze map with backtrack algorithm */
extern void backgen(int[complexity][complexity] , int);

/* Error messages for the program */
extern void error(char const *, int, char const *);

extern int* hex2rgb(int);
#endif
