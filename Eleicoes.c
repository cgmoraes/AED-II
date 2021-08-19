/*Em tempo de crise, tal qual ocorre no momento com o Covid-19, tudo que compõe orçamento de
governos e instituições deve ser repensando para redução de gastos. Eleições em muitos lugares do mundo são
realizadas em 2 turnos, entretanto, pode-se gerar alguma economia de recursos se puderem ser realizadas em
apenas 1 turno. Porém, a não realização de um segundo turno tem o potencial de eleger um candidato que tenha
um alto percentual de rejeição e que possivelmente não ganharia um segundo turno.
Com o objetivo de tornar eleições com 2 turnos mais econômica, uma universidade está propondo um
procedimento inovador para eleição de reitor para ser realizado em um único dia, onde cada eleitor pode votar em
até 3 candidatos, em ordem de sua preferência, ou seja, o primeiro candidato escolhido é o de maior preferência, e
assim sucessivamente. Para contabilização de votos no primeiro turno apenas os votos em primeira opção são
contabilizados. Caso não haja vencedor no primeiro turno com pelo menos 50% dos votos válidos, um segundo
turno virtual é realizado entre os 2 primeiros candidatos mais votados na eleição de primeiro turno sem realizar
outra consulta, onde, a escolha em qualquer das 3 opções feitas pelos eleitores pode ser contabilizada como um
único voto válido para o segundo turno.
Em uma eleição com C candidatos, cada candidato possui um número único entre 1 e C. Qualquer voto
com valor menor do que 1 ou maior do que C é considerado como voto inválido. Para um candidato vencer no
primeiro turno, ele precisa conquistar pelo menos 50% dos votos válidos. Uma eleição sem nenhum voto válido
no primeiro turno não possui um resultado válido. Empates em número de votos são resolvidos de acordo com o
número dos candidatos. Se dois candidatos empatarem em qualquer um dos turnos, a ordem entre esses candidatos
na classificação é definida de acordo com a ordem crescente dos números desses candidatos (considera-se que o
candidato de menor número é o de maior idade e, portanto, de maior prioridade).
Caso nenhum candidato tenha conquistado pelo menos 50% dos votos em primeira opção, então um
segundo turno virtual é realizado. No segundo turno, o voto de cada eleitor pode ser contabilizado no máximo
uma vez. Se o eleitor não votou em nenhum dos 2 candidatos que disputam o segundo turno em nenhuma das 3
opções, então o seu voto não é computado como voto válido no segundo turno. Caso contrário, o voto de sua
maior preferência em algum candidato que concorre no segundo turno é contado como voto válido ao candidato
escolhido. Por exemplo, em um segundo turno disputado entre os candidatos 2 e 3, se um eleitor votou nos
candidatos 1 2 3, então o seu voto vai para o candidato 2 apenas, pois, em caso do candidato 1 não passar do
primeiro turno, considera-se que o eleitor escolheria o candidato 2 em um segundo turno com a participação do
candidato 2 e qualquer outro candidato.
A sua tarefa é escrever um programa que realize a contagem de votos em até 2 turnos conforme as regras
propostas das eleições econômicas.
Entrada
A primeira linha de um caso de teste contém os inteiros V (1 ≤ V ≤ 10.000), indicando o número de
eleitores votantes, e C, indicando o número de candidatos (1 ≤ C ≤ 100). Nas próximas V linhas, são apresentados
os votos de cada eleitor votante. Em cada uma dessas linhas, são fornecidos 3 inteiros com as escolhas, em ordem
de preferência, de um eleitor.
Saída
Caso não haja nenhum voto válido em primeira opção, imprima apenas o número 0. Caso contrário, o seu
programa deve imprimir na primeira linha da saída o número do candidato vencedor do primeiro turno e a
porcentagem de votos com 2 dígitos de precisão, separados por um espaço em branco. Caso o vencedor do
primeiro turno tenha vencido com menos de 50% dos votos válidos, você deve imprimir na segunda linha o
número do vencedor do segundo turno e sua porcentagem de votos com 2 dígitos de precisão, separados por um
espaço em branco. Para os cálculos da porcentagens, deve-se considerar apenas os votos válidos.*/

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
