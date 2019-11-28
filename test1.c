#include <stdio.h>

#define N 4

int arrsum(int *a){
	
	int sum =0;
	
	for(int i = 0; i < N; ++i) sum += a[i];

	return sum;
}

int main(void){
	int a[N] = {1,2,3,5};

	printf("%d\n", arrsum(a));
