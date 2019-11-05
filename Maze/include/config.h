#ifndef _MAZE_CONFIG_H
#define _MAZE_CONFIG_H

/* Game playing */
#define winwidth        800     /* the screen width resolution */
#define winheight       800     /* the screen height resolution */
#define difficulty      3       /* the game level (0: easiest, 5: hardest) */
#define sensibility     1.2     /* the mouse motion sensibility */
/* Maze field */
#define complexity      32      /* the maze complexity (min: 16, max: 1024) */
#define wallheight      1.0     /* the maze wall height */
#define cellsize        12.0    /* the size of a squared cell of the maze */
#define ballradius      0.25    /* the radius os the ball */
/* Theme colors */
#define wallcolor       .6,.6,.5
#define floorcolor      .4,.4,.3
#define background      .3,.5,.5
#define playercolor     .8,.6,.1

#endif
