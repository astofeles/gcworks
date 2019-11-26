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
    // camera.prop = ((float) winwidth) / winheight;
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
    // camera.mode = SUP;
    // camera gaming properties
    camera.speed = 1.0;
}

void mazeMapInit() {
    backgen();
}

void initPlayer() {
    // player phisical
    player.x = 0.5 + maze.start_i;
    player.y = 0;
    player.z = 0.5 + maze.start_j;
    player.radius = ballradius;
    player.speed = 0.1;
    // fred phisical
    fred.x = player.z;
    fred.z = player.x;
    fred.radius = ballradius;
    fred.speed = 0.1;
}


void initFeromon() {
    int i, j;
    for (i = 0; i < complexity; i++)
        for (j = 0; j < complexity; j++)
            ferom[i][j] = 0;
}

int getMapCell(float x, float z) {
    int i, j;
    i = (int) (z);
    j = (int) (x);
    return maze.map[i][j];
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

void feromonSpread(int i, int j) {
    int qnt, top = 0, length, k, l;
    struct node { int i, j, q; } stack[maxcomplexity * maxcomplexity], list[4], pop;
    // fill feromon matrix with zeros
    for (k = 0; k < complexity; k++)
        for (l = 0; l < complexity; l++)
            ferom[k][l] = 0;
    qnt = 2 *complexity;
    stack[top++] = (struct node) {i,j,qnt};
    while (top > 0) {
        // mark feromon level
        ferom[i][j] = qnt;
        qnt--;
        // list neightbors unvisited
        length = 0;
        if (i > 0 && !(maze.map[i][j] & SOUTH) && (ferom[i-1][j] < qnt)) list[length++] = (struct node) {i-1,j,qnt};
        if (j > 0 && !(maze.map[i][j] & WEST) && (ferom[i][j-1] < qnt)) list[length++] = (struct node) {i,j-1,qnt};
        if (i < complexity-1 && !(maze.map[i][j] & NORTH) && (ferom[i+1][j] < qnt)) list[length++] = (struct node) {i+1,j,qnt};
        if (j < complexity-1 && !(maze.map[i][j] & EAST) && (ferom[i][j+1] < qnt)) list[length++] = (struct node) {i,j+1,qnt};

        if (length > 0 && qnt > 0) {
            for (k = length-1; k > 0; k--) {
                // push almost all neighbors
                stack[top++] = list[k];
            }
            i = list[0].i;
            j = list[0].j;
            qnt = list[0].q;
        } else {
            pop = stack[--top];
            i = pop.i;
            j = pop.j;
            qnt = pop.q;
        }
    }
}

int endded(float x, float z) {
    int i, j;
    i = (int) (x);
    j = (int) (z);
    return (i == maze.end_i) && (j == maze.end_j);
}

void setFred() {
    int i, j, max = 0, dir = NONE, xi, zi, dirs[9], available = 0;
    xi = fred.x;
    zi = fred.z;
    i = (int) fred.z;
    j = (int) fred.x;
    // list where fred can go
    if (!colide(fred.x + fred.speed, fred.z)) available |= NORTH;
    if (!colide(fred.x - fred.speed, fred.z)) available |= SOUTH;
    if (!colide(fred.x, fred.z + fred.speed)) available |= EAST;
    switch (dir) {
        case NORTH:
            if (!colide(fred.x+fred.speed, fred.z))
                fred.x += fred.speed;
            break;
        case SOUTH:
            if (!colide(fred.x-fred.speed, fred.z))
                fred.x -= fred.speed;
            break;
        case EAST:
            if (!colide(fred.x, fred.z + fred.speed))
                fred.z += fred.speed;
            break;
        case WEST:
            if (!colide(fred.x, fred.z - fred.speed))
                fred.z -= fred.speed;
            break;
        case NONE:
            break;
        default:
            ERROR("Not a direction");
    }
}
#endif
