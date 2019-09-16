#include "zerooneknapsack.h"

#pragma warning(disable:4996)

#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif

//�賶�� �뷮 capacity, �賶�� ���� ���� ���� items, ���� ���� item_count
//�賶�� ��� ���� ��ġ�� �ִ밡 �ǵ��� ������ ����.
int zeroOneKnapsack_Recursive(double capacity, KnapsackItem *items, int item_count) {
	if (item_count == 0 || capacity == 0) {
		return 0;
	}
	//������ ������ �� ���� ��
	if (items[item_count - 1].weight > capacity) {
		return zeroOneKnapsack_Recursive(capacity, items, item_count - 1);
	}
	//������ ������ �� ���� ��
	else {
		//���� ���ο� ���� �ִ��� ���Ѵ�.
		//�����ߴٸ� �� ������ ���Ը�ŭ �賶�� �뷮�� ���ҽ��Ѿ� �մϴ�.
		return max(zeroOneKnapsack_Recursive(capacity, items, item_count - 1), 
			items[item_count - 1].profit + 
			zeroOneKnapsack_Recursive(capacity - items[item_count - 1].weight, 
				items, item_count - 1));
	}
}

//���� ��ȹ������ 0-1 �賶 ������ �ذ��ϴ� �Լ�
//�賶�� �뷮 capacity, �賶�� ���� ���ǵ鿡 ���� ���� items, ���� ���� ���� item_count
//�賶�� ��� ���ǵ��� ��ġ�� �����ϴ� 2���� �迭�� ppValues
int zeroOneKnapsack_DP(int capacity, KnapsackItem *items, int item_count) {
	int max_profit = 0;

	int **ppValues = NULL;

	if (capacity <= 0 || item_count <= 0) {
		return max_profit;
	}

	//2���� �迭�� �������� �Ҵ��ϰ� �ʱ�ȭ.
	//2���� �迭�� ũ��� �賶�� �뷮 capacity, ���� ���� ���� item_count�� ���� ũ��.
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

	//���� ��ȹ��
	//������ ���� 1������ ��ü ������ ������ item_count��ŭ ���ϴ�.
	//������ �뷮 1���� �ִ� �뷮 capacity���� ���ϴ�.
	//for������ 0���� �����ϴ� ������ �� �迭�� ��ġ �ε��� 0�� ���Ҹ� 0���� �ʱ�ȭ�ϱ� ����.
	for (int i = 0;i <= item_count;i++) {
		for (int w = 0;w <= capacity;w++) {
			//���� ������ �����ظ� ������� ���� ������ �����ظ� ���ϴ� �κ�.
			if (i == 0 || w == 0) { //�迭 �ʱ�ȭ��
				ppValues[i][w] = 0;
			}
			else if (items[i - 1].weight <= w) {
				ppValues[i][w] = max(items[i - 1].profit + ppValues[i - 1][w - items[i - 1].weight],
					ppValues[i - 1][w]);
			}
			else { //���� �賶 �뷮���� ������ ���԰� �� Ŭ ��
				ppValues[i][w] = ppValues[i - 1][w];
			}
		}
	}
	max_profit = ppValues[item_count][capacity]; //������ ���ҿ� ����� �賶�� �ִ� ��ġ�� ��ȯ.

	for (int i = 0;i < item_count + 1;i++) {
		free(ppValues[i]);
	}
	free(ppValues);

	return max_profit;
}

//�賶�� ������ ������ ������, �� ������ ��ġ, ���Ը� �Է� ���� �Լ�.
void inputItems(KnapsackItem *items, int item_count) {
	int i = 0;
	for (i = 0;i < item_count;i++) {
		printf("%d ��° ������ �̸��� �Է��� �ּ���\n", i + 1);
		scanf("%s", items[i].name);

		printf("%d ��° ������ ���Կ� ��ġ�� �Է��� �ּ���\n", i + 1);
		scanf("%d %lf", &items[i].weight, &items[i].profit);

		items[i].selected = 0;
	}
}