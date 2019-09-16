#ifndef _LINKEDGRAPH_
#define _LINKEDGRAPH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist3.h"

#define LINKED_GRAPH_TYPE_DIRECT         0
#define LINKED_GRAPH_TYPE_UNDIRECT       1

typedef struct LinkedGraphType
{
	int graphType;
	int nodeCount;          // ��� ����.
	int edgeCount;          // ���� ����.
	LinkedList** ppAdjEdge;	// ���� ������ ���� ���� ����Ʈ (������)�� �迭
}  LinkedGraph;

LinkedGraph* createLinkedGraph(int graphType, int nodeCount);

int checkVertexValid(LinkedGraph* pGraph, int node);

int addEdgeInternalLG(LinkedGraph* pGraph, int fromNode, int toNode, int weight);

int addEdgeLG(LinkedGraph* pGraph, int fromNode, int toNode, int weight);

int removeEdgeInternalLG(LinkedGraph* pGraph, int fromNode, int toNode);

int removeEdgeLG(LinkedGraph* pGraph, int fromNode, int toNode);

GraphEdge* getEdgeLG(LinkedGraph* pGraph, int fromNode, int toNode);

void displayGraphLG(LinkedGraph* pGraph);

void deleteGraphLG(LinkedGraph* pGraph);

#endif


