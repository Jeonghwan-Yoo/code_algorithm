#include <stdio.h>
#include "ed.h"

int main(int argc, char *argv[]) {
	char string1[] = "sunday";
	char string2[] = "saturday";

	int m = (int)strlen(string1);
	int n = (int)strlen(string2);
	int nED = ED_Recursive(string1, string2, m, n);
	printf("[%s]�� [%s]�� Edit Distance ����(���� ����):%d\n", string1, string2, nED);

	nED = ED_DP(string1, string2, m, n);
	printf("[%s]�� [%s]�� Edit Distance ����(���� ��ȹ��):%d\n", string1, string2, nED);

	//���� ���ڿ��� �� ���ڿ��� �ٲپ ����� ����� ����. 
	nED = ED_DP(string2, string1, n, m);
	printf("[%s]�� [%s]�� Edit Distance ����(���� ��ȹ��):%d\n", string2, string1, nED);

	return 0;

}