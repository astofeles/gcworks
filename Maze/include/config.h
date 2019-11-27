#ifndef _MAZE_CONFIG_H
#define _MAZE_CONFIG_H

/* Game playing */
#define thename         "A-maze"    /* the game name */
#define winwidth        800     /* the screen width resolution */
#define winheight       800     /* the screen height resolution */
#define difficulty      3       /* the game level (0: easiest, 5: hardest) */
#define sensibility     1.2     /* the mouse motion sensibility */
/* Maze field */
#define maxcomplexity   128      /* the maze complexity (min: 16, max: 1024) */
#define wallheight      0.5     /* the maze wall height */
/* ball characteristics */
#define ballradius      0.18    /* the radius os the ball */
#define hrings          10      /* the number of horizontal rings */
#define vrings          10      /* the number of vertical rings */
#define minspeed        0.1     /* the minimum speed */
#define maxspeed        0.8     /* the maximum speed */
/* camera defaults */
#define camheight       8      /* the default camera height */
#define mincamheight    4
#define maxcamheight    20
/* Theme colors */
#define wallcolor       .6,.6,.5
#define floorcolor      .1,.1,.1
#define background      .3,.5,.5
#define playercolor     .8,.6,.1
#define fredcolor       .9,.1,.1
#define startcolor      .3,.3,.1
#define endcolor        .4,.1,.2

#endif
