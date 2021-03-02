#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <stdbool.h>

struct Grafo{
	int vertices; /// Quantidade de vértices do grafo
	int arcos; /// Quantidade de arcos de um grafo
	int **matriz; /// Matriz adjacência "Grafo"
};

// Johnson and Trotter algorithm. Todas as funções abaixo.
int searchArr(int a[], int n, int mobile);
int getMobile(int a[], bool dir[], int n);
int *printOnePerm(int a[], bool dir[], int n, int *vetor);
int fact(int n);
int **printPermutation(int n, int **permutacoes);
// Até aqui ------------------------------------------------//

// Indica quantas vezes cada nodo do grafo pode fazer ligações
int calculaVertices(int **inputNumeros, FILE *file);

// Aloca os dados da matriz do grafo
int **alocaMatrizDoGrafo(int **matriz, int tam);

// Inicia a matriz do grafo
int **iniciaMatriz(int tam, int **matriz);

// inicia o grafo
struct Grafo *iniciaGrafo(int **inputNumeros, FILE *file);

// Função que imprime a matriz do grafo
void imprimeMatrizDoGrafo(int **matriz, int tam);

// Desaloca os elementos da matriz do grafo
void liberaMatrizDoGrafo(int **matriz, int tam);

// Insere algum elemento no grafo
int **insereNoGrafo(struct Grafo *grafo, int linha, int coluna);

// Função que roda o algoritimo de seriabilidade
struct Grafo *seriabilidade(struct Grafo *grafo, int **inputNumeros, char **inputChars, FILE *file);

// Imprime a matriz que resulta no conflito
void imprimeConflito(int **inputNumeros, char **inputChars, int i, int k, int conflito);

// Indica a quantidade de processos está acontecendo e separa eles em submatrizes
int calculaQuantidadeDeSubMatrizes(int **inputNumeros, char **inputChars, FILE *file);

// Função que faz o algoritimo da visão equivalente
struct Grafo *visaoEquivalente(struct Grafo *grafo, int **inputNumeros, char **inputChars, FILE *file);

// Calcula onde começa e onde terminar cada submatriz
int **calculaInicioFimSubMatriz(int **inputNumeros, char **inputChars, int subMat, int **inicioFim, FILE *file);

// DEpois de calcular o inicio e fim, aloca as submatrizes no lugar exato, tipo int
int **subMatrizInt(int **inputNumeros, int **inicioFim, int **subInt, int i);

// DEpois de calcular o inicio e fim, aloca as submatrizes no lugar exato, tipo char
char **subMatrizChar(char **inputChars, int **inicioFim, char **subChar, int i);

// Desaloca submatriz
void desalocaSubMatriz(int **matriz, int linha);

// Calcula quantos transações está acontecendo, pode ser 1,2,3 etc...
int *calculaQuantosTTExistemNaMatriz(int **subInt, char **subChar, int linha, int *atributos);

// Salva os valores dos atributos em um vetor
char *calculaQuantosAtributosExistemNaMatriz(int **subInt, char **subChar, int linha, char *atributos);

// Cálcula quantas transações existe na matriz. 1,2,3
int quantidadeDeTes(int *tes);

// Cálcula quantos atributos existe na matriz. X,Y,Z
int quantidadeDeAtributos(char *atributos);

// Cópia os valores da submatriz original para um submatriz auxiliar do tipo int
int **copiaSubInt(int **subInt, int **subIntAux, int linha);

// Cópia os valores da submatriz original para um submatriz auxiliar do tipo char
char **copiaSubChar(char **subChar, char **subCharAux, int linha);

// Verifica a primeira propriedade do algoritimo de visão equivalente
int verificaCondicaoUm(int **subInt, int **subIntAux, char **subChar, char **subCharAux, int linha, char *atributos, int qtdAtributos, int *z);

// Verifica a segunda propriedade do algoritimo de visão equivalente
int verificaCondicaoDois(int **subInt, int **subIntAux, char **subChar, char **subCharAux, int linha, char *atributos, int qtdAtributos, int *c);

// Verifica a terceira propriedade do algoritimo de visão equivalente
int verificaCondicaoTres(int **subInt, int **subIntAux, char **subChar, char **subCharAux, int linha, char *atributos, int qtdAtributos, int *c);

// Cria uma flag se existe uma visao equivalente. Toda a parte de cima arruma as entradas para rodar o algoritimo
int testaAlgoritimoNaSubMatriz(int **subInt, char **subChar, int linha, int *tes, char *atributos);

// Ordena o vetor, para imprimir em ordem crescente no final
int *ordenaVetor(int *tes, int qtd);

// Imprime o output final, indicando o resultado de ambos os algoritimos.
void imprimeResultadoFinal(struct Grafo *grafo, int *tes, int i, int qtd, int flag);

#endif