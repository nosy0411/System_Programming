#include <stdio.h>

int main(){
	int k=4;
	int j=3;
	int A=(-1<<k);
	int B=(~(-1<<k))<<j;

	printf("A.=%x\n",A);
	printf("B.=%x\n",B);
}
