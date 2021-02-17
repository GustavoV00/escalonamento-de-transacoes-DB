#include <stdlib.h>
#include <stdio.h>
#include "./functions.h"
#include "./arrumaEntrada.h"


int calculaVertices(int **inputNumeros){
    FILE *file = fopen("./teste.in", "r");
    rewind(file);
    int quantidade = quantidadeDeLinhas(file);

    int maior = 0;
    for (int i = 0; i < quantidade+1; i++){
        if (inputNumeros[i][1] > maior){
            maior = inputNumeros[i][1];
        }
    }


    fclose(file);
    return maior;
}

int **alocaMatrizDoGrafo(int **matriz, int tam){

    matriz = malloc((tam) * sizeof(int *)); // Aloca um vetor de linhas

	for (int i = 0; i < tam; i++)
		matriz[i] = malloc(tam * sizeof(int *));

	for (int i = 0; i < tam; i ++)
		for (int j = 0; j < tam; j++)
			matriz[i][j] = 0;

    return matriz;
}

int **iniciaMatriz(int tam, int **matriz){
    
    matriz = alocaMatrizDoGrafo(matriz, tam);

    for (int i = 0; i < tam; i++)
        for (int j = 0; j < tam; j++)
            matriz[i][j] = 0;

    return matriz;
}

struct Grafo *iniciaGrafo(int **inputNumeros){
    struct Grafo *grafo = malloc (sizeof (struct Grafo));
    grafo -> vertices = calculaVertices(inputNumeros);
    grafo -> arcos = 0;
    grafo -> matriz = iniciaMatriz(grafo -> vertices, grafo -> matriz); 

    return grafo;
}

void imprimeMatrizDoGrafo(int **matriz, int tam){

    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++)
            printf("%d ", matriz[i][j]);

        printf("\n");
    }
}

void liberaMatrizDoGrafo(int **matriz, int tam){
	for (int i = 0; i < tam; i++){
		free(matriz[i]);
	}
	free(matriz);
}



// Daqui para cima são as funções do grafo
// ------------------------------------------------------------------------//
// Daqui para baixo é os algoritimos de seriablidade e de visão equivalente

struct Grafo *seriabilidade(struct Grafo *grafo, int **inputNumeros, char **inputChars){

    



    return grafo;
}


