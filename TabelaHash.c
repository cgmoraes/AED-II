/*Aten¸c˜ao:
1. E/S: tanto a entrada quanto a sa´ıda de dados devem ser “secas”, ou seja, n˜ao devem
apresentar frases explicativas.
2. Identificadores de vari´aveis: escolha nomes apropriados.
3. Documenta¸c˜ao: inclua cabe¸calho, coment´arios e indenta¸c˜ao no programa.
• Descri¸c˜ao:
Implemente as opera¸c˜oes b´asicas do algoritmo de pesquisa baseado em transforma¸c˜ao de chave
(hashing), conforme as especifica¸c˜oes abaixo. Utilize o m´etodo da divis˜ao como fun¸c˜ao de
transforma¸c˜ao e a estrat´egia de encadeamento para tratar colis˜oes. Escreva um procedimento
separado para as seguintes opera¸c˜oes: (1) pesquisa, (2) inser¸c˜ao e (3) remo¸c˜ao. Se necess´ario,
na opera¸c˜ao de inser¸c˜ao, coloque o novo item ap´os todos os itens demais, ou seja, no final.
• Entrada:
A entrada consiste de v´arios n´umeros inteiros separados por espa¸cos. O primeiro n´umero
indica o tamanho da tabela de hash a ser utilizada. Todos os demais n´umeros exceto o ´ultimo
ser˜ao inseridos na tabela. O ´ultimo n´umero ser´a utilizado como chave a ser pesquisada na
tabela. No caso de uma pesquisa sem sucesso, esse n´umero tamb´em ser´a inserido na tabela,
caso contr´ario, ele dever´a ser removido.
• Sa´ıda:
Imprima a tabela de hash, cada entrada da tabela em uma linha, separando os elementos de
uma mesma entrada com um espa¸co.*/

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
