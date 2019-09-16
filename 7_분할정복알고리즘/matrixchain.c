#include "matrixchain.h"

//p는 행렬의 행과 열의 개수를 저장하는 배열의 시작 주소
int minimumMatrixChainRecursive(int p[], int i, int j) {
	int k = 0;
	int min = 99999;
	int value = 0;

	if (i == j) {
		return 0;
	}
	for (k = i;k < j;k++) {
		value = minimumMatrixChainRecursive(p, i, k) + minimumMatrixChainRecursive(p, k + 1, j)
			+ p[i - 1] * p[k] * p[j];

		if (value < min) {
			min = value;
		}
	}
	return min;
}