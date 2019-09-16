#include <stdio.h>
#include <stdlib.h>

#include "linkedgraph3.h"
#include "linkedstack3.h"
#include "grapharrayheap3.h"
#include "mst_kruskal.h"

// 기존 그래프 G의 간선을 가중치 값에 따라 오름차순으로 정렬.
ArrayMinHeap *orderEdges(LinkedGraph* pGraph);

// 순환 발생 검사.
int checkCycle(LinkedGraph* pGraph, int fromNodeID, int toNodeID);

//최소 비용 신장 트리를 반환
//트리를 이용하여 그래프를 나타낼 순 없지만, 반대로 그래프를 이용해서 트리를 나타낼 수 있습니다.
//먼저 최소 비용 신장 트리를 생성한 다음 루프를 돌면서 최소 비용을 가지는 간선을 추가합니다.
//그래프의 모든 노드가 선택되었다면 알고리즘을 종료합니다.
LinkedGraph* mstKruskal(LinkedGraph* pGraph)
{
	LinkedGraph* pReturn = NULL;
	int i = 0, isCycle = 0, currentEdgeCount = 0;
	int edgeCount = 0;
	ArrayMinHeap    *pMinHeap = NULL;
	HeapNode        *pHeapNode = NULL;
	int             *pVisited = NULL;

	if (pGraph == NULL) {
		printf("Graph is NULL\n");
		return NULL;
	}

	edgeCount = pGraph->edgeCount;
	//최소 비용 신장 트리 생성. pGraph의 노드 개수를 이용.
	pReturn = createLinkedGraph(LINKED_GRAPH_TYPE_UNDIRECT, pGraph->nodeCount);
	//신장 트리에 노드가 추가되었는지를 저장하는 1차원 배열 생성 및 초기화
	pVisited = (int*)malloc(sizeof(int) * pGraph->nodeCount);
	if (NULL == pReturn || NULL == pVisited) {
		return NULL;
	}
	memset(pVisited, 0, sizeof(int) * pGraph->nodeCount);

	//간선들을 가중치에 따라 오름차순으로 정렬을 수행함.
	pMinHeap = orderEdges(pGraph);
	if (pMinHeap == NULL) {
		return NULL;
	}
	for (i = 0; i < edgeCount; i++) {
		//Step1
		//가중치가 가장 작은 간선을 최소 히프에서 추출함
		pHeapNode = deleteMinHeapAH(pMinHeap);
		if (pHeapNode != NULL) {
			//최소 비용 간선으로 순환이 발생하는지 점검. 발생시 다음 간선으로 넘어감.
			isCycle = checkCycle(pReturn, pHeapNode->data.fromNodeID,
				pHeapNode->data.toNodeID);
			if (isCycle != 0) {
				printf("[%d], 순환 발생: (%d,%d)->%d, Skip\n",
					i, pHeapNode->data.fromNodeID,
					pHeapNode->data.toNodeID, pHeapNode->data.key);
				free(pHeapNode);
				continue;
			}
			//순환이 발생하지 않는다면 최소 비용 간선을 '신장 트리'에 추가.
			addEdgeLG(pReturn, pHeapNode->data.fromNodeID,
				pHeapNode->data.toNodeID, pHeapNode->data.key);
			printf("[%d], 최소 가중치: (%d,%d)->%d\n",
				i, pHeapNode->data.fromNodeID,
				pHeapNode->data.toNodeID, pHeapNode->data.key);

			//추가한 간선과 연결되 노드가 이미 '신장 트리'에 있는지 점검.
			//없다면 '신장 트리'에 추가하고 현재 신장 트리의 노드 개수를 증가.
			if (0 == pVisited[pHeapNode->data.fromNodeID]) {
				pVisited[pHeapNode->data.fromNodeID] = 1;
			}
			if (0 == pVisited[pHeapNode->data.toNodeID]) {
				pVisited[pHeapNode->data.toNodeID] = 1;
			}
			currentEdgeCount++;
			free(pHeapNode);

			//Step2
			//알고리즘의 종료 조건을 만족하는지 확인.
			if ((pReturn->nodeCount - 1) == currentEdgeCount) {
				break;
			}
		}
	}
	if (NULL != pVisited) {
		free(pVisited);
	}

	return pReturn;
}

//간선을 가중치 값에 따라 으롬차순으로 정렬.
ArrayMinHeap *orderEdges(LinkedGraph* pGraph) {
	int i = 0;
	int edgeCount = 0;
	ArrayMinHeap *pReturn = NULL;
	LinkedListNode *pListNode = NULL;
	LinkedList* pEdgeList = NULL;

	if (pGraph == NULL) {
		printf("Graph is NULL\n");
		return pReturn;
	}

	edgeCount = pGraph->edgeCount;
	if (edgeCount == 0) {
		printf("오류, 간선 개수가 0개\n");
		return pReturn;
	}

	pReturn = createArrayMinHeap(edgeCount);
	if (pReturn == NULL) {
		return pReturn;
	}

	for (i = 0; i < pGraph->nodeCount; i++) {
		{
			pEdgeList = pGraph->ppAdjEdge[i];
			pListNode = pEdgeList->headerNode.pLink;
			while (pListNode != NULL) {
				int vertexID = pListNode->data.toNodeID;
				int weight = pListNode->data.weight;

				// 무방향 그래프라면, 동일한 간선이 2개 리턴되므로,
				// 시작 노드 id가 종료 노드 id보다 작은 경우만 리턴되도록 한다.
				// 즉, 간선 1개만 리턴되도록 한다.
				if (pGraph->graphType == LINKED_GRAPH_TYPE_DIRECT
					|| (pGraph->graphType == LINKED_GRAPH_TYPE_UNDIRECT && i < vertexID)) {
					GraphEdgeInfo edgeInfo = { 0, };
					edgeInfo.fromNodeID = i;
					edgeInfo.toNodeID = vertexID;
					edgeInfo.key = weight;
					insertMinHeapAH(pReturn, edgeInfo);
				}

				pListNode = pListNode->pLink;
			}
		}
	}

	return pReturn;
}


// 간선 추가로 인해 순환이 발생하는 지 검사.
// 기존에 경로가 있었다면, 순환이 발생한다.
// 기존의 깊이우선탐색(DFS)를 사용.
int checkCycle(LinkedGraph* pGraph, int fromNodeID, int toNodeID)
{
	int pReturn = 0;

	int i = 0;
	int vertextID = 0;
	LinkedStack* pStack = NULL;
	LinkedStackNode* pStackNode = NULL;
	LinkedListNode *pListNode = NULL;
	int *pVisited = NULL;

	if (pGraph == NULL) {
		return pReturn;
	}

	pStack = createLinkedStack();
	if (pStack == NULL) {
		return pReturn;
	}

	pVisited = (int*)malloc(sizeof(int) * pGraph->nodeCount);
	if (pVisited == NULL) {
		printf("Error, malloc() in traversalDFS()\n");
		deleteLinkedStack(pStack);
		return pReturn;
	}

	// 초기화.
	for (i = 0; i < pGraph->nodeCount; i++) {
		pVisited[i] = 0;
	}

	pVisited[fromNodeID] = 1;
	pushLS(pStack, fromNodeID);

	while (isLinkedStackEmpty(pStack) == 0) {
		pStackNode = popLS(pStack);
		if (pStackNode != NULL) {
			vertextID = pStackNode->data;
			if (vertextID == toNodeID) {
				//printf("(%d,%d)-기존에 경로가 존재합니다.\n",
				//		fromNodeID, toNodeID);
				pReturn = 1;
				break;
			}

			pListNode = pGraph->ppAdjEdge[vertextID]->headerNode.pLink;
			while (pListNode != NULL) {
				int vertexID = pListNode->data.toNodeID;
				if (pVisited[vertexID] == 0) {
					pVisited[vertexID] = 1;
					pushLS(pStack, vertexID);
				}

				pListNode = pListNode->pLink;
			}
		}
	}

	free(pVisited);
	deleteLinkedStack(pStack);

	return pReturn;
}
