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
    glScalef(n, 0, n);
    glutSolidCube(1);
    glPopMatrix();
}

/* Draws a single maze cell. Note that a Maze is composed by NxN
 * cells, where N is the maze complexity defined in 'config.h' */
void drawCell(int cell) {
    glPushMatrix();
    glColor3f(wallcolor);
    // one cell will be seen as divided by four:
    // then each little square is 0.25 the square.
    // note that .i is the order the wall is drawn
    //
    // .7        .6         .5
    //    ,---,---,---,---,
    //    |NE | NORTH | NW|
    //    |---+---+---+---|
    //    | E |   |   | W |
    // .8 |-A-+---+---+-E-| .4
    //    | S |   |   | S |
    //    |---+---+---+---|
    //    |SE | SOUTH | SW|
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
    // south-west corner (aways)
    glTranslatef(1.5, 0, 0);
    glutSolidCube(1);
    // west wall (not aways)
    glTranslatef(0, 0, 1.5);
    if (cell & WEST) {
        glPushMatrix();
        glScalef(1, 1, 2);
        glutSolidCube(1);
        glPopMatrix();
    }
    // north-west corner (aways)
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
    // east corner (not aways)
    glTranslatef(0, 0, -1.5);
    if (cell & EAST) {
        glPushMatrix();
        glScalef(1, 1, 2);
        glutSolidCube(1);
        glPopMatrix();
    }
    glPopMatrix();
}

/* draws the map based on the maze matrix */
void drawMap(int ** map, int n) {
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

void drawMaze(int **map, int n) {
    glPushMatrix();
    drawFloor(n);
    glScalef(1, wallheight, 1);
    drawMap(map, n);
    glPopMatrix();
}

#endif
