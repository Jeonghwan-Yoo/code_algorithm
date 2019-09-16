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
	if (start < end) //1개뿐이면 정렬하지 않습니다.
	{
		pivot = partitionQuickSort(value, start, end); //키 위치 교환+새로운 피봇으로 교환.
		quickSort(value, start, pivot - 1); //2개의 부분 집합에 대해 퀵정렬을 실행.
		quickSort(value, pivot + 1, end);
	}
}
//피봇 값을 기준으로 두 자료의 위치를 교환하고, 최종 피봇의 위치를 반환합니다.
int partitionQuickSort(int value[], int start, int end)
{
	//pivot 및 right를 가장 오른쪽 자료를 가리키도록 초기화. left는 가장 왼쪽.
	int pivot = end;
	int right = end;
	int left = start;
	int temp = 0;

	//만약, left와 right가 같다면 자료의 교환이 필요 없다.
	//피봇을 기준으로 키 위치를 교환
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
			printf("정렬 범위: %d~%d, 피봇-[%d], Left(%d)-Right(%d) 교환 전,", start, end, value[pivot]
				, value[left], value[right]);
			printArrayForQuickSort(value, start, end);

			temp = value[left];
			value[left] = value[right];
			value[right] = temp;

			printf("정렬 범위: %d~%d, 피봇-[%d], 교환 후,", start, end, value[pivot]);
			printArrayForQuickSort(value, start, end);
		}
	}
	printf("정렬 범위: %d~%d, 피봇-[%d], Left(%d)-Right(%d) 교환 전,", start, end, value[pivot]
		, value[left], value[right]);
	printArrayForQuickSort(value, start, end);

	//새로운 피봇으로 교환.
	temp = value[pivot];
	value[pivot] = value[right];
	value[right] = temp;

	printf("정렬 범위: %d~%d, 피봇 교환 후,", start, end);
	printArrayForQuickSort(value, start, end);

	return right;
}