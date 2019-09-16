#include "fibonacci.h"

int fibonacci_Recursive(int n) {
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 1;
	}
	else {
		return fibonacci_Recursive(n - 1) + fibonacci_Recursive(n - 2);
	}
}

int fibonacci_DP(int n) {
	int ret = 0;
	int *f_data = NULL;

	if (n == 0) {
		return 0;
	}
	else if (n <= 2) {
		return 1;
	}

	f_data = (int*)malloc(sizeof(int)*n); //n의 크기만큼 동적으로 메모리를 할당.
	if (f_data != NULL) {
		f_data[0] = f_data[1] = 1;

		for (int i = 2;i < n;i++) {
			f_data[i] = f_data[i - 1] + f_data[i - 2]; //fibonacci(3)의 값을 f_data[2]에 저장
		}
		ret = f_data[n - 1];
		free(f_data);
	}
	return ret;
}