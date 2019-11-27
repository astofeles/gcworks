#ifndef _MAZE_H
#define _MAZE_H

#include <stdlib.h>
#include "config.h"

/* These are the flags definied to the map maze system
 * 0b0001 -> EAST
 * 0b0010 -> NORTH
 * 0b0100 -> WEST
 * 0b1000 -> SOUTH */
#define EAST    0x1
#define NORTH   0x2
#define WEST    0x4
#define SOUTH   0x8
#define NONE    0x0

int complexity;

/* This struct defines the properties used by the camera */
struct {
    float posx, posy, posz;
    float lx, ly, lz;
    float ux, uy, uz;
    float xmin, xmax, ymin, ymax, zmin, zmax;
    float aperture, prop, min, max;
    float speed;
    int angle;
    enum {
        SUP,
        THIRD,
        FIRST, // DEPRECIATED
        PAUSE  // DEPRECIATED
    } mode;
} camera;
/* Defines the default timer */
struct {
    size_t start;
    size_t end;
    double last_time;
} timer, fredDelay;
/* Defines the main player struct */
struct {
    float x, y, z, radius;      // phisical characteristics
    float speed;
} player, fred;

/* This is the global map matrix of the maze */
struct {
    int map[maxcomplexity][maxcomplexity], start_i, start_j, end_i, end_j;
} maze;
/* The feremon index of the player */
int ferom[maxcomplexity][maxcomplexity];

/* It initializes the camera with some default values */
extern void initCamera();

/* init the feromon matrix */
extern void initFeromon();

/* It initializes the player */
extern void initPlayer();

/* It initializes the global maze map */
extern void mazeMapInit();

/* Spreads the feromon based in the given position */
extern void feromonSpread(int, int);

/* Returns the value in matrix that references to the given (X,Z) position */
extern int getMapCell(float, float);

/* checks if a ball in given position colides in the maze */
extern int colide(float, float);

/* checks if collided with fred */
extern int colideFred(float, float);

/* checks if position is in the end of the maze */
extern int endded(float, float);

/* sets fred movement */
extern void setFred();

#endif
