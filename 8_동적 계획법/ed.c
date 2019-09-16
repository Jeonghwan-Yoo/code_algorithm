#include "ed.h"

int min3(int a, int b, int c) {
	if (a < b&&a < c) {
		return a;
	}
	else if (b < c) {
		return b;
	}
	else {
		return c;
	}
}

//�� ���ڿ��� �� ���ڿ��� ���� m�� n�� �޾Ƽ� �ּ� ���� �Ÿ��� ���մϴ�.
int ED_Recursive(char *string1, char *string2, int m, int n) {
	//�� ����� �Ǵ� ���ڿ� �� �ϳ��� �� ���ڿ��̸� ������ ���ڿ��� ���̸� ���� �Ÿ��� ��ȯ.
	if (m == 0) {
		return n;
	}
	if (n == 0) {
		return m;
	}
	//���� �� ��� ���ڰ� ���� ���� ���
	//�� ���ڿ� ��� �� ��ġ�� �̵����� ���� �Ÿ��� ���մϴ�.
	//���� �� ��� ���ڰ� ���� ���� ������ ���� �Ÿ��� �������� �ʽ��ϴ�.
	if (string1[m - 1] == string2[n - 1]) {
		return ED_Recursive(string1, string2, m - 1, n - 1);
	}
	//��� ȣ���� ���� ���� ���� �߿��� �ּڰ��� ���ϰ� �ű⿡ 1�� ���ؼ� ���� ������ �����Ÿ��� ���Ѵ�.
	else {
		return 1 + min3(ED_Recursive(string1, string2, m, n - 1),
			ED_Recursive(string1,string2,m-1,n), ED_Recursive(string1, string2, m-1, n-1));
	}
}

//�� ���ڿ�, �� ���ڿ��� ���̸� m�� n.
//�� ���ڿ��� ���� �Ÿ� ��� ����� �����ϴ� 2���� �迭 ppValues.
int ED_DP(char *string1, char *string2, int m, int n) {
	int ret = 0;
	if (m == 0 || n == 0) {
		return 0;
	}
	int **ppValues = NULL;
	//2���� �迭�� �������� �Ҵ��ϰ� �ʱ�ȭ.
	//2���� �迭�� ũ��� ���ڿ��� ���� (m+1)*(n+1)
	ppValues = (int**)malloc(sizeof(int*)*(m + 1));
	if (ppValues == NULL) {
		return ret;
	}
	for (int i = 0;i < m + 1;i++) {
		ppValues[i] = (int*)malloc(sizeof(int)*(n + 1));
		if (ppValues[i] != NULL) {
			memset(ppValues[i], 0, sizeof(int)*(n + 1));
		}
		else {
			return ret;
		}
	}
	//���� ��ȹ��
	//0���� �����ϴ� ������ �� �迭�� ��ġ �ε��� 0�� ���Ҹ� 0���� �ʱ�ȭ�ϱ� ����
	//��, �� ��� ���ڿ��� �� ���ڿ��� ��쿡 ���� ó��.
	//string1�� ���� m��ŭ
	for (int i = 0;i <= m;i++) {
		//string2�� ���� n��ŭ
		for (int j = 0;j <= n;j++) {
			//�� ��� ���ڿ��� �� ���ڿ��̶�� �ٸ� ���ڿ��� ���̰� �����Ÿ�.
			if (i == 0) {
				ppValues[i][j] = j;
			}
			else if (j == 0) {
				ppValues[i][j] = i;
			}
			//���� �� ��� ���ڰ� ���� ���� ��쿡 ���� ó��.
			else if (string1[i - 1] == string2[j - 1]) {
				ppValues[i][j] = ppValues[i - 1][j - 1];
			}
			//���� ������ �����ظ� ������� ���� ������ �����ظ� ���ϴ� �κ�.
			else {
				ppValues[i][j] = 1 + min3(ppValues[i - 1][j], ppValues[i][j - 1], 
					ppValues[i - 1][j - 1]);
			}
		}
	}
	//����� ���� ���� �Ÿ��� ��ȯ.
	ret = ppValues[m][n];
	//�������� �Ҵ�� �޸𸮿� ���� ���� ó��.
	for (int i = 0;i < m + 1;i++) {
		free(ppValues[i]);
	}
	free(ppValues);

	return ret;
}