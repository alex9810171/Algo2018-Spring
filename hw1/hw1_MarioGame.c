#include <stdio.h>

int main(){

	int temp_0 = 0;
	int total = 0;
	int maxScore = 0, maxHead = 0, maxTail = 0;
	int score = 0, head = 0, tail = -1;
	int pillar[200000];

	// get data
	while(scanf("%d", &pillar[temp_0]) != EOF)
		temp_0 ++;

	// get total 
	total = temp_0;

	// copy twice to simulate a circle, reset temp_0
	for(temp_0 = 0; temp_0 < total; temp_0 ++)
		pillar[temp_0 + total] = pillar[temp_0];

	// method_1. accumulated test:
	// (1) if head & tail < 0, drop
	// (2) if too long, head ++
	// (3) total < 0, throw all
	for(head = 0; head < total; head ++){
		// get max value from fixed start
		if(pillar[head] > 0){
			for(tail = maxTail; tail < head + total; tail ++){
				if(maxTail < head) tail = head; // start from bigger
				score += pillar[tail];
				if(score > maxScore){
					maxScore = score;
					maxHead = head;
					maxTail = tail;
				}
			}

			// prepare for next round: delete back we don't need
			for(temp_0 = maxTail+1; temp_0 < tail; temp_0 ++)
				score -= pillar[temp_0];
			tail = maxTail;
		}
		
		// prepare for next round: delete front
		if(tail >= head)
			score -= pillar[head];
		head ++;

	}
	printf("%d\n", maxScore);

	return 0;
}
