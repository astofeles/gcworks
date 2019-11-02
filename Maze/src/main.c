#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>
#include <ctype.h>
#include "util.h"
#include "maze.h" // mazeMapInit, initCamera
#include "graphical.h" // drawMaze, setCamera
#include "config.h"

void display();
void mouse(int, int, int, int);
void keyboard(unsigned char, int, int);

int main(int argc, char *argv[]) {
    srand(time(NULL));
    initCamera();   // default camera values
    mazeMapInit();  // create random maze

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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

    if (camera.mode == THIRD || camera.mode == FIRST) {
        gluPerspective(camera.aperture, camera.prop, camera.min, camera.max);
    } else if (camera.mode == SUP) {
        glOrtho(camera.xmin, camera.xmax, camera.ymin, camera.ymax, camera.zmin, camera.zmax);
    } 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camera.posx, camera.posy, camera.posz, camera.lx, camera.ly, camera.lz, 1, 0, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    setLights();
    drawMaze(map, complexity);
    glPopMatrix();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {

}

void keyboard(unsigned char key, int x, int y) {
    if (tolower(key) == 'w') {
        camera.posx += 0.5;
        camera.lx += 0.5;
    } else if (tolower(key) == 's') {
        camera.posx -= 0.5;
        camera.lx -= 0.5;
    } else if (tolower(key) == 'a') {
        camera.posz -= 0.5;
        camera.lz -= 0.5;
    } else if (tolower(key) == 'd') {
        camera.posz += 0.5;
        camera.lz += 0.5;
    } else if (tolower(key) == '\t') {
        camera.mode = (camera.mode + 1) % 3;
    } else if (tolower(key) == 'q') {
        glutExit();
        exit(0);
    }

    glutPostRedisplay();
}
