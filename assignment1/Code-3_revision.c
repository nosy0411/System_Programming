#include <stdio.h>
#include <string.h>

int strlonger(char *s, char *t){
	return strlen(s)>strlen(t);
}


int main(){
	char s1[10]="Korea";
	char t1[10]="America";

	int diff=strlonger(s1,t1);
	printf("%d\n",diff);
}

