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
    links* y;
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
			check=0;
            temp=n->nxt;
            if(temp==NULL){
                n->prv->nxt=n->nxt;
				if(i->prv==NULL){
					i->prv=n;
					n->nxt=i;
					n->prv=NULL;
					break;
            	}
				i->prv->nxt=n;
            	n->nxt=i;
            	n->prv=i->prv;
            	break;
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
        }
	}
    while(i->prv!=NULL){
        i=i->prv;
    }
    y->head=i;
	return (*y);
}

int wordcount(links l, int i) {
	node* no = l.head;
	int val = 0;
	for (; no != NULL && no->count != i; no = no->nxt);
	for (; no != NULL && no->count == i; no = no->nxt, val++);
	return val;
}

// Print each item in a list in sequence.
void PrintList(links* plist) {
    for (node* cur = plist->head; cur != NULL; cur = cur->nxt)
        printf("%-20s\t %d\n", cur->word,cur->count);
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

int main(void)
{
	links list1;
    list1.head = NULL;
	int i;
    char w1[20]="asdf";
    char w2[20]="ghjk";
    char w3[20]="zvbf";
    char w4[20]="qqqq";
    char w5[20]="hhhh";
    char w6[20]="vvvv";
	for (i = 0; i < 8; i++)
		insert(&list1,w1); // 8개의 리스트에 랜덤으로 수를 넣는 반복문
    for (i = 0; i < 9; i++)
		insert(&list1,w2);
    for (i = 0; i < 10; i++)
		insert(&list1,w3);
    insert(&list1,w4);
    for (i = 0; i < 10; i++)
		insert(&list1,w6);
    for (i = 0; i < 5; i++)
		insert(&list1,w5);
    PrintList(&list1);
    printf("------최종 정렬------\n");
	list1=countalign(&list1);
	printf("------최종 정렬------\n");
    PrintList(&list1);
    printrank(list1);
	 // 정렬 된 모습을 출력
}