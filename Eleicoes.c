#include <stdio.h>

void zerarvetor(int E[], int c)
{
	int i;
	for (i = 0; i < c + 1; i++)
		E[i] = 0;
}

int eleitores(int E[], int A[], int v, int c)
{
	int i, cont = 0;
	for (i = 0; i < v; i++) {
		if (A[i] >= 1 && A[i] <= c)
			E[A[i]] += 1;
		else
			cont++;
	}
	return cont;
}

int maiorvalor(int E[], int c, int *pos, int primeiro)
{
	int i, maior = 0;
	for (i = 1; i < c + 1; i++) {
		if (E[i] > maior && i != primeiro) {
			maior = E[i];
			*pos  = i;
		}
	}
	return maior;
}

int primeirotur(int primeiro, int segundo, float maiorpr, float maiorse)
{
	if (maiorpr == maiorse && primeiro < segundo && maiorpr >= 50) {
		printf("%d %.2f", primeiro, maiorpr);
		return 0;
	} else if (maiorpr == maiorse && primeiro > segundo && maiorpr >= 50) {
		printf("%d %.2f", segundo, maiorse);
		return 0;
	} else if (primeiro == 0) {
		printf("0");
		return 0;
	} else if (maiorpr == maiorse && primeiro > segundo && maiorpr < 50)
		printf("%d %.2f", segundo, maiorse);
	else
		printf("%d %.2f", primeiro, maiorpr);
}

int segundotur(int P[], int S[], int T[], int E[], int v, int primeiro,
	       int segundo, float maiorpr, float maiorse)
{
	printf("\n");
	int i, cont = 0;

	for (i = 0; i < v; i++) {
		if (P[i] == primeiro || P[i] == segundo)
			;
		else if (S[i] == primeiro || S[i] == segundo)
			E[S[i]] += 1;
		else if (T[i] == primeiro || T[i] == segundo)
			E[T[i]] += 1;
		else
			cont++;
	}

	if (E[primeiro] > E[segundo]) {
		maiorpr = ((float)E[primeiro] / (v - cont)) * 100;
		printf("%d %.2f", primeiro, maiorpr);
		return 0;
	} else if (E[primeiro] < E[segundo]) {
		maiorse = ((float)E[segundo] / (v - cont)) * 100;
		printf("%d %.2f", segundo, maiorse);
		return 0;
	} else if (primeiro < segundo) {
		maiorpr = ((float)E[primeiro] / (v - cont)) * 100;
		printf("%d %.2f", primeiro, maiorpr);
		return 0;
	} else {
		maiorse = ((float)E[segundo] / (v - cont)) * 100;
		printf("%d %.2f", segundo, maiorse);
		return 0;
	}
}

int main()
{
	int i, v, c, cont = 0, primeiro, segundo;
	float maiorpr = 0, maiorse = 0;
	scanf("%d", &v);
	scanf("%d", &c);

	int P[v], S[v], T[v], E[c + 1];

	for (i = 0; i < v; i++) {
		scanf("%d", &P[i]);
		scanf("%d", &S[i]);
		scanf("%d", &T[i]);
	}

	zerarvetor(E, c);
	cont = eleitores(E, P, v, c);

	if (cont == v) {
		printf("0");
		return 0;
	}

	maiorpr = maiorvalor(E, c, &primeiro, 0);
	maiorse = maiorvalor(E, c, &segundo, primeiro);

	maiorpr = (maiorpr / (v - cont)) * 100;
	maiorse = (maiorse / (v - cont)) * 100;

	primeirotur(primeiro, segundo, maiorpr, maiorse);

	if (maiorpr < 50) {
		segundotur(P, S, T, E, v, primeiro, segundo, maiorpr, maiorse);
	}
	return 0;
}