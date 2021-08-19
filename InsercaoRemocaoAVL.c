/*Aten¸c˜ao:
1. E/S: tanto a entrada quanto a sa´ıda de dados devem ser “secas”, ou seja, n˜ao devem
apresentar frases explicativas.
2. Identificadores de vari´aveis: escolha nomes apropriados.
3. Documenta¸c˜ao: inclua cabe¸calho, coment´arios e indenta¸c˜ao no programa.
• Descri¸c˜ao:
Implemente as opera¸c˜oes b´asicas de um algoritmo de pesquisa em ´arvores AVL, conforme as especifica¸c˜oes abaixo. Escreva um procedimento (fun¸c˜ao) separado para as seguintes opera¸c˜oes:
(1) inicializa¸c˜ao, (2) pesquisa, (3) inser¸c˜ao e (4) remo¸c˜ao. Se necess´ario, na opera¸c˜ao de
remo¸c˜ao, dˆe a preferˆencia para a promo¸c˜ao da menor chave da sub´arvore `a direita, ou seja, o
sucessor. calcular a altura da ´arvore, caso seja necess´ario.
• Entrada:
A entrada consiste de v´arios n´umeros inteiros separados por espa¸cos. Todos os n´umeros
exceto o ´ultimo ser˜ao inseridos na ´arvore AVL. O ´ultimo n´umero ser´a utilizado como chave
a ser pesquisada na ´arvore. No caso de uma pesquisa sem sucesso, esse n´umero tamb´em ser´a
inserido na ´arvore, caso contr´ario, ele dever´a ser removido da ´arvore.
• Sa´ıda:
Imprima a ´arvore AVL representada por parˆenteses aninhados (veja exemplos na tarefa anterior - Tarefa 07).*/

#include "stdio.h"
#include "stdlib.h"

typedef struct node *Node;
typedef struct tree *Tree;

typedef struct node {
	int key;
	int height;
	Node p, left, right;
} node;

typedef struct tree {
	Node root;
} tree;

Tree create()
{
	Tree T	= (Tree)malloc(sizeof(tree));
	T->root = NULL;
	return T;
}

int height(Node x)
{
	if (x == NULL)
		return 0;
	return x->height;
}

int balance(Node x)
{
	if (x == NULL)
		return 0;
	return height(x->left) - height(x->right);
}

int max(int a, int b) { return (a > b) ? a : b; }

Node treeMinimum(Node x)
{
	if (x->left == NULL)
		return x;
	else
		treeMinimum(x->left);
}

void transplant(Tree T, Node u, Node v)
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

Node LL(Node x)
{
	Node pA = x->left, pB = pA->right;
	pA->right  = x;
	x->left	   = pB;
	x->height  = max(height(x->left), height(x->right)) + 1;
	pA->height = max(height(pA->left), height(pA->right)) + 1;
	return pA;
}

Node RR(Node x)
{
	Node pA = x->right, pB = pA->left;
	pA->left   = x;
	x->right   = pB;
	x->height  = max(height(x->left), height(x->right)) + 1;
	pA->height = max(height(pA->left), height(pA->right)) + 1;
	return pA;
}

Node LR(Node x)
{
	Node pA = x->left->right, pB = pA->left;
	pA->left       = x->left;
	x->left->right = pB;
	x->left->height =
	    max(height(x->left->left), height(x->left->right)) + 1;
	pA->height = max(height(pA->left), height(pA->right)) + 1;
	x->left	   = pA;
	pB	   = pA->right;
	pA->right  = x;
	x->left	   = pB;
	x->height  = max(height(x->left), height(x->right)) + 1;
	pA->height = max(height(pA->left), height(pA->right)) + 1;
	return pA;
}

Node RL(Node x)
{
	Node pA = x->right->left, pB = pA->right;
	pA->right      = x->right;
	x->right->left = pB;
	x->right->height =
	    max(height(x->right->left), height(x->right->right)) + 1;
	pA->height = max(height(pA->left), height(pA->right)) + 1;
	x->right   = pA;
	pB	   = pA->left;
	pA->left   = x;
	x->right   = pB;
	x->height  = max(height(x->left), height(x->right)) + 1;
	pA->height = max(height(pA->left), height(pA->right)) + 1;
	return pA;
}

Node treeDelete(Node x, int k)
{
	if (x == NULL)
		return x;
	if (k < x->key)
		x->left = treeDelete(x->left, k);
	else if (k > x->key)
		x->right = treeDelete(x->right, k);
	else {
		if ((x->left == NULL) || (x->right == NULL)) {
			Node temp = x->left ? x->left : x->right;

			if (temp == NULL) {
				temp = x;
				x    = NULL;
			} else
				*x = *temp;
			free(temp);
		} else {
			Node temp = treeMinimum(x->right);
			x->key	  = temp->key;
			x->right  = treeDelete(x->right, temp->key);
		}
	}
	if (x == NULL)
		return x;
	x->height = 1 + max(height(x->left), height(x->right));

	int BF	= balance(x);
	int BF1 = balance(x->left);
	int BF2 = balance(x->right);

	if (BF > 1 && BF1 >= 0)
		return LL(x);

	if (BF < -1 && BF2 <= 0)
		return RR(x);

	if (BF > 1 && BF1 < 0)
		return LR(x);

	if (BF < -1 && BF2 > 0)
		return RL(x);

	return x;
}

Node newNode(int k)
{
	Node z	  = (Node)malloc(sizeof(node));
	z->key	  = k;
	z->height = 1;
	z->p	  = NULL;
	z->left	  = NULL;
	z->right  = NULL;
	return z;
}

Node treeInsert(Node x, int k)
{

	if (x == NULL)
		return (newNode(k));

	if (k < x->key)
		x->left = treeInsert(x->left, k);
	else if (k > x->key)
		x->right = treeInsert(x->right, k);
	else
		return x;

	x->height = 1 + max(height(x->left), height(x->right));

	int BF = balance(x);

	if (BF > 1 && k < x->left->key)
		return LL(x);

	if (BF < -1 && k > x->right->key)
		return RR(x);

	if (BF > 1 && k > x->left->key)
		return LR(x);

	if (BF < -1 && k < x->right->key)
		return RL(x);

	return x;
}

Node treeSearch(Tree T, Node x, int k)
{
	if (x == NULL) {
		return treeInsert(T->root, k);
	} else if (k == x->key) {
		return treeDelete(T->root, k);
	}
	if (k < x->key)
		treeSearch(T, x->left, k);
	else
		treeSearch(T, x->right, k);
}

int maxDepth(Node x)
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

void print(Node x)
{
	if (x != NULL) {
		printf("(C%d", x->key);
		print(x->left);
		print(x->right);
		printf(")");
	} else
		printf("()");
}

int main()
{
	Tree T = create();
	int i, n, valor;
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		scanf("%d", &valor);
		T->root = treeInsert(T->root, valor);
	}
	scanf("%d", &valor);
	T->root = treeSearch(T, T->root, valor);
	print(T->root);
	return 0;
}
