#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>
#include "util.h"
#include "maze.h" // mazeMapInit, initCamera
#include "graphical.h" // drawMaze, setCamera
#include "config.h"

void display();
void mouse(int, int, int, int);
void keyboard(unsigned char, int, int);

int main(int argc, char *argv[]) {
    srand(time(NULL));
    printf("DBG: Antes initCamera()\n");
    initCamera();   // default camera values
    printf("DBG: Antes mazeMapInit()\n");
    mazeMapInit();  // create random maze
    printf("DBG: Depois mazeMapInit()\n");

    glutInit(&argc, argv);
    glutInitWindowSize(winwidth, winheight);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("A Maze");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}

void display() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH); 
    glEnable(GL_SMOOTH);
    glEnable(GL_BLEND);
    glClearColor(background, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (camera.mode == PERSP) {
        gluPerspective(camera.aperture, camera.prop, camera.min, camera.max);
    } else {
        glOrtho(camera.xmin, camera.xmax, camera.ymin, camera.ymax, camera.zmin, camera.zmax);
    } 

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    gluLookAt(camera.posx, camera.posy, camera.posz, camera.lx, camera.ly, camera.lz, 1, 1, 0);

    glPushMatrix();
    printf("Antes de 'drawMaze'\n");
    drawMaze(map, complexity);
    printf("Depois de 'drawMaze'\n");
    glPopMatrix();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {

}

void keyboard(unsigned char key, int x, int y) {

}
