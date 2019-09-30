#include <stdio.h>

int main(){
	int x=3;

	printf("%d %d\n",x*5, (x<<2)+x);
	printf("%d %d\n",x*9, (x<<3)+x);
	printf("%d %d\n",x*30, (x<<5)-(x<<1));
	printf("%d %d\n",x*(-56), (x<<3)-(x<<6));
}

