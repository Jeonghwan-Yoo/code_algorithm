#include <stdio.h>
#include <stdlib.h>
#include "linkedlist1.h"
#include "linkedgraph1.h"
#include "single_source_sp.h"

//�ٟ彺Ʈ�� �˰���
int *shortestPathDijkstra(LinkedGraph* pGraph, int sourceNodeID) {
	int *pDistance = NULL;

	int *pS = NULL;
	int nodeCount = 0, i = 0;
	int vNodeID = 0, y_w = 0, y_v = 0;

	LinkedList *pEdgeList = NULL;
	LinkedListNode *pEdgeNode = NULL;
	GraphEdge *pEdge = NULL;

	nodeCount = pGraph->nodeCount; //pGraph�� ��� ���� ����
	//��ȯ �� �� ���� S ������ ���� �޸� �Ҵ�
	pDistance = (int*)malloc(sizeof(int)*nodeCount);  
	pS = (int*)malloc(sizeof(int)*nodeCount); //S�� ���ԵǾ����� 1, �ƴϸ� 0.
	printf("Step-0. �ʱ�ȭ\n");
	//�ʱ�ȭ �ܰ�. ���� S�� �� ��带 �߰��ϰ� ���� ������ �� �������� �Ÿ��� ����.
	for (i = 0;i < nodeCount;i++) {
		pS[i] = 1;
		pEdge = getEdgeLG(pGraph, sourceNodeID, i);
		if (NULL != pEdge) { //���� ���� ���� ����Ǿ��ٸ� ����� ������ ����ġ�� ����.
			pDistance[i] = pEdge->weight;
		}
		else { //������� �ʾҴٸ� MAX_INT
			pDistance[i] = MAX_INT;
		}
	}
	//���� ��忡 ���� ���� ����. ���� �������� �Ÿ��� 0�̸� ���� S���� ����.
	pDistance[sourceNodeID] = 0;
	pS[sourceNodeID] = 0;

	printDistanceInfo(sourceNodeID, pDistance, nodeCount);

	for (i = 0;i < nodeCount - 1;i++) {
		printf("\n[%d]��° ����\n", i + 1);

		//Step-1.
		//���� S�� �ִ� �Ÿ��� ������ ��带 ����.
		vNodeID = getMinDistance(pDistance, pS, nodeCount);
		pS[vNodeID] = 0;

		pEdgeList = pGraph->ppAdjEdge[vNodeID]; //���õ� ����� ����Ʈ�� ������ ������ ����.
		//������ ���鼭 ���� ������ ���� ������ ��� ����� �ִ� �Ÿ��� ������ �ǽ�.
		pEdgeNode = pEdgeList->headerNode.pLink;
		while (pEdgeNode != NULL) {
			int wNodeID = pEdgeNode->data.toNodeID;
			int c_v_w = pEdgeNode->data.weight;

			y_v = pDistance[vNodeID];
			y_w = pDistance[wNodeID];
			//���� �ִ� �Ÿ��� ���ο� �ִ� �Ÿ��� ��.
			if (y_v + c_v_w < y_w) {
				pDistance[wNodeID] = y_v + c_v_w;
				printf("\t[%d]����� ���� ���� [%d]�� ����, �Ÿ��� [%d]���� "
					"[%d](��)�� Line �پ��\n",wNodeID,vNodeID,y_w,y_v+c_v_w);
			}
			pEdgeNode = pEdgeNode->pLink;
		}
		printDistanceInfo(sourceNodeID, pDistance, nodeCount);
	}
	free(pS);

	return pDistance;
}

//S�߿��� �ִ� �Ÿ��� ������ ��带 ���ϴ� �Լ�
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

//���ݱ��� ���� �Ÿ��� ����ϴ� �Լ�
void printDistanceInfo(int sourceNodeID, int* pDistance, int nodeCount) {
	int i = 0;

	for (i = 0;i < nodeCount;i++) {
		printf("\t[%d]���� [%d]���� �Ÿ�:%d\n", sourceNodeID, i, pDistance[i]);
	}
}