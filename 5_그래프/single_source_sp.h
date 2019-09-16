/*
5.2.1.4구현 소스
single_source_sp.h:최단 경로를 구하는 함수 선언(다잌스트라 알고리즘)
single_source_sp.c:최단 경로를 구하는 함수 구현(다잌스트라 알고리즘)
05_01.c:예제 프로그램
linkedgraph1.h:연결 리스트로 구현한 그래프의 구조체와 함수 선언
linkedgraph1.c:연결 리스트로 구현한 그래프의 함수 구현
linkedlist.h:연결 리스트에 대한 구조체와 함수 선언
linkedlist.c:연결 리스트에 대한 함수 구현


*/

#ifndef _GRAPH_SP_
#define _GRAPH_SP_

#define MAX_INT 99999 //oo에 해당.

int *shortestPathDijkstra(LinkedGraph* pGraph, int sourceNodeID);
int getMinDistane(int* pDistance, int *ps, int nodeCount);
void printDistanceInfo(int sourceNodeID, int* pDistance, int nodeCount);

#endif