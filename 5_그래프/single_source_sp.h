/*
5.2.1.4���� �ҽ�
single_source_sp.h:�ִ� ��θ� ���ϴ� �Լ� ����(�ٟ彺Ʈ�� �˰���)
single_source_sp.c:�ִ� ��θ� ���ϴ� �Լ� ����(�ٟ彺Ʈ�� �˰���)
05_01.c:���� ���α׷�
linkedgraph1.h:���� ����Ʈ�� ������ �׷����� ����ü�� �Լ� ����
linkedgraph1.c:���� ����Ʈ�� ������ �׷����� �Լ� ����
linkedlist.h:���� ����Ʈ�� ���� ����ü�� �Լ� ����
linkedlist.c:���� ����Ʈ�� ���� �Լ� ����


*/

#ifndef _GRAPH_SP_
#define _GRAPH_SP_

#define MAX_INT 99999 //oo�� �ش�.

int *shortestPathDijkstra(LinkedGraph* pGraph, int sourceNodeID);
int getMinDistane(int* pDistance, int *ps, int nodeCount);
void printDistanceInfo(int sourceNodeID, int* pDistance, int nodeCount);

#endif