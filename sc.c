#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

typedef struct node {
	char word[20];
	struct node* nxt;
	struct node* prv;
	int count;
}node;

typedef struct {
	node* head;
}links;

void strswap(char a[20], char b[20]) {
	char c[20];
	strcpy(c, a);
	strcpy(a, b);
	strcpy(b, c);
}

void insrt(links* x, char w[20]) {
	node* n = x->head;
	if (n == NULL) {
		node* y = (node*)malloc(sizeof(node));
		x->head = y;
		strcpy(x->head->word, w);
		x->head->prv = NULL;
		x->head->nxt = NULL;
		x->head->count = 1;
		return;
	}
	while (n->nxt != NULL) {
		n = n->nxt;
	}
	n->nxt = (node*)malloc(sizeof(node));
	n->nxt->prv = n;
	n->nxt->nxt = NULL;
	n->nxt->count = 1;
	strcpy(n->nxt->word, w);
	return;
}

void countup(links* x, char w[20]) {
	node* n = x->head;
	if (n == NULL) {
		insrt(x, w);
			return;
		}
	while (n != NULL) {
		if (strcmp(n->word, w) == 0) {
			n->count++;
		ii:
			if (n->prv != NULL && n->count > n->prv->count) {
				strswap(n->word, n->prv->word);
				int i = n->count;					
				n->count = n->prv->count;
				n->prv->count = i;
				n = n->prv;
				goto ii;
			}
			n = n->nxt;
		}
		else n = n->nxt;
	}
}

int main() {
	links l;
	l.head = NULL;
	FILE* f;
	char c[20];
	char buf[2];
	int bb;
	int cou = 0;
	char cc;
	clock_t a, b;
	float tm;
	a = clock();
	f=fopen("/home/inhosecond/repositories/System_Programming/cano.txt", "r");
	int state = 0;

	while (1) {
		bb = fscanf(f, "%c", &cc);
		if (bb == EOF)break;
		if (state == 0) {
			if (!isalpha(cc))continue;
			else {
				if(cc<='Z')cc+=('a'-'A');
				state = 1;
				sprintf(c, "%c", cc);
			}
		}
		else if (state == 1) {
			if (!isalpha(cc)) {
				state = 0;
				printf("%s\t", c);
				countup(&l, c);
			}
			else {
				if(cc<='Z')cc+=('a'-'A');
				sprintf(buf, "%c", cc);
				strcat(c, buf);
			}
		}
	}
	b = clock();
	tm = (float)(b - a) / CLOCKS_PER_SEC;
	printf("\ntime %f\n", tm);
	printf("\n%s (count) %d\n", l.head->word,l.head->count);
	fclose(f);
}