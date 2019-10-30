#ifndef _MAZE_CONFIG_H
#define _MAZE_CONFIG_H

/* Game playing */
#define winwidth        600    /* the screen width resolution */
#define winheight       300    /* the screen height resolution */
#define level           3      /* the game level (0: easiest, 5: hardest) */
#define sensibility     1.2    /* the mouse motion sensibility */
/* Maze field */
#define complexity      32     /* the maze complexity (min: 16, max: 1024) */
#define wallheight      3.0    /* the maze wall height */
#define cellsize        12.0   /* the size of a squared cell of the maze */
/* Theme colors */
#define wallcolor       .3,.8,.1
#define floorcolor      .8,.4,.2

#endif
