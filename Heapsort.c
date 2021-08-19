/*Implemente o algoritmo de ordenação HeapSort, conforme
especificado nos slides e video-aula (de acordo com o livro T. Cormen).
Escreva um procedimento separado para as seguintes operações: a) maxheapfy(...), b) build-max-heap(…), c) heap-extract-max(…) e d)
heapSort(…).
Entrada
A entrada consiste de duas linhas, sendo a primeira contendo um número
inteiro N (1 ≤ N ≤ 10.000) que especifica a quantidade de valores do arranjo original a
serem ordenados.
A segunda linha contém uma sequência de números inteiros separados por
espaços, onde cada número inteiro Ai pode estar na faixa: 0 ≤ Ai ≤ 10.000,
correspondendo ao arranjo original a ser ordenado.
Saída
A saída consiste de duas linhas, sendo a primeira o vetor rearranjado após a
chamada a rotina build-max-heap(…). A segunda linha corresponde ao vetor final
devidamente ordenado.*/

#include <stdio.h>
#include <stdlib.h>

void PRINT_VECTOR(int V[], int n)
{
	int i;
	for (i = 1; i <= n; i++)
		printf("%d ", V[i]);
	printf("\n");
}

void swap(int *a, int *b)
{
	int aux;
	aux = *a;
	*a  = *b;
	*b  = aux;
}

void MAX_HEAPIFY(int A[], int i, int n)
{
	int l = 2 * i, r = (2 * i) + 1, max;
	if ((l <= n) && (A[l] > A[i]))
		max = l;
	else
		max = i;
	if ((r <= n) && (A[r] > A[max]))
		max = r;
	if (max != i) {
		swap(&A[i], &A[max]);
		MAX_HEAPIFY(A, max, n);
	}
}

void BUILD_MAX_HEAP(int A[], int n)
{
	int i;
	for (i = n / 2; i > 0; i--) {
		MAX_HEAPIFY(A, i, n);
	}
	PRINT_VECTOR(A, n);
}

int HEAP_EXTRACT_MAX(int A[], int n)
{
	if (n < 1)
		return 0;
	int max = A[1];
	A[1]	= A[n];
	n--;
	MAX_HEAPIFY(A, 1, n);
	return max;
}

void HEAPSORT(int A[], int n)
{
	BUILD_MAX_HEAP(A, n);
	int i, V[n];
	for (i = n; i > 0; i--)
		V[i] = HEAP_EXTRACT_MAX(A, i);
	PRINT_VECTOR(V, n);
}

int main()
{
	int i, n;
	scanf("%d", &n);
	int A[n + 1];
	for (i = 1; i < n + 1; i++)
		scanf("%d", &A[i]);
	HEAPSORT(A, n);
	return 0;
}
