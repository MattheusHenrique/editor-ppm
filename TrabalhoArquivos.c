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

void esticarContraste(int R[MAX][MAX], int G[MAX][MAX], int B[MAX][MAX], int novaR[MAX][MAX], int novaG[MAX][MAX], int novaB[MAX][MAX], int cols, int rows){
	// Insira seu código aqui
}

void escalaCinza(int R[MAX][MAX], int G[MAX][MAX], int B[MAX][MAX], int novaR[MAX][MAX], int novaG[MAX][MAX], int novaB[MAX][MAX], int cols, int rows){
	// Insira seu código aqui
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

  scanf("%s", efeito);

	// Insira seu código aqui


  return 0;
}
