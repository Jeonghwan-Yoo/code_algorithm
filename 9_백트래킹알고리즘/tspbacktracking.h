/*
9.1.2백트래킹의 구현
09_01.c:예제 프로그램
tspbacktracking.h:외판원 문제 해 구하기 관련 상수와 함수 선언
tspbacktracking.c:외판원 문제 해 구하기 관련 함수 구현

방문해야 할 전체 도시의 개수를 NUM_OF_NODE
*/

#ifndef tspbacktracking_h
#define tspbacktracking_h

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define NUM_OF_NODE 4 //도시의 개수

//현재 찾은 경로가 무엇인지를 출력하는 함수.
//그래프 정보 pGraph, 방문한 경로 정보 pPath, 방문한 도시 개수 step, 방문 비용 cost
void printPath(int pGraph[][NUM_OF_NODE], int *pPath, int step, int cost);
//백트래킹 알고리즘을 이용하여 실제 외판원 문제를 해결하는 함수.
void TSP_BackTracking(int pGraph[][NUM_OF_NODE], int step, int cost, int pPath[],
	int pOptimalPath[], int* pMinCost);

#endif

