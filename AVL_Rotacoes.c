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