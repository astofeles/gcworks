#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>
#include <ctype.h>
#include <string.h>
#include "util.h"
#include "maze.h"      // mazeMapInit, initCamera
#include "graphical.h" // drawMaze, setCamera
#include "config.h"

void display();
void mouse(int, int, int, int);
void keyboard(unsigned char, int, int);
void messages(int);

int option = 1;

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

<<<<<<< HEAD
    glPushMatrix();
        setLights();
        drawMaze(map, complexity);
        drawPlayer();
    glPopMatrix();
=======
    messages(option);
>>>>>>> ab65c674553184386a5062e119bcce89a13fe58d

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {

}

void keyboard(unsigned char key, int x, int y) {
<<<<<<< HEAD
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
        }     } 
    if (tolower(key) == 's') {
        // superior view
        if (camera.mode == SUP) {
            xi -= player.speed;
        // third person view
        } else if (camera.mode == THIRD) {
            xi -= player.speed * cosf(camera.angle * M_PI / 180);
            zi -= player.speed * sinf(camera.angle * M_PI / 180);
        } else if (camera.mode == FIRST){
            // TODO: resolve first person
        }     } 
    if (tolower(key) == 'a') {
        // superior view
        if (camera.mode == SUP) {
            zi -= player.speed;
        } else if (camera.mode == THIRD) {
            xi += player.speed * sinf(camera.angle * M_PI / 180);
            zi -= player.speed * cosf(camera.angle * M_PI / 180);
        } else if (camera.mode == FIRST){
            // TODO: resolve first person
        }     } 
    if (tolower(key) == 'd') {
        if (camera.mode == SUP) {
            zi += player.speed;
        } else if (camera.mode == THIRD) {
            xi -= player.speed * sinf(camera.angle * M_PI / 180);
            zi += player.speed * cosf(camera.angle * M_PI / 180);
        } else if (camera.mode == FIRST){
            // TODO: resolve first person
        } 
=======
    int cell;
    cell = getMapCell(player.x, player.z);
    printf("DBG: x,z = %.2f, %.2f\n", player.x, player.z);
    printf("DBG: %c %c %c %c\n", (cell&SOUTH)?'S':' ', (cell&EAST)?'E':' ', (cell&NORTH)?'N':' ', (cell&WEST)?'W':' ');
    if (tolower(key) == 'w' && option != 2 && option != 1) {
        if (!(cell&EAST)) {
            camera.posx += 1;
            player.x += 1;
        }
    } else if (tolower(key) == 's' && option != 2 && option != 1) {
        if (!(cell&WEST)) {
            camera.posx -= 1;
            player.x -= 1;
        }
    } else if (tolower(key) == 'a' && option != 2 && option != 1) {
        if (!(cell&SOUTH)) {
            camera.posz -= 1;
            player.z -= 1;
        }
    } else if (tolower(key) == 'd' && option != 2 && option != 1) {
        if (!(cell&NORTH)) {
            camera.posz += 1;
            player.z += 1;
        }
>>>>>>> ab65c674553184386a5062e119bcce89a13fe58d
    } else if (tolower(key) == '\t') {
        camera.mode = (camera.mode + 1) % 3;
    } else if (tolower(key) == 'q') {
        glutExit();
        exit(0);
<<<<<<< HEAD
    }
=======
    }else if(key == ' '){
	option = 0;

    }else if(tolower(key) == 'p'){
	option = 2;
>>>>>>> ab65c674553184386a5062e119bcce89a13fe58d

    }

    glutPostRedisplay();
}

void text(float s, float d, float f, char *string){

	//Coloca o texto na janela utilizando-se das coordenadas x ,y, z
	glRasterPos3f(s,d,f);
	int len=strlen(string);
	for(int i = 0; i < len; i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	
	}	

	glutPostRedisplay();

}


void messages(int flag){

	if(flag == 0){
		glPushMatrix();
      		 setLights();
     	 	 drawMaze(map, complexity);
      		 drawPlayer();
    		glPopMatrix();
		
      	}else if(flag == 1){
	       glPushMatrix();	
		 glColor3ub(255,255,255);
		 text( 5, 0, 0,  "Pressione a barra da iniciar");
		 text( 4, 0, 0,  "Controles:        ");
	 	 text( 3, 0, 0,  "'w' - move para cima");
	 	 text( 2, 0, 0,  "'s' - move para tras");
	 	 text( 1, 0, 0,  "'a' - move para esquerda");
	 	 text( 0, 0, 0,  "'d' - move para direita");
		 text(-1, 0, 0,  "'q' - Sair do jogo");
 	      glPopMatrix();

	}else if(flag == 2){
		glPushMatrix();
		 glColor3ub(255,255,255);
		 text( 5, 0, 0,  "Pause");
	 	 text( 4, 0, 0,  "Controles:");
		 text( 3, 0, 0,  "espaco - para retornar ao jogo");
	 	 text( 2, 0, 0,  "'w' - move para cima");
	 	 text( 1, 0, 0,  "'s' - move para tras");
	 	 text( 0, 0, 0,  "'a' - move para esquerda");
	 	 text(-1, 0, 0,  "'d' - move para direita");
		 text(-2, 0, 0,  "'q' - Sair do jogo");
		glPopMatrix();		  

	}

}



