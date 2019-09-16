#include <stdio.h>
#include <stdlib.h>
#include "linkedlist1.h"
#include "linkedgraph1.h"
#include "single_source_sp.h"

//다잌스트라 알고리즘
int *shortestPathDijkstra(LinkedGraph* pGraph, int sourceNodeID) {
	int *pDistance = NULL;

	int *pS = NULL;
	int nodeCount = 0, i = 0;
	int vNodeID = 0, y_w = 0, y_v = 0;

	LinkedList *pEdgeList = NULL;
	LinkedListNode *pEdgeNode = NULL;
	GraphEdge *pEdge = NULL;

	nodeCount = pGraph->nodeCount; //pGraph의 노드 개수 조사
	//반환 값 및 집합 S 저장을 위한 메모리 할당
	pDistance = (int*)malloc(sizeof(int)*nodeCount);  
	pS = (int*)malloc(sizeof(int)*nodeCount); //S에 포함되었으면 1, 아니면 0.
	printf("Step-0. 초기화\n");
	//초기화 단계. 집합 S에 각 노드를 추가하고 시작 노드부터 각 노드까지의 거리를 설정.
	for (i = 0;i < nodeCount;i++) {
		pS[i] = 1;
		pEdge = getEdgeLG(pGraph, sourceNodeID, i);
		if (NULL != pEdge) { //만약 시작 노드와 연결되었다면 연결된 간선의 가중치로 설정.
			pDistance[i] = pEdge->weight;
		}
		else { //연결되지 않았다면 MAX_INT
			pDistance[i] = MAX_INT;
		}
	}
	//시작 노드에 대한 예외 설정. 시작 노드까지의 거리가 0이면 집합 S에서 제거.
	pDistance[sourceNodeID] = 0;
	pS[sourceNodeID] = 0;

	printDistanceInfo(sourceNodeID, pDistance, nodeCount);

	for (i = 0;i < nodeCount - 1;i++) {
		printf("\n[%d]번째 루프\n", i + 1);

		//Step-1.
		//집합 S중 최단 거리를 가지는 노드를 선택.
		vNodeID = getMinDistance(pDistance, pS, nodeCount);
		pS[vNodeID] = 0;

		pEdgeList = pGraph->ppAdjEdge[vNodeID]; //선택된 노드의 리스트를 포인터 변수에 저장.
		//루프를 돌면서 현재 선택한 노드와 인접한 모든 노드의 최단 거리의 변경을 실시.
		pEdgeNode = pEdgeList->headerNode.pLink;
		while (pEdgeNode != NULL) {
			int wNodeID = pEdgeNode->data.toNodeID;
			int c_v_w = pEdgeNode->data.weight;

			y_v = pDistance[vNodeID];
			y_w = pDistance[wNodeID];
			//기존 최단 거리와 새로운 최단 거리를 비교.
			if (y_v + c_v_w < y_w) {
				pDistance[wNodeID] = y_v + c_v_w;
				printf("\t[%d]노드의 이전 노드는 [%d]로 변경, 거리는 [%d]에서 "
					"[%d](으)로 Line 줄어듬\n",wNodeID,vNodeID,y_w,y_v+c_v_w);
			}
			pEdgeNode = pEdgeNode->pLink;
		}
		printDistanceInfo(sourceNodeID, pDistance, nodeCount);
	}
	free(pS);

	return pDistance;
}

//S중에서 최단 거리를 가지는 노드를 구하는 함수
int getMinDistance(int* distance, int *pS, int nodeCount) {
	int pReturn = 0;
	int min_distance = MAX_INT;
	int i = 0;

	for (i = 0;i < nodeCount;i++) {
		if (0 != pS[i] && distance[i] < min_distance) {
			min_distance = distance[i];
			pReturn = i;
		}
	}
	return pReturn;
}

//지금까지 구한 거리를 출력하는 함수
void printDistanceInfo(int sourceNodeID, int* pDistance, int nodeCount) {
	int i = 0;

	for (i = 0;i < nodeCount;i++) {
		printf("\t[%d]부터 [%d]까지 거리:%d\n", sourceNodeID, i, pDistance[i]);
	}
}