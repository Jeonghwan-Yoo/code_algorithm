#include <stdio.h>
#include "tspbacktracking.h"

//각 도시 사이의 연결 정보를 저장하는 배열 변수.
int costGraph[NUM_OF_NODE][NUM_OF_NODE] = {
	{0, 10, 15, 20},
	{10, 0, 35, 25},
	{15, 35, 0, 30},
	{20, 25, 30, 0}
};

int main(void) {
	int mincost = INT_MAX;
	int path[NUM_OF_NODE + 1] = { 0 }, optimalPath[NUM_OF_NODE + 1] = { 0 };
	path[0] = 0; //시작 노드 지정:0번 노드

	printf("Traveling Salesman (백트래킹 알고리즘)\n");
	//시작할 때 방문 도시 개수 step은 0이며 현재까지의 비용 cost도 0입니다.
	TSP_BackTracking(costGraph, 0, 0, path, optimalPath, &mincost);

	printf("\n최소 비용:%d\n", mincost);
	printPath(costGraph, optimalPath, NUM_OF_NODE, mincost);

	return 0;
}