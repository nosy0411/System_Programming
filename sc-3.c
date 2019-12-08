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
	node* tail;
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
		x->tail=x->head;
		return;
	}

	x->tail->nxt = (node*)malloc(sizeof(node));
	x->tail->nxt->prv = x->tail;
	x->tail->nxt->nxt = NULL;
	x->tail->nxt->count = 1;
	strcpy(x->tail->nxt->word, w);
	x->tail=x->tail->nxt;
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
			int i = n->count;
			node* n2 = n;
		ii:
			if (n->prv != NULL && i > n->prv->count) {
				n = n->prv;
				goto ii;
			}
			else {
				if (n == n2)return;
				strswap(n->word, n2->word);
				n->count++;
				n2->count--;
				return;
			}
		}
		else n = n->nxt;
	}
	insrt(x, w);
}

void insert(links* x, char w[20]) {
    int check=0;
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
		if(strcmp(n->word,w)==0){
			n->count++;
			return;
		}
        check=1;
		n = n->nxt;
	}
    if(check==0){
        if(strcmp(n->word,w)==0){
			n->count++;
			return;
		}
        else{
            n->nxt = (node*)malloc(sizeof(node));
            n->nxt->prv = n;
            n->nxt->nxt = NULL;
            n->nxt->count = 1;
            strcpy(n->nxt->word, w);
            return;
        }
    }
    if(strcmp(n->word,w)==0){
		n->count++;
		return;
	}
    n->nxt = (node*)malloc(sizeof(node));
    n->nxt->prv = n;
    n->nxt->nxt = NULL;
    n->nxt->count = 1;
    strcpy(n->nxt->word, w);
    return;
}

links countalign(links* x){
	node *n, *temp, *i;
	i=x->head;
    n=x->head->nxt;
	int check=0;
	while (n != NULL){
        while(i->prv!=NULL && check==0){
            i=i->prv;
        }
		if(n->count <= i->count){
			i=i->nxt;
            check=1;
            if(strcmp(n->word,i->word)==0){
                n=n->nxt;
				check=0;
                continue;
            }

		}
		else{
            temp=n->nxt;
            if(temp==NULL){
                n->prv->nxt=n->nxt;
            }
            else{
                n->nxt->prv=n->prv;
                n->prv->nxt=n->nxt;
                if(i->prv==NULL){
                    i->prv=n;
                    n->nxt=i;
                    n->prv=NULL;
                    n=temp;
                    continue;
                }
                i->prv->nxt=n;
                n->nxt=i;
                n->prv=i->prv;
                n=temp;
                continue;
            }
            if(i->prv==NULL){
                i->prv=n;
                n->nxt=i;
                n->prv=NULL;
                n=temp;
                continue;
            }
            i->prv->nxt=n;
            n->nxt=i;
            n->prv=i->prv;
            n=temp;
        }
	}
    while(i->prv!=NULL){
        i=i->prv;
    }
    x->head=i;
	return (*x);
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
				printf("\n%d ??몰라 %d 단어수: ", no->count, cnt);
				for (no2 = l.head; no2->count != no->count; no2 = no2->nxt);			//���⵵ ������ ��ġ ����ϸ� ó������ ��ȸ�� �ʿ� ����
				for (; no2->count == no->count; no2 = no2->nxt) {
					printf("%s, ", no2->word);
				}
			}
		}
		no = no->nxt;
	}
	cnt = wordcount(l, 1);
	printf("\n1 ㅁㄴㅇㄹ %dㄹㄹㄹ: ", cnt);
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
		bb = fscanf(f, "%c", &cc);
		if (bb == EOF)break;
		if (state == 0) {
			if (!isalpha(cc))continue;
			else {
				cc = Tolower(cc);
				state = 1;
				sprintf(c, "%c", cc);
			}
		}
		else if (state == 1) {
			if (!isalpha(cc)) {
				state = 0;
				insert(l, c);
				tot++;
			}
			else {
				cc = Tolower(cc);
				sprintf(buf, "%c", cc);
				strcat(c, buf);
			}
		}
	}
	return tot;
}

// Print each item in a list in sequence.
void PrintList(links* plist) {
    for (node* cur = plist->head; cur != NULL; cur = cur->nxt)
        printf("%s\t\t %d\n", cur->word,cur->count);
}

int main() {
	links l;
	links *k;
	l.head = NULL;
	FILE* f;
	clock_t a, b;
	float tm;
	a = clock();
	f=fopen("/home/inhosecond/repositories/System_Programming/cano.txt", "r");
	int tot = scanwords(f, &l);
	l=countalign(&l);
	printrank(l);
	fclose(f);
	b = clock();
	tm = (float)(b - a) / CLOCKS_PER_SEC;
	printf("\n\n%f시간", tm);
	printf("%d", wordkind(l));
	printf("\n%d\n", tot);
	printf("------최종 정렬------\n");
	// PrintList(&l);
}
