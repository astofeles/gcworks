#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>    // gl*, glut*, glu*
#include <ctype.h>
#include <math.h>
#include "util.h"       // ERROR
#include "maze.h"       // mazeMapInit, initCamera, initPlayer, map
#include "graphical.h"  // drawMaze, setCamera
#include "config.h"     // background, complexity, thename

// functions prototypes
void display();
void mouse(int, int, int, int);
void motion(int, int);
void special(int, int, int);
void keyboard(unsigned char, int, int);

// global variables
int firstmov = 1;

int main(int argc, char *argv[]) {
    srand(time(NULL));
    initPlayer();   // default player values
    initCamera();   // default camera values
    mazeMapInit();  // create random maze

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInit(&argc, argv);
    glutInitWindowSize(winwidth, winheight);
    glutInitWindowPosition(10, 10);
    glutCreateWindow(thename);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
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
    firstmov = 1;
    glutPostRedisplay();
}

void motion(int x, int y) {
    static int x0 = 0, y0 = 0;
    int dx, dy;
    if (!firstmov) {
        dx = x - x0;
        dy = y - y0;
        if (camera.mode == THIRD) {
            camera.angle += dx;
        } else if (camera.mode == FIRST) {
            camera.angle -= dx;
        }
    }
    x0 = x;
    y0 = y;
    firstmov = 0;
    glutPostRedisplay();
}

void special(int key, int x, int y)  {
    if (key == GLUT_KEY_UP)
        keyboard('w', x, y);
    else if (key == GLUT_KEY_DOWN)
        keyboard('s', x, y);
    else if (key == GLUT_KEY_LEFT)
        keyboard('a', x, y);
    else if (GLUT_KEY_RIGHT)
        keyboard('d', x, y);
    else
        ERROR("Command not found");
}

void keyboard(unsigned char key, int x, int y) {
    float xi, zi;
    xi = player.x;
    zi = player.z;
    if (tolower(key) == 'w') {
        // superior view
        if (camera.mode == SUP) {
            xi += player.speed;
        // third person view
        } else if (camera.mode == THIRD) {
            xi += player.speed * cosf(camera.angle * M_PI / 180);
            zi += player.speed * sinf(camera.angle * M_PI / 180);
        } else if (camera.mode == FIRST){
            // TODO: resolve first person
        } else {
            ERROR("Invalid camera mode");
        }
    } else if (tolower(key) == 's') {
        // superior view
        if (camera.mode == SUP) {
            xi -= player.speed;
        // third person view
        } else if (camera.mode == THIRD) {
            xi -= player.speed * cosf(camera.angle * M_PI / 180);
            zi -= player.speed * sinf(camera.angle * M_PI / 180);
        } else if (camera.mode == FIRST){
            // TODO: resolve first person
        } else {
            ERROR("Invalid camera mode");
        }
    } else if (tolower(key) == 'a') {
        // superior view
        if (camera.mode == SUP) {
            zi -= player.speed;
        } else if (camera.mode == THIRD) {
            xi += player.speed * sinf(camera.angle * M_PI / 180);
            zi -= player.speed * cosf(camera.angle * M_PI / 180);
        } else if (camera.mode == FIRST){
            // TODO: resolve first person
        } else {
            ERROR("Invalid camera mode");
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
            ERROR("Invalid camera mode");
        }
    } else if (tolower(key) == '\t') {
        camera.mode = (camera.mode + 1) % 3;
    } else if (tolower(key) == 'q') {
        glutExit();
        exit(0);
    } else {
        ERROR("Command not found");
    }

    if (!colide(xi, player.z)) player.x = xi;
    if (!colide(player.x, zi)) player.z = zi;

    glutPostRedisplay();
}
