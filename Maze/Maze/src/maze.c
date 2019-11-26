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

// void RECUR(int i, int j, int qnt) {
//     if (qnt >= 1) {
//         ferom[i][j] = qnt;
//         if (i > 0 && !(maze.map[i][j] & SOUTH)) RECUR(i-1,j,qnt-1);
//         if (j > 0 && !(maze.map[i][j] & WEST)) RECUR(i,j-1,qnt-1);
//         if (i < complexity-1 && !(maze.map[i][j] & NORTH)) RECUR(i+1,j,qnt-1);
//         if (j < complexity-1 && !(maze.map[i][j] & EAST)) RECUR(i,j+1,qnt-1);
//     }
// }
// 
// void feromonSpread(int i, int j) {
//     int qnt, k, l;
//     for (k = 0; k < complexity; k++) {
//         for (l = 0; l < complexity; l++) {
//             ferom[k][l] = 0;
//         }
//     }
//     RECUR(i,j,complexity * complexity - 1);
// }


void feromonSpread(int i, int j) {
    int qnt, top = 0, length, k, l;
    struct node { int i, j, q; } stack[maxcomplexity * maxcomplexity], list[4], pop;
    // fill feromon matrix with zeros
    for (k = 0; k < complexity; k++)
        for (l = 0; l < complexity; l++)
            ferom[k][l] = 0;
    qnt = complexity * complexity;
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
    static int dir = EAST, count = 0;;
    printf("DBG: setFred entered\n");
    int k, l, i, j, max = 0, xi, zi, available = 0;
    int alldirs[] = {NORTH, SOUTH, EAST, WEST};
    struct node {
        int ferom, dir;
    } dirs[5], swap;
    xi = fred.x;
    zi = fred.z;
    // index feromon
    i = (int) fred.x;
    j = (int) fred.z;
    // zero dirs
    for (k = 0; k < 4; k++) dirs[k] = (struct node) {0, NONE} ;
    // list where fred can go
    if (!colide(fred.x + fred.speed, fred.z)) available |= NORTH;
    if (!colide(fred.x, fred.z + fred.speed)) available |= EAST;
    if (!colide(fred.x - fred.speed, fred.z)) available |= SOUTH;
    if (!colide(fred.x, fred.z - fred.speed)) available |= WEST;
    printf("DBG: Available %x\n", available);
    // get neighbors feromon
    dirs[0] = (struct node) {ferom[i+1][j], NORTH};
    dirs[1] = (struct node) {ferom[i][j+1], EAST};
    dirs[2] = (struct node) {ferom[i-1][j], SOUTH};
    dirs[3] = (struct node) {ferom[i][j-1], WEST};
    dirs[4] = (struct node) {ferom[i][j], dir};
    /// DEBUG
    printf("DBG: dirs = [ ");
    for (k = 0; k < 4; k++) printf("%d ", dirs[k].dir);
    printf(" ]\n");
    //// DEBUG
    // sort neighbors feromon
    for (k = 0; k < 4; k++) {
        for (l = 0; l < k; l++) {
            if (dirs[k].ferom < dirs[l].ferom) {
                swap = dirs[k];
                dirs[k] =  dirs[l];
                dirs[l] = swap;
            }
        }
    }
    // walk
    for (k = 4; k >= 0; k--) {
        if (dirs[k].dir & available) {
            printf("DBG: dir = %d\n", dirs[k].dir);
                dir = dirs[k].dir;
            break;
        }
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
#endif
