#ifndef __ARRUMAENTRADA__
#define __ARRUMAENTRADA__

#include <stdio.h>
#include <stdlib.h>

int verificaNulo(FILE *file);
int quantidadeDeLinhas(FILE *file);
int **alocaMatriz(int linhas, int **input);
char **alocaMatrizChar(int linhas, char **input);
void imprimeMatriz(int **input, int linhas);
void imprimeMatrizChar(char **input, int linhas);
int **alocaValoresDeEntrada(int **input, int linhas, FILE *file);
char **alocaValoresDeEntradaChar(char **input, int linhas, FILE *file);
int** alocaDadosDeEntradaInt(int **input);
char** alocaDadosDeEntradaChar(char **input);
void liberaMatriz (int **input);



#endif