#include "coinchange.h"

/*
C������ �������� ������ �ִ� �Լ� qsort()�� �⺻ ���̺귯���� �����մϴ�.
#include <stdlib.h>
void qsort(void *base, size_t nel, size_t width, int (*compare)(const void*, const void*));
base�� �迭�� ���� �ּ�.
nel�� �迭�� ����� ������ ����
width�� ���� 1���� ũ��
compare�� ���� �� ������ �����ϴ� �Լ� ������.

�Լ� ������
int compare((void *)&elem1, (void *)&elem2);
�� ������ ������ 2���� ���ҿ� ���� ������ elem1�� elem2�� ���� �ް� ��������� �������� ��ȯ�մϴ�.
<0:������ȯ
0:0��ȯ
>0:�����ȯ.
���� ������������ �����ϰ� ������ ������ ���� ��ȯ�ϸ� �˴ϴ�. 
>0:elem1<elem2
0:elem1==elem2
<0:elem1>elem2
���������̸� �ݴ�� ��ȯ�ϰ� �ϸ� �˴ϴ�.

qsort()�� ���������� �� �Լ��� �̿��Ͽ� �迭 ���� ��� ���ҵ��� ũ�⿡ ���� �����մϴ�.
�������� Ȥ�� ���������� compare()�� ��� �����Ǿ������� ���� �����˴ϴ�.
*/

//qsort()�� ȣ���Ͽ� ������ ���� ������ ������ �� ����ϴ� �Լ�.
int compare_CoinItem_value(const void *value1, const void *value2) {
	CoinItem *item1 = (CoinItem*)value1;
	CoinItem *item2 = (CoinItem*)value2;

	//����ü�� ��� ������ �̿��Ͽ� �� ����
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

//���� ���õ� ������ ������ ���ϴ� �Լ�
int getChangeCount(int target_change, int coin_value) {
	int count = 0;

	//���� �ݾ��� ���� �ݾ׺��� Ŀ�� ���� ������ ����� �� �ִ�.
	if (target_change >= coin_value) {
		count = target_change / coin_value; //������ ������ ���մϴ�.
	}

	return count;
}

//�Է� �Ķ���ͷ� �Ž����� �ݾ��� change_total, ���� ������ ����� �迭 items, ������ ���� item_count
int getChange(int change_total, CoinItem *items, int item_count) {
	int current_change = change_total;
	int i = 0;

	//���� �ݾ��� ū ������� ����
	qsort(items, item_count, sizeof(CoinItem), compare_CoinItem_value);

	//���� ������ ���
	printf("���� ���\n\t��\n");
	for (i = 0;i < item_count;i++) {
		printf("%d\t%d\n", i, items[i].value);
	}

	//Ž�� �˰��� �����κ�
	//items�� �����ͷ� ���޵Ǿ� ����� �Ķ������ ������ �մϴ�.
	for (i = 0;i < item_count;i++) {
		int count = getChangeCount(current_change, items[i].value); //�κ� �� ����.
		items[i].selected = count;
		current_change = current_change - count * items[i].value; //���� �Ž������� �ٽ� ���.
	}
	return current_change; //���� ���� �Ž������� ��ȯ. �߳����� 0.
}

//��¥�� ������ �ִ����� ����ڿ��Լ� �Է� �޴� �Լ�.
void inputItems(CoinItem *items, int item_count) {
	int i = 0;
	for (i = 0;i < item_count;i++) {
		printf("%d ��° ������ ������ �Է��� �ּ��� (��, 100)\n", i + 1);
		scanf_s("%d", &items[i].value);
		items[i].selected = 0;
	}
}

//�˰����� ó�� ����� ����ϴ� �Լ�.
void printResult(CoinItem *items, int item_count, int remained) {
	int i = 0;
	printf("(����)\t(��������)\n");
	for (i = 0;i < item_count;i++) {
		printf("%d\t%d\n", items[i].value, items[i].selected);
	}
	printf("���� �Ž�����:%d\n", remained);
}