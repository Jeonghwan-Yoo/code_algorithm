#include <stdio.h>
#include "fractionalknapsack.h"

int main() {
	KnapsackItem *items = NULL;

	int item_count = 0;
	double capacity = 0, max_profit = 0;

	printf("������ ��ü �뷮�� �Է��� �ּ���\n");
	scanf_s("%lf", &capacity); //������ ��ü �뷮�� �Է�

	printf("������ �� ���ΰ���?\n");
	scanf_s("%d", &item_count); //�賶�� ��� ������ ������ ������� �Է�

	if (item_count > 0 && capacity > 0) {
		items = (KnapsackItem*)malloc(sizeof(KnapsackItem)*item_count);
		if (NULL != items) {
			inputItems(items, item_count);
			max_profit = fractionalKnapsack(capacity, items, item_count); //�ش��� ���Ѵ�.
			printResult(items, item_count, max_profit); //����Ѵ�.

			free(items); //�޸� ����.
		}
	}
	else {
		printf("�뷮�� ������ ������ 0���� Ŀ�� �մϴ�\n");
	}
	return 0;
}