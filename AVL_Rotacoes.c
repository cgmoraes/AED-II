/*Aten¸c˜ao:
1. E/S: tanto a entrada quanto a sa´ıda de dados devem ser “secas”, ou seja, n˜ao devem
apresentar frases explicativas.
2. Identificadores de vari´aveis: escolha nomes apropriados.
3. Documenta¸c˜ao: inclua cabe¸calho, coment´arios e indenta¸c˜ao no programa.
• Descri¸c˜ao:
Implemente as opera¸c˜oes b´asicas do algoritmo de balanceamento em ´arvores AVL. Escreva
um procedimento separado para as seguintes opera¸c˜oes: (1) Altura: retorna a altura de um
dado n´o; (2) FB: retorna o fator de balanceamento de um dado n´o; (3) ArvoreAVL: verifica
se uma ´arvore ´e ou n˜ao AVL; (4) LL, RR, LR, RL: executa uma rota¸c˜ao em um dado n´o; (5)
BalancaNo: verifica um dado n´o e efetua o seu balanceamento, caso necess´ario. Deve-se
ainda efetuar uma ´unica rota¸c˜ao no n´o raiz, de acordo com as regras de balanceamento de
uma ´arvore AVL.
• Entrada:
A entrada consiste de uma ´arvore bin´aria de busca (ABB) representada por parˆenteses aninhados. Um exemplo pode ser encontrado abaixo.
• Sa´ıda:
Imprima, na primeira linha, a altura da ´arvore bin´aria de busca (ABB) de entrada e, em
seguida (segunda linha), a pr´opria ´arvore usando a representa¸c˜ao por parˆenteses aninhados.
Posteriormente, deve-se computar uma nova ABB onde se efetuou uma rota¸c˜ao LL, RR, LR
ou RL aplicada apenas no n´o raiz. A rota¸c˜ao dever´a ser efetuada de acordo com as regras
de balanceamento de uma ´arvore AVL.
Ap´os computada a nova ´arvore, deve-se imprimir o tipo de rota¸c˜ao efetuada (RR, LL, RL ou
LR, usando sempre letras ma´ısculas) no n´o raiz na terceira linha. Depois, na quarta linha,
imprima a altura desta ABB transformada. Finalmente, na quinta e ´ultima linha, imprima
pr´opria ABB de sa´ıda usando a representa¸c˜ao por parˆenteses aninhados.
Obs: Todas as entradas exigem algum tipo de rota¸c˜ao no n´o raiz.*/

#include "stdio.h"
#include "stdlib.h"

typedef int TChave;

typedef struct {
	TChave Chave;
} TItem;

typedef struct SNo *TArvBin;

typedef struct SNo {
	TItem Item;
	TArvBin Esq, Dir;
} TNo;

TArvBin Carrega()
{
	char c;
	TArvBin No;
	scanf("%c", &c);
	if (c == '(') {
		scanf("%c", &c);
		if (c == 'C') {
			No = (TArvBin)malloc(sizeof(TNo));
			scanf("%d", &No->Item.Chave);
			No->Esq = Carrega();
			No->Dir = Carrega();
			scanf("%c", &c);
		} else if (c == ')')
			No = NULL;
	}
	return No;
}

void Imprime(TArvBin No)
{
	if (No != NULL) {
		printf("(C%d", No->Item.Chave);
		Imprime(No->Esq);
		Imprime(No->Dir);
		printf(")");
	} else
		printf("()");
}

int Altura(TArvBin No)
{
	if (No == NULL)
		return 0;
	else {
		int EAltura = Altura(No->Esq);
		int DAltura = Altura(No->Dir);
		if (EAltura > DAltura)
			return ++EAltura;
		else
			return ++DAltura;
	}
}

int FB(TArvBin No)
{
	int Esq, Dir;
	Esq = Altura(No->Esq);
	Dir = Altura(No->Dir);
	return Esq - Dir;
}

void Rotacao(TArvBin No)
{
	TArvBin pA = NULL, pB = NULL, pC = NULL;
	if (No != NULL && No->Esq != NULL && FB(No) > 1 && FB(No->Esq) > 0) {
		pA	= No;
		pB	= pA->Esq;
		pA->Esq = pB->Dir;
		pB->Dir = pA;
		pA	= pB;
		printf("LL\n");
		printf("%d\n", Altura(pA) - 1);
		Imprime(pA);
	} else if (No != NULL && No->Dir != NULL && FB(No) < -1 &&
		   FB(No->Dir) < 0) {
		pA	= No;
		pB	= pA->Dir;
		pA->Dir = pB->Esq;
		pB->Esq = pA;
		pA	= pB;
		printf("RR\n");
		printf("%d\n", Altura(pA) - 1);
		Imprime(pA);
	} else if (No != NULL && No->Esq != NULL && FB(No) > 1 &&
		   FB(No->Esq) < 0) {
		pA	= No;
		pB	= pA->Esq;
		pC	= pB->Dir;
		pB->Dir = pC->Esq;
		pC->Esq = pB;
		pA->Esq = pC->Dir;
		pC->Dir = pA;
		pA	= pC;
		printf("LR\n");
		printf("%d\n", Altura(pA) - 1);
		Imprime(pA);
	} else if (No != NULL && No->Dir != NULL && FB(No) < -1 &&
		   FB(No->Dir) > 0) {
		pA	= No;
		pB	= pA->Dir;
		pC	= pB->Esq;
		pB->Esq = pC->Dir;
		pC->Dir = pB;
		pA->Dir = pC->Esq;
		pC->Esq = pA;
		pA	= pC;
		printf("RL\n");
		printf("%d\n", Altura(pA) - 1);
		Imprime(pA);
	}
}

int main()
{
	TArvBin Raiz;
	Raiz = Carrega();

	printf("%d\n", Altura(Raiz) - 1);
	Imprime(Raiz);
	printf("\n");
	Rotacao(Raiz);

	return 0;
}
