#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	char nome[15];
	int idade;
	int posInicial;
} dados;

void swap(dados *a, dados *b)
{
	int i, c;
	char d[15];
	c	 = a->idade;
	a->idade = b->idade;
	b->idade = c;

	for (i = 0; i < 15; i++)
		d[i] = a->nome[i];

	for (i = 0; i < 15; i++)
		a->nome[i] = b->nome[i];

	for (i = 0; i < 15; i++)
		b->nome[i] = d[i];

	c	      = a->posInicial;
	a->posInicial = b->posInicial;
	b->posInicial = c;
}

int mediana(dados A[], int p, int r)
{
	int a, b, c, meio, medianaIndice;

	meio	      = (p + r) / 2;
	a	      = A[p].idade;
	b	      = A[meio].idade;
	c	      = A[r].idade;
	medianaIndice = 0;

	if (a < b) {
		if (b < c)
			medianaIndice = meio;
		else {
			if (a < c)
				medianaIndice = r;
			else
				medianaIndice = p;
		}
	} else {
		if (c < b)
			medianaIndice = meio;
		else {
			if (c < a)
				medianaIndice = r;
			else
				medianaIndice = p;
		}
	}

	swap(&A[medianaIndice], &A[r]);
}

int partition(dados A[], int p, int r)
{
	mediana(A, p, r);

	int i = p - 1, j, x = A[r].idade;

	for (j = p; j < r; j++) {
		if (A[j].idade <= x) {
			i++;
			swap(&A[i], &A[j]);
		}
	}

	swap(&A[i + 1], &A[r]);
	return i + 1;
}

void quicksort(dados A[], int p, int r)
{
	if (p < r) {
		int q;
		q = partition(A, p, r);
		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);
	}
}

void estabilidade(dados A[], int n)
{
	int i;
	for (i = 0; i < n - 1; i++) {
		if (A[i].idade == A[i + 1].idade &&
		    A[i].posInicial > A[i + 1].posInicial) {
			printf("no\n");
			return;
		}
	}
	printf("yes\n");
}

int main()
{
	int i, m, n, p;
	scanf("%d", &n);
	dados pessoa[n];

	for (i = 0; i < n; i++) {
		scanf("%s", pessoa[i].nome);
		scanf("%d", &pessoa[i].idade);
		pessoa[i].posInicial = i;
	}

	scanf("%d", &p);
	scanf("%d", &m);

	quicksort(pessoa, 0, n - 1);
	estabilidade(pessoa, n);

	for (i = p - 1; i < p + m - 1; i++) {
		printf("%s ", pessoa[i].nome);
		printf("%d", pessoa[i].idade);
		printf("\n");
	}
	return 0;
}