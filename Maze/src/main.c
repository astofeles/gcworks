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

}

void keyboard(unsigned char key, int x, int y) {
    int cell;
    cell = getMapCell(player.x, player.z);
    printf("DBG: x,z = %.2f, %.2f\n", player.x, player.z);
    printf("DBG: %c %c %c %c\n", (cell&SOUTH)?'S':' ', (cell&EAST)?'E':' ', (cell&NORTH)?'N':' ', (cell&WEST)?'W':' ');
    if (tolower(key) == 'w') {
        if (!(cell&EAST)) {
            camera.posx += 1;
            player.x += 1;
        }
    } else if (tolower(key) == 's') {
        if (!(cell&WEST)) {
            camera.posx -= 1;
            player.x -= 1;
        }
    } else if (tolower(key) == 'a') {
        if (!(cell&SOUTH)) {
            camera.posz -= 1;
            player.z -= 1;
        }
    } else if (tolower(key) == 'd') {
        if (!(cell&NORTH)) {
            camera.posz += 1;
            player.z += 1;
        }
    } else if (tolower(key) == '\t') {
        camera.mode = (camera.mode + 1) % 3;
    } else if (tolower(key) == 'q') {
        glutExit();
        exit(0);
    }

    glutPostRedisplay();
}
