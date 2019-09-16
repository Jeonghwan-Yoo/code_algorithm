#include "tspbacktracking.h"

//pPath의 내용을 출력
//경로 내에 몇 개의 도시 정보가 있는지 도시 개수는 step으로 전달. 현재까지 비용 정보는 cost로
void printPath(int pGraph[][NUM_OF_NODE], int *pPath, int step, int cost) {
	for (int i = 0;i <= step;i++) {
		if (i > 0) {
			printf(" -(%d)-> ", pGraph[pPath[i - 1]][pPath[i]]);
		}
		printf("%c", 'A' + pPath[i]);
	}
	printf("\t비용:%d\n", cost);
}

//가장 최근에 추가한 도시가 혹시 중복된 도시인지 점검.
//step은 가장 마지막에 방문한 도시를 의미.
int checkValidPath(int pPath[], int step) {
	//새로 추가된 step번째 도시가 이미 방문한 도시인지 점검한다.
	for (int i = 0;i < step;i++) {
		if (pPath[i] == pPath[step]) {
			return 0;
		}
	}
	return 1;
}

//경로 저장 방법
//int 배열에 방문한 도시의 인덱스 정보를 저장하는 방식으로 경로를 저장.
//이때 몇 개의 도시를 방문했는지는 별도의 변수 step으로 저장.
//A->B->D이면 정수 배열에는 위치 정보 0,1,3이 차례로 저장.
//시작 도시를 제외한 방문 도시의 개수는 2개, 경로를 나타내는 배열 pPath의 마지막 원소를 가리킴.

//그래프 정보 pGraph, 현재 방문한 도시 개수 step, 현재까지의 방문 비용 cost
//현재 방문 경로 pPath은 입출력파라미터. 현재 경로에 다음으로 방문할 도시를 추가.
//선택한 경로가 최적의 경로라고 판단될 때 최적의 경로를 반환하는 pOptimalPath, 최소 방문 비옹 pMinCost.
void TSP_BackTracking(int pGraph[][NUM_OF_NODE], int step, int cost, int pPath[],
	int pOptimalPath[], int* pMinCost) {
	int next_node = 0, current_node = 0, total_cost = 0;
	if (checkValidPath(pPath, step)) { //유효한 경로인지 점검(가장 최근에 추가한 도시가 중복인지)
		current_node = pPath[step];

		//마지막 노드인 경우 다음 노드가 시작 노드
		//현재 전달 받은 경로가 정상적인 경로라면 완전한 해인지 점검.
		//시작 도시를 제외하고 현재 방문한 도시의 개수가 3이면 마지막 도시까지 방문한 경우.
		if (step == NUM_OF_NODE - 1) {
			//다시 원래 시작 노드로
			next_node = pPath[0];
			pPath[step + 1] = next_node;
			total_cost = cost + pGraph[current_node][next_node];
			//현재 해가 기존 최적해보다 더 좋은 경우 최적해 변경
			if (total_cost < *pMinCost) {
				*pMinCost = total_cost;
				memcpy(pOptimalPath, pPath, sizeof(int)*NUM_OF_NODE);
				printf("*"); //최적해가 변경되었다는 것을 표시.
			}
			//완전한 해를 새롭게 하나 구했기 때문에 현재 구한 해를 출력
			printPath(pGraph, pPath, NUM_OF_NODE, total_cost);
		}
		//완전한 해가 아니라면 완전한 해를 구하기 위해 다음 도시를 방문.
		else {
			//시작 도시를 제외한 나머지 도시들에 대해서 루프
			for (int toNode = 1;toNode < NUM_OF_NODE;toNode++) {
				next_node = toNode;
				pPath[step + 1] = next_node; //toNode를 경로에 추가.
				total_cost = cost + pGraph[current_node][next_node]; //비용도 추가.
				//재귀적 호출해서 백트래킹을 진행.
				TSP_BackTracking(pGraph, step + 1, total_cost, pPath, pOptimalPath, pMinCost);
			}
		}
	}
}