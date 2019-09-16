/*
5.3.4.4구현 소스
mst_prim.h:'최소 비용 신장 트리' 구조체와 함수 선언(프림 알고리즘)
mst_prim.c:'최소 비용 신장 트리' 구조체와 함수 구현(프림 알고리즘)
05_04.c:예제 프로그램
linkedgraph4.h:연결 리스트로 구현한 그래프의 구조체와 함수 선언
linkedgraph4.c:연결 리스트로 구현한 그래프의 함수 구현
linkedlist4.h:연결 리스트에 대한 구조체와 함수 선언
linkedlist4.c:연결 리스트에 대한 함수 구현
linkedstack4.h:연결 리스트로 구현한 스택의 구조체와 함수 선언
linkedstack4.c:연결 리스트로 구현한 스택의 함수 구현

*/

#ifndef _GRAPH_MST_PRIM_
#define _GRAPH_MST_PRIM_

#define MAX_INT 99999

//시작노드와 종료 노드의 정보가 모두 필요해서 다시 구조체 만듦.
typedef struct PrimGraphEdgeType {
	int fromNodeID; //시작 노드 ID
	int toNodeID; //중료 노드 ID
	int weight; //가중치
}PrimGraphEdge;

//프림 알고리즘
LinkedGraph *mstPrim(LinkedGraph* pGraph, int startNodeID);

//노드(fromNodeID)와 연결된 간선 중에서
//가중치 가장 작으면서 순환을 발생시키지 않는 간선 선택
void getMinWeightEdge(LinkedGraph* pGraph, LinkedGraph* pMST,
	int fromNodeID, PrimGraphEdge *pMinWegithEdge);

//순환 검사
int checkCycle(LinkedGraph* pGraph, int fromNodeID, int toNodeID);

//기존에 이미 있는 간선인지 검사
int checkEdge(LinkedGraph* pGraph, int fromNodeID, int toNodeID);

#endif