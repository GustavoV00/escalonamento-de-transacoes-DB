#ifndef __ARRUMAENTRADA__
#define __ARRUMAENTRADA__

#include <stdio.h>
#include <stdlib.h>

/// Verifica se o arquivo existe
int verificaNulo(FILE *file);

/// Abre o arquivo de entrada e cálcula a quantidade de linhas
int quantidadeDeLinhas(FILE *file);

/// Aloca os dados do tipo inteiro, para o arquivo de entrada
int **alocaMatriz(int linhas, int **input);

/// Aloca os dados do tipo char, para o arquivo de entrada.
char **alocaMatrizChar(int linhas, char **input);

/// Imprime a matriz do tipo inteiro, para o arquivo de entrada
void imprimeMatriz(int **input, int linhas);

/// Imprime a matriz do tipo char, para o arquivo de entrada
void imprimeMatrizChar(char **input, int linhas);

/// Pega os dados de entrada do tipo inteiro e coloca na matriz do tipo int
int **alocaValoresDeEntrada(int **input, int linhas, FILE *file);

/// Aloca os dados de entrada do arquivo na matriz do tipo char
char **alocaValoresDeEntradaChar(char **input, int linhas, FILE *file);

/// Aloca os dados de entrada do tipo int, em uma matriz do tipo int
int** alocaDadosDeEntradaInt(int **input);

/// Aloca os dados de entrada do tipo CHAR, em uma matriz do tipo char
char** alocaDadosDeEntradaChar(char **input);

/// Desaloca os dados da matriz 
void liberaMatriz (int **input);



#endif