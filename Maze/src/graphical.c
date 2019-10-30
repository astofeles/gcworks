#include "graphical.h"

#ifdef _MAZE_GRAPHICAL_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include "maze.h"
#include "util.h"
#include "config.h"

void drawFloor(int n) {
    glPushMatrix();
    glColor3f(floorcolor);
    glScalef(n, 0.1, n);
    glTranslatef(0.5, 0, 0.5);
    glutSolidCube(1);
    glPopMatrix();
}

/* Draws a single maze cell. Note that a Maze is composed by NxN
 * cells, where N is the maze complexity defined in 'config.h' */
void drawCell(int cell) {
    glPushMatrix();
    glColor3f(wallcolor);
    if ((cell & 0x0f) == 0x0f) {
        glTranslatef(0.5, 0.5, 0.5);
        glutSolidCube(1);
    } else {
        // one cell will be seen as divided by four:
        // then each little square is 0.25 the square.
        // note that .i is the order the wall is drawn
        //
        // .7        .6         .5
        //    ,---,---,---,---,
        //    |NW | NORTH | NE|
        //    |---+---+---+---|
        //    | W |   |   | E |
        // .8 |-E-+---+---+-A-| .4
        //    | S |   |   | S |
        //    |---+---+---+---|
        //    |SW | SOUTH | SE|
        //    '---'---'---'---'
        // .1        .2         .3
        //
        glScalef(0.25, 1, 0.25);
        // south-east corner (aways)
        glTranslatef(0.5, 0.5, 0.5);
        glutSolidCube(1);
        // south wall (not aways)
        glTranslatef(1.5, 0, 0);
        if (cell & SOUTH) {
            glPushMatrix();
            glScalef(2, 1, 1);
            glutSolidCube(1);
            glPopMatrix();
        }
        // south-east corner (aways)
        glTranslatef(1.5, 0, 0);
        glutSolidCube(1);
        // east wall (not aways)
        glTranslatef(0, 0, 1.5);
        if (cell & EAST) {
            glPushMatrix();
            glScalef(1, 1, 2);
            glutSolidCube(1);
            glPopMatrix();
        }
        // north-east corner (aways)
        glTranslatef(0, 0, 1.5);
        glutSolidCube(1);
        // north wall (not aways)
        glTranslatef(-1.5, 0, 0);
        if (cell & NORTH) {
            glPushMatrix();
            glScalef(2, 1, 1);
            glutSolidCube(1);
            glPopMatrix();
        }
        // north-east corner (aways)
        glTranslatef(-1.5, 0, 0);
        glutSolidCube(1);
        // west corner (not aways)
        glTranslatef(0, 0, -1.5);
        if (cell & WEST) {
            glPushMatrix();
            glScalef(1, 1, 2);
            glutSolidCube(1);
            glPopMatrix();
        }
    }
    glPopMatrix();
}

/* Draws the map based on the maze matrix
 * 
 * Note that it follows the convension. see 'graphical.h'
 */
void drawMap(int map[complexity][complexity], int n) {
    int i, j;
    glPushMatrix();
    for (i = 0; i < n; i++) {
        glPushMatrix();
        for (j = 0; j < n; j++) {
            drawCell(map[i][j]);
            glTranslatef(1, 0, 0);
        }
        glPopMatrix();
        glTranslatef(0, 0, 1);
    }
    glPopMatrix();
}

void drawMaze(int map[complexity][complexity], int n) {
    glPushMatrix();
    drawFloor(n);
    glScalef(1, wallheight, 1);
    drawMap(map, n);
    glPopMatrix();
}

/* It uses the opengl to set the camera in the correct way */
void setCamera() {
    if (camera.mode == PERSP) {
        gluPerspective(camera.aperture, camera.prop, camera.min, camera.max);
    } else {
        glOrtho(camera.xmin, camera.xmax, camera.ymin, camera.ymax, camera.zmin, camera.zmax);
    } 
    gluLookAt(camera.posx, camera.posy, camera.posz, camera.lx, camera.ly, camera.lz, 0, 1, 0);
}

#endif
