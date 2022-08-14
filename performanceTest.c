#include <stdio.h>
int main(){
	int i = 0, j = 0;
	long a = 0;
	for(i = 0; i < 10000000; i ++)
		for(j = 0; j < 100; j ++)
			a ++;
	printf("test finished!\na = %lu\n", a);
	return 0;
}
