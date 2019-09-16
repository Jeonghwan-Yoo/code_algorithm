#include <stdio.h>
#include <stdlib.h>

//새로 추가된 퀸이 기존의 퀸들을 공격하거나 공격받는 위치인지를 조사
int NQueen_Promising(int pPath[], int row) {
	for (int i = 0;i < row;i++) {
		if (pPath[row] == pPath[i] || row - i == abs(pPath[row] - pPath[i])) {
			return 1;
		}
	}
	return 0;
}

//현재 체스판의 상태를 출력
void PrintQueens(int q[], int queenNum) {
	int row = 0, col;
	for (row = 0;row < queenNum;row++) {
		for (col = 0;col < queenNum;col++) {
			if (q[row] == col) { //퀸의 위치
				printf("Q");
			}
			else {
				printf("X");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void NQueen_BackTracking(int queenNum, int row, int pPath[]) {
	for (int i = 0;i < queenNum;i++) { //모든 열에 대해서 퀸 추가 시도
		pPath[row] = i; //(row,i)에 새로운 퀸 추가 시도
		if (!NQueen_Promising(pPath, row)) { //가지치기 조건을 만족하지 않아야 추가
			if (row == queenNum - 1) { //row가 마지막 행인지 조사
				PrintQueens(pPath, queenNum); //퀸 위치들 출력
			}
			else { //다음 행에 대해 재귀 호출
				NQueen_BackTracking(queenNum, row + 1, pPath);
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int queenNum = 8; //체스판의 크기 및 퀸의 개수
	int *pPath = malloc(sizeof(int)*queenNum); //퀸의 위치(열의 위치)를 저장할 1차원 배열 할당
	if (pPath != NULL) {
		NQueen_BackTracking(queenNum, 0, pPath);
		free(pPath);
	}
	return 0;
}