#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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

// CPP program to print all permutations using 
// Johnson and Trotter algorithm. 

bool LEFT_TO_RIGHT = true; 
bool RIGHT_TO_LEFT = false; 

// Utility functions for finding the 
// position of largest mobile integer in a[]. 
int searchArr(int a[], int n, int mobile) 
{ 
	for (int i = 0; i < n; i++) 
		if (a[i] == mobile) 
		    return i + 1; 
    return -1;
} 

// To carry out step 1 of the algorithm i.e. 
// to find the largest mobile integer. 
int getMobile(int a[], bool dir[], int n) 
{ 
	int mobile_prev = 0, mobile = 0; 
	for (int i = 0; i < n; i++) 
	{ 
		// direction 0 represents RIGHT TO LEFT. 
		if (dir[a[i]-1] == RIGHT_TO_LEFT && i!=0) 
		{ 
			if (a[i] > a[i-1] && a[i] > mobile_prev) 
			{ 
				mobile = a[i]; 
				mobile_prev = mobile; 
			} 
		} 

		// direction 1 represents LEFT TO RIGHT. 
		if (dir[a[i]-1] == LEFT_TO_RIGHT && i!=n-1) 
		{ 
			if (a[i] > a[i+1] && a[i] > mobile_prev) 
			{ 
				mobile = a[i]; 
				mobile_prev = mobile; 
			} 
		} 
	} 

	if (mobile == 0 && mobile_prev == 0) 
		return 0; 
	else
		return mobile; 
} 

// Prints a single permutation 
int *printOnePerm(int a[], bool dir[], int n, int *vetor) 
{ 
	int mobile = getMobile(a, dir, n); 
	int pos = searchArr(a, n, mobile); 

	// swapping the elements according to the 
	// direction i.e. dir[]. 
	if (dir[a[pos - 1] - 1] == RIGHT_TO_LEFT) {
        int aux = a[pos-1];
        a[pos-1] = a[pos-2];
        a[pos-2] = aux;
    }
	//swap(a[pos-1], a[pos-2]); 

	else if (dir[a[pos - 1] - 1] == LEFT_TO_RIGHT){
        int aux = a[pos];
        a[pos] = a[pos-1];
        a[pos-1] = aux;
    } 
	//swap(a[pos], a[pos-1]); 

	// changing the directions for elements 
	// greater than largest mobile integer. 
	for (int i = 0; i < n; i++) 
	{ 
		if (a[i] > mobile) 
		{ 
			if (dir[a[i] - 1] == LEFT_TO_RIGHT) 
				dir[a[i] - 1] = RIGHT_TO_LEFT; 
			else if (dir[a[i] - 1] == RIGHT_TO_LEFT) 
				dir[a[i] - 1] = LEFT_TO_RIGHT; 
		} 
	} 

	for (int i = 0; i < n; i++){
		//printf("%d ", a[i]);
        vetor[i] = a[i];
    }
    //printf("\n");
    return vetor;
} 

// To end the algorithm for efficiency it ends 
// at the factorial of n because number of 
// permutations possible is just n!. 
int fact(int n) 
{ 
	int res = 1; 
	for (int i = 1; i <= n; i++) 
		res = res * i; 
	return res; 
} 

// This function mainly calls printOnePerm() 
// one by one to print all permutations. 
int **printPermutation(int n, int **permutacoes) 
{ 
	// To store current permutation 
	int a[n]; 

	// To store current directions 
	bool dir[n]; 

	// storing the elements from 1 to n and 
	// printing first permutation. 
	for (int i = 0; i < n; i++) 
	{ 
		a[i] = i + 1; 
        //printf("%d ", a[i]);
	} 
    //printf("\n");
    //printf("%d\n", endl);

	// initially all directions are set 
	// to RIGHT TO LEFT i.e. 0. 
	for (int i = 0; i < n; i++) 
		dir[i] = RIGHT_TO_LEFT; 

	// for generating permutations in the order. 
	for (int i = 1; i < fact(n); i++) 
		permutacoes[i] = printOnePerm(a, dir, n, permutacoes[i]); 

    return permutacoes;
} 

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
        while(inputChars[k][0] != 'C'){
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
        auxT1 = -1;
        auxT2 = -1;
        for(int k = 0; k < linha; k++){
            if(subChar[k][0] == 'R' && subChar[k][1] == atributos[i]){
                //printf("test1:%d\n", k);
                auxT1 = subInt[k][1];
                break;
            } 
        }

        for(int k = 0; k < linha; k++){
            if(subCharAux[k][0] == 'R' && subCharAux[k][1] == atributos[i]){

                auxT2 = subIntAux[k][1];
                break;
            }
        }
        
        z[i] = (auxT1 == auxT2 || auxT1 == -1 || auxT2 == -1) ? 1 : 0;
        printf("HereZ:%d e %d = %d | %c\n", auxT1, auxT2, z[i], atributos[i]);


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
    printf("\n");
    int flag = 1;
    int auxT1 = -1, auxT2 = -1;

    int i = 0;
    while(i < qtdAtributos){
        //printf("D:%d e %d e %c\n", i, qtdAtributos, atributos[i]);
        auxT1 = -1;
        auxT2 = -1;
        for(int k = 0; k < linha; k++){
            if(subChar[k][0] == 'W' && subChar[k][1] == atributos[i]){
                
                for(int u = k; u < linha; u++){
                    if(subChar[u][0] == 'R' && subChar[u][1] == atributos[i]){
                        
                        auxT1 = subInt[u][1];
                    } 
                }
            }
        }

        for(int k = 0; k < linha; k++){
            if(subCharAux[k][0] == 'W' && subCharAux[k][1] == atributos[i]){
                for(int u = k; u < linha; u++){
                    if(subCharAux[u][0] == 'R' && subCharAux[u][1] == atributos[i]){
                        printf("%c e %c e %d\n", subCharAux[u][0], subCharAux[k][1], u);
                        auxT2 = subIntAux[u][1];
                    } 
                }
            }
        }

        x[i] = (auxT1 == auxT2) ? 1 : 0;
        printf("HereX:%d e %d = %d | %c\n", auxT1, auxT2, x[i], atributos[i]);

        i += 1;
    }
    
    for(int i = 0; i < qtdAtributos; i++){
        if(x[i] == 0)
            flag = 0;
    }
    printf("\n");
    return flag;
}

// Escrita no final
int verificaCondicaoTres(int **subInt, int **subIntAux, char **subChar, char **subCharAux, int linha, char *atributos, int qtdAtributos, int *c){
    int flag = 1;
    int auxT1 = -1, auxT2 = -1;

    int i = 0;
    while(i < qtdAtributos){
        //printf("D:%d e %d e %c\n", i, qtdAtributos, atributos[i]);
        auxT1 = -1;
        auxT2 = -1;
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
        
        c[i] = (auxT1 == auxT2 || auxT1 == -1 || auxT2 == -1) ? 1 : 0;
        printf("HereC:%d e %d = %d | %c\n", auxT1, auxT2, c[i], atributos[i]);

        i += 1;
    }
    
    for(int i = 0; i < qtdAtributos; i++){
        if(c[i] == 0)
            flag = 0;
    }
    printf("\n");
    return flag;
}

int testaAlgoritimoNaSubMatriz(int **subInt, char **subChar, int linha, int *tes, char *atributos){

    int flag = 0, auxInt[1], indice;
    int **subIntAux = NULL;
    char **subCharAux = NULL;
    int **permutacoes = NULL;
    int quantidade = 1;
    int maior = 0;
    subIntAux = alocaMatriz(linha, subIntAux);
    subCharAux = alocaMatrizChar(linha, subCharAux);

    char auxChar[2];

    int qtdtes = quantidadeDeTes(tes);
    int qtdAtributos = quantidadeDeAtributos(atributos);
    for (int i = 0; i < qtdtes; i++)
        maior = (tes[i] > maior) ? tes[i] : maior;
    
    for(int i = qtdtes; i > 1; i--)
        quantidade *= i;

    permutacoes = alocaMatriz(quantidade, permutacoes);
    permutacoes = printPermutation(qtdtes, permutacoes);

    for(int i = 0; i < maior; i++)
        permutacoes[0][i] = i+1;

    printf("\n\n");

    for(int i = 0; i < quantidade; i++){
        for(int j = 0; j < qtdtes; j++){
            indice = permutacoes[i][j];
            permutacoes[i][j] = tes[indice-1];
            printf("%d ", permutacoes[i][j]);
        }
        printf("\n");
    }


    int *z = malloc(qtdAtributos * sizeof(int));
    int *x = malloc(qtdAtributos * sizeof(int));
    int *c = malloc(qtdAtributos * sizeof(int));

    int i = 0;

    while(i < quantidade && flag == 0){
        subIntAux = copiaSubInt(subInt, subIntAux, linha);
        subCharAux = copiaSubChar(subChar, subCharAux, linha);

        int h = 0;
        int u = 0;
        while(u < qtdtes){
            printf("\nTest:%d \n", permutacoes[i][u]);
            for(int k = 0; k < linha; k++){
                if(permutacoes[i][u] == subIntAux[k][1]){
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

            u += 1;
        }
        z[i] = verificaCondicaoUm(subInt, subIntAux, subChar, subCharAux, linha, atributos, qtdAtributos, z);

        x[i] = verificaCondicaoDois(subInt, subIntAux, subChar, subCharAux, linha, atributos, qtdAtributos, x);

        c[i] = verificaCondicaoTres(subInt, subIntAux, subChar, subCharAux, linha, atributos, qtdAtributos, c);
        
        if(z[i] == 1 && x[i] == 1 && c[i] == 1)
            flag = 1;

        printf("z = %d, x = %d, c = %d | %d\n", z[i], x[i], c[i], flag);

        printf("\n");
        imprimeMatriz(subIntAux, linha);
        printf("\n");
        imprimeMatrizChar(subCharAux, linha);
        printf("\n");
        i += 1;
        printf("----------------------------------------\n");
    }

    desalocaSubMatriz((int **) subIntAux, linha);
    desalocaSubMatriz((int **) subCharAux, linha);
    printf("\n");
    free(z);
    free(x);
    free(c);
    return flag;
}

void imprimeResultadoFinal(struct Grafo *grafo, int *tes, int i, int qtd, int flag){
    int serial = 0;
    int inicio = tes[0] - 1;
    printf("test:%d e %d\n", tes[qtd-1] - 1, inicio);
    printf("Vertices:%d\n", grafo -> vertices);

    printf("%d ", i);
    for(int k = 0; k < qtd && tes[k] != 0; k++)
        if(tes[k+1] == 0)
            printf("%d ", tes[k]);
        else
            printf("%d,", tes[k]);
    
    for(int k = inicio; k < tes[qtd-1]; k++)
        for(int u = inicio; u < tes[qtd-1]; u++){
            if(grafo -> matriz[k][u] == 1 && grafo -> matriz[u][k] == 1){
                serial = 1;
            }
                
        }

    if (serial == 1)
        printf("NS ");
    else
        printf("SS ");

    if (flag == 1)
        printf("SV ");
    else
        printf("NV ");

    printf("\n\n");
}
struct Grafo *visaoEquivalente(struct Grafo *grafo, int **inputNumeros, char **inputChars){
    int subMat = calculaQuantidadeDeSubMatrizes(inputNumeros, inputChars);
    int flags[subMat];
    int **inicioFim = NULL;
    int **subInt = NULL;
    char **subChar = NULL;

    printf("%d\n", subMat);

    int i = 0;
    while(i < subMat){
        
        inicioFim = calculaInicioFimSubMatriz(inputNumeros, inputChars, subMat, inicioFim);
        printf("inicio:%d e Fim:%d\n", inicioFim[i][0], inicioFim[i][1]);


        int linha = inicioFim[i][1] - inicioFim[i][0];
        if(linha > 0){
            subInt = alocaMatriz(linha+1, subInt);
            subChar = alocaMatrizChar(linha+1, subChar);

            subInt = subMatrizInt(inputNumeros, inicioFim, subInt, i);
            subChar = subMatrizChar(inputChars, inicioFim, subChar, i);

            int *tes = malloc((linha*linha) * sizeof(int));
            char *atributos = malloc((linha*linha) * sizeof(char));

            tes = calculaQuantosTTExistemNaMatriz(subInt, subChar, linha, tes);
            int qtdTes = quantidadeDeTes(tes);
            atributos = calculaQuantosAtributosExistemNaMatriz(subInt, subChar, linha, atributos);

            //imprimeMatriz(subInt, linha+1);
            printf("\n");
            //imprimeMatrizChar(subChar, linha+1);
            printf("\n");


            // Cria uma flag se existe uma visao equivalente.
            flags[i] = testaAlgoritimoNaSubMatriz(subInt, subChar, linha+1, tes, atributos);
            printf("Flags: %d \n", flags[i]);
            printf("----------------------------------------\n");

            imprimeResultadoFinal(grafo, tes, i, qtdTes, flags[i]);




            desalocaSubMatriz((int **) subInt, linha+1);
            desalocaSubMatriz((int **) subChar, linha+1);
            free(tes);
            free(atributos);
        }

        desalocaSubMatriz(inicioFim, subMat);
        i += 1;

    }

    return grafo;
}