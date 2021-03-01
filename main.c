#include <stdlib.h>
#include <stdio.h>
#include "./arrumaEntrada.h"
#include "./functions.h"


int main(){
	int  **inputNumeros = NULL;
	char **inputChars = NULL;
	struct Grafo *grafo;

	// Cria uma matriz do tipo inteiro, do arquivo de entrada do tipo int
	inputNumeros = alocaDadosDeEntradaInt(inputNumeros);
	printf("\n");

	// Cria uma matriz do tipo char, do arquivo de entrada do tipo char
	inputChars = alocaDadosDeEntradaChar(inputChars);

	// Inicia o grafo
	grafo = iniciaGrafo(inputNumeros);
	printf("\n");

	// Testa o algoritimo de seriabilidade
	grafo = seriabilidade(grafo, inputNumeros, inputChars);

	// Testa o algoritimo de visão equivalente
	grafo = visaoEquivalente(grafo, inputNumeros, inputChars);

	// Imprime a matriz do grafo
	imprimeMatrizDoGrafo(grafo -> matriz, grafo -> vertices);

	// Libera os dados da matriz do grafo
	liberaMatrizDoGrafo(grafo -> matriz, grafo -> vertices);

	// Libera os dados do tipo inteior
	liberaMatriz((int **) inputNumeros);

	// Libera os dados do tipo char
	liberaMatriz((int **) inputChars);
	
	return 0;
}