/*
6.3.2Ž�� �˰����� ����
06_02:���� ���α׷�
fractionalknapsack.h:�κ� �賶 ���� �ذ� ���� ����ü�� �Լ� ����
fractionalknapsack.c:�κ� �賶 ���� �ذ� ���� �Լ� ����

����ü�� ������ �̸��� �����ϴ� ��� ���� name, ���Ը� �����ϴ� ��� ���� weight, 
������ �����ϴ� ��� ���� profit, ���õ� ������ ���Ը� �����ϴ� ��� ���� selected�� ����.

*/

#ifndef fractionalknapsack_h
#define fractionalknapsack_h

#include <stdio.h>
#include <stdlib.h>

typedef struct _KnapsackItem {
	char name[100];
	double weight;
	double profit;
	double selected;
}KnapsackItem;

//�賶�� ��� ���ǵ��� ������ ����ڿ��Լ� �Է� �޽��ϴ�. ��� ���� item_count�� ���� ���� ����.
void inputItems(KnapsackItem *items, int item_count);
//���� Ž�� �˰����� �̿��Ͽ� �κ� �賶 ������ ���� �����ظ� ���ϴ� �Լ�. items�� ����� �Ķ����.
//�� ������ �賶�� �󸶸�ŭ ������ ���õ� ���� ���� ���� items�� ����˴ϴ�.
//��ȯ�� ���� �賶�� ��� ���ǵ��� �� ��ġ(����)�� ��Ÿ���ϴ�.
double fractionalKnapsack(double capacity, KnapsackItem *items, int item_count);
//�ռ� ���� �� ������ �󸶸�ŭ �賶�� ��� �ִ����� ���.
void printResult(KnapsackItem *items, int item_count, double max_profit);

#endif
