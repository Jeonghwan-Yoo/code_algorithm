#include <stdio.h>
#include <stdlib.h>

#include "quickSort.h"

void printArrayForQuickSort(int value[], int start, int end)
{
	for (int i = start; i <= end;i++)
	{
		printf("%d ", value[i]);
	}
	printf("\n");
}

void quickSort(int value[], int start, int end)
{
	int pivot = 0;
	if (start < end) //1�����̸� �������� �ʽ��ϴ�.
	{
		pivot = partitionQuickSort(value, start, end); //Ű ��ġ ��ȯ+���ο� �Ǻ����� ��ȯ.
		quickSort(value, start, pivot - 1); //2���� �κ� ���տ� ���� �������� ����.
		quickSort(value, pivot + 1, end);
	}
}
//�Ǻ� ���� �������� �� �ڷ��� ��ġ�� ��ȯ�ϰ�, ���� �Ǻ��� ��ġ�� ��ȯ�մϴ�.
int partitionQuickSort(int value[], int start, int end)
{
	//pivot �� right�� ���� ������ �ڷḦ ����Ű���� �ʱ�ȭ. left�� ���� ����.
	int pivot = end;
	int right = end;
	int left = start;
	int temp = 0;

	//����, left�� right�� ���ٸ� �ڷ��� ��ȯ�� �ʿ� ����.
	//�Ǻ��� �������� Ű ��ġ�� ��ȯ
	while (left < right) {
		while ((value[left] < value[pivot]) && (left < right))
		{
			left++;
		}
		while ((value[right] >= value[pivot]) && (left < right))
		{
			right--;
		}

		if (left < right)
		{
			printf("���� ����: %d~%d, �Ǻ�-[%d], Left(%d)-Right(%d) ��ȯ ��,", start, end, value[pivot]
				, value[left], value[right]);
			printArrayForQuickSort(value, start, end);

			temp = value[left];
			value[left] = value[right];
			value[right] = temp;

			printf("���� ����: %d~%d, �Ǻ�-[%d], ��ȯ ��,", start, end, value[pivot]);
			printArrayForQuickSort(value, start, end);
		}
	}
	printf("���� ����: %d~%d, �Ǻ�-[%d], Left(%d)-Right(%d) ��ȯ ��,", start, end, value[pivot]
		, value[left], value[right]);
	printArrayForQuickSort(value, start, end);

	//���ο� �Ǻ����� ��ȯ.
	temp = value[pivot];
	value[pivot] = value[right];
	value[right] = temp;

	printf("���� ����: %d~%d, �Ǻ� ��ȯ ��,", start, end);
	printArrayForQuickSort(value, start, end);

	return right;
}