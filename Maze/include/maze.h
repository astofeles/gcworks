#ifndef _MAZE_H
#define _MAZE_H

#include "config.h"

/* These are the flags definied to the map maze system
 * 0b0001 -> EAST
 * 0b0010 -> NORTH
 * 0b0100 -> WEST
 * 0b1000 -> SOUTH */
#define EAST    1
#define NORTH   2
#define WEST    4
#define SOUTH   8
#define NONE    0


/* This struct defines the properties used by the camera */
struct {
    float posx, posy, posz;
    float lx, ly, lz;
    float ux, uy, uz;
    float aperture, prop, min, max;
    float xmin, xmax, ymin, ymax, zmin, zmax;
    float speed;
    int angle;
    enum {
        SUP,
        THIRD,
        FIRST,
        PAUSE
    } mode;
} camera;

/* Defines the main player struct */
struct {
    float x, y, z, radius;      // phisical characteristics
    float speed;
} player;

/* This is the global map matrix of the maze */
struct {
    int map[complexity][complexity], start_i, start_j, end_i, end_j;
} maze;
/* The feremon index of the player */
int ferom[complexity][complexity];

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

#endif
