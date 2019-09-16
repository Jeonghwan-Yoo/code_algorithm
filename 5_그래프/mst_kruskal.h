/*
5.3.3.4구현 소스
mst_kruskal.h:'최소 비용 신장 트리' 구조체와 함수 선언(크루스칼 알고리즘)
mst_kruskal.c:'최소 비용 신장 트리' 함수 구현(크루스칼 알고리즘)
05_03.c:예제 프로그램
linkedgraph3.h:연결 리스트로 구현한 그래프의 구조체와 함수 선언
linkedgraph3.c:연결 리스트로 구현한 그래프의 함수 구현
linkedlist3.h:연결 리스트에 대한 구조체와 함수 선언
linkedlist3.c:연결 리스트에 대한 함수 구현
grapharrayheap3.h:최소 히프에 대한 구조체와 함수 선언
grapharrayheap3.c:최소 히프에 대한 함수 구현
linkedstack3.h:연결 리스트로 구현한 스택의 구조체와 함수 선언
linkedstack3.c:연결 리스트로 구현한 스택의 함수 구현

최소 히프를 이용하여 간선의 가중치에 따라 오름차순으로 정렬합니다.
스택은 크루스칼 알고리즘으로 간선을 추가할 때 순환이 발생하는지 점검할 때 내부적으로 사용.

*/

#ifndef _GRAPH_MST_KRUSKAL_
#define _GRAPH_MST_KRUSKAL_

//크루스칼(Kruskal) 알고리즘
LinkedGraph *mstKruskal(LinkedGraph* pGraph);

#endif