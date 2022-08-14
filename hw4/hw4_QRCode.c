#include <stdio.h>

int matrix_X = 0, matrix_Y = 0;
int matrix[1000][1000];
int maxArea = 0;

void draw(int pos_X, int pos_Y){
	int area = 0;
	
	if(area > maxArea) maxArea = area;
}

int main(){
	int i = 0, j = 0;

	scanf("%d %d", &matrix_X, &matrix_Y);
	for(j = 0; j < matrix_Y; j ++)
		for(i = 0; i < matrix_X; i ++)
			scanf("%d", &matrix[j][i]);
	
	for(j = 0; j < matrix_Y; j ++)
		for(i = 0; i < matrix_X; i ++)
			if(matrix[j][i] == 0) draw(i, j);

	printf("%d\n", maxArea);
	
	return 0;
}
