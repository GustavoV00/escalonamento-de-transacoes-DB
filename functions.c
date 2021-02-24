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
            //printf("entrei aqui: %d e %d e %d\n", k, inputNumeros[k][j], subInt[u][j]);

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

// Esse atributos é o tes
int *calculaQuantosTTExistemNaMatriz(int **subInt, char **subChar, int linha, int *atributos){
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

char *calculaQuantosAtributosExistemNaMatriz(int **subInt, char **subChar, int linha, char *atributos){
    char quantidade = 0;
    for(int i = 0; i < linha+1; i++)
        atributos[i] = '0';


    int i = 0;
    while(i < linha){
        
        int k = 0;
        while(k < linha){
            if(subChar[i][1] == atributos[k])
                break;

            else if(subChar[i][1] != atributos[k] && atributos[k] == '0'){
                atributos[k] = subChar[i][1];
                quantidade += 1;
                break;
            }
            k += 1;
        }
        i += 1;
    }

    for(int k = 0; k < linha; k++)
        printf("%c ", atributos[k]);
    printf("\n\n");
        
    return atributos;
}

int quantidadeDeTes(int *atributos){
    int quantidade = 0;
    
    for(int i = 0; atributos[i] != 0; i++)
        quantidade += 1;

    return quantidade;
}

int quantidadeDeAtributos(char *atributos){
    int quantidade = 0;
    
    for(int i = 0; atributos[i] != '0'; i++)
        quantidade += 1;

    return quantidade;
}

int **copiaSubInt(int **subInt, int **subIntAux, int linha){

    for (int i = 0; i < linha; i++)
        for(int j = 0; j < COL; j++)
            subIntAux[i][j] = subInt[i][j];

    return subIntAux;
}

char **copiaSubChar(char **subChar, char **subCharAux, int linha){

    for (int i = 0; i < linha; i++)
        for(int j = 0; j < COL; j++)
            subCharAux[i][j] = subChar[i][j];

    return subCharAux;
}

// Leitura inicial
int verificaCondicaoUm(int **subInt, int **subIntAux, char **subChar, char **subCharAux, int linha, char *atributos, int qtdAtributos, int *z){
    int flag = 1;
    int auxT1, auxT2;

    int i = 0;
    while(i < qtdAtributos){
        //printf("D:%d e %d e %c\n", i, qtdAtributos, atributos[i]);
        for(int k = 0; k < linha; k++){
            if(subChar[k][0] == 'R' && subChar[k][1] == atributos[i]){
                //printf("test1:%d\n", k);
                auxT1 = subInt[k][1];
                break;
            } 
        }

        for(int k = 0; k < linha; k++){
            if(subCharAux[k][0] == 'R' && subCharAux[k][1] == atributos[i]){

                //printf("test2:%d\n", k);
                auxT2 = subIntAux[k][1];
                break;
            }
        }
        
        z[i] = (auxT1 == auxT2) ? 1 : 0;
        printf("Here:%d e %d = %d\n", auxT1, auxT2, z[i]);


        i += 1;
    }

    for(int i = 0; i < qtdAtributos; i++){
        if(z[i] == 0)
            flag = 0;
    }

    return flag;
}

// Atualização na leitura
int verificaCondicaoDois(int **subInt, int **subIntAux, char **subChar, char **subCharAux, int linha, char *atributos, int qtdAtributos, int *x){
    int flag = 1;


    return flag;
}

// Escrita no final
int verificaCondicaoTres(int **subInt, int **subIntAux, char **subChar, char **subCharAux, int linha, char *atributos, int qtdAtributos, int *c){
    int flag = 1;
    int auxT1, auxT2;

    int i = 0;
    while(i < qtdAtributos){
        //printf("D:%d e %d e %c\n", i, qtdAtributos, atributos[i]);
        for(int k = 0; k < linha; k++){
            if(subChar[k][0] == 'W' && subChar[k][1] == atributos[i]){
                auxT1 = subInt[k][1];
            } 
        }

        for(int k = 0; k < linha; k++){
            if(subCharAux[k][0] == 'W' && subCharAux[k][1] == atributos[i]){
                auxT2 = subIntAux[k][1];

            }
        }
        
        c[i] = (auxT1 == auxT2) ? 1 : 0;
        //printf("Here:%d e %d = %d\n", auxT1, auxT2, c[i]);


        i += 1;
    }
    
    for(int i = 0; i < qtdAtributos; i++){
        if(c[i] == 0)
            flag = 0;
    }
    printf("\n");
    return flag;
}

int testaAlgoritimoNaSubMatriz(int **subInt, char **subChar, int linha){
    int flag = 0, auxInt[1];
    int **subIntAux = NULL;
    char **subCharAux = NULL;

    subIntAux = alocaMatriz(linha, subIntAux);
    subCharAux = alocaMatrizChar(linha, subCharAux);

    char auxChar[2];
    int *tes = malloc(linha+1 * sizeof(int));
    char *atributos = malloc(linha+1 * sizeof(char));

    tes = calculaQuantosTTExistemNaMatriz(subInt, subChar, linha, tes);
    atributos = calculaQuantosAtributosExistemNaMatriz(subInt, subChar, linha, atributos);

    int qtdtes = quantidadeDeTes(tes);
    int qtdAtributos = quantidadeDeAtributos(atributos);
    
    int *z = malloc(qtdtes * sizeof(int));
    int *x = malloc(qtdtes * sizeof(int));
    int *c = malloc(qtdtes * sizeof(int));

    int i = 0;
    while(i < qtdtes){
        subIntAux = copiaSubInt(subInt, subIntAux, linha);
        subCharAux = copiaSubChar(subChar, subCharAux, linha);

        int h = 0;
        for(int k = 0; k < linha; k++){
            if(tes[i] == subInt[k][1]){
                int a = k;
                while(a > h){
                    auxInt[0] = subIntAux[a-1][0];
                    auxInt[1] = subIntAux[a-1][1];
                    subIntAux[a-1][0] = subIntAux[a][0];
                    subIntAux[a-1][1] = subIntAux[a][1];
                    subIntAux[a][0] = auxInt[0];
                    subIntAux[a][1] = auxInt[1];

                    auxChar[0] = subCharAux[a-1][0];
                    auxChar[1] = subCharAux[a-1][1];
                    subCharAux[a-1][0] = subCharAux[a][0];
                    subCharAux[a-1][1] = subCharAux[a][1];
                    subCharAux[a][0] = auxChar[0];
                    subCharAux[a][1] = auxChar[1];

                    a -= 1;
                }
                h += 1;
            }


        }
        z[i] = verificaCondicaoUm(subInt, subIntAux, subChar, subCharAux, linha, atributos, qtdAtributos, z);

        x[i] = verificaCondicaoDois(subInt, subIntAux, subChar, subCharAux, linha, atributos, qtdAtributos, x);

        c[i] = verificaCondicaoTres(subInt, subIntAux, subChar, subCharAux, linha, atributos, qtdAtributos, c);
        
        printf("z = %d, x = ?, c = %d | %d\n", z[i], c[i], i);
        if(z[i] == 1 && c[i] == 1)
            flag = 1;

        printf("\n");
        imprimeMatriz(subIntAux, linha);
        printf("\n");
        imprimeMatrizChar(subCharAux, linha);
        printf("\n");
        i += 1;
    }

    desalocaSubMatriz((int **) subIntAux, linha);
    desalocaSubMatriz((int **) subCharAux, linha);
    printf("------------------------------------------------------");
    printf("\n");
    free(tes);
    free(atributos);
    free(z);
    free(x);
    free(c);
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
        printf("Flags: %d \n", flags[i]);


        desalocaSubMatriz((int **) subInt, linha+1);
        desalocaSubMatriz((int **) subChar, linha+1);
    }

    return grafo;
}