#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

struct trafficInfo{
	int vehicle; // bus = 0, MRT = 1;
	int busName;
	char MRTName;
	int distance;
};
struct treeNode{
	int distance;
	int parent;
	int color;
};
struct trafficInfo infoMatrix[1001][1001];
struct treeNode nodeMatrix[1001];

void getInfo(int mBusName, char mMRTName){
	int stop, from, to, i;

	scanf("%d", &stop);
	if(mBusName != -1){
		for(i = 0; i < stop; i ++){
			scanf("%d %d", &from, &to);
			infoMatrix[from][to].vehicle = 0;
			infoMatrix[from][to].busName = mBusName;
			scanf("%d", &infoMatrix[from][to].distance);
		}
	}
	else{
		for(i = 0; i < stop; i ++){
			scanf("%d %d", &from, &to);
			infoMatrix[from][to].vehicle = 1;
			infoMatrix[from][to].MRTName = mMRTName;
			scanf("%d", &infoMatrix[from][to].distance);
		}
	}
}

int extraDistance(int parentNode, int thisNode, int nextNode){
	if(parentNode == thisNode) return 0;
	else if(infoMatrix[parentNode][thisNode].vehicle == 1 && infoMatrix[thisNode][nextNode].vehicle == 0) return 5;
	else if(infoMatrix[parentNode][thisNode].vehicle == 0 && infoMatrix[thisNode][nextNode].vehicle == 0){
		if(infoMatrix[parentNode][thisNode].busName == infoMatrix[thisNode][nextNode].busName) return 0;
		else return 5;
	}
	else if(infoMatrix[parentNode][thisNode].vehicle == 1 && infoMatrix[thisNode][nextNode].vehicle == 1){
		if(infoMatrix[parentNode][thisNode].MRTName == infoMatrix[thisNode][nextNode].MRTName) return 0;
		else return 10;
	}
	else if(infoMatrix[parentNode][thisNode].vehicle == 0 && infoMatrix[thisNode][nextNode].vehicle == 1) return 10;
	return 0;
}

int searchMinNode(int currentMin){
	int minNode = -1, minDistance = 2147483647, i;
	for(i = 1; i < 1001; i ++){
		if(nodeMatrix[i].color == 1){
			if(nodeMatrix[i].distance < minDistance){
				minNode = i;
				minDistance = nodeMatrix[i].distance;
			}
		}
		else continue;
	}
	if(currentMin < minDistance) return -1;
	return minNode;
}

int getMinDistance(int from, int to){
	int minDistance = 2147483647, minNode, distance;
	int i;
	bool reach = false, finish = false;

	// initialize
	for(i = 0; i < 1001; i ++){
		nodeMatrix[i].distance = 2147483647;
		nodeMatrix[i].parent = -1;
		nodeMatrix[i].color = 0;
	}

	// first node
	nodeMatrix[from].distance = 0;
	nodeMatrix[from].parent = from;
	nodeMatrix[from].color = 1;

	// Dijkstra's algorithm
	while(!finish){
		minNode = searchMinNode(minDistance);
		if(minNode == -1) finish = true;
		else{
			nodeMatrix[minNode].color = 2;
			for(i = 1; i < 1001; i ++){
				if(infoMatrix[minNode][i].distance == 0) continue;
				else if(nodeMatrix[i].color > 1) continue;
				else{
					distance = nodeMatrix[minNode].distance + infoMatrix[minNode][i].distance + extraDistance(nodeMatrix[minNode].parent, minNode, i);
					if(nodeMatrix[i].color == 0){
						nodeMatrix[i].color = 1;
						nodeMatrix[i].parent = minNode;
						nodeMatrix[i].distance = distance;
					}
					else{
						if(nodeMatrix[i].distance > distance){
							nodeMatrix[i].parent = minNode;
							nodeMatrix[i].distance = distance;
						}
					}
					if(i == to){
						reach = true;
						minDistance = nodeMatrix[i].distance;
					}
				}
			}
		}
	}

	// result
	if(reach) return minDistance;
	return -1;
}

int BFSMethod(int from, int to){
	int distance, count, i, j;
	bool finish = false;

	// initialize
	for(i = 0; i < 1001; i ++){
		nodeMatrix[i].distance = 2147483647;
		nodeMatrix[i].parent = -1;
		nodeMatrix[i].color = 0;
	}

	// first node
	nodeMatrix[from].distance = 0;
	nodeMatrix[from].parent = from;
	nodeMatrix[from].color = 1;

	// BFS algorithm
	while(!finish){
		count = 0;
		for(i = 0; i < 1001; i ++){
			if(nodeMatrix[i].color == 1){
				count ++;
				for(j = 1; j < 1001; j ++){
					if(infoMatrix[i][j].distance == 0) continue;
					else{
						distance = nodeMatrix[i].distance + infoMatrix[i][j].distance + extraDistance(nodeMatrix[i].parent, i, j);
						if(nodeMatrix[j].color == 0){
							nodeMatrix[j].color = 1;
							nodeMatrix[j].parent = i;
							nodeMatrix[j].distance = distance;
						}
						else{
							if(nodeMatrix[j].distance > distance){
								nodeMatrix[j].parent = i;
								nodeMatrix[j].distance = distance;
							}
						}

					}
				}
				nodeMatrix[i].color = 2;
			}
		}
		if(count == 0) finish = true;
	}

	if(nodeMatrix[to].color == 2) return nodeMatrix[to].distance;
	return -1;
}

int main(){
	int mBusName, temp, from, to, minDistance_0 = 2147483647, minDistance_1 = 2147483647, i;
	char doType[2], mMRTName[3];
	while(scanf("%s", doType) != EOF){
		if(doType[0] == 'L'){
			for(i = 0; i < 3; i ++) mMRTName[i] = '\0';
			scanf("%s", mMRTName);
			if(isdigit(mMRTName[0])){
				mBusName = mMRTName[0] - '0';
				if(isdigit(mMRTName[1])){
					temp = mMRTName[1] - '0';
					mBusName = mBusName*10 + temp;
				}
				getInfo(mBusName, '-');
			}
			else getInfo(-1, mMRTName[0]);
		}
		else if(doType[0] == 'Q'){
			scanf("%d %d", &from, &to);
			if(from == to) printf("0\n");
			else{
				minDistance_0 = getMinDistance(from, to);
				minDistance_1 = BFSMethod(from, to);
				if(minDistance_0 < minDistance_1) printf("%d\n", minDistance_0);
				else printf("%d\n", minDistance_1);
			}
		}
		else break;
	}
	return 0;
}
/* MRT to Bus : 5 min
 * Bus to Bus : 5 min
 * MRT to MRT : 10 min
 * Bus to MRT : 10 min
 * Single Way, Single direction
 *
 * Input : (1) info part
 * 		   "L", name, stop (name = en >> MRT; name = num >> Bus)
 * 		   from, to, time
 *
 *		   (2) search part
 * 		   "Q", from, to
 *
 * 		   (3) end part
 * 		   "E"
 *
 * Output : min time, if no = -1
 *
 * void test(int doType){
	int i;
	if(doType == 0) printf("123\n");
	else if(doType == 1){
		for(i = 1 ; i < 8; i ++){
			printf("nodeMatrix[%d].color = %d ", i, nodeMatrix[i].color);
			printf("nodeMatrix[%d].parent = %d ", i, nodeMatrix[i].parent);
			printf("nodeMatrix[%d].distance = %d\n", i, nodeMatrix[i].distance);
		}
	}
}
 */

// if name is null, name = 0 || ' '
