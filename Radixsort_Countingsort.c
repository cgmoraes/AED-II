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