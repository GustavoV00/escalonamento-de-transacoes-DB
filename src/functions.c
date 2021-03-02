#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "./../includes/functions.h"
#include "./../includes/arrumaEntrada.h"

#define COL 2


/**
 * Indica quantas vezes cada nodo do grafo pode fazer ligações
 */
int calculaVertices(int **inputNumeros, FILE *file){
    // Calcula a quantidade de linhas da matriz
    int quantidade = quantidadeDeLinhas(file);

    rewind(file);
    int maior = 0;
    // Percorre a matriz para encontrar o maior numero
    for (int i = 0; i < quantidade; i++){
        // Após encontrar o maior número da matriz, esse número
        // indnica a quantidade máxima de nodos
        if (inputNumeros[i][1] > maior){
            maior = inputNumeros[i][1];
        }
    }


    return maior;
}

/**
 * Aloca os dados da matriz do grafo
 */
int **alocaMatrizDoGrafo(int **matriz, int tam){

    matriz = malloc((tam) * sizeof(int *)); // Aloca um vetor de linhas

    // Aloca as colunas
	for (int i = 0; i < tam; i++)
		matriz[i] = malloc(tam * sizeof(int *));

    // Deixa os valores da matriz zerado
	for (int i = 0; i < tam; i ++)
		for (int j = 0; j < tam; j++)
			matriz[i][j] = 0;

    return matriz;
}

/**
 * Inicia a matriz do grafo
 */
int **iniciaMatriz(int tam, int **matriz){
    
    // Aloca na memória a matriz do grafo
    matriz = alocaMatrizDoGrafo(matriz, tam);

    // Zera toda a matriz do grafo
    for (int i = 0; i < tam; i++)
        for (int j = 0; j < tam; j++)
            matriz[i][j] = 0;

    return matriz;
}

/**
 * inicia o grafo
 */
struct Grafo *iniciaGrafo(int **inputNumeros, FILE *file){
    // Aloca o grafo na memória
    struct Grafo *grafo = malloc (sizeof (struct Grafo));

    // Aloca a quantidade de vezes que um nodo pode fazer uma ligação
    rewind(file);
    grafo -> vertices = calculaVertices(inputNumeros, file);
    printf("teste: %d\n", grafo -> vertices);

    // Indica a quantidade de arcos que o grafo possuir
    grafo -> arcos = 0;

    // Inicia a matriz do grafo
    grafo -> matriz = iniciaMatriz(grafo -> vertices, grafo -> matriz); 

	imprimeMatrizDoGrafo(grafo -> matriz, grafo -> vertices);
    return grafo;
}

/**
 * Função que imprime a matriz do grafo
 */
void imprimeMatrizDoGrafo(int **matriz, int tam){

    // Percore todos os elemtnos da matriz do grafo e imprime todos eles
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++)
            printf("%d ", matriz[i][j]);

        printf("\n");
    }
}

/**
 * Desaloca os elementos da matriz do grafo
 */
void liberaMatrizDoGrafo(int **matriz, int tam){
    // Libera todas as colunas
	for (int i = 0; i < tam; i++){
		free(matriz[i]);
	}

    // Libera a linha
	free(matriz);
}

/**
 * Insere algum elemento no grafo
 */
int **insereNoGrafo(struct Grafo *grafo, int linha, int coluna){

    // Caso o elemento a ser inserido seja 0, então o elemento muda para um, indicando uma ligação
    if(grafo -> matriz[linha][coluna] == 0){
        grafo -> matriz[linha][coluna] = 1;
        grafo -> arcos += 1;
    } 

    return grafo -> matriz;
}



//Verifica se o arquivo existe
// Daqui para cima são as funções do grafo
//--------------------------------------------------------------
//Daqui para baixo é os algoritimos de seriablidade e de visão equivalente


//O Algoritimo abaixo serve para fazer a permutação na visão equivalente. Até a próxima marcação, ainda é as funções do algoritimo Johson and Trotter.

//Algoritimo usado para fazer a permutação. Foi utilizado um algoritimo iterativo, porque eu precisava gravar os dados da permutação em uma //matriz. Que serve para rodar em um loop no código. 
 

bool LEFT_TO_RIGHT = true; 
bool RIGHT_TO_LEFT = false; 


/**
 * Utility functions for finding the 
 * position of largest mobile integer in a[]. 
 */
int searchArr(int a[], int n, int mobile) 
{ 
	for (int i = 0; i < n; i++) 
		if (a[i] == mobile) 
		    return i + 1; 
    return -1;
} 

/**
 * To carry out step 1 of the algorithm i.e. 
 * to find the largest mobile integer. 
 */
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


/**
 * Prints a single permutation 
 */
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
		printf("%d ", a[i]);
        vetor[i] = a[i];
    }
    printf("\n");
    return vetor;
} 

/**
 * To end the algorithm for efficiency it ends 
 * at the factorial of n because number of 
 * permutations possible is just n!. 
 */
int fact(int n) 
{ 
	int res = 1; 
	for (int i = 1; i <= n; i++) 
		res = res * i; 
	return res; 
} 

/**
 * This function mainly calls printOnePerm() 
 * one by one to print all permutations. 
 */
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
// Marcação. Essa marcação indica o fim das funções do algoritimo Johson and Trotter.


/**
 * Imprime a matriz que resulta no conflito
 */
void imprimeConflito(int **inputNumeros, char **inputChars, int i, int k, int conflito){

    printf("Conflito%d: %d %d %c %c e %d %d %c %c\n", conflito, inputNumeros[i][0], inputNumeros[i][1], inputChars[i][0], inputChars[i][1], inputNumeros[k][0], inputNumeros[k][1], inputChars[k][0], inputChars[k][1]);
    

}

/**
 * Função que roda o algoritimo de seriabilidade
 */
struct Grafo *seriabilidade(struct Grafo *grafo, int **inputNumeros, char **inputChars, FILE *file){
    rewind(file);
    int tam = quantidadeDeLinhas(file);
    rewind(file);

    int i = 0;
    // Roda a quantidade de linhas do arquivo.
    while(i < tam){

        int k = i;
        while(inputChars[k][0] != 'C'){
            int linha = inputNumeros[k][1] - 1;
            int coluna = inputNumeros[i][1] - 1;

            // Verifica primeiro conflito de escrita depois leitura
            if((inputNumeros[i][1] != inputNumeros[k][1]) && (inputChars[i][0] == 'W' && inputChars[k][0] == 'R') && (inputChars[i][1] == inputChars[k][1])){
                int conflito = 1;

                // Imprime onde teve o conflito
                imprimeConflito(inputNumeros, inputChars, i, k, conflito);

                // Insere no grafo indicando onde aconteceu o conflito
                grafo -> matriz = insereNoGrafo(grafo, linha, coluna);
            }

            // Verifica conflito de leitura depois escrita
            if((inputNumeros[i][1] != inputNumeros[k][1]) && (inputChars[i][0] == 'R' && inputChars[k][0] == 'W') && (inputChars[i][1] == inputChars[k][1])){
                int conflito = 2;
                // Imprime onde teve o conflito
                imprimeConflito(inputNumeros, inputChars, i, k, 
                conflito);

                // Insere no grafo indicando onde aconteceu o conflito
                grafo -> matriz = insereNoGrafo(grafo, linha, coluna);
            }

            // Verifica conflito de leitura e leitura
            if((inputNumeros[i][1] != inputNumeros[k][1]) && (inputChars[i][0] == 'W' && inputChars[k][0] == 'W') && (inputChars[i][1] == inputChars[k][1])){
                int conflito = 3;

                // Imprime onde teve o conflito
                imprimeConflito(inputNumeros, inputChars, i, k, conflito);

                // Insere no grafo indicando onde aconteceu o conflito
                grafo -> matriz = insereNoGrafo(grafo, linha, coluna);
            }

            k += 1;
        }

        i += 1;
    }

    return grafo;
}

/**
 * Indica a quantidade de processos está acontecendo e separa eles em submatrizes
 */
int calculaQuantidadeDeSubMatrizes(int **inputNumeros, char **inputChars, FILE *file){
    rewind(file);
    int tam = quantidadeDeLinhas(file)-1;
    int quantidade = 0;

    int i = 0;
    // Faz um loop pela matriz inteira
    while(i < tam){

        // Quando identificar um commit, indica que a submatriz chegou no fim
        if(inputChars[i][0] == 'C' && inputChars[i+1][0] == 'C')
            quantidade += 1;

        i += 1;
    }    

    return quantidade;

}

/**
 * Calcula onde começa e onde terminar cada submatriz
 */
int **calculaInicioFimSubMatriz(int **inputNumeros, char **inputChars, int subMat, int **inicioFim, FILE *file){
    rewind(file);
    int quantidade = quantidadeDeLinhas(file)-1;
    int fim = 0;
    int inicio = 0;

    // Aloca uma matriz, indicando onde começa e onde terminar cada submatriz da matriz principal
    inicioFim = alocaMatrizDoGrafo(inicioFim, subMat);

    int i = 0;
    int k = 0;

    // Percorre a matriz inteira
    while(i < quantidade){
        // Caso exista um commit, indica ond está o inicio
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

/**
 * DEpois de calcular o inicio e fim, aloca as submatrizes no lugar exato, tipo int
 */
int **subMatrizInt(int **inputNumeros, int **inicioFim, int **subInt, int i){

    int u = 0;
    // Percorre pelo inicio e fim das marcações de submatrizes
    for (int k = inicioFim[i][0]; k <= inicioFim[i][1]; k++){
        for (int j = 0; j < COL; j++){
            subInt[u][j] = inputNumeros[k][j];

        }
        u += 1;
    }

    return subInt;
}

/**
 * DEpois de calcular o inicio e fim, aloca as submatrizes no lugar exato, tipo char
 */
char **subMatrizChar(char **inputChars, int **inicioFim, char **subChar, int i){

    int u = 0;
    // Percorre pelo inicio e fim das marcações de submatrizes
    for (int k = inicioFim[i][0]; k <= inicioFim[i][1]; k++){
        for (int j = 0; j < COL; j++){
            subChar[u][j] = inputChars[k][j];
        }
        u += 1;
    }

    return subChar;
}

/**
 * Desaloca da memória a submatriz
 */
void desalocaSubMatriz(int **matriz, int linha){

	for (int i = 0; i < linha; i++){
		free(matriz[i]);
	}
	free(matriz);

}

/**
 * Calcula quantos transações está acontecendo, pode ser 1,2,3 etc...
 */
int *calculaQuantosTTExistemNaMatriz(int **subInt, char **subChar, int linha, int *atributos){
    int quantidade = 0;
    // Zera o vetor de atributos
    for(int i = 0; i < linha+1; i++)
        atributos[i] = 0;


    int i = 0;
    // Percorre a subMatriz para calcular a quantidade de atributos
    while(i < linha){
        
        int k = 0;
        while(k < linha){
            if(subInt[i][1] == atributos[k])
                break;

            // Se o valor ainda não existe no vetor, ele salva ele. Caso exista, não faz nada.
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

/**
 * Salva os valores dos atributos em um vetor
 */
char *calculaQuantosAtributosExistemNaMatriz(int **subInt, char **subChar, int linha, char *atributos){
    char quantidade = 0;
    for(int i = 0; i < linha+1; i++)
        atributos[i] = '0';


    int i = 0;
    // Percorre a subMatriz para calcular a quantidade de atributos
    while(i < linha){
        
        int k = 0;
        while(k < linha){
            if(subChar[i][1] == atributos[k])
                break;

            // Se o valor ainda não existe no vetor, ele salva ele. Caso exista, não faz nada.
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

/**
 * Cálcula quantas transações existe na matriz. 1,2,3
 */
int quantidadeDeTes(int *atributos){
    int quantidade = 0;
    
    for(int i = 0; atributos[i] != 0; i++)
        quantidade += 1;

    return quantidade;
}

/**
 * Cálcula quantos atributos existe na matriz. X,Y,Z
 */
int quantidadeDeAtributos(char *atributos){
    int quantidade = 0;
    
    for(int i = 0; atributos[i] != '0'; i++)
        quantidade += 1;

    return quantidade;
}

/**
 * Cópia os valores da submatriz original para um submatriz auxiliar do tipo int
 */
int **copiaSubInt(int **subInt, int **subIntAux, int linha){

    for (int i = 0; i < linha; i++)
        for(int j = 0; j < COL; j++)
            subIntAux[i][j] = subInt[i][j];

    return subIntAux;
}

/**
 * Cópia os valores da submatriz original para um submatriz auxiliar do tipo char
 */
char **copiaSubChar(char **subChar, char **subCharAux, int linha){

    for (int i = 0; i < linha; i++)
        for(int j = 0; j < COL; j++)
            subCharAux[i][j] = subChar[i][j];

    return subCharAux;
}

/**
 * Verifica a primeira propriedade do algoritimo
 */
int verificaCondicaoUm(int **subInt, int **subIntAux, char **subChar, char **subCharAux, int linha, char *atributos, int qtdAtributos, int *z){
    int flag = 1;
    int auxT1, auxT2;

    int i = 0;
    // Percorre a quantidade de atributos que a matriz possui
    while(i < qtdAtributos){
        //printf("D:%d e %d e %c\n", i, qtdAtributos, atributos[i]);
        auxT1 = -1;
        auxT2 = -1;
        for(int k = 0; k < linha; k++){

            // Caso encontra uma escrita na submatriz original, salva o valor em auxT1
            if(subChar[k][0] == 'R' && subChar[k][1] == atributos[i]){
                //printf("test1:%d\n", k);
                auxT1 = subInt[k][1];
                break;
            } 
        }

        // Caso encontra uma escrita na submatriz ordenada pela permutação, salva o valor em auxT2
        for(int k = 0; k < linha; k++){
            if(subCharAux[k][0] == 'R' && subCharAux[k][1] == atributos[i]){

                auxT2 = subIntAux[k][1];
                break;
            }
        }
        

        // Vai todos os resultados no vetor z. Se ambos os valores batem, então a condição é aceita.
        z[i] = (auxT1 == auxT2 || auxT1 == -1 || auxT2 == -1) ? 1 : 0;
        printf("HereZ:%d e %d = %d | %c\n", auxT1, auxT2, z[i], atributos[i]);


        i += 1;
    }

    // Se em todos os casos a condição bate, então a flag não é marcada como zero
    for(int i = 0; i < qtdAtributos; i++){
        if(z[i] == 0)
            flag = 0;
    }

    flag = 1;
    return flag;
}

/**
 * Verifica a segunda propriedade do algoritimo de visão equivalente
 */
int verificaCondicaoDois(int **subInt, int **subIntAux, char **subChar, char **subCharAux, int linha, char *atributos, int qtdAtributos, int *x){
    printf("\n");
    int flag = 1;
    int auxT1 = -1, auxT2 = -1;

    int i = 0;
    // Percorre a quantidade de atributos que a matriz possui
    while(i < qtdAtributos){
        //printf("D:%d e %d e %c\n", i, qtdAtributos, atributos[i]);
        auxT1 = -1;
        auxT2 = -1;

        // Percorre a matriz
        for(int k = 0; k < linha; k++){

            // Se encontrar uma escrtia com a transação certa ele entra no if
            if(subChar[k][0] == 'W' && subChar[k][1] == atributos[i]){

                // Percorre a matriz novamente do lugar de onde o k parou
                for(int u = k; u < linha; u++){
                    
                    // Se encontrar uma letiura, significa que a propriedade foi aceita.
                    if(subChar[u][0] == 'R' && subChar[u][1] == atributos[i]){
                        
                        auxT1 = subInt[u][1];
                    } 
                }
            }
        }

        // Percorre a matriz
        for(int k = 0; k < linha; k++){
            // Se encontrar uma escrtia com a transação certa ele entra no if
            if(subCharAux[k][0] == 'W' && subCharAux[k][1] == atributos[i]){
                // Percorre a matriz novamente do lugar de onde o k parou
                for(int u = k; u < linha; u++){
                    // Se encontrar uma letiura, significa que a propriedade foi aceita.
                    if(subCharAux[u][0] == 'R' && subCharAux[u][1] == atributos[i]){
                        printf("%c e %c e %d\n", subCharAux[u][0], subCharAux[k][1], u);
                        auxT2 = subIntAux[u][1];
                    } 
                }
            }
        }

        // Vai todos os resultados no vetor x. Se ambos os valores batem, então a condição é aceita.
        x[i] = (auxT1 == auxT2) ? 1 : 0;
        printf("HereX:%d e %d = %d | %c\n", auxT1, auxT2, x[i], atributos[i]);

        i += 1;
    }
    
    // Se em todos os casos a condição bate, então a flag não é marcada como zero
    for(int i = 0; i < qtdAtributos; i++){
        if(x[i] == 0)
            flag = 0;
    }
    printf("\n");
    return flag;
}

/**
 * Verifica a terceira propriedade do algoritimo de visão equivalente
 */
int verificaCondicaoTres(int **subInt, int **subIntAux, char **subChar, char **subCharAux, int linha, char *atributos, int qtdAtributos, int *c){
    int flag = 1;
    int auxT1 = -1, auxT2 = -1;

    int i = 0;
    while(i < qtdAtributos){
        //printf("D:%d e %d e %c\n", i, qtdAtributos, atributos[i]);
        auxT1 = -1;
        auxT2 = -1;
        for(int k = 0; k < linha; k++){
            // Caso encontra uma escrita na submatriz original, salva o valor em auxT1
            if(subChar[k][0] == 'W' && subChar[k][1] == atributos[i]){
                auxT1 = subInt[k][1];
            } 
        }

        for(int k = 0; k < linha; k++){
            // Caso encontra uma escrita na submatriz ordenada pela permutação, salva o valor em auxT2
            if(subCharAux[k][0] == 'W' && subCharAux[k][1] == atributos[i]){
                auxT2 = subIntAux[k][1];

            }
        }
        
        // Vai todos os resultados no vetor c. Se ambos os valores batem, então a condição é aceita.
        c[i] = (auxT1 == auxT2 || auxT1 == -1 || auxT2 == -1) ? 1 : 0;
        printf("HereC:%d e %d = %d | %c\n", auxT1, auxT2, c[i], atributos[i]);

        i += 1;
    }
    
    // Se em todos os casos a condição bate, então a flag não é marcada como zero
    for(int i = 0; i < qtdAtributos; i++){
        if(c[i] == 0)
            flag = 0;
    }
    printf("\n");
    return flag;
}


/// Cria uma flag se existe uma visao equivalente. Toda a parte de cima arruma as entradas para rodar o algoritimo
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

    // Indica quantas transações existem
    int qtdtes = quantidadeDeTes(tes);

    // Ordena o vetor de transações
    tes = ordenaVetor(tes, qtdtes);

    // Indica quantos atributos existem
    int qtdAtributos = quantidadeDeAtributos(atributos);
    for (int i = 0; i < qtdtes; i++)
        maior = (tes[i] > maior) ? tes[i] : maior;
    
    // Indica quantas permutações existem, para alocar a matriz permutação
    for(int i = qtdtes; i > 1; i--)
        quantidade *= i;

    // Aloca uma matriz que vai caber todas as permutações
    permutacoes = alocaMatriz(quantidade, permutacoes);
    
    // Coloca as permutações na matriz permutações
    permutacoes = printPermutation(qtdtes, permutacoes);

    // Calcula quantas permutações existem
    for(int i = 0; i < qtdtes; i++)
        permutacoes[0][i] = tes[i];



    // Como as permutações vem sempre com o indice 1,2,3 etc... Caso tenha mais de uma submatriz, então os "fors" abaixo, server para arrumar os indices. 
    printf("\n");
    for(int i = 1; i < quantidade; i++){
        for(int j = 0; j < qtdtes; j++){
            indice = permutacoes[i][j];
            permutacoes[i][j] = tes[indice-1];
            
        }
    }

    printf("\n");
    for(int i = 0; i < quantidade; i++){
        printf("%d -> ", i);
        for(int j = 0; j < qtdtes; j++){
            printf("%d ", permutacoes[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

    // Aloca a primeira propriedade
    int *z = malloc(quantidade * sizeof(int));

    // Aloca a segunda propriedade
    int *x = malloc(quantidade * sizeof(int));

    // Aloca a terceira propriedade
    int *c = malloc(quantidade * sizeof(int));

    int i = 0;

    // Enquanto a quantidade de permutações não chega no fim, ou a flag é 0, o while continua tentando encontrar a visão equivalente.
    while(i < quantidade && flag == 0){
        subIntAux = copiaSubInt(subInt, subIntAux, linha);
        subCharAux = copiaSubChar(subChar, subCharAux, linha);

        int h = 0;
        int u = 0;
        // While que percorre todos os elementos da linha da matriz permutação
        while(u < qtdtes){
            printf("\nTest:%d \n", permutacoes[i][u]);
            // For que percorre a submatriz
            for(int k = 0; k < linha; k++){
                // If faz a verificação se os indices i,j da matriz permutação estão correspondende com a submatriz subIntAux. Verificando se as transações são as mesmas para fazer a ordenação.
                if(permutacoes[i][u] == subIntAux[k][1]){
                    int a = k;
                    while(a > h){
                        // Coloca os valores na ordem da permutação
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

        // Verifica a primeira condição da visão equivalente
        z[i] = verificaCondicaoUm(subInt, subIntAux, subChar, subCharAux, linha, atributos, qtdAtributos, z);

        // Verifica a segunda condição da visão equivalente
        x[i] = verificaCondicaoDois(subInt, subIntAux, subChar, subCharAux, linha, atributos, qtdAtributos, x);

        // Verifica a terceira condição da visão equivalente
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

    // Desaloca os vetores e matrizes
    desalocaSubMatriz((int **) subIntAux, linha);
    desalocaSubMatriz((int **) subCharAux, linha);
    printf("\n");
    free(z);
    free(x);
    free(c);
    return flag;
}

/**
 * Ordena o vetor, para imprimir em ordem crescente no final
 */

int *ordenaVetor(int *tes, int qtd){
    int i, j, temp;     
    for(i = 0; i < qtd && tes[i] != 0; i++)
        for(j = 1; j < qtd-i && tes[j] != 0; j++)
		    if(tes[j-1] > tes[j]){
			    temp = tes[j-1];
				tes[j-1] = tes[j];
				tes[j] = temp;
			}  

    return tes;
}

/**
 * Imprime o output final, indicando o resultado de ambos os 
 * algoritimos.
 */
void imprimeResultadoFinal(struct Grafo *grafo, int *tes, int i, int qtd, int flag){
    int serial = 0;
    int inicio = tes[0] - 1;
    FILE *file = stdout;

    printf("test:%d e %d\n", tes[qtd-1] - 1, inicio);
    printf("Vertices:%d\n", grafo -> vertices);

    printf("%d ", i+1);
    tes = ordenaVetor(tes, qtd);
    // Imprime um indíce ID
    for(int k = 0; k < qtd && tes[k] != 0; k++)
        if(tes[k+1] == 0)
            fprintf(file, "%d", tes[k]);
        else
            fprintf(file, "%d,", tes[k]);
    

    // Imprime o vetor de transações
    for(int k = inicio; k < tes[qtd-1]; k++)
        for(int u = inicio; u < tes[qtd-1]; u++){
            if(grafo -> matriz[k][u] == 1 && grafo -> matriz[u][k] == 1){
                serial = 1;
            }
                
        }

    // Imprime o NS, SS E SV,NV
    if (serial == 1)
        fprintf(file, "%s", " NS");
    else
        fprintf(file, "%s", " SS");

    if (flag == 1)
        fprintf(file, "%s", " SV");
    else
        fprintf(file, "%s", " NV");

    printf("\n\n");
}

/**
 * Função que faz o algoritimo da visão equivalente
 */
struct Grafo *visaoEquivalente(struct Grafo *grafo, int **inputNumeros, char **inputChars, FILE *file){
    // Calcula quantas submatrizes existem
    int subMat = calculaQuantidadeDeSubMatrizes(inputNumeros, inputChars, file);
    int flags[subMat];
    int **inicioFim = NULL;
    int **subInt = NULL;
    char **subChar = NULL;

    printf("%d\n", subMat);

    int i = 0;
    // Percore pela quantidade de submatrizes
    while(i < subMat){
        // Calcula onde começa o inicio e o fim de cada submatriz
        inicioFim = calculaInicioFimSubMatriz(inputNumeros, inputChars, subMat, inicioFim, file);
        printf("inicio:%d e Fim:%d\n", inicioFim[i][0], inicioFim[i][1]);


        int linha = inicioFim[i][1] - inicioFim[i][0];
        rewind(file);
        if(linha > 0){
            // Aloca matrizes
            subInt = alocaMatriz(linha+1, subInt);
            subChar = alocaMatrizChar(linha+1, subChar);

            // Aloca subMatrizes
            subInt = subMatrizInt(inputNumeros, inicioFim, subInt, i);
            subChar = subMatrizChar(inputChars, inicioFim, subChar, i);

            // Aloca vetores
            int *tes = malloc((linha*linha) * sizeof(int));
            char *atributos = malloc((linha*linha) * sizeof(char));

            // Calcula quanas transações existem e salva tudo em um vetor
            tes = calculaQuantosTTExistemNaMatriz(subInt, subChar, linha, tes);
            int qtdTes = quantidadeDeTes(tes);

            // Calcula quantas atributos possuem, X,Y,Z etc...
            atributos = calculaQuantosAtributosExistemNaMatriz(subInt, subChar, linha, atributos);

            //imprimeMatriz(subInt, linha+1);
            printf("\n");
            //imprimeMatrizChar(subChar, linha+1);
            printf("\n");


            // Cria uma flag se existe uma visao equivalente. Toda a parte de cima arruma as entradas para rodar o algoritimo
            flags[i] = testaAlgoritimoNaSubMatriz(subInt, subChar, linha+1, tes, atributos);
            printf("Flags: %d \n", flags[i]);
            printf("----------------------------------------\n");

            imprimeResultadoFinal(grafo, tes, i, qtdTes, flags[i]);



            // Desaloca todas as matrizes e vetores alocados
            /*desalocaSubMatriz((int **) subInt, linha+1);
            desalocaSubMatriz((int **) subChar, linha+1);
            free(tes);
            free(atributos);*/
        }

        // Desaloca a matriz também
        desalocaSubMatriz(inicioFim, subMat);
        i += 1;

    }

    return grafo;
}