/*******************************************************************

  - Nome: Prot�tipo_Labirinto.c
  - Por enquanto est� apenas desenhando o ch�o.
  - A fun��o � a desenhaChao.
  - O ch�o est� sendo desenhado em 3 dimens�es (x,y,z).
  - O ch�o est� no plano xz e tem altura 1 no eixo y.
  - A fun��o camera faz com que possa-se observar o ch�o de cima. Na fun��o das dire��es dos eixos est�o especificadas
  - O tamanho do ch�o foi reduzido para facilitar a vizuali��o e a realiza��o de testes
  - Qualquer d�vida perguntar.


************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GL/freeglut.h>

//Tamanho do labirinto
#define LINHAS 32
#define COLUNAS 32

//Declara��o de Vari�veis Globais
int projecao=0; //Vari�vel L�gica para Definir o Tipo de Proje��o (Perspectiva ou Ortogonal)
int oy=0,ox=0,oz=0;         //Vari�veis que definem para onde a c�mera olha
int lx=0, ly=1,  lz=0;         //Vari�veis que definem qual eixo estar� na vertical do monitor.

//C�mera
float now    = 10;
float radius = 10;
float camX = 10;
float camZ = 20;
float camY = 10;

 
//Matriz que define o labirinto
int Matriz[LINHAS][COLUNAS];
int flag = 0; //Impede a gera��o aleat�ria intermin�vel

//Prot�tipos das Fun��es
void Inicializa();
void Display();
void Mouse(int botao, int estado, int x, int y);
void keyboard (unsigned char key, int x, int y);
void camera(int key, int x, int y); //Move a c�mera para obervar o labirinto
void desenhaFormas(int posicao, int x, int y, int i, int j);
void desenhaLabirinto(int Mat[LINHAS][COLUNAS]);
void geraMatriz(int Mat[LINHAS][COLUNAS]);
void desenhaCubo(int x, int y, int i, int j);

//Struct para definir as coordenadas do labirinto
struct mapa{

	int x; //Coordenada x
	int y; //Coordenada y

}mapa;

void geraMatriz(int Mat[LINHAS][COLUNAS]){

	srand(time(NULL));
	if(flag == 0){
		for(int i = 0; i < LINHAS; i++){
	    		for(int j = 0; j < COLUNAS; j++){
				Mat[i][j] = rand() % 2; //Gera n�meros aleat�rios entre 0 e 1.
	    		}
	
		}
	}

	flag = 1;
}

void desenhaChao(){

   glPushMatrix();
        //Defini��o dos vertices do cubo que forma o ch�o
	glBegin(GL_QUADS);
		glNormal3f(0.0f, -1.0f, 0.0f); //Define o vetor normal do ch�o.
		glVertex3f( 20,  -0.5,   20);   //Superior esquerdo
		glVertex3f(-20,  -0.5,   20);   //Inferior esquerdo
		glVertex3f(-20,  -0.5,  -20);   //Superior direito
		glVertex3f( 20,  -0.5,  -20);   //Inferior direito.
       glEnd();
   glPopMatrix();

   glutPostRedisplay();


}

void desenhaCubo(int x, int y, int i , int j){

        glColor3ub(0,255,0);
        glPushMatrix();
		glTranslatef(x, 0, y);
		glutSolidCube(1);
	glPushMatrix();

	glutPostRedisplay();

}



void desenhaLabirinto(int Mat[LINHAS][COLUNAS]){

	int x0, x, y0, y;
	for(int i = 0; i < LINHAS; i++){
	    for(int j = 0; j < COLUNAS; j++){
		x0 = (int)i % 32;
		y0 = (int)i / 32;
		x  = (int)j % 32;
		y  = (int)j / 32;
		mapa.x = x0;
		mapa.y = y0;  
		if(Mat[i][j] == 0){
			
		}
    	     }
	}
	

	glutPostRedisplay();

}


void Display()
{
   
   glEnable(GL_DEPTH_TEST);
   
   glEnable(GL_LINE_SMOOTH);
   glEnable(GL_POLYGON_SMOOTH); 

   glEnable(GL_SMOOTH);
   glEnable(GL_BLEND);
   
   // Inicializa par�metros de rendering
    // Define a cor de fundo da janela de visualiza��o como preta
   glClearColor(1.0, 1.0, 1.0, 1.0); 
   
   
   glMatrixMode(GL_PROJECTION);/*glMatrixMode()- define qual matriz ser� alterada. SEMPRE defina o tipo de apresenta��o 
                              (Ortogonal ou Perspectiva) na matriz PROJECTION.*/
   glLoadIdentity();//"Limpa" ou "transforma" a matriz em identidade, reduzindo poss�veis erros.

   if (projecao==1)
      glOrtho(-150, 150, -150, 150, -150, 150); //Define a proje��o como ortogonal
   else
     gluPerspective(45,1,1,150); //Define a proje��o como perspectiva
   
   glMatrixMode(GL_MODELVIEW);/*glMatrixMode()- define qual matriz ser� alterada. SEMPRE defina a c�mera 
                              (Ortogonal ou Perspectiva) na matriz MODELVIEW (onde o desenho ocorrer�).*/
   glLoadIdentity(); ////"Limpa" ou "transforma" a matriz em identidade, reduzindo poss�veis erros.
   
   gluLookAt(camX, camY, camZ,ox,oy,oz,lx,ly,lz); //Define a pos da c�mera, para onde olha e qual eixo est� na vertical.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* "limpa" um buffer particular ou combina��es de buffers, 
                                                         onde buffer � uma �rea de armazenamento para informa��es da imagem. 
                                                        Nesse caso, est� "limpando os buffers para suportarem anima��es */
   //Chamada para Fun��o  ou fun��es para desenhar o objeto/cena...
   //----------------------------------------------------------------
 
   geraMatriz(Matriz);
   glPushMatrix(); //Salva o estado atual da cena. O que for desenhado ap�s o Push n�o influenciar� o j� representado
      desenhaLabirinto(Matriz);
      glColor3ub(0, 0, 0); //Pinta de preto o ch�o
      desenhaChao();
   glPopMatrix();  //Retorna ao estado anterior da cena. O que for desenhado ap�s o Push n�o influenciou o j� representado
   //----------------------------------------------------------------   
   
   glutSwapBuffers(); //Executa a Cena. SwapBuffers d� suporte para mais de um buffer, permitindo execu��o de anima��es sem cintila��es. 
}

void Mouse(int botao, int estado, int x, int y)
{  //bot�o - recebe o c�digo do bot�o pressionado
   //estado - recebe se est� pressionado ou n�o
   //x, y - recebem respectivamente as posi��es do mouse na tela
  
}

void keyboard (unsigned char key, int x, int y)
{//Key - recebe o c�digo ASCII da tecla
 //x, y - recebem as posi��es do mouse na tela (permite tratar os dois dispositivos)
     
      glutPostRedisplay();

}

void camera(int key, int x, int y)
{//Key - recebe o c�digo ASCII da tecla
 //x, y - recebem respectivamente as posi��es mouse na tela (permite tratar os dois dispositivos)

      float cameraSpeed = 0.5;
      if (key==GLUT_KEY_RIGHT)
      {
         camZ-= cameraSpeed; oz-=cameraSpeed; //Afasta a c�mera no eixo z
      }
      else if (key==GLUT_KEY_PAGE_UP)
      {
         
      }
      else if (key==GLUT_KEY_UP)
      {
	 camY+=cameraSpeed; oy+=cameraSpeed; //Afasta a c�mera no eixo y
         
      }
      else if (key==GLUT_KEY_LEFT)    
      { 

          camZ+= cameraSpeed; oz+=cameraSpeed; //Aproxima a c�mera no eixo

      }
      else if (key==GLUT_KEY_PAGE_DOWN)
      {
        

      }
      else if (key==GLUT_KEY_DOWN)
      {
	camY-=cameraSpeed; oy-=cameraSpeed; //Aproxima a c�mera no eixo y
   
      } 


      glutPostRedisplay();


}


int main(int argc,char **argv)
{
   glutInit(&argc, argv); // Initializes glut
    
   
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); /*Define as caracter�sticas do espa�o vetorial. 
                                                                           //  Nesse caso, permite anima��es (sem cintila��es), cores compostas por Verm. Verde e Azul,
                                                                           //  Buffer que permite trablhar com profundidade e elimina faces escondidas.*/           
  
   glutInitWindowSize(300, 300);
   glutInitWindowPosition(10, 10);
   glutCreateWindow("Prot�tipo Labirinto - 3D");
   glutDisplayFunc(Display);
   glutMouseFunc(Mouse);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(camera);
   glutMainLoop();

   return 0;
 
}
