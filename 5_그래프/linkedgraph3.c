
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist3.h"
#include "linkedgraph3.h"

LinkedGraph* createLinkedGraph(int graphType, int nodeCount)
{
	int i = 0;
	LinkedGraph *pReturn = NULL;

	if (nodeCount > 0) {
		pReturn = (LinkedGraph *)malloc(sizeof(LinkedGraph));
		if (pReturn == NULL) {
			printf("오류, 메모리할당(1), in createLinkedGraph()\n");
			return NULL;
		}
		pReturn->graphType = graphType;
		pReturn->nodeCount = nodeCount;
		pReturn->edgeCount = 0;
	}
	else {
		printf("오류, 최대 노드 개수는 0보다 커야합니다\n");
		return NULL;
	}

	pReturn->ppAdjEdge = (LinkedList **)malloc(sizeof(LinkedList*) * nodeCount);
	if (pReturn->ppAdjEdge == NULL) {
		printf("오류, 메모리할당(3), in createLinkedGraph()\n");
		if (pReturn != NULL)  free(pReturn);
		return NULL;
	}
	for (i = 0; i < nodeCount; i++) {
		pReturn->ppAdjEdge[i] = createLinkedList();
		if (pReturn->ppAdjEdge[i] == NULL) {
			printf("오류, 메모리할당(4), in createLinkedGraph()\n");
			if (pReturn->ppAdjEdge != NULL)  free(pReturn->ppAdjEdge);
			if (pReturn != NULL)  free(pReturn);
			return NULL;
		}
	}

	return pReturn;
}

int checkVertexValid(LinkedGraph* pGraph, int node)
{
	if (pGraph != NULL && node >= 0 && node < pGraph->nodeCount) {
		return 1;
	}
	else {
		return 0;
	}
}

int addEdgeInternalLG(LinkedGraph* pGraph, int fromNode, int toNode, int weight)
{
	int ret = 0;

	if (pGraph != NULL
		&& checkVertexValid(pGraph, fromNode)
		&& checkVertexValid(pGraph, toNode)) {
		GraphEdge data;
		data.toNodeID = toNode;
		data.weight = weight;
		addLinkedListData(pGraph->ppAdjEdge[fromNode], 0, data);
	}
	else {
		ret = -1;
	}

	return ret;
}

int addEdgeLG(LinkedGraph* pGraph, int fromNode, int toNode, int weight)
{
	int ret = 0;

	ret = addEdgeInternalLG(pGraph, fromNode, toNode, weight);
	if (0 == ret) {
		pGraph->edgeCount++;

		if (LINKED_GRAPH_TYPE_UNDIRECT == pGraph->graphType) {
			ret = addEdgeInternalLG(pGraph, toNode, fromNode, weight);
		}
	}

	return ret;
}

int removeEdgeInternalLG(LinkedGraph* pGraph, int fromNode, int toNode)
{
	int ret = -1;
	LinkedList *pList = NULL;
	int i = 0, count = 0;

	if (pGraph != NULL
		&& checkVertexValid(pGraph, fromNode)
		&& checkVertexValid(pGraph, toNode)) {
		pList = pGraph->ppAdjEdge[fromNode];
		count = getLinkedListLength(pList);
		for (i = 0; i < count; i++) {
			GraphEdge* pCurrent = getLinkedListData(pList, i);
			if (NULL != pCurrent && pCurrent->toNodeID == toNode) {
				removeLinkedListData(pList, i);
				ret = 0;
				break;
			}
		}
	}
	else {  // 해당되는 간선이 없는 경우 (삭제에 실패한 경우).
		ret = -1;
	}

	return ret;
}


int removeEdgeLG(LinkedGraph* pGraph, int fromNode, int toNode)
{
	int ret = -1;

	ret = removeEdgeInternalLG(pGraph, fromNode, toNode);
	if (0 == ret && LINKED_GRAPH_TYPE_UNDIRECT == pGraph->graphType) {
		ret = removeEdgeInternalLG(pGraph, toNode, fromNode);
	}

	return ret;
}

GraphEdge* getEdgeLG(LinkedGraph* pGraph, int fromNode, int toNode)
{
	GraphEdge *ret = NULL;
	LinkedList *pList = NULL;
	int i = 0, count = 0;

	if (pGraph != NULL
		&& checkVertexValid(pGraph, fromNode)
		&& checkVertexValid(pGraph, toNode)) {
		pList = pGraph->ppAdjEdge[fromNode];
		count = getLinkedListLength(pList);
		for (i = 0; i < count; i++) {
			GraphEdge* pCurrent = getLinkedListData(pList, i);
			if (NULL != pCurrent && pCurrent->toNodeID == toNode) {
				ret = pCurrent;
				break;
			}
		}
	}

	return ret;
}

int getEdgeCountLG(LinkedGraph* pGraph)
{
	int ret = 0;

	if (NULL != pGraph) {
		ret = pGraph->edgeCount;
	}

	return ret;
}

void displayGraphLG(LinkedGraph* pGraph)
{
	int i = 0, j = 0, count = 0;

	if (pGraph != NULL) {
		count = pGraph->nodeCount;
		for (i = 0; i < count; i++) {
			for (j = 0; j < count; j++) {
				GraphEdge* pEdge = getEdgeLG(pGraph, i, j);
				if (NULL != pEdge) {
					printf("%d ", pEdge->weight);
				}
				else {
					printf("0 ");
				}
			}
			printf("\n");
		}
	}
}

void deleteGraphLG(LinkedGraph* pGraph)
{
	int i = 0;

	if (pGraph != NULL) {
		for (i = 0; i < pGraph->nodeCount; i++) {
			deleteLinkedList(pGraph->ppAdjEdge[i]);
		}
		if (pGraph->ppAdjEdge != NULL) free(pGraph->ppAdjEdge);
		free(pGraph);
	}
}
/*

int main(int argc, char *argv[])
{
	int nodeCount = 6;
	LinkedGraph *pG1 = createLinkedGraph(LINKED_GRAPH_TYPE_UNDIRECT, nodeCount);
	if (pG1 != NULL) {
		addEdgeLG(pG1, 0, 1);
		addEdgeLG(pG1, 0, 2);
		addEdgeLG(pG1, 1, 2);
		addEdgeLG(pG1, 2, 3);
		addEdgeLG(pG1, 3, 4);
		addEdgeLG(pG1, 3, 5);
		addEdgeLG(pG1, 4, 5);

		printf("G1: 무방향 그래프\n");
		displayGraphLG(pG1);

		deleteGraphLG(pG1);
	}

	return 0;
}
 */
