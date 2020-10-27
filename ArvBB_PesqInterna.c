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