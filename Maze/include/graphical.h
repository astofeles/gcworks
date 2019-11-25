#ifndef _MAZE_GRAPHICAL_H
#define _MAZE_GRAPHICAL_H

/* Convension:
 * - The maze plane is in XZ plane, with Y axe being the depth axe pointed upwards
 *
 *           Y
 *           |
 *           |
 *          / `-._
 *         /      ` Z
 *        X
 *
 * - The maze is composed by NxN cells (#), where each cell is primary sized 1.
 *   Therefore the maze is sized NxN
 * - The maze matrix index is prop-equivalent to the maze cells mapped i:x and j:z.
 *   That is, m[i][j] represents cell '#' in x=ki , z = kj , to some k.
 *
 * z
 * ^
 * | #######
 * | #######
 * | #######
 * | #######
 * `----------> x
 *
 * - Matrix index convension for the map follows:
 *
 * Notation: [i,j]
 *
 * x (i)
 * ^
 * |
 * |[N,0] [N,1] ... [N,N]
 * | ...             ...
 * |[1,0] [1,1] ... [1,N]
 * |[0,0] [0,1] ... [0,N]
 * `------------------------> z (j)
 *
 * Notes:
 * [i+1,j] -> goto north
 * [i,j+1] -> goto east
 * [i-1,j] -> goto south
 * [i,j-1] -> goto west
 *
 * - The cell drawing convension can be seen in the drawCell
 *   implementation. see 'graphical.c'
 *
 */

#include "config.h"
#include "maze.h"

/* draws the maze floor based on the number n */
extern void drawFloor(int);

/* draws the map based on the maze matrix */
extern void drawMap();

/* draws the full maze field */
extern void drawMaze();

/* draws the main player */
extern void drawPlayer();

/* draws a given cell of the maze as an 4 bit written in the form:
 * NORTH | EAST | SOUTH | WEST */
extern void drawCell(int);

extern void drawGraph(int**, int);

/* It sets the lights used */
extern void setLights();

/* It sets the camera */
extern void setCamera();

/* It draws the player */
extern void drawPlayer();

/* Draws the start and end cubes */
extern void drawStartEnd();

#endif
