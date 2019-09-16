#include <stdio.h>
#include <stdlib.h>

#include "quickSort.h"

void printArray(int value[], int count);

int main(int argc, char *argv[])
{
	int values[] = { 80, 75, 10, 60, 15, 49, 12, 25 };
	int count = sizeof(values) / sizeof(int);

	printf("�� ���� ���� �� \n");
	printArray(values, count);

	printf("\n�� ������ ���۵˴ϴ� \n");
	quickSort(values, 0, count - 1);

	printf("\n�� ���� ��� \n");
	printArray(values, count);

	return 0;
}

void printArray(int value[], int count)
{
	int i = 0;
	for (i = 0; i < count; i++) {
		printf("%d ", value[i]);
	}
	printf("\n");
}
