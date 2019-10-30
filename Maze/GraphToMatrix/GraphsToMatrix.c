#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	//Variaveis
	int Graph_Adjacency[25][25];
	int Labirynth_Matrix[11][11];
	int Adjacency_Aux[25][5];
	int Line_Aux1, Column_Aux1, Line_Aux2, Column_Aux2;
	int Graph_Node_Count;
	//Construcao  de exemplo de Matriz de Adjacencia
/*	for(Line_Aux1 = 0; Line_Aux1 < 25; Line_Aux1++){
		for(Column_Aux1 = 0; Column_Aux1 < 25; Column_Aux1++){
			Graph_Adjacency[Line_Aux1][Column_Aux1] = 0;
		}
	}*/
	//Passo 1
	for(Line_Aux1 = 0; Line_Aux1 < 25; Line_Aux1++){
		for(Column_Aux1 = 0; Column_Aux1 < 25; Column_Aux1++){
			Adjacency_Aux[Line_Aux1][Column_Aux1]=-1;
		}
	}
	//Passo 2
	for(Line_Aux1 = 0; Line_Aux1 < 25; Line_Aux1++){
		Adjacency_Aux[Line_Aux1][0] = Line_Aux1;
		Column_Aux2=1;
		for(Column_Aux1 = Line_Aux1; Column_Aux1 < 25; Column_Aux1++){
			if(Graph_Adjacency[Line_Aux1][Column_Aux1] == 1){
				Adjacency_Aux[Line_Aux1][Column_Aux2]=Column_Aux1;
				Column_Aux2++;
			}
		}
	}
	//Passo 3
	for(Line_Aux1 = 0; Line_Aux1 < 11; Line_Aux1++){
		for(Column_Aux1 = 0; Column_Aux1 < 11; Column_Aux1++){
			if( (Line_Aux1%2) == 1 && (Column_Aux1%2) == 1){
				Labirynth_Matrix[Line_Aux1][Column_Aux1]=0;
			}
			else{
				Labirynth_Matrix[Line_Aux1][Column_Aux1]=1;
			}
		}
	}
	//Passo 4
	for(Line_Aux1 = 0; Line_Aux1 < 25; Line_Aux1++){
		Graph_Node_Count = 0;
		Line_Aux2 = 1;
		Column_Aux2 = 1;
		while(Graph_Node_Count < Line_Aux1){
			Graph_Node_Count++;
			if(Column_Aux2 < 9){
				Column_Aux2 = Column_Aux2 + 2;
			}
			else{
				Column_Aux2 = 1;
				Line_Aux2 = Line_Aux2 + 2;
			}
		}
		for(Column_Aux1 = 1; Column_Aux1 < 5 && Column_Aux1 > -1; Column_Aux1++){
			if( (Adjacency_Aux[Line_Aux1][0] - Adjacency_Aux[Line_Aux1][Column_Aux1]) == -1 ){
				Labirynth_Matrix[Line_Aux2][Column_Aux2 + 1]=0;
			}
			if( (Adjacency_Aux[Line_Aux1][0] - Adjacency_Aux[Line_Aux1][Column_Aux1]) == -5 ){
				Labirynth_Matrix[Line_Aux2 + 1][Column_Aux2]=0;
			}
		}
	}
	//Printfs para demonstrar as diversas matrizes, incluindo a do labirinto que é construída corretamente.
/*	for(Line_Aux1 = 0; Line_Aux1 < 11; Line_Aux1++){
		for(Column_Aux1 = 0; Column_Aux1 < 11; Column_Aux1++){
			printf("%d ", Labirynth_Matrix[Line_Aux1][Column_Aux1]);
		}
		printf("\n");
	}
	for(Line_Aux1 = 0; Line_Aux1 < 25; Line_Aux1++){
		for(Column_Aux1 = 0; Column_Aux1 < 5; Column_Aux1++){
			printf("%d ", Adjacency_Aux[Line_Aux1][Column_Aux1]);
		}
		printf("\n");
	}
	for(Line_Aux1 = 0; Line_Aux1 < 25; Line_Aux1++){
		for(Column_Aux1 = 0; Column_Aux1 < 25; Column_Aux1++){
			printf("%d ", Graph_Adjacency[Line_Aux1][Column_Aux1]);
		}
		printf("\n");
	}*/
	return 0;
}
