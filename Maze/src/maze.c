#include "maze.h"

#ifdef _MAZE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>
#include "util.h"       // backgen
#include "config.h"     // winwidth, winheight, playercolor, ballradius, camheight

void initCamera() {
    // initial camera settings
    // camera position
    camera.posx = player.x;
    camera.posy = camheight;
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
    camera.xmin = -8;
    camera.xmax = 8;
    camera.ymin = -8;
    camera.ymax = 8;
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
}


int getMapCell(float x, float z) {
    int i, j;
    i = (int) (z);
    j = (int) (x);
    printf("DBG: i,j = %d,%d\n", i, j);
    return map[i][j];
}

#endif
