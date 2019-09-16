#include <stdio.h>
#include <stdlib.h>

#include "selectionSort.h"

void printArrayForSelectionSort(int value[], int count);

void selectionSort(int value[], int count) 
{
	int i = 0, j = 0;
	int min = 0, temp = 0;

	for (i = 0;i < count - 1;i++) //마지막 위치는 정렬안해도 이미 최대값.
	{ 
		//아직 정렬되지 않은 자료 중에서 가장 적은 값을 가지는 자료를 찾는 부분.
		min = i;
		for (j = i + 1;j < count;j++) //아직 정렬되지 않은 자료 중에서 최솟값을 가지는 자료 i+1.
		{ 
			if (value[j] < value[min]) 
			{
				min = j;
			}
		}
		//교환 단계
		temp = value[i];
		value[i] = value[min];
		value[min] = temp;

		//정렬 과정을 출력하기 위한 디버깅용 소스.
		printf("Step-%d, ", i + 1);
		printArrayForSelectionSort(value, count);
	} //end-of-for
}

//정수 배열(value)와 배열의 개수(count)를 입력 파라미터로 받아 루프를 돌면서 배열의 내용을 출력.
void printArrayForSelectionSort(int value[], int count) {
	int i = 0;
	for (i = 0;i < count;i++) 
	{
		printf("%d ", value[i]);
	}
	printf("\n");
}