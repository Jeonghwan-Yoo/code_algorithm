#include "coinchange_dp.h"

//거스름돈 change_total, 동전 정보 items, 동전 개수 item_count
int getChange_Recursive(int change_total, CoinItem *items, int item_count) {
	int k = 0;
	int min = INT_MAX;
	int value = 0;

	if (change_total <= 0) {
		return 0;
	}

	//모든 종류의 동전을 각각 1개씩 사용한 하위 문제를 만듭니다.
	for (k = 0;k < item_count;k++) {
		if (change_total >= items[k].value) {
			value = getChange_Recursive(change_total - items[k].value, items, item_count) + 1;
			//하위 문제 중에서 최솟값을 선택.
			if (value < min) {
				min = value;
			}
		}
	}
	return min;
}

//pTotalCount의 메모리 할당과 관련된 부분이 추가됨.
//동전 k의 금액에 해당하는 dk가 소스에서는 item[j].value입니다.
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
	//마지막 원소에 저장된 최소 동전 개수를 구하여 반환
	min = pTotalCount[change_total]; 
	free(pTotalCount);

	return min;
}

//동전의 종류 개수와 각 동전의 금액을 입력 받는 함수.
void inputItems(CoinItem *items, int item_count) {
	int i = 0;
	for (i = 0;i < item_count;i++) {
		printf("%d 번째 동전의 단위를 입력해 주세요(예, 100)\n", i + 1);
		scanf_s("%d", &items[i].value);

		items[i].selected = 0;
	}
}