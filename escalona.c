#include <stdlib.h>
#include <stdio.h>
#include "./struct.c"
#include "arrumaEntrada.h"


int main(){
	int  **inputNumeros = NULL;
	char **inputChars = NULL;



	inputNumeros = alocaDadosDeEntradaInt(inputNumeros);
	printf("\n");
	inputChars = alocaDadosDeEntradaChar(inputChars);


	liberaMatriz((int **) inputNumeros);
	liberaMatriz((int **) inputChars);
	return 0;
}
