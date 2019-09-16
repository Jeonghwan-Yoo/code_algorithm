#include <stdio.h>
#include <stdlib.h>
#include "mergeSort.h"

void printArrayforMergeSort(int value[], int start, int middle, int end)
{
	int t = 0;
	printf("���� ���� : %d-%d, �߰� ��ġ-%d, ", start, end, middle);
	for (t = start;t <= end;t++) 
	{
		printf("%d ", value[t]);
	}
	printf("\n");
}

void mergeSortInternal(int value[], int buffer[], int start, int middle, int end)
{
	int i = 0, j = 0, k = 0, t = 0;
	i = start; //ù ��° �κ� ����
	j = middle + 1; //�� ��° �κ� ����
	k = start; //�ӽ� ���� ����� ��� ������ ��

	while (i <= middle && j <= end) //�� �κ����� ������ ���¿��� ������ŭ ��.
	{
		if (value[i] <= value[j]) //ù ��° �κ��� �� ������
		{
			buffer[k] = value[i]; //���� ó��ĭ�� ���� ���� ī��
			i++; //������ �̵�.
		}
		else //ù ��° �κ��� �� ũ��
		{
			buffer[k] = value[j];
			j++; //������ �̵�.
		}
		k++; //���� ������ �̵�.
	}
	//���� ���� ���� �ڷᰡ �ִ� ��� ���� ����� �߰�.
	if (i > middle) 
	{
		for (t = j;t <= end;t++, k++)
		{
			buffer[k] = value[t];
		}
	}
	else
	{
		for (t = i;t <= middle;t++, k++)
		{
			buffer[k] = value[t];
		}
	}
	//���ۿ� ������ ���� ���� ���� ����.
	for (t = start;t <= end;t++)
	{
		value[t] = buffer[t];
	}
	//���� �迭 ���� ���.
	printArrayforMergeSort(value, start, middle, end);
}

//���� ����� �Ǵ� �迭��ŭ �߰� �޸� ������ �ʿ��մϴ�.
void mergeSort(int value[], int buffer[], int start, int end)
{
	int middle = 0;
	if (start < end) //���Ұ� 1���� ������
	{
		middle = (start + end) / 2;
		//��� ȣ���� ���� ����
		mergeSort(value, buffer, start, middle); //���� �ܰ�
		mergeSort(value, buffer, middle + 1, end);
		mergeSortInternal(value, buffer, start, middle, end); //���մܰ�
	}
}