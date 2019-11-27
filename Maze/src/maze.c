#include "maze.h"

#ifdef _MAZE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/freeglut.h>
#include "util.h"       // backgen
#include "config.h"     // winwidth, winheight, playercolor, ballradius, camheight
#include "time.h"       // clock

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
    if (maze.start_i < (complexity/2))
        fred.x = (float) complexity - 0.5;
    else
        fred.x = 0.5;
    if (maze.end_j < (complexity/2))
        fred.z = (float) complexity - 0.5;
    else
        fred.z = 0.5;
    fred.radius = ballradius;
    fred.speed = 0.05;
    fredDelay.start = clock();
}


void initFeromon() {
    int i, j;
    for (i = 0; i < complexity; i++)
        for (j = 0; j < complexity; j++)
            ferom[i][j] = 0;
}

int getMapCell(float x, float z) {
    int i, j;
    i = (int) (x);
    j = (int) (z);
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
    if (dx - ballradius <= 0.2 && (cell&SOUTH)) ret |= SOUTH;
    if (dx + ballradius >= 0.8 && (cell&NORTH)) ret |= NORTH;
    if (dz - ballradius <= 0.2 && (cell&WEST)) ret |= WEST;
    if (dz + ballradius >= 0.8 && (cell&EAST)) ret |= EAST;
    // corners bitwise verification
    if (dx - ballradius <= 0.2 && dz - ballradius <= 0.2) ret |= (WEST | SOUTH);
    if (dx - ballradius <= 0.2 && dz + ballradius >= 0.8) ret |= (EAST | SOUTH);
    if (dx + ballradius >= 0.8 && dz - ballradius <= 0.2) ret |= (WEST | NORTH);
    if (dx + ballradius >= 0.8 && dz + ballradius >= 0.8) ret |= (EAST | NORTH);
    return ret;
}

void feromonSpread(int i, int j) {
    // visited is check in 5th bit (0b10000)
    const int visited = 0x10;
    int qnt, top = 0, length, k, l;
    struct node {
        int i, j, q;
    } stack[maxcomplexity * maxcomplexity], list[4], pop, curr;
    // fill feromon matrix with zeros
    // and unvisit elements in maze.map matrix
    for (k = 0; k < complexity; k++) {
        for (l = 0; l < complexity; l++) {
            ferom[k][l] = 0;
            maze.map[k][l] &= 0x0f;
        }
    }
    qnt = complexity;
    stack[top++] = (struct node) {i,j,qnt};
    while (top > 0 && qnt > 0) {
        // set pseudoon current postion
        ferom[i][j] = qnt;
        maze.map[i][j] |= visited;
        // list not visited possible neighbors
        length = 0;
        if (!(maze.map[i][j] & NORTH) && !(maze.map[i+1][j] & visited))
            list[length++] = (struct node) {i+1, j, qnt-1};
        if (!(maze.map[i][j] & EAST) && !(maze.map[i][j+1] & visited))
            list[length++] = (struct node) {i, j+1, qnt-1};
        if (!(maze.map[i][j] & SOUTH) && !(maze.map[i-1][j] & visited))
            list[length++] = (struct node) {i-1, j, qnt-1};
        if (!(maze.map[i][j] & WEST) && !(maze.map[i][j-1] & visited))
            list[length++] = (struct node) {i, j-1, qnt-1};
        // check is there is neighbors
        if (length > 0) {
            // push all neighbors but first
            for (k = length-1; k > 0; --k)
                stack[top++] = list[k];
            curr = list[0];
            i = curr.i;
            j = curr.j;
            qnt = curr.q;
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
    static int dir = NONE, count = 0;
    int k, l, i, j, max = 0, available = 0, min, s, length;
    int alldirs[] = {NORTH, SOUTH, EAST, WEST};
    struct node {
        int ferom, dir;
    } dirs[5], swap;
    // index feromon
    i = (int) fred.x;
    j = (int) fred.z;
    // list where fred can go
    if (!colide(fred.x + fred.speed, fred.z)) available |= NORTH;
    if (!colide(fred.x, fred.z + fred.speed)) available |= EAST;
    if (!colide(fred.x - fred.speed, fred.z)) available |= SOUTH;
    if (!colide(fred.x, fred.z - fred.speed)) available |= WEST;
    // get neighbors feromon
    length = 0;
    if (!(maze.map[i][j] & NORTH))
        dirs[length++] = (struct node) {ferom[i+1][j], NORTH};
    if (!(maze.map[i][j] & EAST))
        dirs[length++] = (struct node) {ferom[i][j+1], EAST};
    if (!(maze.map[i][j] & SOUTH))
        dirs[length++] = (struct node) {ferom[i-1][j], SOUTH};
    if (!(maze.map[i][j] & WEST))
        dirs[length++] = (struct node) {ferom[i][j-1], WEST};
    dirs[length++] = (struct node) {ferom[i][j], dir};
    // sort neighbors feromon
    s = 1;
    while (s) {
        s = 0;
        for (k = 0; k < length-1; k++) {
            if (dirs[k].ferom > dirs[k+1].ferom) {
                swap = dirs[k];
                dirs[k] = dirs[k+1];
                dirs[k+1] = swap;
                s = 1;
            }
        }
    }
    // walk
    for (k = length-1; k >= 0; k--) {
        if (dirs[k].dir & available) {
            dir = dirs[k].dir;
            if (dirs[k].ferom == 0) count++;
            else count = 0;
            break;
        }
    }
    if (count >= complexity * complexity) {
        count = 0;
        do {
            dir = alldirs[rand() % 4];
        } while (!(dir & available));
    }
    switch (dir) {
        case NORTH:
            fred.x += fred.speed;
            break;
        case SOUTH:
            fred.x -= fred.speed;
            break;
        case EAST:
            fred.z += fred.speed;
            break;
        case WEST:
            fred.z -= fred.speed;
            break;
        case 0:
            break;
        default:
            ERROR("wrong direction");
    }
}

int colideFred(float x, float z) {
    if ( sqrt(pow(x - fred.x,2) + pow(z - fred.z,2)) < ballradius)
        return 1;
    return 0;
}
#endif
