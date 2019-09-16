#include <stdio.h>
#include "matrixchain.h"

int main(int argc, char *argv[]) {
	int p_of_A[] = { 100,1,100,1,100 }; //(100x1) (1x100) (100x1) (1x100)
	int count_of_p = sizeof(p_of_A) / sizeof(p_of_A[0]);
	int start_matrix_index = 1; //시작 행렬의 인덱스는 1
	int end_matrix_index = count_of_p - 1; //행렬의 개수는 p_of_A의 개수에서 1만큼 적다.
	int result = 0;

	result = minimumMatrixChainRecursive(p_of_A, start_matrix_index, end_matrix_index);
	printf("최소 곱셈 횟수:%d\n", result);

	return 0;
}