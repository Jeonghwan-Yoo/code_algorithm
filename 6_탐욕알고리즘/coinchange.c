#include "coinchange.h"

/*
C언어에서는 퀵정렬을 제공해 주는 함수 qsort()를 기본 라이브러리로 제공합니다.
#include <stdlib.h>
void qsort(void *base, size_t nel, size_t width, int (*compare)(const void*, const void*));
base는 배열의 시작 주소.
nel은 배열에 저장된 원소의 개수
width는 원소 1개의 크기
compare는 실제 비교 연산을 수행하는 함수 포인터.

함수 포인터
int compare((void *)&elem1, (void *)&elem2);
비교 연산을 수행할 2개의 원소에 대한 포인터 elem1과 elem2를 전달 받고 결과값으로 정수값을 반환합니다.
<0:음수반환
0:0반환
>0:양수반환.
만약 내림차순으로 정렬하고 싶으면 다음과 같이 반환하면 됩니다. 
>0:elem1<elem2
0:elem1==elem2
<0:elem1>elem2
오름차순이면 반대로 반환하게 하면 됩니다.

qsort()는 내부적으로 비교 함수를 이용하여 배열 내의 모든 원소들을 크기에 따라 정렬합니다.
오름차순 혹은 내림차순은 compare()가 어떻게 구현되었는지에 따라 결정됩니다.
*/

//qsort()를 호출하여 동전을 단위 순서로 정렬할 때 사용하는 함수.
int compare_CoinItem_value(const void *value1, const void *value2) {
	CoinItem *item1 = (CoinItem*)value1;
	CoinItem *item2 = (CoinItem*)value2;

	//구조체의 멤버 변수를 이용하여 비교 연산
	if (item1->value < item2->value) {
		return 1;
	}
	else if (item1->value > item2->value) {
		return -1;
	}
	else {
		return 0;
	}
}

//현재 선택된 동전의 개수를 구하는 함수
int getChangeCount(int target_change, int coin_value) {
	int count = 0;

	//남은 금액이 동전 금액보다 커야 현재 동전을 사용할 수 있다.
	if (target_change >= coin_value) {
		count = target_change / coin_value; //동전의 개수를 구합니다.
	}

	return count;
}

//입력 파라미터로 거스름돈 금액인 change_total, 동전 정보가 저장된 배열 items, 동전의 개수 item_count
int getChange(int change_total, CoinItem *items, int item_count) {
	int current_change = change_total;
	int i = 0;

	//동전 금액이 큰 순서대로 정렬
	qsort(items, item_count, sizeof(CoinItem), compare_CoinItem_value);

	//동전 정보를 출력
	printf("정렬 결과\n\t값\n");
	for (i = 0;i < item_count;i++) {
		printf("%d\t%d\n", i, items[i].value);
	}

	//탐욕 알고리즘 구현부분
	//items는 포인터로 전달되어 입출력 파라미터의 역할을 합니다.
	for (i = 0;i < item_count;i++) {
		int count = getChangeCount(current_change, items[i].value); //부분 해 도출.
		items[i].selected = count;
		current_change = current_change - count * items[i].value; //남은 거스름돈을 다시 계산.
	}
	return current_change; //현재 남은 거스름돈을 반환. 잘끝나면 0.
}

//얼마짜리 동전이 있는지를 사용자에게서 입력 받는 함수.
void inputItems(CoinItem *items, int item_count) {
	int i = 0;
	for (i = 0;i < item_count;i++) {
		printf("%d 번째 동전의 단위를 입력해 주세요 (예, 100)\n", i + 1);
		scanf_s("%d", &items[i].value);
		items[i].selected = 0;
	}
}

//알고리즘의 처리 결과를 출력하는 함수.
void printResult(CoinItem *items, int item_count, int remained) {
	int i = 0;
	printf("(동전)\t(동전개수)\n");
	for (i = 0;i < item_count;i++) {
		printf("%d\t%d\n", items[i].value, items[i].selected);
	}
	printf("남은 거스름돈:%d\n", remained);
}