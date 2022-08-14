#include <stdio.h>
#include <stdbool.h>

struct wood_data{
	int from;
	int to;
	int color;
	int distance;
};
int numOfWood;
struct wood_data woodData[1000];
int jumpTime = 0;
int adjList[1000][999];
int visited_queue[1000];
int headptr;
int tailptr;

void detail_print(int mode){
	int i = 0, j = 0;
	if(mode == 0){
		printf("distance:\n");
		for(i = 0; i < numOfWood; i ++){
			printf("%d ", woodData[i].distance);
		}
		printf("\n");
		printf("adjList:\n");
		for(i = 0; i < numOfWood; i ++){
			printf("row %d: ",i);
			for(j = 0; j < numOfWood-1 && adjList[i][j] != -1; j ++)
				printf("%d ", adjList[i][j]);
			printf("\n");
		}
	}
	printf("visited_queue:\n");
	for(i = 0; i < numOfWood; i ++)
		printf("%d ", visited_queue[i]);
	printf("\n");
	printf("headptr = %d, tailptr = %d\n", headptr, tailptr);
}

bool isOverlap(int wood_A, int wood_B){
	if(woodData[wood_B].from >= woodData[wood_A].from
			&& woodData[wood_B].from < woodData[wood_A].to) return true;
	else if(woodData[wood_A].from >= woodData[wood_B].from
			&& woodData[wood_A].from < woodData[wood_B].to) return true;
	else return false;
}

int main(){
	int i = 0, j = 0, k = 0, u = 0;

	// 1. scan
	scanf("%d", &numOfWood);
	for(i = 0; i < numOfWood; i ++)
		scanf("%d %d", &woodData[i].from, &woodData[i].to);

	// 2. create adjList
	for(i = 0; i < numOfWood; i ++)
		for(j = 0; j < numOfWood-1; j ++)
			adjList[i][j] = -1;
	for(i = 0; i < numOfWood; i ++){
		k = 0;
		for(j = 0; j < numOfWood; j ++)
			if(i != j && isOverlap(i, j)){
				adjList[i][k] = j;
				k ++;
			}
	}

	// 3. use BFS_search to traverse any road which can reach goal
	for(i = 0; i < 1000; i ++) visited_queue[i] = -1;
	k = 0;
	woodData[0].color = 1;
	visited_queue[0] = 0;
	tailptr ++;
	for(i = headptr; i < tailptr && k == 0; i ++){
		for(j = 0; j < 999 && adjList[visited_queue[i]][j] != -1 && k == 0; j ++)
			if(woodData[adjList[visited_queue[i]][j]].color == 0){
				woodData[adjList[visited_queue[i]][j]].color = 1;
				woodData[adjList[visited_queue[i]][j]].distance = woodData[visited_queue[i]].distance + 1;
				visited_queue[tailptr] = adjList[visited_queue[i]][j];
				tailptr ++;
				if(adjList[visited_queue[i]][j] == numOfWood-1)k = -1;
			}
		visited_queue[headptr] = -1;
		headptr ++;
	}
	printf("%d\n", woodData[numOfWood-1].distance);

	return 0;
}
