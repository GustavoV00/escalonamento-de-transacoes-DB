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

void imprimeConflito(int **inputNumeros, char **inputChars, int i, int k, int conflito){

    printf("Conflito%d: %d %d %c %c e %d %d %c %c\n", conflito, inputNumeros[i][0], inputNumeros[i][1], inputChars[i][0], inputChars[i][1], inputNumeros[k][0], inputNumeros[k][1], inputChars[k][0], inputChars[k][1]);
    

}


struct Grafo *seriabilidade(struct Grafo *grafo, int **inputNumeros, char **inputChars){
    FILE *file = fopen("./teste.in", "r");
    int tam = quantidadeDeLinhas(file) + 1;

    rewind(file);

    //verificarSeriabilidadeCaso1()
    //verificarSeriablidadeCaso2()
    //verificarSeriablidadeCaso3()

    int i = 0;
    while(i < tam){

        int k = i;
        while(k < tam && inputChars[k][0] != 'C'){
            // Primeiro if, Acontece uma escrita depois de uma leitura
            // 
            if((inputNumeros[i][1] != inputNumeros[k][1]) && (inputChars[i][0] == 'W' && inputChars[k][0] == 'R') && (inputChars[i][1] == inputChars[k][1])){
                int conflito = 1;
                imprimeConflito(inputNumeros, inputChars, i, k, conflito);
                //int linha = inputNumeros[k][1];
                //int coluna = inputNumeros[i][1];
                //grafo -> matriz = insereNoGrafo(grafo, linha, coluna);
            }

            if((inputNumeros[i][1] != inputNumeros[k][1]) && (inputChars[i][0] == 'R' && inputChars[k][0] == 'W') && (inputChars[i][1] == inputChars[k][1])){
                int conflito = 2;
                imprimeConflito(inputNumeros, inputChars, i, k, conflito);
            }


            if((inputNumeros[i][1] != inputNumeros[k][1]) && (inputChars[i][0] == 'W' && inputChars[k][0] == 'W') && (inputChars[i][1] == inputChars[k][1])){
                int conflito = 3;
                imprimeConflito(inputNumeros, inputChars, i, k, conflito);
            }


            k += 1;
        }
        i += 1;
    }

    fclose(file);
    return grafo;
}


