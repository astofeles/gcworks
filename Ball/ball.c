#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <GL/freeglut.h>

/* Bouncing Ball
 * 
 * MOUSE (click + drag + click)
 * :: obit the model
 * TAB
 * :: look at ball / floor
 * SPACE
 * :: pause simulation
 */

/* general configuration of the main window */
/* the window heigth */
#define WIN_HEIGTH 360
/* the window width */
#define WIN_WIDTH 480
/* the 'x' window position */
#define WIN_POSX 100
/* the 'y' window postition */
#define WIN_POSY 100
/* the window title */
#define WIN_TITLE "Bouncing Ball - OpenGL"

/* the ball can be moving UP or DOWN */
enum {
    UP,
    DOWN
} direction;
/* where the camera has to look at */
enum {
    BALL,
    FLOOR,
} lookat = BALL;
/* is not zero whether mouse is being clicked */
int mouseActive = 0;
/* game is paused */
int paused = 0;
/* the ball y position */
float ballZ = 8.0f;
/* the ball radius */
float radius = 0.5f;

/* camera look variables */
int angCamZ = 0;
int angCamY = 45;

/* functions prototypes */
/* the default rendering function */
void render();
/* the mouse clicked event hendler */
void mouse(int, int, int, int);
/* the keyboard event handler */
void keyboard(unsigned char, int, int);
/* the mouse motion event handler */
void motion(int, int);
/* update the position os the ball */
void update();
/* creates a delay */
void delay(int);

void render() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH); 
    glEnable(GL_SMOOTH);
    glEnable(GL_BLEND);
    /* background */
    glClearColor(0.1, 0.6, 0.5, 0.0); // black
    /* other configs */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)WIN_WIDTH/(float)WIN_HEIGTH, 1, 150);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        20 * sinf(angCamZ * M_PI / 180), 
        20 * cosf(angCamZ * M_PI / 180), 
        20 * sinf(angCamY * M_PI / 180), 
        0, 0, (lookat == BALL) ? ballZ : 0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* floor */
    glPushMatrix();
    glTranslatef(0, 0, -1);
    glScalef(5, 5, 0.5);
    glColor3ub(70, 200, 50); // green
    glutSolidCube(1);
    glPopMatrix();
    /* ball */
    glPushMatrix();
    glTranslatef(0, 0, ballZ);
    glColor3f(0.6, 0.1, 0.6);
    glutSolidSphere(2 * radius, 16, 10);
    glColor3f(0.8, 0.7, 0.1);
    glPopMatrix();
    /* swap buffers */
    if (!paused) update();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        mouseActive = !mouseActive;
    glutPostRedisplay();
}

void motion(int x, int y) {
    static int x0 = 0, y0 = 0;
    if (mouseActive) {
        angCamZ += (x - x0) % 360;
        angCamY += (y - y0) % 360;
        if (angCamZ < 0) angCamZ += 360;
        if (angCamY < 0) angCamY += 360;
    }
    x0 = x, y0 = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') paused = !paused;
    else if (key == '\t') lookat = (lookat + 1) % 2;
    else if (tolower(key) == 'q') {
        glutExit();
        exit(0);
    }
    glutPostRedisplay();
}

void update() {
    if (direction == DOWN) {
        ballZ -= 0.5;
    } else if (direction == UP) {
        ballZ += 0.5;
    }
    if (direction == DOWN && ballZ <= radius) {
        direction = UP;
    } else if (direction == UP && ballZ >= 10) {
        direction = DOWN;
    }
    if (!mouseActive) {
        angCamZ += 2;
    }
    delay(40000);
    glutPostRedisplay();
}

void delay(int tm) {
    clock_t start = clock();
    clock_t end = start + tm;
    while (clock() < end) ;
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGTH);
    glutInitWindowPosition(WIN_POSX, WIN_POSY);
    glutCreateWindow(WIN_TITLE);
    glutDisplayFunc(render);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(motion);
    glutMainLoop();

    return 0;
}

