#include "graphical.h"

#ifdef _MAZE_GRAPHICAL_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>

void drawFloor() {
    glPushMatrix();
    glColor3ub(100, 100, 200);
    glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f); //Define o vetor normal do chão.
		glVertex3f( 512,  -0.5,  512);   //Superior esquerdo
		glVertex3f(-512,  -0.5,  512);   //Inferior esquerdo
		glVertex3f(-512,  -0.5,  -512);   //Superior direito
		glVertex3f( 512,  -0.5,  -512);   //Inferior direito.
   glEnd();
   glPopMatrix();
   glutPostRedisplay();
}

void drawGraph(int **graph, int n) {

}

#endif
