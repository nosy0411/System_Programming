#include <stdio.h>

int sum_array(int a[], unsigned len){
	
	int i;
	int result=0;

	for(i=0;i<=len-1;i++){
		result +=a[i];
	}

	return result;
}



int main(){
	int A[10];
	int i;

	for(i=0;i<10;i++){
		A[i]=i+1;
	}

	int final=sum_array(A,10);
	
	printf("%d\n",final);
}
