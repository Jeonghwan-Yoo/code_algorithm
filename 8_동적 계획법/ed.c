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

//두 문자열과 각 문자열의 길이 m과 n을 받아서 최소 편집 거리를 구합니다.
int ED_Recursive(char *string1, char *string2, int m, int n) {
	//비교 대상이 되는 문자열 중 하나가 빈 문자열이면 나머지 문자열의 길이를 편집 거리로 반환.
	if (m == 0) {
		return n;
	}
	if (n == 0) {
		return m;
	}
	//현재 비교 대상 문자가 서로 같은 경우
	//두 문자열 모두 비교 위치를 이동시켜 편집 거리를 구합니다.
	//현재 비교 대상 문자가 서로 같기 때문에 편집 거리는 증가하지 않습니다.
	if (string1[m - 1] == string2[n - 1]) {
		return ED_Recursive(string1, string2, m - 1, n - 1);
	}
	//재귀 호출을 통해 하위 문제 중에서 최솟값을 구하고 거기에 1을 더해서 현재 문제의 편집거리를 구한다.
	else {
		return 1 + min3(ED_Recursive(string1, string2, m, n - 1),
			ED_Recursive(string1,string2,m-1,n), ED_Recursive(string1, string2, m-1, n-1));
	}
}

//두 문자열, 두 문자열의 길이를 m과 n.
//두 문자열의 편집 거리 계산 결과를 저장하는 2차원 배열 ppValues.
int ED_DP(char *string1, char *string2, int m, int n) {
	int ret = 0;
	if (m == 0 || n == 0) {
		return 0;
	}
	int **ppValues = NULL;
	//2차원 배열을 동적으로 할당하고 초기화.
	//2차원 배열의 크기는 문자열의 길이 (m+1)*(n+1)
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
	//동적 계획법
	//0부터 시작하는 이유는 각 배열의 위치 인덱스 0의 원소를 0으로 초기화하기 위해
	//또, 비교 대상 문자열이 빈 문자열인 경우에 대한 처리.
	//string1의 길이 m만큼
	for (int i = 0;i <= m;i++) {
		//string2의 길이 n만큼
		for (int j = 0;j <= n;j++) {
			//비교 대상 문자열이 빈 문자열이라면 다른 문자열의 길이가 편집거리.
			if (i == 0) {
				ppValues[i][j] = j;
			}
			else if (j == 0) {
				ppValues[i][j] = i;
			}
			//현재 비교 대상 문자가 서로 같은 경우에 대한 처리.
			else if (string1[i - 1] == string2[j - 1]) {
				ppValues[i][j] = ppValues[i - 1][j - 1];
			}
			//하위 문제의 최적해를 기반으로 상위 문제의 최적해를 구하는 부분.
			else {
				ppValues[i][j] = 1 + min3(ppValues[i - 1][j], ppValues[i][j - 1], 
					ppValues[i - 1][j - 1]);
			}
		}
	}
	//저장된 최종 편집 거리를 반환.
	ret = ppValues[m][n];
	//동적으로 할당된 메모리에 대한 해제 처리.
	for (int i = 0;i < m + 1;i++) {
		free(ppValues[i]);
	}
	free(ppValues);

	return ret;
}