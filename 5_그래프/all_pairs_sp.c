#include <stdio.h>
#include <stdlib.h>
#include "linkedlist2.h"
#include "linkedgraph2.h"
#include "all_pairs_sp.h"

//플로이드(Floyd) 알고리즘
int** shortestPathFloyd(LinkedGraph* pGraph) {
	int **ppDistance = NULL;
	int r = 0, s = 0, v = 0;
	int nodeCount = 0;
	GraphEdge *pEdge = NULL;

	nodeCount = pGraph->nodeCount; //입력 파라미터인 그래프 pGraph의 노드 개수 조사
	//최단 거리 저장을 위한 2차원 배열의 메모리 할당
	ppDistance = (int**)malloc(sizeof(int*)*nodeCount); 

	//루프를 돌면서 2차원 배열의 각 row에 해당하는 1차원 배열을 동적으로 할당.
	for (r = 0;r < nodeCount;r++) {
		ppDistance[r] = (int*)malloc(sizeof(int)*nodeCount);
	}

	//Step-0 초기화
	//각 노드 사이의 거리를 초기화. 두 노드를 연결하는 간선의 가중치 값을 이용
	for (r = 0;r < nodeCount;r++) {
		for (s = 0;s < nodeCount;s++) {
			if (r == s) {
				ppDistance[r][s] = 0;
			}
			else {
				pEdge = getEdgeLG(pGraph, r, s);
				if (NULL != pEdge) {
					ppDistance[r][s] = pEdge->weight;
				}
				else {
					ppDistance[r][s] = MAX_INT;
				}
			}
		}
	}
	printMatrix(ppDistance, nodeCount);

	//Step 1. 3중 루프
	//3중 루프를 돌면서 최단 거리 변경을 수행.
	for (v = 0;v < nodeCount;v++) {
		for (r = 0;r < nodeCount;r++) {
			for (s = 0;s < nodeCount;s++) {
				if (ppDistance[r][v] + ppDistance[v][s] < ppDistance[r][s]) {
					ppDistance[r][s] = ppDistance[r][v] + ppDistance[v][s];
				}
			}
		}
		printf("[%d]-루프\n", v + 1);
		printMatrix(ppDistance, nodeCount);
	}
	return ppDistance;
}

void printMatrix(int **A, int nodeCount) {
	int r = 0;
	int s = 0;

	for (s = 0;s < nodeCount;s++) {
		printf("\t%d", s);
	}
	printf("\n");

	for (r = 0;r < nodeCount;r++) {
		printf("%d: ", r);
		for (s = 0;s < nodeCount;s++) {
			printf("\t%d", A[r][s]);
		}
		printf("\n");
	}
}