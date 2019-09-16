#include <stdio.h>
#include "zerooneknapsack.h"

#pragma warning(disable:4996)

int main() {
	KnapsackItem *items = NULL;

	int item_count = 0;
	double capacity = 0, max_profit = 0;

	printf("������ ��ü �뷮�� �Է��� �ּ���\n");
	scanf("%lf", &capacity);

	printf("������ �� ���ΰ���?\n");
	scanf("%d", &item_count);

	if (item_count > 0 && capacity > 0) {
		items = (KnapsackItem*)malloc(sizeof(KnapsackItem)*item_count);
		if (NULL != items) {
			inputItems(items, item_count);

			max_profit = zeroOneKnapsack_Recursive(capacity, items, item_count);
			printf("�ִ� ����(���� ������):%.2f\n", max_profit);

			max_profit = zeroOneKnapsack_DP(capacity, items, item_count);
			printf("�ִ� ����(���� ��ȹ��):%.2f\n", max_profit);

			free(items);
		}
	}
	else {
		printf("�뷮�� ������ ������ 0���� Ŀ�� �մϴ�\n");
	}

	return 0;
}