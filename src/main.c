#include <stdlib.h>
#include <stdio.h>
#include "./../includes/arrumaEntrada.h"
#include "./../includes/functions.h"


int main(){
	int  **inputNumeros = NULL;
	char **inputChars = NULL;
	struct Grafo *grafo;
	char entrada[255];
	FILE *file = stdin;


	// Cria uma matriz do tipo inteiro, do arquivo de entrada do tipo int
	inputNumeros = alocaDadosDeEntradaInt(inputNumeros, file);

	// Cria uma matriz do tipo char, do arquivo de entrada do tipo char
	inputChars = alocaDadosDeEntradaChar(inputChars, file);

	// Inicia o grafo
	grafo = iniciaGrafo(inputNumeros, file);

	// Testa o algoritimo de seriabilidade
	grafo = seriabilidade(grafo, inputNumeros, inputChars, file);

	// Testa o algoritimo de visão equivalente
	grafo = visaoEquivalente(grafo, inputNumeros, inputChars, file);

	// Imprime a matriz do grafo
	imprimeMatrizDoGrafo(grafo -> matriz, grafo -> vertices);

	// Libera os dados da matriz do grafo
	liberaMatrizDoGrafo(grafo -> matriz, grafo -> vertices);

	// Libera os dados do tipo inteior
	liberaMatriz((int **) inputNumeros, file);

	// Libera os dados do tipo char
	liberaMatriz((int **) inputChars, file);
	
	fclose(file);
	return 0;
}