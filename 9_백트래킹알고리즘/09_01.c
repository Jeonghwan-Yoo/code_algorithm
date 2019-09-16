#include <stdio.h>
#include "tspbacktracking.h"

//�� ���� ������ ���� ������ �����ϴ� �迭 ����.
int costGraph[NUM_OF_NODE][NUM_OF_NODE] = {
	{0, 10, 15, 20},
	{10, 0, 35, 25},
	{15, 35, 0, 30},
	{20, 25, 30, 0}
};

int main(void) {
	int mincost = INT_MAX;
	int path[NUM_OF_NODE + 1] = { 0 }, optimalPath[NUM_OF_NODE + 1] = { 0 };
	path[0] = 0; //���� ��� ����:0�� ���

	printf("Traveling Salesman (��Ʈ��ŷ �˰���)\n");
	//������ �� �湮 ���� ���� step�� 0�̸� ��������� ��� cost�� 0�Դϴ�.
	TSP_BackTracking(costGraph, 0, 0, path, optimalPath, &mincost);

	printf("\n�ּ� ���:%d\n", mincost);
	printPath(costGraph, optimalPath, NUM_OF_NODE, mincost);

	return 0;
}