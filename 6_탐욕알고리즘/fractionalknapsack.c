#include "fractionalknapsack.h"
#pragma warning(disable:4996)

//qsort() �Լ��� ȣ���Ͽ� ������ (��ġ/����) ���� ������ ������ �� ����ϴ� �Լ�.
//���޵Ǵ� 2�� ���ҿ� ���ؼ� �� ������ �����ϴ� �Լ�.
int compare_KnapsackItem_ratio(const void *value1, const void *value2) {
	KnapsackItem *item1 = (KnapsackItem*)value1;
	KnapsackItem *item2 = (KnapsackItem*)value2;

	double ratio1 = item1->profit / item1->weight;
	double ratio2 = item2->profit / item2->weight;

	//�� ������ ������ ���ؼ� �� ����
	//������ ū ������� ���� �ؾ� �մϴ�.
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

//�賶�� �뷮�� ��Ÿ���� capacity, ���ǵ��� ������ �����ϴ� items, ������ �������� item_count
double fractionalKnapsack(double capacity, KnapsackItem *items, int item_count) {
	double max_profit = 0, current_weight = 0;
	int i = 0;

	//(����/����)���� ������� ������ ����
	qsort(items, item_count, sizeof(KnapsackItem), compare_KnapsackItem_ratio);

	//���ĵ� ���� ������ ���
	printf("���� ���\n\t����\t��ġ\t����\n");
	for (i = 0;i < item_count;i++) {
		printf("%d\t%f\t%f\t%f\n", i, items[i].weight, items[i].profit,
			items[i].profit / items[i].weight);
	}

	//Ž�� �˰��� �κ�.
	//������ ���� ū ���Ǻ��� ������� ��� ���ǿ� ���ؼ� �κ��ظ� ����մϴ�.
	for (i = 0;i < item_count;i++) {
		if (current_weight + items[i].weight < capacity) { //��� �賶�� ���� �� �ִ��� ����.
			items[i].selected = items[i].weight; //���� weight ��� �賶�� ��ܼ�
			current_weight = current_weight + items[i].weight; //���� �賶�� ��� ����+item����
			max_profit += items[i].profit; //���� �賶�� ��� ��ġ+item��ġ
		}
		else { //���� �賶�� ���� �� ���ٸ�.
			double remaining = capacity - current_weight; //�賶�� ���������� ���� ������ �뷮.
			items[i].selected = remaining; //���� �뷮��ŭ ���� ���õ� ������ ���� �� �ֽ��ϴ�.
			max_profit += items[i].profit*items[i].selected / items[i].weight; //�Ϻ��� ��ġ
			break;
		}
	}
	return max_profit; //���������� �賶�� ��� ���ǵ��� ��ġ�� �󸶸�ŭ�� �Ǵ��� ��ȯ.
}

//�賶�� ��� ���ǵ��� ������ ����ڿ��Լ� �Է� �޴� �Լ�.
void inputItems(KnapsackItem *items, int item_count) {
	int i = 0;
	for (i = 0;i < item_count;i++) {
		printf("%d ��° ������ �̸��� �Է��� �ּ���\n", i + 1);
		scanf("%s", items[i].name);

		printf("%d ��° ������ ���Կ� ��ġ�� �Է��� �ּ���\n", i + 1);
		scanf("%lf %lf", &items[i].weight, &items[i].profit);

		items[i].selected = 0;
	}
}

//�˰����� ó�� ����� ����ϴ� �Լ�, �� ������ �󸶸�ŭ �賶�� ��� �ִ����� ���.
void printResult(KnapsackItem *items, int item_count, double max_profit) {
	int i = 0;
	printf("�ִ� ����:%.2f\n", max_profit);
	printf("(���õ� ����)\t(��ü ����)\n");
	for (i = 0;i < item_count;i++) {
		printf("%s\t%.2f\t%.2f\n", items[i].name, items[i].selected, items[i].weight);
	}
}