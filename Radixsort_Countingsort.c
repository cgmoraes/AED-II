/*O Counting sort é um algoritmo de ordenação adequado para ordenar N inteiros de valores 0 a k
e k=O(N). Porém, este método apresenta restrição para ser aplicado na classificação de um
conjunto de strings, pois para isso seria preciso realizar conversão de base numérica e k se
tornaria muito grande para strings compridas.
O Radix sort, por outro lado, pode ser aplicado para ordenação de strings utilizando o Counting
sort para ordenar a entrada em relação a apenas uma posição das strings por vez, sendo que cada
caracter seria considerado como um “dígito” do algoritmo. Considerando que strings podem ter
comprimentos diferentes, um caractere adicional (espaço em branco, ou o número 32 da tabela
ASCII em decimal, por exemplo) pode ser utilizado para preencher posições vazias de strings
mais curtas, para que todas strings tenham o mesmo comprimento d (tamanho da maior string).
Deve-se implementar um programa que leia da entrada um conjunto de nomes com até 15
caracteres cada (cada caractere é uma letra dentro dos intervalos [A, Z] e [a, z]) e que ordene-os
em ordem alfabética. Você deverá converter todas as letras maiúsculas para letras minúsculas
antes de realizar a ordenação.
A ordenação deve ser realizada utilizando o algoritmo de ordenação Radix sort e o Counting
sort para ordenar cada posição das strings. O número de dígitos d deve ser o comprimento da
maior string presente na entrada de cada caso de teste. Para cada “dígito”, você deve imprimir os
valores em cada posição do vetor auxiliar C após a execução da linha 8 do algoritmo Counting
sort apresentado acima. O vetor C deve ser de tamanho k=27, sendo a primeira posição
destinada ao caractere adicional (vazio) e as posições restantes referentes às 26 letras minúsculas
em ordem crescente (a, …, z). 
Após a ordenação, você deve imprimir uma região indicada da lista ordenada com os nomes em
letras minúsculas.
Entrada
A primeira linha da entrada contém o número N (2 ≤ N ≤ 100.000) referente a quantidade de
nomes a serem ordenados. As próximas N linhas devem conter os respectivos nomes de acordo
com a ordem de entrada, sendo um nome para cada linha.
A linha seguinte indica o que deverá ser impresso na saída, e contém dois números: P (1 ≤ P ≤
N) referente a posição do primeiro nome da lista ordenada a ser impresso, e o número M (1 ≤ M
≤ N-P+1) referente a quantidade de números a partir do P-ésimo nome da lista ordenada.
Saída
Para cada “dígito” i do Radix sort, imprima uma linha com os 27 valores do vetor C do
Counting sort. Nas próximas M linhas, imprima os M nomes presentes a partir da P-ésima
posição da lista ordenada, um nome a cada linha sem os caracteres adicionais. */

#include "stdio.h"

typedef struct word {
	char name[15];
} Words;

void printC(int C[])
{
	int i;
	for (i = 0; i < 27; i++)
		printf("%d ", C[i]);
	printf("\n");
}

void print(Words word[], int start, int end)
{
	int i;
	for (i = start; i < end; i++)
		printf("%s\n", word[i].name);
}

void countingSort(Words word[], int j, int n)
{
	int i, C[27] = {0};
	Words B[n];

	for (i = 0; i < n; i++) {
		if (word[i].name[j] == 32)
			C[0]++;
		else
			C[word[i].name[j] - 96]++;
	}

	for (i = 1; i < 27; i++)
		C[i] += C[i - 1];

	printC(C);

	for (i = n - 1; i >= 0; i--) {
		if (word[i].name[j] == 32) {
			B[C[0] - 1] = word[i];
			C[0]--;
		} else {
			B[C[word[i].name[j] - 96] - 1] = word[i];
			C[word[i].name[j] - 96]--;
		}
	}

	for (i = 0; i < n; i++)
		word[i] = B[i];
}

void radixSort(Words word[], int d, int n)
{
	int i;
	for (i = d - 1; i >= 0; i--)
		countingSort(word, i, n);
}

int lc_getD(Words word[], int n)
{
	int i, j, d = 0;
	for (i = 0; i < n; i++) {
		for (j = 1; word[i].name[j - 1] != 0; j++) {
			if (word[i].name[j - 1] < 97)
				word[i].name[j - 1] += 32;
			if (j > d)
				d = j;
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < d; j++) {
			if (word[i].name[j] == 0) {
				word[i].name[j]	    = 32;
				word[i].name[j + 1] = 0;
			}
		}
	}
	return d;
}

int main()
{
	int i, n, start, end;
	scanf("%d", &n);
	Words word[n];
	for (i = 0; i < n; i++)
		scanf("%s", word[i].name);
	scanf("%d %d", &start, &end);
	radixSort(word, lc_getD(word, n), n);
	print(word, start - 1, end + start - 1);
}
