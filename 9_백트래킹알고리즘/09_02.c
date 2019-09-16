#include <stdio.h>
#include <stdlib.h>

//���� �߰��� ���� ������ ������ �����ϰų� ���ݹ޴� ��ġ������ ����
int NQueen_Promising(int pPath[], int row) {
	for (int i = 0;i < row;i++) {
		if (pPath[row] == pPath[i] || row - i == abs(pPath[row] - pPath[i])) {
			return 1;
		}
	}
	return 0;
}

//���� ü������ ���¸� ���
void PrintQueens(int q[], int queenNum) {
	int row = 0, col;
	for (row = 0;row < queenNum;row++) {
		for (col = 0;col < queenNum;col++) {
			if (q[row] == col) { //���� ��ġ
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
	for (int i = 0;i < queenNum;i++) { //��� ���� ���ؼ� �� �߰� �õ�
		pPath[row] = i; //(row,i)�� ���ο� �� �߰� �õ�
		if (!NQueen_Promising(pPath, row)) { //����ġ�� ������ �������� �ʾƾ� �߰�
			if (row == queenNum - 1) { //row�� ������ ������ ����
				PrintQueens(pPath, queenNum); //�� ��ġ�� ���
			}
			else { //���� �࿡ ���� ��� ȣ��
				NQueen_BackTracking(queenNum, row + 1, pPath);
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int queenNum = 8; //ü������ ũ�� �� ���� ����
	int *pPath = malloc(sizeof(int)*queenNum); //���� ��ġ(���� ��ġ)�� ������ 1���� �迭 �Ҵ�
	if (pPath != NULL) {
		NQueen_BackTracking(queenNum, 0, pPath);
		free(pPath);
	}
	return 0;
}