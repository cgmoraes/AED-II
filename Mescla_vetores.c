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