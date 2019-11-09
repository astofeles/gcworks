#include "maze.h"

#ifdef _MAZE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/freeglut.h>
#include "util.h"       // backgen
#include "config.h"     // winwidth, winheight, playercolor, ballradius, camheight

void initCamera() {
    // initial camera settings
    // camera position
    camera.posx = player.x;
    camera.posy = camheight/2;
    camera.posz = player.z;
    // camera lookat
    camera.lx = player.x;
    camera.ly = 0;
    camera.lz = player.z;
    // upwards settings
    camera.ux = 1;
    camera.uz = 0;
    camera.uy = 0;
    // perspective properties
    camera.aperture = 45;
    camera.prop = ((float) winwidth) / winheight;
    camera.min = 1;
    camera.max = 200;
    // orthogonal properties
    camera.xmin = -8.0 * camera.prop;
    camera.xmax = 8.0 * camera.prop;
    camera.ymin = -8.0;
    camera.ymax = 8.0;
    camera.zmin = -32;
    camera.zmax = 32;
    // camera mode (SUP, THIRD or FIRST)
    camera.mode = SUP;
    // camera gaming properties
    camera.speed = 1.0;
}

void mazeMapInit() {
    backgen(map, complexity);
}

void initPlayer() {
    // player phisical
    player.x = 0.5;
    player.y = 0;
    player.z = 0.5;
    player.radius = ballradius;
    player.speed = 0.1;
}


int getMapCell(float x, float z) {
    int i, j;
    i = (int) (z);
    j = (int) (x);
    return map[i][j];
}


/* checks if a ball in given position colides in the maze */
int colide(float x, float z) {
    float dx, dz;
    int cell, ret;
    ret = NONE;
    cell = getMapCell(x, z);
    dx = x - (int)x;
    dz = z - (int)z;
    // walls bitwise verification
    if (dx - ballradius <= 0.2 && (cell&WEST)) ret |= WEST;
    if (dx + ballradius >= 0.8 && (cell&EAST)) ret |= EAST;
    if (dz - ballradius <= 0.2 && (cell&SOUTH)) ret |= SOUTH;
    if (dz + ballradius >= 0.8 && (cell&NORTH)) ret |= NORTH;
    // corners bitwise verification
    if (dx - ballradius <= 0.2 && dz - ballradius <= 0.2) ret |= (WEST | SOUTH);
    if (dx - ballradius <= 0.2 && dz + ballradius >= 0.8) ret |= (WEST | NORTH);
    if (dx + ballradius >= 0.8 && dz - ballradius <= 0.2) ret |= (EAST | SOUTH);
    if (dx + ballradius >= 0.8 && dz + ballradius >= 0.8) ret |= (EAST | NORTH);
    return ret;
}

#endif
