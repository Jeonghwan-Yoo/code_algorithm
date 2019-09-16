#include <stdio.h>
#include "fractionalknapsack.h"

int main() {
	KnapsackItem *items = NULL;

	int item_count = 0;
	double capacity = 0, max_profit = 0;

	printf("가방의 전체 용량을 입력해 주세요\n");
	scanf_s("%lf", &capacity); //가방의 전체 용량을 입력

	printf("물건을 몇 개인가요?\n");
	scanf_s("%d", &item_count); //배낭에 담길 물건의 졸류가 몇가지인지 입력

	if (item_count > 0 && capacity > 0) {
		items = (KnapsackItem*)malloc(sizeof(KnapsackItem)*item_count);
		if (NULL != items) {
			inputItems(items, item_count);
			max_profit = fractionalKnapsack(capacity, items, item_count); //해답을 구한다.
			printResult(items, item_count, max_profit); //출력한다.

			free(items); //메모리 해제.
		}
	}
	else {
		printf("용량과 물건의 개수는 0보다 커야 합니다\n");
	}
	return 0;
}