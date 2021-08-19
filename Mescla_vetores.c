/*Instruções:
1. E/S: tanto a entrada quanto a saı́da de dados devem ser “secas”, ou seja,
não devem apresentar frases explicativas. Siga o modelo fornecido e apenas
complete as partes informadas (veja o exemplo abaixo).
2. Identificadores de variáveis: escolha nomes apropriados.
3. Documentação: inclua cabeçalho, comentários e indentação no programa.
4. Submeta o programa no sistema judge: http://judge.sjc.unifesp.br/ (acesso
remoto por VPN).
5. O programa pode ser escrito em C, C++ ou Java.
Descrição:
Implemente um algoritmo que mescle dois vetores de números inteiros já
ordenados e crie um terceiro vetor, igualmente ordenado de números inteiros.
Entrada:
A entrada consiste de 4 linhas onde a primeira define o tamanho do primeiro
vetor (array VETA), limitado a 100 elementos do tipo inteiro. Na segunda linha
deve-se informar cada elementos de VETA (sempre números inteiros positivos,
negativos ou zero). Na terceira e quarta linha o procedimento se repete mas para o
segundo array, ou seja, deve-se informar o tamanho de VETB e os elementos do
próprio array VETB.
Saı́da :
Imprima o vetor mesclado resultante com os números em ordem crescente.
*/

#include <stdio.h>

int main()
{
	int i, j, A, B, swap;

	scanf("%d", &A);
	int vetA[A];

	for (i = 0; i < A; i++) {
		scanf("%d", &vetA[i]);
	}

	scanf("%d", &B);
	int vetB[B];

	for (i = 0; i < B; i++) {
		scanf("%d", &vetB[i]);
	}

	int vetfinal[A + B];

	for (i = 0; i < A; i++) {
		vetfinal[i] = vetA[i];
	}

	for (i = 0; i < B; i++) {
		vetfinal[A + i] = vetB[i];
	}

	for (i = 0; i < A + B - 1; i++) {
		for (j = 0; j < A + B - i - 1; j++) {

			if (vetfinal[j] > vetfinal[j + 1]) {
				swap		= vetfinal[j];
				vetfinal[j]	= vetfinal[j + 1];
				vetfinal[j + 1] = swap;
			}
		}
	}

	for (i = 0; i < A + B; i++) {
		printf("%d ", vetfinal[i]);
	}

	return 0;
}
