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

/* This struct defines the properties used by the camera */
struct {
    float posx, posy, posz;
    float lx, ly, lz;
    float aperture, prop, min, max;
    float xmin, xmax, ymin, ymax, zmin, zmax;
    float speed;
    enum {
        PERSP,
        ORTHO
    } mode;
} camera;

/* This is the global map matrix of the maze */
int map[complexity][complexity];

/* It initializes the camera with some default values */
extern void initCamera();

/* It initializes the global maze map */
extern void mazeMapInit();

#endif
