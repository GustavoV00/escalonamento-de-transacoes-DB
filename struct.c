#ifndef __ESTRUTURAS__
#define __ESTRUTURAS__


struct Nodo{
	int tempo; // id
	int t; // Identificador da transacao
	char operacao; // R(READ), W(Write), C(Commit)
	char data; // Ex: R(X) -> R(saldo)
	struct Nodo **conflito;
};


#endif
