#include <stdio.h>
#include "coinchange_dp.h"

int main() {
	CoinItem *items = NULL;

	int item_count = 0;
	int change_total = 0, result = 0;

	printf("�Ž������� ���ΰ���?\n");
	scanf_s("%d", &change_total);

	printf("������ ������ �� ���ΰ���?\n");
	scanf_s("%d", &item_count);

	if (item_count > 0 && change_total > 0) {
		items = (CoinItem*)malloc(sizeof(CoinItem)*item_count);
		if (NULL != items) {
			inputItems(items, item_count);

			result = getChange_Recursive(change_total, items, item_count);
			printf("�ּ� ���� ����(���� ����):%d\n", result);

			result = getChange_DP(change_total, items, item_count);
			printf("�ּ� ���� ����(���� ��ȹ��):%d\n", result);

			free(items);
		}
	}
	else {
		printf("�뷮�� ������ ������ 0���� Ŀ�� �մϴ�\n");
	}
	return 0;
}