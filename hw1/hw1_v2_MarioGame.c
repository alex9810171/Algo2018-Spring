#include <stdio.h>

int main(){
	// variables
	int i = 0, j = 0;
	int total = 0;
	int maxScore = 0, score = 0;
	int pillar[200000];
	int head = 0;

	// get data
	while(scanf("%d", &pillar[i]) != EOF)
		i ++;

	// get total
	total = i;

	// copy twice to simulate a circle
	for(i = 0; i < total; i ++)
		pillar[i + total] = pillar[i];
	
	// method_1. sequence test:
	if(total < 1000)
		for(i = 0; i < total; i ++){
			if(pillar[i] <= 0) continue;
			else for(j = 0; j < total; j ++){
				score += pillar[i + j];
				if(score > maxScore) maxScore = score;
			}
			score = 0;
		}
	// method_2. accumulated test:
	else
		for(i = 0; (i-head) < total && i < 2*total; i ++){
			score += pillar[i];
			if(score > maxScore) maxScore = score;
			else if(score <= 0){
				head = i+1;
				score = 0;
			}
		}
	
	// output
	printf("%d\n", maxScore);

	return 0;
}
