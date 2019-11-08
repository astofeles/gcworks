#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>
#include <ctype.h>
#include <math.h>
#include "util.h"
#include "maze.h"       // mazeMapInit, initCamera, map
#include "graphical.h"  // drawMaze, setCamera
#include "config.h"     // background, complexity

#define ERROR() (error(__FILE__,__LINE__))

void display();
void mouse(int, int, int, int);
void motion(int, int);
void keyboard(unsigned char, int, int);

int main(int argc, char *argv[]) {
    srand(time(NULL));
    initPlayer();   // default player values
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
    glutPassiveMotionFunc(motion);
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

    setCamera();

    glPushMatrix();
    setLights();
    drawMaze(map, complexity);
    drawPlayer();
    glPopMatrix();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    glutPostRedisplay();
}

void motion(int x, int y) {
    static int x0 = 0, y0 = 0;
    int dx, dy;
    dx = x - x0;
    dy = y - y0;
    if (camera.mode == THIRD) {
        camera.angle += dx;
    } else if (camera.mode == FIRST) {
        camera.angle -= dx;
    }
    x0 = x;
    y0 = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    int col;
    float xi, zi;
    xi = player.x;
    zi = player.z;
    if (tolower(key) == 'w') {
        if (camera.mode == SUP) {
            xi += player.speed;
        } else if (camera.mode == THIRD) {
            xi += player.speed * cosf(camera.angle * M_PI / 180);
            zi += player.speed * sinf(camera.angle * M_PI / 180);
        } else if (camera.mode == FIRST){
            // TODO: resolve first person
        } else {
            ERROR();
        }
    } else if (tolower(key) == 's') {
        if (camera.mode == SUP) {
            xi -= player.speed;
        } else if (camera.mode == THIRD) {
            xi -= player.speed * cosf(camera.angle * M_PI / 180);
            zi -= player.speed * sinf(camera.angle * M_PI / 180);
        } else if (camera.mode == FIRST){
            // TODO: resolve first person
        } else {
            ERROR();
        }
    } else if (tolower(key) == 'a') {
        if (camera.mode == SUP) {
            zi -= player.speed;
        } else if (camera.mode == THIRD) {
            xi += player.speed * sinf(camera.angle * M_PI / 180);
            zi -= player.speed * cosf(camera.angle * M_PI / 180);
        } else if (camera.mode == FIRST){
            // TODO: resolve first person
        } else {
            ERROR();
        }
    } else if (tolower(key) == 'd') {
        if (camera.mode == SUP) {
            zi += player.speed;
        } else if (camera.mode == THIRD) {
            xi -= player.speed * sinf(camera.angle * M_PI / 180);
            zi += player.speed * cosf(camera.angle * M_PI / 180);
        } else if (camera.mode == FIRST){
            // TODO: resolve first person
        } else {
            ERROR();
        }
    } else if (tolower(key) == '\t') {
        camera.mode = (camera.mode + 1) % 3;
    } else if (tolower(key) == 'q') {
        glutExit();
        exit(0);
    } else {
        ERROR();
    }

    if (!colide(xi, player.z)) {
        player.x = xi;
    }
    if (!colide(player.x, zi)) {
        player.z = zi;
    }

    glutPostRedisplay();
}
