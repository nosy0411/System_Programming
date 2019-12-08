#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#define Tolower(c) c>='A'&& c<='Z' ? c+'a'-'A' : c

#define N 50

typedef struct node {
	char word[N];
	struct node* nxt;
	struct node* prv;
	int count;
}node;

typedef struct {
	node* head;
}links;

void strswap(char a[N], char b[N]) {
	char c[N];
	strcpy(c, a);
	strcpy(a, b);
	strcpy(b, c);
}

void insrt(links* x, char w[N]) {
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
	strcpy(n->nxt->word,w);
	return;
}

void countup(links* x, char w[N]) {
	node* n = x->head;
	if (n == NULL) {
		insrt(x, w);
		return;
	}
	while (n != NULL) {
		if (strcmp(n->word, w) == 0) {
			n->count++;
			node* n2 = n->prv;
		ii:
			if (n2 != NULL && n->count > n2->count) {
				n2 = n2->prv;
				goto ii;
			}
			else {
				if (n2 == NULL) n2 = x->head;
				strswap(n->word, n2->word);
				n->count--;
				n2->count++;
				return;
			}
		}
		else n = n->nxt;
	}
	insrt(x, w);
}

int wordkind(links l) {
	node* no = l.head;
	int val = 0;
	while (no!=NULL) {
		no = no->nxt;
		val++;
	}
	return val;
}

int wordcount(links l, int i) {
	node* no = l.head;
	int val = 0;
	for (; no != NULL && no->count != i; no = no->nxt);
	for (; no != NULL && no->count == i; no = no->nxt, val++);
	return val;
}

void printrank(links l) {
	node* no = l.head;
	node* no2 = l.head;
	int cnt;
	while (no != NULL) {
		if (no->nxt != NULL) {
			if (no->count != no->nxt->count) {
				cnt = wordcount(l, no->count);
				printf("\n%d  %d : ", no->count, cnt);
				for (no2 = l.head; no2->count != no->count; no2 = no2->nxt);
				for (; no2->count == no->count; no2 = no2->nxt) {
					printf("%s, ", no2->word);
				}
			}
		}
		no = no->nxt;
	}
	cnt = wordcount(l, 1);
	printf("\n1  %d : ", cnt);
	for (no2 = l.head; no2->count != 1; no2 = no2->nxt);
	for (; no2!=NULL; no2 = no2->nxt) {
		printf("%s, ", no2->word);
	}
}

int scanwords(FILE* f, links *l) {
	int state = 0;
	char c[N];
	char buf[2];
	int bb;
	int tot=0;
	char cc;
	while (1) {
		bb = fscanf(f, "%c", &cc);
		if (bb == EOF)break;
		if (state == 0) {
			if (!isalpha(cc))continue;
			else {
				cc = Tolower(cc);
				state = 1;
				sprintf(c,"%c", cc);
			}
		}
		else if (state == 1) {
			if (!isalpha(cc)) {
				state = 0;
				countup(l, c);
				tot++;
			}
			else {
				cc = Tolower(cc);
				sprintf(buf,"%c", cc);
				strcat(c, buf);
			}
		}
	}
	return tot;
}

int main() {
	links l;
	l.head = NULL;
	FILE* f;
	clock_t a, b;
	float tm;
	a = clock();
	f=fopen("/home/inhosecond/repositories/System_Programming/harrypotter_and_cano.txt", "r");
	int tot = scanwords(f, &l);
	printrank(l);
	fclose(f);
	b = clock();
	tm = (float)(b - a) / CLOCKS_PER_SEC;
	printf("\n\n%f", tm);
	printf("%d", wordkind(l));
	printf("\n%d", tot);
}