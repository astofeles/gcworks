#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <GL/freeglut.h>

/* Robotic Arm 
 *
 * Basically, the program has two major modes:
 * - MOVE: the mode that the arm can be effectivelly moved
 * - ORBIT: the mode that the camera can be rotated
 * 
 * MOUSE (click + drag + click)
 * :: in MOVE mode, moves the red ball
 * :: in ORBIT mode, orbit the model
 * TAB
 * :: in MOVE mode, changes the red ball
 * W A S D
 * :: in MOVE mode, moves the orange ball
 * O
 * :: if program is in MOVE mode, go to ORBIT mode
 * M
 * :: if profram is in ORBIT mode, go to MOVE mode
 * Q
 * :: close the program
 * R
 * :: reset to initial position
 *
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
#define WIN_TITLE "Robotic Arm - OpenGL"

/* the possibles modes in the app:
 * MOVE: moving the arm without moving the camera
 * ORBIT: moving the camerea without moving the arm */
enum {
    MOVE,
    ORBIT
} mode = MOVE;

/* the selection part of the arm. Can be set as:
 * the SHOULDER, the ELBOW, or the WRIST.
 * Note that the selected part will be noted in wine
 * color in the model.  */
enum {
    SHOULDER,
    ELBOW,
    WRIST
} selection = SHOULDER;
/* is not zero whether mouse is being clicked */
int mouseActive = 0;

/* Rotation angles (in degree) of the spheres that will 
 * be part of the robotic arm */
/* The Y1,Z1 controls the angle of the robot base (shoulder) */
int angRotZ1 = 0;
int angRotY1 = -70;
/* The Y2 controls the angle od the elbow */
int angRotY2 = 50;
int angRotZ2 = 0;
/* The Z3 is the angle of the wrist */
int angRotX3 = 0;
/* camera look variables */
int angCamZ = 0;
int angCamY = 45;

/* functions prototypes */
/* the default rendering function */
void render();
/* the mouse clicked event hendler */
void mouse(int, int, int, int);
/* the mouse motion event handler */
void motion(int, int);
/* the default keyboard event handler */
void keyboard(unsigned char, int, int);

void render() {
    int i;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH); 
    glEnable(GL_SMOOTH);
    glEnable(GL_BLEND);
    /* background */
    glClearColor(0.2, 0.2, 0.2, 0.0); // black
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
        0, 0, 0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* floor */
    glPushMatrix();
    glTranslatef(0, 0, -1);
    glScalef(5, 5, 0.5);
    glColor3ub(70, 200, 50); // green
    glutSolidCube(1);
    glPopMatrix();
    /* shoulder */
    glColor4ub(200, 120, 100, 120); // orange
    if (selection == SHOULDER) glColor3ub(200, 50, 100); // wine
    glIndexi(23);
    glRotatef(angRotZ1, 0, 0, 1);
    glRotatef(angRotY1, 0, 1, 0);
    glutSolidSphere(1.0, 16, 10);
    glColor3ub(100, 120, 200); // blue
    glTranslatef(2.5, 0, 0);
    glScalef(5, 1, 1);
    glutSolidCube(1);
    glScalef(.2, 1, 1);
    glTranslatef(2.5, 0, 0);
    /* elbow */
    glColor4ub(200, 120, 100, 0.8); // orange
    if (selection == ELBOW) glColor3ub(200, 50, 100); // wine
    glRotatef(angRotY2, 0, 1, 0);
    glRotatef(angRotZ2, 0, 0, 1);
    glutSolidSphere(1.0, 16, 10);
    glColor3ub(100, 120, 200); // blue
    glTranslatef(2.5, 0, 0);
    glScalef(5, 1, 1);
    glutSolidCube(1);
    glScalef(.2, 1, 1);
    glTranslatef(2.5, 0, 0);
    /* wrist */
    glColor3ub(200, 120, 100); // orange
    if (selection == WRIST) glColor3ub(200, 50, 100); // wine
    glRotatef(angRotX3, 1, 0, 0);
    glutSolidSphere(1.0, 16, 10);
    /* hand */
    glColor3ub(100, 120, 200); // blue
    for (i = 0; i < 4; i++) {
        glutSolidCone(0.8, 2, 4, 3);
        glRotatef(90, 1, 0, 0);
    }
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
        if (mode == MOVE) {
            if (selection == SHOULDER) {
                angRotY1 += y - y0;
                if (angRotY1 < -90) angRotY1 = -90;
                else if (angRotY1 > 0) angRotY1 = 0;
                angRotZ1 += x - x0;
                if (angRotZ1 > 360) angRotZ1 = 360 - angRotZ1;
                else if (angRotZ1 < 0) angRotZ1 += 360;
            } else if (selection == ELBOW) {
                angRotY2 += y - y0;
                angRotZ2 += x - x0;
            } else if (selection == WRIST) {
                angRotX3 += x - x0;
            }
        } else if(mode == ORBIT) {
            angCamZ += (x - x0) % 360;
            angCamY += (y - y0) % 360;
            if (angCamZ < 0) angCamZ += 360;
            if (angCamY < 0) angCamY += 360;
        }
    }
    x0 = x, y0 = y;
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y) {
    if (mode == MOVE) {
        if (tolower(key) == 'w') {
            if (selection == SHOULDER) angRotY2 -= 2;
            else angRotY1 -= 2;
        } else if (tolower(key) == 's') {
            if (selection == SHOULDER) angRotY2 += 2;
            else angRotY1 += 2;
        } else if (tolower(key) == 'a') {
            if (selection == SHOULDER) angRotX3 -= 2;
            else angRotZ1 -= 2;
        } else if (tolower(key) == 'd') {
            if (selection == SHOULDER) angRotX3 += 2;
            else angRotZ1 += 2;
        } else if (key == '\t') selection = (selection + 1) % 3;
    } 
    if (tolower(key) == 'o') mode = ORBIT;
    else if (tolower(key) == 'm') mode = MOVE;
    else if (tolower(key) == 'r') {
        // reset everything
        angRotZ1 = 0;
        angRotY1 = -70;
        angRotY2 = 50;
        angRotZ2 = 0;
        angRotX3 = 0;
        angCamZ = 0;
        angCamY = 45;
    } else if (tolower(key) == 'q') {
        glutExit();
        exit(0);
    }
    glutPostRedisplay();
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

