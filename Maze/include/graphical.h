#ifndef _MAZE_GRAPHICAL_H
#define _MAZE_GRAPHICAL_H

/* Convension:
 * - The maze plane is in XZ plane, with
 * Y axe being the depth axe pointed upwards
 * - The maze is composed by NxN cells (#),
 *   where each cell is primary sized 1.
 *   Therefore the maze is sized NxN
 * - The maze matrix index is prop-equivalent
 *   to the maze cells mapped i:x and j:z.
 *   That is, m[i][j] represents cell '#' in
 *   x=ki , z = kj , to some k.
 *
 * z
 * ^
 * | #######
 * | #######
 * | #######
 * | #######
 * `----------> x
 *
 */

/* draws the maze floor based on the number n */
extern void drawFloor(int);

/* draws the map based on the maze matrix */
extern void drawMap(int **, int);

/* draws the full maze field */
extern void drawMaze(int **, int);

extern void drawPlayer();

/* draws a given cell of the maze as an 4 bit written in the form:
 * NORTH | EAST | SOUTH | WEST */
extern void drawCell(int);

extern void drawGraph(int**, int);

#endif
