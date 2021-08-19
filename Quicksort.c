/*O Quicksort é um algoritmo considerado muito rápido para a maioria das
situações. Considere o algoritmo abaixo do Quicksort, em que o pivô
escolhido como uma mediana de 3 valores, onde esse três valores devem
ser definidos como: a) primeiro elemento do intervalo considerado do vetor,
b) o elemento na posição do meio e c) o último elemento, de acordo com o
pseudo-código a seguir:
 //Escolha do Pivo por mediana de 3
 meio = (p+r)/2;
 a = A[p];
 b = A[meio];
 c = A[r];
 medianaIndice = 0; //índice da mediana (zero para inicio)
 //A sequência de if...else a seguir verifica qual é a mediana
 if (a < b)
 if (b < c) //a < b && b < c
 medianaIndice = meio;
 else
 if (a < c) //a < c && c <= b
 medianaIndice = r;
 else //c <= a && a < b
 medianaIndice = p;
 else
 if (c < b) //c < b && b <= a
 medianaIndice = meio; 
 eles
 if (c < a) //b <= c && c < a
 medianaIndice = r;
 else //b <= a && a <= c
 medianaIndice = p;
 //coloca o elemento da mediana no fim para poder usar o
 //Quicksort do Cormen
 trocar(A, medianaIndice, r)
 //Restante do código do algoritmo de particao (Cormen)
 ...
Você deve implementar um programa que leia da entrada um conjunto de
informações sobre N pessoas contendo o nome de cada pessoa com até 15
caracteres e a sua idade. O seu programa deverá utilizar o algoritmo do
Quicksort com escolha do pivo por mediana de 3, conforme indicado acima,
e que ordene-os de forma crescente por idade. Posteriormente deve-se
verificar se o resultado da ordenação é estável, ou seja, se pessoas com a
mesma idade foram mantidas na mesma ordem relativa da entrada. Após a
ordenação, você deve imprimir uma região indicada da lista ordenada.
Entrada
A primeira linha da entrada contém o número N (2 ≤ N ≤ 105.000) de pessoas a serem
ordenadas. Nas próximas N linhas são apresentados, em cada linha, um nome de até 15
caracteres e um inteiro representando a idade. A linha seguinte contém dois números P
(1 ≤ P ≤ N) da posição do primeiro nome a ser impresso e o número M (1 ≤ M ≤ N-P+1) de
pessoas a serem impressas partir do P-éssimo nome.
Saída
Na primeira linha da saída, imprima “yes” se a ordenação for estável, ou “no”, caso
contrário. Nas próximas M linhas, imprima os M nomes e idades presentes a partir da Péssima posição da lista ordenada, uma pessoa a cada linha.*/

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
