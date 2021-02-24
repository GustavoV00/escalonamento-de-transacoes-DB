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
void imprimeConflito(int **inputNumeros, char **inputChars, int i, int k, int conflito);
struct Grafo *visaoEquivalente(struct Grafo *grafo, int **inputNumeros, char **inputChars);
int **calculaInicioFimSubMatriz(int **inputNumeros, char **inputChars, int subMat, int **inicioFim);
int **subMatrizInt(int **inputNumeros, int **inicioFim, int **subInt, int i);
char **subMatrizChar(char **inputChars, int **inicioFim, char **subChar, int i);
void desalocaSubMatriz(int **matriz, int linha);
int *calculaQuantosTTExistemNaMatriz(int **subInt, char **subChar, int linha, int *atributos);
char *calculaQuantosAtributosExistemNaMatriz(int **subInt, char **subChar, int linha, char *atributos);
int quantidadeDeTes(int *tes);
int quantidadeDeAtributos(char *atributos);
int **copiaSubInt(int **subInt, int **subIntAux, int linha);
char **copiaSubChar(char **subChar, char **subCharAux, int linha);
int verificaCondicaoUm(int **subInt, int **subIntAux, char **subChar, char **subCharAux, int linha, char *atributos, int qtdAtributos, int *z);
int verificaCondicaoDois(int **subInt, int **subIntAux, char **subChar, char **subCharAux, int linha, char *atributos, int qtdAtributos, int *c);
int verificaCondicaoTres(int **subInt, int **subIntAux, char **subChar, char **subCharAux, int linha, char *atributos, int qtdAtributos, int *c);
int testaAlgoritimoNaSubMatriz(int **subInt, char **subChar, int linha, int *tes, char *atributos);
void imprimeResultadoFinal(struct Grafo *grafo, int *tes, int i, int qtd, int flag);

#endif