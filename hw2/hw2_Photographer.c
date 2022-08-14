#include <stdio.h>
#include <stdbool.h>
int grade = 0, people = 0;
int gradeData[10000][15];
int selectProcess[10000];
int joinGrade[10000];
int maxJoin = 1;

void afterSort(){
	int i = 0, j = 0;
	for(i = 0; i < grade; i ++){
		for(j = 0; j < people; j ++)
			printf("%d ", gradeData[i][j]);
		printf("\n");
	}
}

void selectionSort(){
	int min = 0;
	int i = 0, j = 0, temp[15];
	for(i = 0; i < grade - 1; i ++){
		min = i;
		for(j = i+1; j < grade; j ++)
			if(gradeData[j][0]  < gradeData[min][0])
				min = j;
		if(min != i)
			for(j = 0; j < people; j ++){
				temp[j] = gradeData[i][j];
				gradeData[i][j] = gradeData[min][j];
				gradeData[min][j] = temp[j];
			}
	}
}

void minSort(int a){
	int i = 0, temp = 0;
	int minLocate = selectProcess[a];
	for(i = selectProcess[a]+1; i < people; i ++)
		if(gradeData[a][i] < gradeData[a][minLocate])
			minLocate = i;
	if(minLocate != selectProcess[a]){
		temp = gradeData[a][selectProcess[a]];
		gradeData[a][selectProcess[a]] = gradeData[a][minLocate];
		gradeData[a][minLocate] = temp;
	}
	selectProcess[a] ++;
}

bool compare(int a, int b){
	bool success = true;
	int i = 0;
	for(i = 0; i < people && success == true; i ++){
		if(selectProcess[a] == i)
			minSort(a);
		if(selectProcess[b] == i)
			minSort(b);
		if(gradeData[a][i] >= gradeData[b][i])
			success = false;
	}
	return success;
}

int main(){
	int i = 0, j = 0, tempMax = 1;

	// 1.input
	scanf("%d %d", &grade, &people);
	for(i = 0; i < grade; i ++)
		for(j = 0; j < people; j ++)
			scanf("%d", &gradeData[i][j]);

	// 2.initialize & sort class
	for(i = 0; i < grade; i ++){
		selectProcess[i] = 0;
		minSort(i);
	}
	selectionSort();
	joinGrade[0] = 1;

	// 3.minSort & compare
	for(i = 1; i < grade; i ++){
		for(j = 0; j < i; j ++){
			if(joinGrade[j]+grade-i <= maxJoin) continue;
			else if(compare(j,i) && joinGrade[j]+1 > tempMax)
				tempMax = joinGrade[j]+1;
		}
		joinGrade[i] = tempMax;
		if(joinGrade[i] > maxJoin) maxJoin = joinGrade[i];
		tempMax = 1;
	}

	printf("%d\n", maxJoin);
	return 0;
}
