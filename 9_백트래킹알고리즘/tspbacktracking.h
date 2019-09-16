/*
9.1.2��Ʈ��ŷ�� ����
09_01.c:���� ���α׷�
tspbacktracking.h:���ǿ� ���� �� ���ϱ� ���� ����� �Լ� ����
tspbacktracking.c:���ǿ� ���� �� ���ϱ� ���� �Լ� ����

�湮�ؾ� �� ��ü ������ ������ NUM_OF_NODE
*/

#ifndef tspbacktracking_h
#define tspbacktracking_h

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define NUM_OF_NODE 4 //������ ����

//���� ã�� ��ΰ� ���������� ����ϴ� �Լ�.
//�׷��� ���� pGraph, �湮�� ��� ���� pPath, �湮�� ���� ���� step, �湮 ��� cost
void printPath(int pGraph[][NUM_OF_NODE], int *pPath, int step, int cost);
//��Ʈ��ŷ �˰����� �̿��Ͽ� ���� ���ǿ� ������ �ذ��ϴ� �Լ�.
void TSP_BackTracking(int pGraph[][NUM_OF_NODE], int step, int cost, int pPath[],
	int pOptimalPath[], int* pMinCost);

#endif

