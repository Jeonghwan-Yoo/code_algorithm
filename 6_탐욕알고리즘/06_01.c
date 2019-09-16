#include <stdio.h>
#include "coinchange.h"

int main() {
	CoinItem *items = NULL;

	int item_count = 0;
	int change_total = 0, remained = 0;

	printf("�Ž������� ���ΰ���?\n");
	scanf_s("%d", &change_total); //�Ž������� ������

	printf("������ ������ �� �����ΰ���?\n");
	scanf_s("%d", &item_count); //������ ������ ������� �Է� �޽��ϴ�.

	if (item_count > 0 && change_total > 0) {
		items = (CoinItem*)malloc(sizeof(CoinItem)*item_count); //������ ������ŭ �޸𸮸� �Ҵ�.
		if (NULL != items) {
			inputItems(items, item_count); //������ �ݾ��� �Է¹޽��ϴ�.
			remained = getChange(change_total, items, item_count); //�ּ� ���� ������ ���մϴ�.
			printResult(items, item_count, remained); //���� ���� ������ ����մϴ�.

			free(items); //�Ҵ�� �޸𸮸� �����մϴ�.
		}
	}
	else {
		printf("�뷮�� ������ ������ 0���� Ŀ�� �մϴ�\n");
	}
	return 0;
}