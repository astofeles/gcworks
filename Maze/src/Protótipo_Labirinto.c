/*******************************************************************

  - Nome: Protótipo_Labirinto.c
  - Por enquanto está apenas desenhando o chão.
  - A função é a desenhaChao.
  - O chão está sendo desenhado em 3 dimensões (x,y,z).
  - O chão está no plano xz e tem altura 1 no eixo y.
  - Quando rodar o código será como se tivesse vendo o de frente para o eixo xz
  - Necessário fazer uma câmera para orbitar a cima do chão
  - Qualquer dúvida perguntar.

************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GL/freeglut.h>


//Tamanho do labirinto
#define LINHAS 32
#define COLUNAS 32

//Declaração de Variáveis Globais
int posx=0, posy=1, posz=20; //Variáveis que definem a posição da câmera
int oy=0,ox=0,oz=0;         //Variáveis que definem para onde a câmera olha
int lx=0, ly=1,  lz=0;         //Variáveis que definem qual eixo estará na vertical do monitor.

//Matriz que define o labirinto
int Matriz[LINHAS][COLUNAS];
int flag = 0; //Impede a geração aleatória interminável

//Protótipos das Funções
void Inicializa();
void Display();
void Mouse(int botao, int estado, int x, int y);
void keyboard (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);
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
				Mat[i][j] = rand() % 2; //Gera números aleatórios entre 0 e 1.
	    		}
	
		}
	}

	flag = 1;
}

void desenhaChao(){

   glPushMatrix();
        //Definição dos vertices do cubo que forma o chão
	glBegin(GL_QUADS);
		glNormal3f(0.0f, -1.0f, 0.0f); //Define o vetor normal do chão.
		glVertex3f( 512,  -0.5,  512);   //Superior esquerdo
		glVertex3f(-512,  -0.5,  512);   //Inferior esquerdo
		glVertex3f(-512,  -0.5,  -512);   //Superior direito
		glVertex3f( 512,  -0.5,  -512);   //Inferior direito.
       glEnd();
   glPopMatrix();

   glutPostRedisplay();


}

void desenhaCubo(int x, int y, int i , int j){


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
			desenhaCubo(x, y, i ,j);
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
   
   // Inicializa parâmetros de rendering
    // Define a cor de fundo da janela de visualização como preta
   glClearColor(1.0, 1.0, 1.0, 1.0); 
   
   
   glMatrixMode(GL_PROJECTION);/*glMatrixMode()- define qual matriz será alterada. SEMPRE defina o tipo de apresentação 
                              (Ortogonal ou Perspectiva) na matriz PROJECTION.*/
   glLoadIdentity();//"Limpa" ou "transforma" a matriz em identidade, reduzindo possíveis erros.

   glOrtho(-150, 150, -150, 150, -150, 150); //Define a projeção como ortogonal
  
   glMatrixMode(GL_MODELVIEW);/*glMatrixMode()- define qual matriz será alterada. SEMPRE defina a câmera 
                              (Ortogonal ou Perspectiva) na matriz MODELVIEW (onde o desenho ocorrerá).*/
   glLoadIdentity(); ////"Limpa" ou "transforma" a matriz em identidade, reduzindo possíveis erros.

   gluLookAt(posx,posy,posz,ox,oy,oz,lx,ly,lz); //Define a pos da câmera, para onde olha e qual eixo está na vertical.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* "limpa" um buffer particular ou combinações de buffers, 
                                                         onde buffer é uma área de armazenamento para informações da imagem. 
                                                        Nesse caso, está "limpando os buffers para suportarem animações */
   //Chamada para Função  ou funções para desenhar o objeto/cena...
   //----------------------------------------------------------------
   
   geraMatriz(Matriz);
   glPushMatrix(); //Salva o estado atual da cena. O que for desenhado após o Push não influenciará o já representado
      desenhaLabirinto(Matriz);
      glColor3ub(0, 0, 0); //Pinta de preto o chão
      desenhaChao();
   glPopMatrix();  //Retorna ao estado anterior da cena. O que for desenhado após o Push não influenciou o já representado
   //----------------------------------------------------------------   
   
   glutSwapBuffers(); //Executa a Cena. SwapBuffers dá suporte para mais de um buffer, permitindo execução de animações sem cintilações. 
}

void Mouse(int botao, int estado, int x, int y)
{  //botão - recebe o código do botão pressionado
   //estado - recebe se está pressionado ou não
   //x, y - recebem respectivamente as posições do mouse na tela
   switch (botao)
   {
      case GLUT_LEFT_BUTTON:
      if (estado == GLUT_DOWN)
      {                  
         projecao=1;
         posx=0; posy=0; posz=0;
         ox=0,oy=0,oz=0;
         lx=0, ly=1,lz=0;
         glutPostRedisplay();
      }
      break;

      case GLUT_RIGHT_BUTTON:
      if(estado == GLUT_DOWN)
      {
         projecao=0;
         posx=0; posy=10; posz=20;
         oy=0; ox=0;  oz=0;
         lx=0, ly=1, lz=0;
         glutPostRedisplay();
      }
      break;
   }
}

void keyboard (unsigned char key, int x, int y)
{//Key - recebe o código ASCII da tecla
 //x, y - recebem as posições do mouse na tela (permite tratar os dois dispositivos)
      if (key=='d')
      {
         lz=0; ly=1; ox+=5;
      }
      else if (key=='e')
      {
         lz=0; ly=1; ox-=5;
      }
      else if (key=='c')
      {
         lz=0; ly=1; oy+=5;
      }
      else if (key=='b')    
      {
         lz=0; ly=1; oy-=5;
      }
      else if (key==27)
      {         
         exit(0);
      }
      glutPostRedisplay();
}

void TeclasEspeciais (int key, int x, int y)
{//Key - recebe o código ASCII da tecla
 //x, y - recebem respectivamente as posições mouse na tela (permite tratar os dois dispositivos)
      if (key==GLUT_KEY_RIGHT)
      {
         posx+=5; ox+=5;
      }
      else if (key==GLUT_KEY_PAGE_UP)
      {
         posy+=5; oy+=5;
      }
      else if (key==GLUT_KEY_UP)
      {
         posz-=5; oz-=5;
      }
      else if (key==GLUT_KEY_LEFT)    
      { 
         posx-=5; ox-=5;
      }
      else if (key==GLUT_KEY_PAGE_DOWN)
      {
         posz-=5; oz-=5;
      }
      else if (key==GLUT_KEY_DOWN)
      {      
         posz+=5; oz+=5;
      }
      glutPostRedisplay();
}


int main(int argc,char **argv)
{
   glutInit(&argc, argv); // Initializes glut
    
   
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); /*Define as características do espaço vetorial. 
                                                                           //  Nesse caso, permite animações (sem cintilações), cores compostas por Verm. Verde e Azul,
                                                                           //  Buffer que permite trablhar com profundidade e elimina faces escondidas.*/           
  
   glutInitWindowSize(300, 300);
   glutInitWindowPosition(10, 10);
   glutCreateWindow("Estrutura para uma Aplicação 3D");
   glutDisplayFunc(Display);
   glutMouseFunc(Mouse);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(TeclasEspeciais);
   glutMainLoop();

   return 0;
 
}
