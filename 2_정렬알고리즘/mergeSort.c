#include <stdio.h>
#include <stdlib.h>
#include "mergeSort.h"

void printArrayforMergeSort(int value[], int start, int middle, int end)
{
	int t = 0;
	printf("정렬 범위 : %d-%d, 중간 위치-%d, ", start, end, middle);
	for (t = start;t <= end;t++) 
	{
		printf("%d ", value[t]);
	}
	printf("\n");
}

void mergeSortInternal(int value[], int buffer[], int start, int middle, int end)
{
	int i = 0, j = 0, k = 0, t = 0;
	i = start; //첫 번째 부분 집합
	j = middle + 1; //두 번째 부분 집합
	k = start; //임시 정렬 결과를 어디에 저장할 지

	while (i <= middle && j <= end) //두 부분으로 나눠진 상태에서 개수만큼 비교.
	{
		if (value[i] <= value[j]) //첫 번째 부분이 더 작으면
		{
			buffer[k] = value[i]; //버퍼 처음칸에 작은 값을 카피
			i++; //포인터 이동.
		}
		else //첫 번째 부분이 더 크면
		{
			buffer[k] = value[j];
			j++; //포인터 이동.
		}
		k++; //버퍼 포인터 이동.
	}
	//병합 이후 남은 자료가 있는 경우 정렬 결과에 추가.
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
	//버퍼에 저장한 값을 실제 값에 대입.
	for (t = start;t <= end;t++)
	{
		value[t] = buffer[t];
	}
	//현재 배열 상태 출력.
	printArrayforMergeSort(value, start, middle, end);
}

//정렬 대상이 되는 배열만큼 추가 메모리 공간이 필요합니다.
void mergeSort(int value[], int buffer[], int start, int end)
{
	int middle = 0;
	if (start < end) //원소가 1개일 때까지
	{
		middle = (start + end) / 2;
		//재귀 호출을 통해 구성
		mergeSort(value, buffer, start, middle); //분할 단계
		mergeSort(value, buffer, middle + 1, end);
		mergeSortInternal(value, buffer, start, middle, end); //병합단계
	}
}