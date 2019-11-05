#include "maze.h"

#ifdef _MAZE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>
#include "util.h"       // backgen
#include "config.h"     // winwidth, winheight, playercolor,
                        // ballradius, 

void initCamera() {
    // initial camera settings
    // camera position
    camera.posx = player.x;
    camera.posy = 16;
    camera.posz = player.z;
    // camera lookat
    camera.lx = player.x;
    camera.ly = 0;
    camera.lz = player.z;
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
    // camera mode (PERSP or ORTHO)
    camera.mode = SUP;
    // camera gaming properties
    camera.speed = 1.0;
}

void mazeMapInit() {
    backgen(map, complexity);
}

void initPlayer() {
    // player phisical
    player.x = 1;
    player.y = 0;
    player.z = 1;
    player.radius = ballradius;
}

#endif
