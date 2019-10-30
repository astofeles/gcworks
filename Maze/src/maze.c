#include "maze.h"

#ifdef _MAZE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>

void setCamera() {
    if (camera.mode == PERSP) {
        gluPerspective(camera.aperture, camera.prop, camera.min, camera.max);
    } else {
        glOrtho(camera.xmin, camera.xmax, camera.ymin, camera.ymax, camera.zmin, camera.zmax);
    } 
    gluLookAt(camera.posx, camera.posy, camera.posz, camera.lx, camera.ly, camera.lz, 0, 1, 0);
}

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
    camera.prop = 1;
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
    camera.mode = ORTHO;
}

#endif
