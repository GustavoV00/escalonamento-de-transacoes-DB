#ifndef __FUNCTIONS__
#define __FUNCTIONS__

struct Grafo{
	int vertices; // Quantidade de vértices do grafo
	int arcos; // Quantidade de arcos de um grafo
	int **matriz; // Matriz adjacência "Grafo"
};

int calculaVertices(int **inputNumeros);
int **alocaMatrizDoGrafo(int **matriz, int tam);
int **iniciaMatriz(int tam, int **matriz);
struct Grafo *iniciaGrafo(int **inputNumeros);
void imprimeMatrizDoGrafo(int **matriz, int tam);
void liberaMatrizDoGrafo(int **matriz, int tam);
struct Grafo *seriabilidade(struct Grafo *grafo, int **inputNumeros, char **inputChars);

#endif