#include "coinchange_dp.h"

//�Ž����� change_total, ���� ���� items, ���� ���� item_count
int getChange_Recursive(int change_total, CoinItem *items, int item_count) {
	int k = 0;
	int min = INT_MAX;
	int value = 0;

	if (change_total <= 0) {
		return 0;
	}

	//��� ������ ������ ���� 1���� ����� ���� ������ ����ϴ�.
	for (k = 0;k < item_count;k++) {
		if (change_total >= items[k].value) {
			value = getChange_Recursive(change_total - items[k].value, items, item_count) + 1;
			//���� ���� �߿��� �ּڰ��� ����.
			if (value < min) {
				min = value;
			}
		}
	}
	return min;
}

//pTotalCount�� �޸� �Ҵ�� ���õ� �κ��� �߰���.
//���� k�� �ݾ׿� �ش��ϴ� dk�� �ҽ������� item[j].value�Դϴ�.
int getChange_DP(int change_total, CoinItem *items, int item_count) {

	int min = 0;
	int *pTotalCount = NULL;

	pTotalCount = (int*)malloc(sizeof(int)*(change_total + 1));
	if (pTotalCount == NULL) {
		return min;
	}
	memset(pTotalCount, 0, sizeof(int)*item_count);

	for (int i = 1;i <= change_total;i++) {
		min = 9999;
		for (int j = 0;j < item_count;j++) {
			if (items[j].value <= i) {
				if (min > pTotalCount[i - items[j].value] + 1) {
					min = pTotalCount[i - items[j].value] + 1;
				}
			}
		}
		pTotalCount[i] = min;
	}
	//������ ���ҿ� ����� �ּ� ���� ������ ���Ͽ� ��ȯ
	min = pTotalCount[change_total]; 
	free(pTotalCount);

	return min;
}

//������ ���� ������ �� ������ �ݾ��� �Է� �޴� �Լ�.
void inputItems(CoinItem *items, int item_count) {
	int i = 0;
	for (i = 0;i < item_count;i++) {
		printf("%d ��° ������ ������ �Է��� �ּ���(��, 100)\n", i + 1);
		scanf_s("%d", &items[i].value);

		items[i].selected = 0;
	}
}