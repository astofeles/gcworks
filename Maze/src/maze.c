#include "maze.h"

#ifdef _MAZE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>
#include "util.h" // backgen
#include "config.h" // winwidth, winheight

void initCamera() {
    // initial camera settings
    // camera position
    camera.posx = 16;
    camera.posy = 32;
    camera.posz = 16;
    // camera lookat
    camera.lx = 16;
    camera.ly = 0;
    camera.lz = 16;
    // perspective properties
    camera.aperture = 45;
    camera.prop = ((float) winwidth) / winheight;
    camera.min = 1;
    camera.max = 200;
    // orthogonal properties
    camera.xmin = -16;
    camera.xmax = 48;
    camera.ymin = -16;
    camera.ymax = 48;
    camera.zmin = -16;
    camera.zmax = 48;
    // camera mode (PERSP or ORTHO)
    camera.mode = PERSP;
    // camera gaming properties
    camera.speed = 1.0;
}

void mazeMapInit() {
    backgen(map, complexity);
}

#endif
