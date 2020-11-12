#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 255

void readImage(char *name, int R[MAX][MAX], int G[MAX][MAX], int B[MAX][MAX], int *cols, int *rows){
	int i, j, lixo;
	char p;

	FILE *f;
	f = fopen(name, "r");
	if(f==NULL){
		printf("Erro ao abrir a imagem \"%s\".\n", name);
		return;
	}
	fscanf(f, "%c", &p);
	fscanf(f, "%d", &lixo);
	fscanf(f, "%d %d", cols, rows);
	fscanf(f, "%d", &lixo);
	for(i=0;i<(*rows);i++){
		for(j=0;j<(*cols);j++){
			fscanf(f, "%d %d %d", &R[i][j], &G[i][j], &B[i][j]);
		}
	}

	fclose(f);
}

void writeImage(char *arqSaida, int R[MAX][MAX], int G[MAX][MAX], int B[MAX][MAX], int cols, int rows){
  	int i, j;
  	FILE *f;

  	f = fopen(arqSaida, "w");
  	fprintf(f, "P3\n%d %d\n255\n",cols, rows);

	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			fprintf(f, "%d %d %d", R[i][j], G[i][j], B[i][j]);
			if (j<cols-1){
				fprintf(f, " ");
			}
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

void esticarContraste(char *arqSaida, int R[MAX][MAX], int G[MAX][MAX], int B[MAX][MAX], int novaR[MAX][MAX], int novaG[MAX][MAX], int novaB[MAX][MAX], int cols, int rows){
	int i, j;
	int imagem;
	int maxR = 0, maxG = 0, maxB = 0;
	int minR = 0, minG = 0, minB = 0;
	
	//Calcula o minimo e o maximo e aplica a distorçao
	for(i=0; i<cols; i++){
		for(j=0; j<rows; j++){
			if(maxR < R[i][j])
				maxR = R[i][j];
			if(minR > R[i][j])
				minR = R[i][j];
			novaR[i][j] = ((R[i][j] - minR)*255)/(maxR - minR);
			
			if(maxG < G[i][j])
				maxG = G[i][j];
			if(minG > G[i][j])
				minG = G[i][j];
			novaG[i][j] = ((G[i][j] - minG)* 255)/(maxG - minG);
			
			if(maxB < B[i][j])
				maxB = B[i][j];
			if(minB > B[i][j])
				minB = B[i][j];
			novaB[i][j] = ((B[i][j] - minB)* 255)/(maxB - minB);
		}
	}	

	//Escreve as modificaçoes no arquivo de saida
	writeImage(arqSaida, novaR, novaG, novaB, cols, rows);
}


void escalaCinza(char *arqSaida, int R[MAX][MAX], int G[MAX][MAX], int B[MAX][MAX], int novaR[MAX][MAX], int novaG[MAX][MAX], int novaB[MAX][MAX], int cols, int rows){
	int i, j;
	int imagem;
	//ALGORITIMO PARA DEIXAR IMAGEM CINZA
	for(i=0; i<cols; i++){
		for(j=0; j<rows; j++){
			novaR[i][j] = (R[i][j] + G[i][j] + B[i][j])/3;
			novaG[i][j] = novaR[i][j];
			novaB[i][j] = novaR[i][j];
		}
	}
	//Escreve as modificaçoes no arquivo de saida
	writeImage(arqSaida, novaR, novaG, novaB, cols, rows);

}


//escolher a função que aplicara o efeito
void aplicaEfeito(char *arqSaida, char escolha[20], int R[MAX][MAX], int G[MAX][MAX], int B[MAX][MAX], int novaR[MAX][MAX], int novaG[MAX][MAX], int novaB[MAX][MAX], int cols, int rows){
	if(strcmp (escolha, "Cinza") == 0){
		escalaCinza(arqSaida, R, G, B, novaR, novaG, novaB, cols, rows);
	}
	else if(strcmp (escolha, "Esticar") == 0){
		esticarContraste(arqSaida, R, G, B, novaR, novaG, novaB, cols, rows);
	}

  	else{
		printf("Comando Invalido\n");

	}
	
}



int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Argumentos invalidos.\n");
    fprintf(stderr, "Usado:");
    for (int i=0; i<argc; i++) {
			fprintf(stderr, " %s", argv[i]);
    }
    fprintf(stderr, "\n");
    return 1;
  }
  char efeito[20];
  char *arqEntrada = argv[1];
  char *arqSaida = argv[2];
  int R[MAX][MAX], G[MAX][MAX], B[MAX][MAX], novaR[MAX][MAX], novaG[MAX][MAX], novaB[MAX][MAX];
  int cols, rows;
 

  readImage(arqEntrada, R, G, B, &cols, &rows);
  
  printf("Digite Cinza ou Esticar: ");
  scanf("%s", efeito);

  aplicaEfeito(arqSaida, efeito, R, G, B, novaR, novaG, novaB, cols, rows);

  

  

  return EXIT_SUCCESS;
}
