#include <stdio.h>
#include "fibonacci.h"

int main() {
	int result = 0;
	int n = 10;

	result = fibonacci_Recursive(n);
	printf("���� ������ fibonacci_Recursive(%d)=%d\n", n, result);

	result = fibonacci_DP(n);
	printf("���� ��ȹ�� fibonacci_DP(%d)=%d\n", n, result);

	return 0;
}