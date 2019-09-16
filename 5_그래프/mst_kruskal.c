#include <stdio.h>
#include <stdlib.h>

#include "linkedgraph3.h"
#include "linkedstack3.h"
#include "grapharrayheap3.h"
#include "mst_kruskal.h"

// ���� �׷��� G�� ������ ����ġ ���� ���� ������������ ����.
ArrayMinHeap *orderEdges(LinkedGraph* pGraph);

// ��ȯ �߻� �˻�.
int checkCycle(LinkedGraph* pGraph, int fromNodeID, int toNodeID);

//�ּ� ��� ���� Ʈ���� ��ȯ
//Ʈ���� �̿��Ͽ� �׷����� ��Ÿ�� �� ������, �ݴ�� �׷����� �̿��ؼ� Ʈ���� ��Ÿ�� �� �ֽ��ϴ�.
//���� �ּ� ��� ���� Ʈ���� ������ ���� ������ ���鼭 �ּ� ����� ������ ������ �߰��մϴ�.
//�׷����� ��� ��尡 ���õǾ��ٸ� �˰����� �����մϴ�.
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
	//�ּ� ��� ���� Ʈ�� ����. pGraph�� ��� ������ �̿�.
	pReturn = createLinkedGraph(LINKED_GRAPH_TYPE_UNDIRECT, pGraph->nodeCount);
	//���� Ʈ���� ��尡 �߰��Ǿ������� �����ϴ� 1���� �迭 ���� �� �ʱ�ȭ
	pVisited = (int*)malloc(sizeof(int) * pGraph->nodeCount);
	if (NULL == pReturn || NULL == pVisited) {
		return NULL;
	}
	memset(pVisited, 0, sizeof(int) * pGraph->nodeCount);

	//�������� ����ġ�� ���� ������������ ������ ������.
	pMinHeap = orderEdges(pGraph);
	if (pMinHeap == NULL) {
		return NULL;
	}
	for (i = 0; i < edgeCount; i++) {
		//Step1
		//����ġ�� ���� ���� ������ �ּ� �������� ������
		pHeapNode = deleteMinHeapAH(pMinHeap);
		if (pHeapNode != NULL) {
			//�ּ� ��� �������� ��ȯ�� �߻��ϴ��� ����. �߻��� ���� �������� �Ѿ.
			isCycle = checkCycle(pReturn, pHeapNode->data.fromNodeID,
				pHeapNode->data.toNodeID);
			if (isCycle != 0) {
				printf("[%d], ��ȯ �߻�: (%d,%d)->%d, Skip\n",
					i, pHeapNode->data.fromNodeID,
					pHeapNode->data.toNodeID, pHeapNode->data.key);
				free(pHeapNode);
				continue;
			}
			//��ȯ�� �߻����� �ʴ´ٸ� �ּ� ��� ������ '���� Ʈ��'�� �߰�.
			addEdgeLG(pReturn, pHeapNode->data.fromNodeID,
				pHeapNode->data.toNodeID, pHeapNode->data.key);
			printf("[%d], �ּ� ����ġ: (%d,%d)->%d\n",
				i, pHeapNode->data.fromNodeID,
				pHeapNode->data.toNodeID, pHeapNode->data.key);

			//�߰��� ������ ����� ��尡 �̹� '���� Ʈ��'�� �ִ��� ����.
			//���ٸ� '���� Ʈ��'�� �߰��ϰ� ���� ���� Ʈ���� ��� ������ ����.
			if (0 == pVisited[pHeapNode->data.fromNodeID]) {
				pVisited[pHeapNode->data.fromNodeID] = 1;
			}
			if (0 == pVisited[pHeapNode->data.toNodeID]) {
				pVisited[pHeapNode->data.toNodeID] = 1;
			}
			currentEdgeCount++;
			free(pHeapNode);

			//Step2
			//�˰����� ���� ������ �����ϴ��� Ȯ��.
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

//������ ����ġ ���� ���� ������������ ����.
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
		printf("����, ���� ������ 0��\n");
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

				// ������ �׷������, ������ ������ 2�� ���ϵǹǷ�,
				// ���� ��� id�� ���� ��� id���� ���� ��츸 ���ϵǵ��� �Ѵ�.
				// ��, ���� 1���� ���ϵǵ��� �Ѵ�.
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


// ���� �߰��� ���� ��ȯ�� �߻��ϴ� �� �˻�.
// ������ ��ΰ� �־��ٸ�, ��ȯ�� �߻��Ѵ�.
// ������ ���̿켱Ž��(DFS)�� ���.
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

	// �ʱ�ȭ.
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
				//printf("(%d,%d)-������ ��ΰ� �����մϴ�.\n",
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
