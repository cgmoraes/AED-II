/*• Aten¸c˜ao:
1. E/S: tanto a entrada quanto a sa´ıda de dados devem ser “secas”, ou seja, n˜ao devem
apresentar frases explicativas.
2. Identificadores de vari´aveis: escolha nomes apropriados.
3. Documenta¸c˜ao: inclua cabe¸calho, coment´arios e indenta¸c˜ao no programa.
• Descri¸c˜ao:
Implemente as opera¸c˜oes b´asicas de um algoritmo de pesquisa para Arvores Bin´arias de Busca ´
conforme as especifica¸c˜oes abaixo. Escreva um programa que contenha os procedimentos a
seguir: (1) inicializa¸c˜ao, (2) pesquisa, (3) inser¸c˜ao e (4) remo¸c˜ao. N˜ao ´e permitido o uso de
algoritmos de ordena¸c˜ao para manter os dados ordenados, caso seja necess´ario. Na opera¸c˜ao
de remo¸c˜ao, se necess´ario, dˆe a preferˆencia para a promo¸c˜ao da menor chave da sub´arvore `a
direita, ou seja, o sucessor.
• Entrada:
A primeira linha da entrada consiste de uma sequˆencia de n´umeros inteiros positivos separados
por espa¸cos. A sequˆencia termina quando for digitado um n´umero inteiro negativo. A linha
seguinte cont´em um n´umero inteiro positivo que ser´a utilizado como chave a ser pesquisada
no dicion´ario. No caso de uma pesquisa sem sucesso, esse n´umero dever´a ser inserido no
dicion´ario, caso contr´ario, ele dever´a ser removido do dicion´ario.
• Sa´ıda:
Imprima duas linhas, cada qual com dois n´umeros inteiros, onde o primeiro valor representa
tamanho do dicion´ario de dados, ou seja, a quantidade de dados armazenados, e o segundo
valor deve exibir a altura m´axima da ´arvore a partir da raiz. A primeira linha exibe a
quantidade de elementos e altura da ´arvore ap´os a inser¸c˜ao dos dados, e a segunda linha deve
exibir as mesmas informa¸c˜oes ap´os a pesquisa, oque poder´a causar aumento ou diminui¸c˜ao
na quantidade de elementos e/ou na altura da ´arvore.*/

#include "stdio.h"
#include "stdlib.h"

typedef struct node {
	int key;
	struct node *p, *left, *right;
} Node;

typedef struct tree {
	struct node *root;
} Tree;

Tree *create()
{
	Tree *T = (Tree *)malloc(sizeof(Tree));
	T->root = NULL;
	return T;
}

Node *treeMinimum(Node *x)
{
	if (x->left == NULL)
		return x;
	else
		treeMinimum(x->left);
}

Node *treeMaximum(Node *x)
{
	if (x->right == NULL)
		return x;
	else
		treeMinimum(x->right);
}

void transplant(Tree *T, Node *u, Node *v)
{
	if (u->p == NULL)
		T->root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	if (v != NULL)
		v->p = u->p;
}

void treeDelete(Tree *T, Node *z)
{
	Node *y = NULL;
	if (z->left == NULL)
		transplant(T, z, z->right);
	else if (z->right == NULL)
		transplant(T, z, z->left);
	else {
		y = treeMinimum(z->right);
		if (y->p != z) {
			transplant(T, y, y->right);
			y->right    = z->right;
			y->right->p = y;
		}
		transplant(T, z, y);
		y->left	   = z->left;
		y->left->p = y;
	}
	free(z);
}

void treeInsert(Tree *T, Node *z)
{
	Node *y = NULL;
	Node *x = T->root;
	while (x != NULL) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if (y == NULL)
		T->root = z;
	else if (z->key < y->key)
		y->left = z;
	else {
		y->right = z;
	}
}

Node *newNode(int k)
{
	Node *z	 = (Node *)malloc(sizeof(Node));
	z->key	 = k;
	z->p	 = NULL;
	z->left	 = NULL;
	z->right = NULL;
	return z;
}

int treeSearch(Tree *T, Node *x, int k, int i)
{
	if (x == NULL) {
		treeInsert(T, newNode(k));
		return ++i;
	} else if (k == x->key) {
		treeDelete(T, x);
		return --i;
	}
	if (k < x->key)
		treeSearch(T, x->left, k, i);
	else
		treeSearch(T, x->right, k, i);
}

int maxDepth(Node *x)
{
	if (x == NULL)
		return 0;
	else {
		int lDepth = maxDepth(x->left);
		int rDepth = maxDepth(x->right);
		if (lDepth > rDepth)
			return ++lDepth;
		else
			return ++rDepth;
	}
}

void print(Tree *T, int i)
{
	printf("%d %d", i, maxDepth(T->root));
	printf("\n");
}

int main()
{
	Tree *T = create();
	int k = 0, n, i = 0;
	while (k >= 0) {
		scanf("%d", &k);
		if (k >= 0) {
			treeInsert(T, newNode(k));
			i++;
		}
	}
	scanf("%d", &n);
	print(T, i);
	i = treeSearch(T, T->root, n, i);
	print(T, i);
	return 0;
}
