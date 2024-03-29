#include <stdio.h>
#include "zerooneknapsack.h"

#pragma warning(disable:4996)

int main() {
	KnapsackItem *items = NULL;

	int item_count = 0;
	double capacity = 0, max_profit = 0;

	printf("가방의 전체 용량을 입력해 주세요\n");
	scanf("%lf", &capacity);

	printf("물건은 몇 개인가요?\n");
	scanf("%d", &item_count);

	if (item_count > 0 && capacity > 0) {
		items = (KnapsackItem*)malloc(sizeof(KnapsackItem)*item_count);
		if (NULL != items) {
			inputItems(items, item_count);

			max_profit = zeroOneKnapsack_Recursive(capacity, items, item_count);
			printf("최대 이익(분할 정복법):%.2f\n", max_profit);

			max_profit = zeroOneKnapsack_DP(capacity, items, item_count);
			printf("최대 이익(동적 계획법):%.2f\n", max_profit);

			free(items);
		}
	}
	else {
		printf("용량과 물건의 개수는 0보다 커야 합니다\n");
	}

	return 0;
}