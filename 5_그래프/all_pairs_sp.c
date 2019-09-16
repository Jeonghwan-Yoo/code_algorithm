#include <stdio.h>
#include <stdlib.h>
#include "linkedlist2.h"
#include "linkedgraph2.h"
#include "all_pairs_sp.h"

//�÷��̵�(Floyd) �˰���
int** shortestPathFloyd(LinkedGraph* pGraph) {
	int **ppDistance = NULL;
	int r = 0, s = 0, v = 0;
	int nodeCount = 0;
	GraphEdge *pEdge = NULL;

	nodeCount = pGraph->nodeCount; //�Է� �Ķ������ �׷��� pGraph�� ��� ���� ����
	//�ִ� �Ÿ� ������ ���� 2���� �迭�� �޸� �Ҵ�
	ppDistance = (int**)malloc(sizeof(int*)*nodeCount); 

	//������ ���鼭 2���� �迭�� �� row�� �ش��ϴ� 1���� �迭�� �������� �Ҵ�.
	for (r = 0;r < nodeCount;r++) {
		ppDistance[r] = (int*)malloc(sizeof(int)*nodeCount);
	}

	//Step-0 �ʱ�ȭ
	//�� ��� ������ �Ÿ��� �ʱ�ȭ. �� ��带 �����ϴ� ������ ����ġ ���� �̿�
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

	//Step 1. 3�� ����
	//3�� ������ ���鼭 �ִ� �Ÿ� ������ ����.
	for (v = 0;v < nodeCount;v++) {
		for (r = 0;r < nodeCount;r++) {
			for (s = 0;s < nodeCount;s++) {
				if (ppDistance[r][v] + ppDistance[v][s] < ppDistance[r][s]) {
					ppDistance[r][s] = ppDistance[r][v] + ppDistance[v][s];
				}
			}
		}
		printf("[%d]-����\n", v + 1);
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