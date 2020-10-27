#include "stdio.h"
#include "stdlib.h"

enum Lados { ESQ, DIR };

typedef int TChave;

typedef struct {
	TChave chave;
} TItem;

typedef struct SNo *TArvBin;

typedef struct SNo {
	TItem item;
	int cor;
	struct SNo *lado[2];
} TNo;

TArvBin raiz = NULL;

int main()
{
	TArvBin novoNo(int item);
	void remover(int item);
	void imprime(TArvBin x);
	void inserir(int item);
	void verifica(int valor);
	int ehNegro(TArvBin No);
	int alturaN(TArvBin x);
	int busca(TArvBin x, int valor);
	int i, n, valor;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &valor);
		inserir(valor);
	}

	scanf("%d", &valor);
	printf("%d\n", alturaN(raiz));
	imprime(raiz);

	verifica(valor);

	printf("\n%d\n", alturaN(raiz));
	imprime(raiz);
	return 0;
}

void remover(int item)
{
	TArvBin pilha[98], z, x, y, a, b, c;
	int direcao[98], alt = 0, diferenca, i;
	int cor;

	if (!raiz) {
		return;
	}

	z = raiz;
	while (z != NULL) {
		if ((item - z->item.chave) == 0)
			break;
		diferenca      = (item - z->item.chave) > 0 ? 1 : 0;
		pilha[alt]     = z;
		direcao[alt++] = diferenca;
		z	       = z->lado[diferenca];
	}

	if (z->lado[DIR] == NULL) {
		if ((z == raiz) && (z->lado[ESQ] == NULL)) {
			free(z);
			raiz = NULL;
		} else if (z == raiz) {
			raiz = z->lado[ESQ];
			free(z);
		} else {
			pilha[alt - 1]->lado[direcao[alt - 1]] = z->lado[ESQ];
		}
	} else {
		x = z->lado[DIR];
		if (x->lado[ESQ] == NULL) {
			x->lado[ESQ] = z->lado[ESQ];
			cor	     = x->cor;
			x->cor	     = z->cor;
			z->cor	     = cor;

			if (z == raiz) {
				raiz = x;
			} else {
				pilha[alt - 1]->lado[direcao[alt - 1]] = x;
			}

			direcao[alt] = 1;
			pilha[alt++] = x;
		} else {
			i = alt++;
			while (1) {
				direcao[alt] = 0;
				pilha[alt++] = x;
				y	     = x->lado[ESQ];
				if (!y->lado[ESQ])
					break;
				x = y;
			}

			direcao[i] = 1;
			pilha[i]   = y;
			if (i > 0)
				pilha[i - 1]->lado[direcao[i - 1]] = y;

			y->lado[ESQ] = z->lado[ESQ];

			x->lado[ESQ] = y->lado[DIR];
			y->lado[DIR] = z->lado[DIR];

			if (z == raiz) {
				raiz = y;
			}

			cor    = y->cor;
			y->cor = z->cor;
			z->cor = cor;
		}
	}

	if (alt < 1)
		return;

	if (z->cor == 0) {
		while (1) {
			a = pilha[alt - 1]->lado[direcao[alt - 1]];
			if (a && a->cor == 1) {
				a->cor = 0;
				break;
			}

			if (alt < 2)
				break;

			if (direcao[alt - 2] == 0) {
				c = pilha[alt - 1]->lado[DIR];

				if (!c)
					break;

				if (c->cor == 1) {
					pilha[alt - 1]->cor = 1;
					c->cor		    = 0;
					pilha[alt - 1]->lado[DIR] =
					    c->lado[ESQ];
					c->lado[ESQ] = pilha[alt - 1];

					if (pilha[alt - 1] == raiz) {
						raiz = c;
					} else {
						pilha[alt - 2]
						    ->lado[direcao[alt - 2]] =
						    c;
					}
					direcao[alt]   = 0;
					pilha[alt]     = pilha[alt - 1];
					pilha[alt - 1] = c;
					alt++;

					c = pilha[alt - 1]->lado[DIR];
				}

				if ((!c->lado[ESQ] || c->lado[ESQ]->cor == 0) &&
				    (!c->lado[DIR] || c->lado[DIR]->cor == 0)) {
					c->cor = 1;
				} else {
					if (!c->lado[DIR] ||
					    c->lado[DIR]->cor == 0) {
						b	     = c->lado[ESQ];
						c->cor	     = 1;
						b->cor	     = 0;
						c->lado[ESQ] = b->lado[DIR];
						b->lado[DIR] = c;
						c = pilha[alt - 1]->lado[DIR] =
						    b;
					}
					c->cor = pilha[alt - 1]->cor;
					pilha[alt - 1]->cor = 0;
					c->lado[DIR]->cor   = 0;
					pilha[alt - 1]->lado[DIR] =
					    c->lado[ESQ];
					c->lado[ESQ] = pilha[alt - 1];
					if (pilha[alt - 1] == raiz) {
						raiz = c;
					} else {
						pilha[alt - 2]
						    ->lado[direcao[alt - 2]] =
						    c;
					}
					break;
				}
			} else {
				c = pilha[alt - 1]->lado[ESQ];
				if (!c)
					break;

				if (c->cor == 1) {
					pilha[alt - 1]->cor = 1;
					c->cor		    = 0;
					pilha[alt - 1]->lado[ESQ] =
					    c->lado[DIR];
					c->lado[DIR] = pilha[alt - 1];

					if (pilha[alt - 1] == raiz) {
						raiz = c;
					} else {
						pilha[alt - 2]
						    ->lado[direcao[alt - 2]] =
						    c;
					}
					direcao[alt]   = 1;
					pilha[alt]     = pilha[alt - 1];
					pilha[alt - 1] = c;
					alt++;

					c = pilha[alt - 1]->lado[ESQ];
				}
				if ((!c->lado[ESQ] || c->lado[ESQ]->cor == 0) &&
				    (!c->lado[DIR] || c->lado[DIR]->cor == 0)) {
					c->cor = 1;
				} else {
					if (!c->lado[ESQ] ||
					    c->lado[ESQ]->cor == 0) {
						b	     = c->lado[DIR];
						c->cor	     = 1;
						b->cor	     = 0;
						c->lado[DIR] = b->lado[ESQ];
						b->lado[ESQ] = c;
						c = pilha[alt - 1]->lado[ESQ] =
						    b;
					}
					c->cor = pilha[alt - 1]->cor;
					pilha[alt - 1]->cor = 0;
					c->lado[ESQ]->cor   = 0;
					pilha[alt - 1]->lado[ESQ] =
					    c->lado[DIR];
					c->lado[DIR] = pilha[alt - 1];
					if (pilha[alt - 1] == raiz) {
						raiz = c;
					} else {
						pilha[alt - 2]
						    ->lado[direcao[alt - 2]] =
						    c;
					}
					break;
				}
			}
			alt--;
		}
	}
}

int ehNegro(TArvBin No) { return (No == NULL) || (No->cor == 0); }

void imprime(TArvBin x)
{
	if (x != NULL) {
		if (ehNegro(x))
			printf("(N%d", x->item.chave);
		else
			printf("(R%d", x->item.chave);
		imprime(x->lado[ESQ]);
		imprime(x->lado[DIR]);
		printf(")");
	} else
		printf("()");
}

int alturaN(TArvBin x)
{
	int altN = 0;
	while (x != NULL) {
		if (x->cor == 0)
			altN++;
		x = x->lado[DIR];
	}
	return altN;
}

int busca(TArvBin x, int valor)
{
	if (x == NULL) {
		return 0;
	} else if (x->item.chave == valor) {
		return 1;
	} else {
		if (valor > x->item.chave) {
			return busca(x->lado[DIR], valor);
		} else {
			return busca(x->lado[ESQ], valor);
		}
	}
}

TArvBin novoNo(int item)
{
	TArvBin No;
	No	       = (TArvBin)malloc(sizeof(TNo));
	No->item.chave = item;
	No->cor	       = 1;
	No->lado[ESQ] = No->lado[DIR] = NULL;
	if (raiz == NULL)
		No->cor = 0;
	return No;
}

void inserir(int item)
{
	TArvBin pilha[98], z, No, x, y;
	int direcao[98], alt = 0, i;
	z = raiz;
	if (!raiz) {
		raiz = novoNo(item);
		return;
	}

	pilha[alt]     = raiz;
	direcao[alt++] = 0;
	while (z != NULL) {
		if (z->item.chave == item) {
			return;
		}
		i	       = (item - z->item.chave) > 0 ? 1 : 0;
		pilha[alt]     = z;
		z	       = z->lado[i];
		direcao[alt++] = i;
	}
	pilha[alt - 1]->lado[i] = No = novoNo(item);
	while ((alt >= 3) && (pilha[alt - 1]->cor == 1)) {
		if (direcao[alt - 2] == 0) {
			y = pilha[alt - 2]->lado[DIR];
			if (y != NULL && y->cor == 1) {
				pilha[alt - 2]->cor = 1;
				pilha[alt - 1]->cor = y->cor = 0;
				alt			     = alt - 2;
			} else {
				if (direcao[alt - 1] == 0) {
					y = pilha[alt - 1];
				} else {
					x	     = pilha[alt - 1];
					y	     = x->lado[DIR];
					x->lado[DIR] = y->lado[ESQ];
					y->lado[ESQ] = x;
					pilha[alt - 2]->lado[ESQ] = y;
				}
				x	     = pilha[alt - 2];
				x->cor	     = 1;
				y->cor	     = 0;
				x->lado[ESQ] = y->lado[DIR];
				y->lado[DIR] = x;
				if (x == raiz) {
					raiz = y;
				} else {
					pilha[alt - 3]->lado[direcao[alt - 3]] =
					    y;
				}
				break;
			}
		} else {
			y = pilha[alt - 2]->lado[ESQ];
			if ((y != NULL) && (y->cor == 1)) {
				pilha[alt - 2]->cor = 1;
				pilha[alt - 1]->cor = y->cor = 0;
				alt			     = alt - 2;
			} else {
				if (direcao[alt - 1] == 1) {
					y = pilha[alt - 1];
				} else {
					x	     = pilha[alt - 1];
					y	     = x->lado[ESQ];
					x->lado[ESQ] = y->lado[DIR];
					y->lado[DIR] = x;
					pilha[alt - 2]->lado[DIR] = y;
				}
				x	     = pilha[alt - 2];
				y->cor	     = 0;
				x->cor	     = 1;
				x->lado[DIR] = y->lado[ESQ];
				y->lado[ESQ] = x;
				if (x == raiz) {
					raiz = y;
				} else {
					pilha[alt - 3]->lado[direcao[alt - 3]] =
					    y;
				}
				break;
			}
		}
	}
	raiz->cor = 0;
}

void verifica(int valor)
{
	if (!busca(raiz, valor)) {
		inserir(valor);
	} else
		remover(valor);
}