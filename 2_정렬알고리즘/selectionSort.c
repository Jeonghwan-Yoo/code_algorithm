#include <stdio.h>
#include <stdlib.h>

#include "selectionSort.h"

void printArrayForSelectionSort(int value[], int count);

void selectionSort(int value[], int count) 
{
	int i = 0, j = 0;
	int min = 0, temp = 0;

	for (i = 0;i < count - 1;i++) //������ ��ġ�� ���ľ��ص� �̹� �ִ밪.
	{ 
		//���� ���ĵ��� ���� �ڷ� �߿��� ���� ���� ���� ������ �ڷḦ ã�� �κ�.
		min = i;
		for (j = i + 1;j < count;j++) //���� ���ĵ��� ���� �ڷ� �߿��� �ּڰ��� ������ �ڷ� i+1.
		{ 
			if (value[j] < value[min]) 
			{
				min = j;
			}
		}
		//��ȯ �ܰ�
		temp = value[i];
		value[i] = value[min];
		value[min] = temp;

		//���� ������ ����ϱ� ���� ������ �ҽ�.
		printf("Step-%d, ", i + 1);
		printArrayForSelectionSort(value, count);
	} //end-of-for
}

//���� �迭(value)�� �迭�� ����(count)�� �Է� �Ķ���ͷ� �޾� ������ ���鼭 �迭�� ������ ���.
void printArrayForSelectionSort(int value[], int count) {
	int i = 0;
	for (i = 0;i < count;i++) 
	{
		printf("%d ", value[i]);
	}
	printf("\n");
}