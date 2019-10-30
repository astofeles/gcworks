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
    camera.posx = 0;
    camera.posy = 20;
    camera.posz = 0;
    // camera lookat
    camera.lx = 0;
    camera.ly = 0;
    camera.lz = 0;
    // perspective properties
    camera.aperture = 45;
    camera.prop = (float) winwidth / winheight;
    camera.min = 1;
    camera.max = 100;
    // orthogonal properties
    camera.xmin = 0;
    camera.xmax = 32;
    camera.ymin = 0;
    camera.ymax = 32;
    camera.zmin = 0;
    camera.zmax = 32;
    // camera mode (PERSP or ORTHO)
    camera.mode = PERSP;
    // camera gaming properties
    camera.speed = 1.0;
}

void mazeMapInit() {
    backgen(map, complexity);
}

#endif
