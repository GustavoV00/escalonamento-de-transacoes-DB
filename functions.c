#include <stdlib.h>
#include <stdio.h>
#include "./functions.h"
#include "./arrumaEntrada.h"

#define COL 2

int calculaVertices(int **inputNumeros){
    FILE *file = fopen("./teste.in", "r");
    rewind(file);
    int quantidade = quantidadeDeLinhas(file);

    int maior = 0;
    for (int i = 0; i < quantidade; i++){
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

int **insereNoGrafo(struct Grafo *grafo, int linha, int coluna){

    if(grafo -> matriz[linha][coluna] == 0){
        grafo -> matriz[linha][coluna] = 1;
        grafo -> arcos += 1;
    } 

    return grafo -> matriz;
}



// Daqui para cima são as funções do grafo
// --------------------------------------------------------------//
// Daqui para baixo é os algoritimos de seriablidade e de visão equivalente

void imprimeConflito(int **inputNumeros, char **inputChars, int i, int k, int conflito){

    printf("Conflito%d: %d %d %c %c e %d %d %c %c\n", conflito, inputNumeros[i][0], inputNumeros[i][1], inputChars[i][0], inputChars[i][1], inputNumeros[k][0], inputNumeros[k][1], inputChars[k][0], inputChars[k][1]);
    

}

struct Grafo *seriabilidade(struct Grafo *grafo, int **inputNumeros, char **inputChars){
    FILE *file = fopen("./teste.in", "r");
    int tam = quantidadeDeLinhas(file);
    rewind(file);

    int i = 0;
    while(i < tam){

        int k = i;
        while(inputNumeros[k][1] != inputNumeros[i][1] || inputChars[k][0] != 'C'){
            // Primeiro if, Acontece uma escrita depois de uma leitura
            int linha = inputNumeros[k][1] - 1;
            int coluna = inputNumeros[i][1] - 1;

            if((inputNumeros[i][1] != inputNumeros[k][1]) && (inputChars[i][0] == 'W' && inputChars[k][0] == 'R') && (inputChars[i][1] == inputChars[k][1])){
                int conflito = 1;
                imprimeConflito(inputNumeros, inputChars, i, k, conflito);
                grafo -> matriz = insereNoGrafo(grafo, linha, coluna);
            }

            if((inputNumeros[i][1] != inputNumeros[k][1]) && (inputChars[i][0] == 'R' && inputChars[k][0] == 'W') && (inputChars[i][1] == inputChars[k][1])){
                int conflito = 2;
                imprimeConflito(inputNumeros, inputChars, i, k, conflito);
                grafo -> matriz = insereNoGrafo(grafo, linha, coluna);
            }


            if((inputNumeros[i][1] != inputNumeros[k][1]) && (inputChars[i][0] == 'W' && inputChars[k][0] == 'W') && (inputChars[i][1] == inputChars[k][1])){
                int conflito = 3;
                imprimeConflito(inputNumeros, inputChars, i, k, conflito);
                grafo -> matriz = insereNoGrafo(grafo, linha, coluna);
            }

            k += 1;
        }

        i += 1;
    }

    fclose(file);
    return grafo;
}

int calculaQuantidadeDeSubMatrizes(int **inputNumeros, char **inputChars){
    FILE *file = fopen("./teste.in", "r");
    int tam = quantidadeDeLinhas(file)-1;
    int quantidade = 0;

    int i = 0;
    while(i < tam){

        if(inputChars[i][0] == 'C' && inputChars[i+1][0] == 'C')
            quantidade += 1;

        i += 1;
    }    

    fclose(file);
    return quantidade;

}


int **calculaInicioFimSubMatriz(int **inputNumeros, char **inputChars, int subMat, int **inicioFim){
    FILE *file = fopen("./teste.in", "r");
    int quantidade = quantidadeDeLinhas(file)-1;
    int fim = 0;
    int inicio = 0;

    inicioFim = alocaMatrizDoGrafo(inicioFim, subMat);

    int i = 0;
    int k = 0;
    while(i < quantidade){
        if(inputChars[i][0] == 'C' && inputChars[i+1][0] == 'C'){
            if (k == 0){
                inicio = 0;
                fim = i - 1;
                inicioFim[k][0] = inicio;
                inicioFim[k][1] = fim;
                k += 1;

            } else {
                inicio = fim + 3;
                fim = i - 1;
                inicioFim[k][0] = inicio;
                inicioFim[k][1] = fim;
                k += 1;

            }
        }

        i += 1;
    }

    return inicioFim;
}


int **subMatrizInt(int **inputNumeros, int **inicioFim, int **subInt, int i){

    int u = 0;
    for (int k = inicioFim[i][0]; k <= inicioFim[i][1]; k++){
        for (int j = 0; j < COL; j++){
            subInt[u][j] = inputNumeros[k][j];
            printf("entrei aqui: %d e %d e %d\n", k, inputNumeros[k][j], subInt[u][j]);

        }
        u += 1;
    }

    return subInt;
}

char **subMatrizChar(char **inputChars, int **inicioFim, char **subChar, int i){

    int u = 0;
    for (int k = inicioFim[i][0]; k <= inicioFim[i][1]; k++){
        for (int j = 0; j < COL; j++){
            subChar[u][j] = inputChars[k][j];
        }
        u += 1;
    }

    return subChar;
}

void desalocaSubMatriz(int **matriz, int linha){

	for (int i = 0; i < linha; i++){
		free(matriz[i]);
	}
	free(matriz);

}

int *calculaQuantosAtributosExistemNaMatriz(int **subInt, char **subChar, int linha, int *atributos){
    int quantidade = 0;
    for(int i = 0; i < linha+1; i++)
        atributos[i] = 0;


    int i = 0;
    while(i < linha){
        
        int k = 0;
        while(k < linha){
            if(subInt[i][1] == atributos[k])
                break;

            else if(subInt[i][1] != atributos[k] && atributos[k] == 0){
                atributos[k] = subInt[i][1];
                quantidade += 1;
                break;
            }
            k += 1;
        }
        i += 1;
    }

    for(int k = 0; k < linha; k++)
        printf("%d ", atributos[k]);
    printf("\n");
        
    return atributos;
}

int quantidadeDeAtributos(int *atributos){
    int quantidade = 0;
    
    for(int i = 0; atributos[i] != 0; i++)
        quantidade += 1;

    return quantidade;
}

int testaAlgoritimoNaSubMatriz(int **subInt, char **subChar, int linha){
    int flag = 0;
    int *atributos = malloc(linha+1 * sizeof(char));
    atributos = calculaQuantosAtributosExistemNaMatriz(subInt, subChar, linha, atributos);
    int qtdAtributos = quantidadeDeAtributos(atributos);

    int i = 0;
    while(i < qtdAtributos){
        printf("Aqui: %d e %d\n", subInt[i][0], subInt[i][1]);
        
        for(int k = 0; k < linha; k++){
            if(atributos[i] == subInt[k][1]){
                


            }
        }

        i += 1;
    }

    printf("\n");
    free(atributos);
    return flag;
}

struct Grafo *visaoEquivalente(struct Grafo *grafo, int **inputNumeros, char **inputChars){
    int subMat = calculaQuantidadeDeSubMatrizes(inputNumeros, inputChars);
    int flags[subMat];
    int **inicioFim;
    int **subInt = NULL;
    char **subChar = NULL;

    printf("%d\n", subMat);

    int i = 0;
    while(i < subMat){
        
        inicioFim = calculaInicioFimSubMatriz(inputNumeros, inputChars, subMat, inicioFim);
        printf("inicio:%d e Fim:%d\n", inicioFim[i][0], inicioFim[i][1]);

        int linha = inicioFim[i][1] - inicioFim[i][0];
        subInt = alocaMatriz(linha+1, subInt);
        subChar = alocaMatrizChar(linha+1, subChar);

        subInt = subMatrizInt(inputNumeros, inicioFim, subInt, i);
        subChar = subMatrizChar(inputChars, inicioFim, subChar, i);

        //imprimeMatriz(subInt, linha+1);
        printf("\n");
        //imprimeMatrizChar(subChar, linha+1);
        printf("\n");

        i += 1;

        // Cria uma flag se existe uma visao equivalente.
        flags[i] = testaAlgoritimoNaSubMatriz(subInt, subChar, linha+1);


        desalocaSubMatriz((int **) subInt, linha+1);
        desalocaSubMatriz((int **) subChar, linha+1);
    }

    return grafo;
}