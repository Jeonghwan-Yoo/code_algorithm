#include <stdio.h>
#include <stdlib.h>

#include "linkedgraph4.h"
#include "linkedstack4.h"

#include "mst_prim.h"

// Prim 알고리즘
LinkedGraph* mstPrim(LinkedGraph* pGraph, int startNodeID)
{
	LinkedGraph*    pReturn = NULL;
	int             *pSelected = NULL; //노드가 선택되었지 확인. 1이면 선택.

	int             i = 0, nodeCount = 0;
	int             mstNodeCount = 0;
	int             fromNodeID = 0;
	PrimGraphEdge   minWeightEdge = { 0, };

	if (pGraph == NULL) {
		printf("Graph is NULL\n");
		return pReturn;
	}

	nodeCount = pGraph->nodeCount;
	//최소 비용 신장 트리 생성. pGraph의 노드개수 이용.
	pReturn = createLinkedGraph(LINKED_GRAPH_TYPE_UNDIRECT, nodeCount);
	
	//신장 트리에 노드가 추가 되었지는 저장하는 1차원 배열 생성 및 초기화.
	pSelected = (int*)malloc(sizeof(int) * nodeCount);
	if (NULL == pReturn || NULL == pSelected) {
		return NULL;
	}
	memset(pSelected, 0, sizeof(int) * nodeCount);

	//시작노드를 추가하고 선택된 노드 개수를 1개로 설정함.
	pSelected[startNodeID] = 1;
	mstNodeCount = 1;

	//알고리즘 종료 조건을 만족하는지 확인
	while (mstNodeCount < nodeCount) {
		//변수 초기화. 최소 가중치 값을 가지는 간선 정보를 저장하는 역할이다.
		//getMinWeightEdge()의 결과를 반환 받는 출력 파라미터로 사용. 입력~출력 파라미터 역할
		//현재 최소 가중치 값을 가지는 간선 정보를 저장하고 있으며(입력)
		//함수 내부에서 최소 가중치 값을 가지는 간선의 정보가 변경될 수 있기 때문(출력)
		minWeightEdge.fromNodeID = 0;
		minWeightEdge.toNodeID = 0;
		minWeightEdge.weight = MAX_INT;

		//모든 정점에 대해 루프를 돌면서 최소 가중치를 가지는 간선을 선택함.
		//minWeightEdge에는 지금까지 찾은 최소 비용 가중치에 대한 정보가 저장되어 있다.
		//그리고 현재 저장된 가중치 값보다 더 작은 간선으로만 변경될 수 있음.
		for (i = 0; i < nodeCount; i++) {
			if (pSelected[i] == 1) {
				fromNodeID = i;
				getMinWeightEdge(pGraph, pReturn, fromNodeID, &minWeightEdge);
			}
		}
		//앞서 선택된 노드와 간선을 '현재 신장 트리'에 추가함.
		//간선의 수 1증가.
		addEdgeLG(pReturn, minWeightEdge.fromNodeID,
			minWeightEdge.toNodeID, minWeightEdge.weight);
		pSelected[minWeightEdge.toNodeID] = 1;
		mstNodeCount++;

		printf("[%d], 최소 가중치: (%d,%d)->%d, 노드 %d 추가\n",
			mstNodeCount, minWeightEdge.fromNodeID, minWeightEdge.toNodeID,
			minWeightEdge.weight, minWeightEdge.toNodeID);
	}

	return pReturn;
}

int checkEdge(LinkedGraph* pGraph, int fromNodeID, int toNodeID) {
	int             ret = 0;
	LinkedList      *pEdgeList = NULL;
	LinkedListNode  *pEdgeNode = NULL;

	if (pGraph != NULL) {
		pEdgeList = pGraph->ppAdjEdge[fromNodeID];
		if (pEdgeList != NULL) {
			pEdgeNode = pEdgeList->headerNode.pLink;
			while (pEdgeNode != NULL) {
				if (pEdgeNode->data.toNodeID == toNodeID) {
					ret = 1;
					break;
				}

				pEdgeNode = pEdgeNode->pLink;
			}
		}
	}

	return ret;
}


// 정점(fromNodeID)과 연결된 간선들 중,
// 가중치가 가장 작으면서 순환을 발생시키지 않는 간선을 선택.
//fromNodeID를 이용하여 이 노드와 연결된 간선에 대해서 while루프.
void getMinWeightEdge(LinkedGraph* pGraph, LinkedGraph* pMST,
	int fromNodeID, PrimGraphEdge *pMinWeightEdge) {
	LinkedListNode  *pListNode = NULL;
	int             isCycle = 0;
	int             isAlready = 0;
	LinkedList      *pEdgeList = pGraph->ppAdjEdge[fromNodeID];

	// pListNode: V(T)에 부속된 간선들 중 하나를 선택.
	pListNode = pEdgeList->headerNode.pLink;
	//종료 노드 정보인 toNodeID와 가중치 정보 weight와 같은 간선의 정보를 얻습니다.
	//그리고 최소 가중치 값을 가지는 간선인지 점검합니다.
	while (pListNode != NULL) {
		int toNodeID = pListNode->data.toNodeID;
		int weight = pListNode->data.weight;

		// 최소값인지 점검.
		if (pListNode->data.weight < pMinWeightEdge->weight) {
			// 기존의 E(T)에 속한 간선인지 점검
			isAlready = checkEdge(pMST, fromNodeID, toNodeID);
			if (0 == isAlready) {
				// 순환을 발생시키는지 점검
				isCycle = checkCycle(pMST, fromNodeID, toNodeID);
				if (0 != isCycle) {
					printf("순환 발생: (%d,%d)->%d, Skip\n",
						fromNodeID,
						toNodeID, pListNode->data.weight);
				}
			}
			// 기존에 이미 E(T)에 속한 간선이 아니면서,
			// 순환을 발생시키지 않는,
			// 최소 가중치 간선을 선택.
			if (isAlready == 0 && isCycle == 0) {
				pMinWeightEdge->fromNodeID = fromNodeID;
				pMinWeightEdge->toNodeID = toNodeID;
				pMinWeightEdge->weight = weight;
			}
		}

		pListNode = pListNode->pLink;
	}
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
