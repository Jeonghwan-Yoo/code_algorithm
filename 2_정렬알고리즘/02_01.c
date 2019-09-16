#include <stdio.h>
#include <stdlib.h>

#include "selectionSort.h"

void printArray(int value[], int count);

int main(int argc, char *argv[]) 
{
	int values[] = { 80,75,10,60,15,49,12,25 };

	printf("선택 정렬 실행 전\n");
	printArray(values, 8);

	printf("\n선택 정렬이 시작됩니다.\n");
	selectionSort(values, 8);

	printf("\n선택 정렬 결과\n");
	printArray(values, 8);

	return 0;
}

void printArray(int value[], int count) {
	int i = 0;
	for (i = 0;i < count;i++)
	{
		printf("%d ", value[i]);
	}
	printf("\n");
}