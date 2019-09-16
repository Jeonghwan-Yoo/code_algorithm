#include <stdio.h>
#include "coinchange.h"

int main() {
	CoinItem *items = NULL;

	int item_count = 0;
	int change_total = 0, remained = 0;

	printf("거스름돈은 얼마인가요?\n");
	scanf_s("%d", &change_total); //거스름돈이 얼마인지

	printf("동전의 종류는 몇 가지인가요?\n");
	scanf_s("%d", &item_count); //동전의 종류가 몇가지인지 입력 받습니다.

	if (item_count > 0 && change_total > 0) {
		items = (CoinItem*)malloc(sizeof(CoinItem)*item_count); //동전의 종류만큼 메모리를 할당.
		if (NULL != items) {
			inputItems(items, item_count); //동전의 금액을 입력받습니다.
			remained = getChange(change_total, items, item_count); //최소 동전 개수를 구합니다.
			printResult(items, item_count, remained); //동전 개수 정보를 출력합니다.

			free(items); //할당된 메모리를 해제합니다.
		}
	}
	else {
		printf("용량과 물건의 개수는 0보다 커야 합니다\n");
	}
	return 0;
}