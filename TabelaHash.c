#include <stdio.h>
#include <stdlib.h>

typedef struct Tabela {
	int chave;
	struct Tabela *prox;
} TH;

TH **criarTabela(int n)
{
	int i;
	TH **T = (TH **)malloc(n * sizeof(TH));
	for (i = 0; i < n; i++) {
		T[i] = (TH *)malloc(sizeof(TH));
	}
	for (i = 0; i < n; i++) {
		T[i]->chave = -1;
		T[i]->prox  = NULL;
	}
	return T;
}

int hash(int n, int x) { return x % n; }

void remover(TH **T)
{
	if ((*T)->prox->prox != NULL)
		(*T)->prox = (*T)->prox->prox;
	else
		(*T)->prox = NULL;
}

TH *novoValor(int x)
{
	TH *z	 = (TH *)malloc(sizeof(TH));
	z->chave = x;
	z->prox	 = NULL;
	return z;
}

void inserir(TH **T, TH *z, int n)
{
	if ((*T)->prox == NULL)
		(*T)->prox = z;
	else
		inserir(&(*T)->prox, z, n);
}

void busca(TH **T, int x, int n)
{
	if ((*T)->prox == NULL)
		inserir(&(*T), novoValor(x), n);
	else if ((*T)->prox->chave == x)
		remover(&(*T));
	else
		busca(&(*T)->prox, x, n);
}

void imprime(TH **T, int n)
{
	int i;
	TH *a;
	for (i = 0; i < n; i++) {
		printf("[%d] ", i);
		a = T[i];
		while (a != NULL) {
			if (a->chave != -1)
				printf("%d ", a->chave);
			a = a->prox;
		}
		printf("\n");
	}
}

int main()
{
	int n, qnt, x, i, pos;
	scanf("%d", &n);
	TH **T;
	T = criarTabela(n);
	scanf("%d", &qnt);
	for (i = 0; i < qnt; i++) {
		scanf("%d", &x);
		pos = hash(n, x);
		inserir(&T[pos], novoValor(x), n);
	}
	scanf("%d", &x);
	pos = hash(n, x);
	busca(&T[pos], x, n);
	imprime(T, n);
	return 0;
}