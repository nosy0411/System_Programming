#include <stdio.h>

int main(){
	int tx = 2147483648;
	unsigned ux = (unsigned)tx;
	int ty = (int)ux;

	printf("%d %u %d\n",tx,ux,ty);
}
