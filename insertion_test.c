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
	i=x->head;
    n=x->head->nxt;
    int check=0;
	while (n != NULL){
        while(i->prv!=NULL && check==0){
            i=i->prv;
        }
        printf("%s\n",i->word);
		if(n->count <= i->count){
            check=1;
			i=i->nxt;
            if(strcmp(n->word,i->word)==0){
                n=n->nxt;
                check=0;
                continue;
            }

		}
		else{
            printf("check;\n");
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
	 // 정렬 된 모습을 출력
}