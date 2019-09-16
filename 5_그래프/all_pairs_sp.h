/*
5.2.2.4구현 소스
all_pairs_sp.h:최단 경로를 구하는 함수 선언(플로이드 알고리즘)
all_pairs_sp.c:최단 경로를 구하는 함수 구현(플로이드 알고리즘)
05_02.c:예제 프로그램
linkedgraph2.h:연결 리스트로 구현한 그래프의 구조체와 함수 선언
linkedgraph2.c:연결 리스트로 구현한 그래프의 함수 구현
linkedlist.h:연결 리스트에 대한 구조체와 함수 선언
linkedlist.c:연결 리스트에 대한 함수 구현

shortestPathFloyd()가 중요한 함수
입력 파라미터로 그래프에 대한 포인터를 전달하면 동적으로 할당된 int 타입의 2차원 배열로 반환.
2차원 배열은 플로이드 알고리즘으로 구한 최단 경로의 거리값을 저장하고 있습니다.
그래프에 있는 모든 노드 사이의 최단 거리를 구한 다음 2차원 정부 배열 ppDistance에 담아 반환합니다.
그래프의 모든 노드 사이의 거리이기 때문에 2차원 배열.
*/

#ifndef _GRAPH_ALL_PAIRS_SP_
#define _GRAPH_ALL_PAIRS_SP_

#define MAX_INT 99999

//플로이드(Floyd)알고리즘
int** shortestPathFloyd(LinkedGraph* pGraph);
void printMatrix(int **ppDistance, int nodeCount);

#endif