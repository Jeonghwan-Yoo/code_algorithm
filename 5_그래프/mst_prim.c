#include <stdio.h>
#include <stdlib.h>

#include "linkedgraph4.h"
#include "linkedstack4.h"

#include "mst_prim.h"

// Prim �˰���
LinkedGraph* mstPrim(LinkedGraph* pGraph, int startNodeID)
{
	LinkedGraph*    pReturn = NULL;
	int             *pSelected = NULL; //��尡 ���õǾ��� Ȯ��. 1�̸� ����.

	int             i = 0, nodeCount = 0;
	int             mstNodeCount = 0;
	int             fromNodeID = 0;
	PrimGraphEdge   minWeightEdge = { 0, };

	if (pGraph == NULL) {
		printf("Graph is NULL\n");
		return pReturn;
	}

	nodeCount = pGraph->nodeCount;
	//�ּ� ��� ���� Ʈ�� ����. pGraph�� ��尳�� �̿�.
	pReturn = createLinkedGraph(LINKED_GRAPH_TYPE_UNDIRECT, nodeCount);
	
	//���� Ʈ���� ��尡 �߰� �Ǿ����� �����ϴ� 1���� �迭 ���� �� �ʱ�ȭ.
	pSelected = (int*)malloc(sizeof(int) * nodeCount);
	if (NULL == pReturn || NULL == pSelected) {
		return NULL;
	}
	memset(pSelected, 0, sizeof(int) * nodeCount);

	//���۳�带 �߰��ϰ� ���õ� ��� ������ 1���� ������.
	pSelected[startNodeID] = 1;
	mstNodeCount = 1;

	//�˰��� ���� ������ �����ϴ��� Ȯ��
	while (mstNodeCount < nodeCount) {
		//���� �ʱ�ȭ. �ּ� ����ġ ���� ������ ���� ������ �����ϴ� �����̴�.
		//getMinWeightEdge()�� ����� ��ȯ �޴� ��� �Ķ���ͷ� ���. �Է�~��� �Ķ���� ����
		//���� �ּ� ����ġ ���� ������ ���� ������ �����ϰ� ������(�Է�)
		//�Լ� ���ο��� �ּ� ����ġ ���� ������ ������ ������ ����� �� �ֱ� ����(���)
		minWeightEdge.fromNodeID = 0;
		minWeightEdge.toNodeID = 0;
		minWeightEdge.weight = MAX_INT;

		//��� ������ ���� ������ ���鼭 �ּ� ����ġ�� ������ ������ ������.
		//minWeightEdge���� ���ݱ��� ã�� �ּ� ��� ����ġ�� ���� ������ ����Ǿ� �ִ�.
		//�׸��� ���� ����� ����ġ ������ �� ���� �������θ� ����� �� ����.
		for (i = 0; i < nodeCount; i++) {
			if (pSelected[i] == 1) {
				fromNodeID = i;
				getMinWeightEdge(pGraph, pReturn, fromNodeID, &minWeightEdge);
			}
		}
		//�ռ� ���õ� ���� ������ '���� ���� Ʈ��'�� �߰���.
		//������ �� 1����.
		addEdgeLG(pReturn, minWeightEdge.fromNodeID,
			minWeightEdge.toNodeID, minWeightEdge.weight);
		pSelected[minWeightEdge.toNodeID] = 1;
		mstNodeCount++;

		printf("[%d], �ּ� ����ġ: (%d,%d)->%d, ��� %d �߰�\n",
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


// ����(fromNodeID)�� ����� ������ ��,
// ����ġ�� ���� �����鼭 ��ȯ�� �߻���Ű�� �ʴ� ������ ����.
//fromNodeID�� �̿��Ͽ� �� ���� ����� ������ ���ؼ� while����.
void getMinWeightEdge(LinkedGraph* pGraph, LinkedGraph* pMST,
	int fromNodeID, PrimGraphEdge *pMinWeightEdge) {
	LinkedListNode  *pListNode = NULL;
	int             isCycle = 0;
	int             isAlready = 0;
	LinkedList      *pEdgeList = pGraph->ppAdjEdge[fromNodeID];

	// pListNode: V(T)�� �μӵ� ������ �� �ϳ��� ����.
	pListNode = pEdgeList->headerNode.pLink;
	//���� ��� ������ toNodeID�� ����ġ ���� weight�� ���� ������ ������ ����ϴ�.
	//�׸��� �ּ� ����ġ ���� ������ �������� �����մϴ�.
	while (pListNode != NULL) {
		int toNodeID = pListNode->data.toNodeID;
		int weight = pListNode->data.weight;

		// �ּҰ����� ����.
		if (pListNode->data.weight < pMinWeightEdge->weight) {
			// ������ E(T)�� ���� �������� ����
			isAlready = checkEdge(pMST, fromNodeID, toNodeID);
			if (0 == isAlready) {
				// ��ȯ�� �߻���Ű���� ����
				isCycle = checkCycle(pMST, fromNodeID, toNodeID);
				if (0 != isCycle) {
					printf("��ȯ �߻�: (%d,%d)->%d, Skip\n",
						fromNodeID,
						toNodeID, pListNode->data.weight);
				}
			}
			// ������ �̹� E(T)�� ���� ������ �ƴϸ鼭,
			// ��ȯ�� �߻���Ű�� �ʴ�,
			// �ּ� ����ġ ������ ����.
			if (isAlready == 0 && isCycle == 0) {
				pMinWeightEdge->fromNodeID = fromNodeID;
				pMinWeightEdge->toNodeID = toNodeID;
				pMinWeightEdge->weight = weight;
			}
		}

		pListNode = pListNode->pLink;
	}
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
