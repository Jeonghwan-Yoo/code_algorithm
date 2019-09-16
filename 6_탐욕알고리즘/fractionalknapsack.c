#include "fractionalknapsack.h"
#pragma warning(disable:4996)

//qsort() 함수를 호출하여 물건의 (가치/무게) 비율 순서로 정렬할 때 사용하는 함수.
//전달되는 2개 원소에 대해서 비교 연산을 수행하는 함수.
int compare_KnapsackItem_ratio(const void *value1, const void *value2) {
	KnapsackItem *item1 = (KnapsackItem*)value1;
	KnapsackItem *item2 = (KnapsackItem*)value2;

	double ratio1 = item1->profit / item1->weight;
	double ratio2 = item2->profit / item2->weight;

	//각 원소의 비율에 대해서 비교 연산
	//비율이 큰 순서대로 정렬 해야 합니다.
	if (ratio1 < ratio2) {
		return 1;
	}
	else if (ratio1 > ratio2) {
		return -1;
	}
	else {
		return 0;
	}
}

//배낭의 용량을 나타내는 capacity, 물건들의 정보를 저장하는 items, 물건의 가짓수인 item_count
double fractionalKnapsack(double capacity, KnapsackItem *items, int item_count) {
	double max_profit = 0, current_weight = 0;
	int i = 0;

	//(가격/무게)비율 순서대로 물건을 정렬
	qsort(items, item_count, sizeof(KnapsackItem), compare_KnapsackItem_ratio);

	//정렬된 물건 정보를 출력
	printf("정렬 결과\n\t무게\t가치\t비율\n");
	for (i = 0;i < item_count;i++) {
		printf("%d\t%f\t%f\t%f\n", i, items[i].weight, items[i].profit,
			items[i].profit / items[i].weight);
	}

	//탐욕 알고리즘 부분.
	//비율이 가장 큰 물건부터 순서대로 모든 물건에 대해서 부분해를 계산합니다.
	for (i = 0;i < item_count;i++) {
		if (current_weight + items[i].weight < capacity) { //모두 배낭에 담을 수 있는지 조사.
			items[i].selected = items[i].weight; //무게 weight 모두 배낭에 담겨서
			current_weight = current_weight + items[i].weight; //현재 배낭에 담긴 무게+item무게
			max_profit += items[i].profit; //현재 배낭에 담긴 가치+item가치
		}
		else { //전부 배낭에 담을 수 없다면.
			double remaining = capacity - current_weight; //배낭에 마지막으로 남은 마지막 용량.
			items[i].selected = remaining; //남은 용량만큼 현재 선택된 물건을 담을 수 있습니다.
			max_profit += items[i].profit*items[i].selected / items[i].weight; //일부의 가치
			break;
		}
	}
	return max_profit; //최종적으로 배낭에 담긴 물건들의 가치가 얼마만큼이 되는지 반환.
}

//배낭에 담길 물건들의 정보를 사용자에게서 입력 받는 함수.
void inputItems(KnapsackItem *items, int item_count) {
	int i = 0;
	for (i = 0;i < item_count;i++) {
		printf("%d 번째 물건의 이름을 입력해 주세요\n", i + 1);
		scanf("%s", items[i].name);

		printf("%d 번째 물건의 무게와 가치를 입력해 주세요\n", i + 1);
		scanf("%lf %lf", &items[i].weight, &items[i].profit);

		items[i].selected = 0;
	}
}

//알고리즘의 처리 결과를 출력하는 함수, 각 물건이 얼마만큼 배낭에 담겨 있는지를 출력.
void printResult(KnapsackItem *items, int item_count, double max_profit) {
	int i = 0;
	printf("최대 이익:%.2f\n", max_profit);
	printf("(선택된 무게)\t(전체 무게)\n");
	for (i = 0;i < item_count;i++) {
		printf("%s\t%.2f\t%.2f\n", items[i].name, items[i].selected, items[i].weight);
	}
}