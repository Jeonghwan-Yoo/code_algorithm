#include "zerooneknapsack.h"

#pragma warning(disable:4996)

#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif

//배낭의 용량 capacity, 배낭에 담을 물건 정보 items, 물건 개수 item_count
//배낭에 담긴 짐의 가치가 최대가 되도록 물건을 선택.
int zeroOneKnapsack_Recursive(double capacity, KnapsackItem *items, int item_count) {
	if (item_count == 0 || capacity == 0) {
		return 0;
	}
	//물건을 선택할 수 없을 때
	if (items[item_count - 1].weight > capacity) {
		return zeroOneKnapsack_Recursive(capacity, items, item_count - 1);
	}
	//물건을 선택할 수 있을 때
	else {
		//선택 여부에 따른 최댓값을 구한다.
		//선택했다면 이 물건의 무게만큼 배낭의 용량을 감소시켜야 합니다.
		return max(zeroOneKnapsack_Recursive(capacity, items, item_count - 1), 
			items[item_count - 1].profit + 
			zeroOneKnapsack_Recursive(capacity - items[item_count - 1].weight, 
				items, item_count - 1));
	}
}

//동적 계획법으로 0-1 배낭 문제를 해결하는 함수
//배낭의 용량 capacity, 배낭에 담을 물건들에 대한 정보 items, 물건 종류 개수 item_count
//배낭의 담긴 물건들의 가치를 저장하는 2차원 배열은 ppValues
int zeroOneKnapsack_DP(int capacity, KnapsackItem *items, int item_count) {
	int max_profit = 0;

	int **ppValues = NULL;

	if (capacity <= 0 || item_count <= 0) {
		return max_profit;
	}

	//2차원 배열을 동적으로 할당하고 초기화.
	//2차원 배열의 크기는 배낭의 용량 capacity, 물건 종류 개수 item_count를 곱한 크기.
	ppValues = (int**)malloc(sizeof(int*)*(item_count + 1));
	if (ppValues == NULL) {
		return max_profit;
	}
	for (int i = 0;i < item_count + 1;i++) {
		ppValues[i] = (int*)malloc(sizeof(int)*(capacity + 1));
		if (ppValues[i] != NULL) {
			memset(ppValues[i], 0, sizeof(int)*(capacity + 1));
		}
		else {
			return max_profit;
		}
	}

	//동적 계획법
	//물건의 개수 1개부터 전체 물건의 가짓수 item_count만큼 돕니다.
	//물건의 용량 1부터 최대 용량 capacity까지 돕니다.
	//for루프가 0부터 시작하는 이유는 각 배열의 위치 인덱스 0의 원소를 0으로 초기화하기 위해.
	for (int i = 0;i <= item_count;i++) {
		for (int w = 0;w <= capacity;w++) {
			//하위 문제의 최적해를 기반으로 상위 문제의 최적해를 구하는 부분.
			if (i == 0 || w == 0) { //배열 초기화시
				ppValues[i][w] = 0;
			}
			else if (items[i - 1].weight <= w) {
				ppValues[i][w] = max(items[i - 1].profit + ppValues[i - 1][w - items[i - 1].weight],
					ppValues[i - 1][w]);
			}
			else { //현재 배낭 용량보다 물건의 무게가 더 클 때
				ppValues[i][w] = ppValues[i - 1][w];
			}
		}
	}
	max_profit = ppValues[item_count][capacity]; //마지막 원소에 저장된 배낭의 최대 가치를 반환.

	for (int i = 0;i < item_count + 1;i++) {
		free(ppValues[i]);
	}
	free(ppValues);

	return max_profit;
}

//배낭에 저장할 물건의 가짓수, 각 물건의 가치, 무게를 입력 받은 함수.
void inputItems(KnapsackItem *items, int item_count) {
	int i = 0;
	for (i = 0;i < item_count;i++) {
		printf("%d 번째 물건의 이름을 입력해 주세요\n", i + 1);
		scanf("%s", items[i].name);

		printf("%d 번째 물건의 무게와 가치를 입력해 주세요\n", i + 1);
		scanf("%d %lf", &items[i].weight, &items[i].profit);

		items[i].selected = 0;
	}
}