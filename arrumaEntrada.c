#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "arrumaEntrada.h"

#define COL 2

int verificaNulo(FILE *file){

	if (file == NULL)
		return -1;
	
	return 1;

}

int quantidadeDeLinhas(FILE *file){
	int quantidade = 0;
	char ch;

	while((ch = fgetc(file)) != EOF){
		if (ch == '\n')
			quantidade++;
	}

	return quantidade;
}

int **alocaMatriz(int linhas, int **input){
	input = malloc((linhas) * sizeof(int *)); // Aloca um vetor de linhas

	for (int i = 0; i < linhas; i++)
		input[i] = malloc(COL * sizeof(int *));

	for (int i = 0; i < linhas; i ++)
		for (int j = 0; j < COL; j++)
			input[i][j] = 0;

	return input;
}

char **alocaMatrizChar(int linhas, char **input){
	input = malloc((linhas) * sizeof(char *)); // Aloca um vetor de linhas

	for (int i = 0; i < linhas; i++)
		input[i] = malloc(COL * sizeof(char *));

	for (int i = 0; i < linhas; i ++)
		for (int j = 0; j < COL; j++)
			input[i][j] = 0;

	return input;
}

void imprimeMatriz(int **input, int linhas){

	for (int i = 0; i < linhas; i++){
		printf("%d -> ", i+1);
		for (int j = 0; j < COL; j++){
			printf("%d ", input[i][j]);
		}
		printf("\n");
	}

}

void imprimeMatrizChar(char **input, int linhas){

	for (int i = 0; i < linhas; i++){
		printf("%d -> ", i+1);
		for (int j = 0; j < COL; j++){
			printf("%c ", input[i][j]);
		}
		printf("\n");
	}

}

int **alocaValoresDeEntrada(int **input, int linhas, FILE *file){
	int lin = 0;
	char buffer[255];
	char aux[3];

	while(fgets(buffer, 255, file)){
		int col = 1;
		int i = 0;
		while(buffer[i] != ' '){
			aux[i] = buffer[i];
			i += 1;
		}
		input[lin][0] = atoi(aux);
		
		while(col < COL){
			if (buffer[i] != ' '){
				input[lin][col] = buffer[i] - 48;
				col += 1;
			}
			i += 1;
		}
		lin += 1;
	}

	return input;
}

char **alocaValoresDeEntradaChar(char **input, int linhas, FILE *file){
	int lin = 0;
	char buffer[255];

	while(fgets(buffer, 255, file)){
		int col = 0;
		int i = 0;
		while(col < COL){
			if (buffer[i] != ' ' && isdigit(buffer[i]) == 0){
				input[lin][col] = buffer[i];
				col += 1;
			}
			i += 1;
		}
		lin += 1;
	}

	return input;
}

int** alocaDadosDeEntradaInt(int **input){
	FILE *file = fopen("./teste.in", "r");
	
	if(verificaNulo(file) == 1){
		int linhas = quantidadeDeLinhas(file);
		linhas += 1;
		input = alocaMatriz(linhas, input);
		rewind(file);
		input = alocaValoresDeEntrada(input, linhas, file);
		//imprimeMatriz(input, linhas);

	} else
		printf("Arquivo Inexistente\n");


	fclose(file);
	return input;
}

char** alocaDadosDeEntradaChar(char **input){
	FILE *file = fopen("./teste.in", "r");
	
	if(verificaNulo(file) == 1){
		int linhas = quantidadeDeLinhas(file);
		linhas += 1;
		input = alocaMatrizChar(linhas, input);
		rewind(file);
		input = alocaValoresDeEntradaChar(input, linhas, file);
		//imprimeMatrizChar(input, linhas);


	} else
		printf("Arquivo Inexistente\n");


	fclose(file);
	return input;
}

void liberaMatriz (int **input){
	FILE *file = fopen("./teste.in", "r");
	rewind(file);

	for (int i = 0; quantidadeDeLinhas(file); i++){
		free(input[i]);
	}
	free(input);

	fclose(file);

}