#include <stdio.h>

int main(){
	int xA=0xffffffff;
	int xB=0x0;
	int tip=0x0ff;
	int xC=0xababcdff;
	int xD=0x00abcdef;
	printf("A.=%d\n",!~xA);
	printf("B.=%d\n",!xB);
	printf("test.=%x\n",tip);
	printf("C.=%d\n",!~(xC | ~0xff));
	printf("D.=%d\n",!((xD>>(3<<3)) & 0xff));
}
