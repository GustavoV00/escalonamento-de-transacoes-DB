#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "./../includes/arrumaEntrada.h"

/// Define do tamanho da matriz de entrada.
#define COL 2


/**
 * Verifica se o arquivo existe
 */
int verificaNulo(FILE *file){

	// Verifica se o arquivo existe
	if (file == NULL)
		return -1;
	
	return 1;

}

void resetaFile (){
	if( fseek(stdin, 0L, SEEK_SET) ) {
    	perror("stdin");
 	   	exit(EXIT_FAILURE);
	}
}


/**
 * Abre o arquivo de entrada e cálcula a quantidade de linhas
 */
int quantidadeDeLinhas(FILE *file){
	int quantidade = 0;
	char ch;


	// Para cada quebra de linha, conta como se fosse uma linha
	while((ch = fgetc(file)) != EOF){
		if (ch == '\n')
			quantidade++;
	}

	return quantidade + 1;
}


/**
 * Aloca os dados do tipo inteiro, para o arquivo de entrada
 */
int **alocaMatriz(int linhas, int **input){
	// Aloca um vetor de linha
	input = malloc((linhas) * sizeof(int *)); 

	// Aloca as colunas da matriz
	for (int i = 0; i < linhas; i++)
		input[i] = malloc(COL * sizeof(int *));

	// Deixa os valores da matriz zerados
	for (int i = 0; i < linhas; i ++)
		for (int j = 0; j < COL; j++)
			input[i][j] = 0;

	return input;
}

/**
 * Aloca os dados do tipo char, para o arquivo de entrada.
 */
char **alocaMatrizChar(int linhas, char **input){
	input = malloc((linhas) * sizeof(char *)); // Aloca um vetor de linhas

	// Aloca as colunas da matriz

	for (int i = 0; i < linhas; i++)
		input[i] = malloc(COL * sizeof(char *));

	// Deixa os valores da matriz zerados
	for (int i = 0; i < linhas; i ++)
		for (int j = 0; j < COL; j++)
			input[i][j] = 0;

	return input;
}


/**
 * Imprime a matriz do tipo inteiro, para o arquivo de entrada
 */
void imprimeMatriz(int **input, int linhas){

	// Percode as linhas da matriz
	for (int i = 0; i < linhas; i++){
		printf("%d -> ", i);
		// Percorre as colunas da matriz
		for (int j = 0; j < COL; j++){
			printf("%d ", input[i][j]);
		}
		printf("\n");
	}

}

/**
 * Imprime a matriz do tipo char, para o arquivo de entrada
 */
void imprimeMatrizChar(char **input, int linhas){

	// Percode as linhas da matriz
	for (int i = 0; i < linhas; i++){
		printf("%d -> ", i);

		// Percorre as colunas da matriz
		for (int j = 0; j < COL; j++){
			printf("%c ", input[i][j]);
		}
		printf("\n");
	}

}


/**
 * Pega os dados de entrada do tipo inteiro e coloca na matriz do tipo int
 */
int **alocaValoresDeEntrada(int **input, int linhas, FILE *file){
	int lin = 0;
	char buffer[255];
	char aux[3];

	// Faz um loop pelo arquivo de entrada
	while(fgets(buffer, 255, file)){
		int col = 1;
		int i = 0;
		// Nega os espaços em branco e pega apenas os numeros
		while(buffer[i] != ' '){
			aux[i] = buffer[i];
			i += 1;
		}
		// Como os dados lidos por um arquivo é do tipo char 
		// o atoi serve para transformar do tipo inteiro
		input[lin][0] = atoi(aux);
		
		// Não lembro o que isso faz
		// Mas se n estou enganado, serve para quando o primeiro 
		// elemento da matriz de entrada for maior que 9
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

/**
 * Aloca os dados de entrada do arquivo na matriz do tipo char
 */
char **alocaValoresDeEntradaChar(char **input, int linhas, FILE *file){
	int lin = 0;
	char buffer[255];

	// Faz um loop pelo arquivo de entrada
	while(fgets(buffer, 255, file)){
		int col = 0;
		int i = 0;
		// Vai alocando os dados do arquivo na matriz
		while(col < COL){
			// Aloca os dados do tipo char no formato ascii na matriz
			if (buffer[i] != ' ' && isdigit(buffer[i]) == 0){
				// Coloca o dado no lugar certo
				input[lin][col] = buffer[i];
				col += 1;
			}
			i += 1;
		}
		lin += 1;
	}

	return input;
}

/**
 * Aloca os dados de entrada do tipo int, em uma matriz do tipo int
 */
int** alocaDadosDeEntradaInt(int **input, FILE *file){
	if(verificaNulo(file) == 1){
		// Conta a quantidade de linhas
		rewind(file);
		int linhas = quantidadeDeLinhas(file);

		// Aloca os dados de uma matriz do tipo char
		input = alocaMatriz(linhas, input);

		// Coloca o ponteiro no começo do arquivo
		rewind(file);

		// Aloca os dados de entrada do arquivo na matriz

		input = alocaValoresDeEntrada(input, linhas, file);

		// Imprime a matriz de dados
		imprimeMatriz(input, linhas);

	} else
		printf("Arquivo Inexistente\n");


	return input;
}

/**
 * Aloca os dados de entrada do tipo CHAR, em uma matriz do tipo char
 */
char** alocaDadosDeEntradaChar(char **input, FILE *file){
	if(verificaNulo(file) == 1){
		// Conta a quantidade de linhas
		rewind(file);
		int linhas = quantidadeDeLinhas(file);

		// Aloca os dados de uma matriz do tipo char
		input = alocaMatrizChar(linhas, input);

		// Coloca o ponteiro no começo do arquivo
		rewind(file);

		// Aloca os dados de entrada do arquivo na matriz do tipo char
		input = alocaValoresDeEntradaChar(input, linhas, file);

		// Imprime a matriz de dados
		imprimeMatrizChar(input, linhas);


	} else
		printf("Arquivo Inexistente\n");


	return input;
}


/**
 * Desaloca os dados da matriz 
 */
void liberaMatriz (int **input, FILE *file){
	// Desaloca os dados da linha
	for (int i = 0; i < quantidadeDeLinhas(file)-1; i++){
		free(input[i]);
	}

	free(input);


}