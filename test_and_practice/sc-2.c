#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#define Tolower(c) c>='A'&& c<='Z' ? c+'a'-'A' : c
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
	strcpy_s(c, 20, a);
	strcpy_s(a, 20, b);
	strcpy_s(b, 20, c);
}

void insrt(links* x, char w[20]) {		//���߿� ȿ���� ���� node*�� ���ڸ� ������ ���� 
	node* n = x->head;
	if (n == NULL) {
		node* y = (node*)malloc(sizeof(node));
		x->head = y;
		strcpy_s(x->head->word, 20, w);
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
	strcpy_s(n->nxt->word, 20, w);
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
				int i = n->count;							//������ �������ٴ� �� ���� ���Ҵٴ� �ǹ̶�, ���߿� ++, --�� ��ü ����. 
				n->count = n->prv->count;					//+������ �ٲٴ� �Ϳ��� ���� �����̶� �ٲٴ� ������ ��ü
				n->prv->count = i;
				n = n->prv;
				goto ii;
			}
			else {
				return;
			}
			n = n->nxt;		//���� �����־�
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
				printf("\n%d �� �ִ� �ܾ� %d����: ", no->count, cnt);
				for (no2 = l.head; no2->count != no->count; no2 = no2->nxt);			//���⵵ ������ ��ġ ����ϸ� ó������ ��ȸ�� �ʿ� ����
				for (; no2->count == no->count; no2 = no2->nxt) {
					printf("%s, ", no2->word);
				}
			}
		}
		no = no->nxt;
	}
	cnt = wordcount(l, 1);
	printf("\n1 �� �ִ� �ܾ� %d����: ", cnt);
	for (no2 = l.head; no2->count != 1; no2 = no2->nxt);
	for (; no2!=NULL; no2 = no2->nxt) {
		printf("%s, ", no2->word);
	}
}

int scanwords(FILE* f, links *l) {
	int state = 0;//0:ó��(�����̽��� ����), 1:�ܾ�, 2:�ܾ(1���¿��� �����̽��� ������) 
	char c[20];
	char buf[2];
	int bb;
	int tot=0;
	char cc;
	while (1) {
		bb = fscanf_s(f, "%c", &cc, 1);
		if (bb == EOF)break;
		if (state == 0) {
			if (!isalpha(cc))continue;
			else {
				cc = Tolower(cc);
				state = 1;
				sprintf_s(c, 20, "%c", cc);
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
				sprintf_s(buf, 2, "%c", cc);
				strcat_s(c, 20, buf);
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
	fopen_s(&f,"C:\\Users\\gsrid\\Desktop\\cano.txt", "r");
	int tot = scanwords(f, &l);
	printrank(l);
	fclose(f);
	b = clock();
	tm = (float)(b - a) / CLOCKS_PER_SEC;
	printf("\n\n%f��", tm);
	printf("%d", wordkind(l));
	printf("\n%d", tot);
	system("pause");
}
/*
���� ���α׷� :
�ܾ� ���� Ƚ������ ���(��������)
*/
