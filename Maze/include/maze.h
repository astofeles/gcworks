#ifndef _MAZE_H
#define _MAZE_H

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
    enum {
        PERSP,
        ORTHO
    } mode;
} camera;

typedef int * maze_field;

extern void create_maze(int **graph, int n);

extern void setCamera();

extern void initCamera();

#endif
