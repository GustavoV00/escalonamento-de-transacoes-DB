#include <stdlib.h>
#include <stdio.h>
#include "./arrumaEntrada.h"
#include "./functions.h"



int main(){
	int  **inputNumeros = NULL;
	char **inputChars = NULL;
	struct Grafo *grafo;

	inputNumeros = alocaDadosDeEntradaInt(inputNumeros);
	printf("\n");
	inputChars = alocaDadosDeEntradaChar(inputChars);


	grafo = iniciaGrafo(inputNumeros);
	printf("\n");

	grafo = seriabilidade(grafo, inputNumeros, inputChars);
	grafo = visaoEquivalente(grafo, inputNumeros, inputChars);

	imprimeMatrizDoGrafo(grafo -> matriz, grafo -> vertices);


	liberaMatrizDoGrafo(grafo -> matriz, grafo -> vertices);
	liberaMatriz((int **) inputNumeros);
	liberaMatriz((int **) inputChars);
	return 0;
}
