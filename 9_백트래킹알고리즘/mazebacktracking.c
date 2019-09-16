#include "mazebacktracking.h"

//����ġ�� ������ �˻��ϴ� �Լ�.
int checkValidPos(int mazeArray[HEIGHT][WIDTH], MapPosition pos) {
	//x�� 0���� ũ�ų� ���� ���� ũ�⺸�� �۾ƾ��մϴ�.
	//y�� 0���� ũ�ų� ���� ���� ũ�⺸�� �۾ƾ��մϴ�.
	if (pos.x >= 0 && pos.x < WIDTH&&pos.y >= 0 && pos.y < HEIGHT) {
		//�����δ� �̵��� �� ���� �̹� �湮�� ���� �� �� �����ϴ�.
		if (mazeArray[pos.y][pos.x] != WALL && mazeArray[pos.y][pos.x] != VISIT) {
			return 1;
		}
	}
	return 0;
}

void maze_BackTracking(int mazeArray[HEIGHT][WIDTH], MapPosition endPos,
	MapPosition currentPos, MapPosition *pPath, int *pStep) {
	
	int step = *pStep;
	mazeArray[currentPos.y][currentPos.x] = VISIT;
	pPath[step] = currentPos;

	if (currentPos.x == endPos.x&&currentPos.y == endPos.y) {
		return;
	}
	else {
		for (int i = 0;i < NUM_DIRECTIONS;i++) {
			//�̵� ������ ��ġ �߿��� �� ��ġ�� �����ϱ� ����
			//DIRECTION_OFFSETS[i]�� 2���� ����, [i][0]�� x���� [i][1]�� y�������� ��ŭ �̵��ϴ���
			MapPosition newPos = { 0 };
			newPos.x = currentPos.x + DIRECTION_OFFSETS[i][0];
			newPos.y = currentPos.y + DIRECTION_OFFSETS[i][1];
			
			if (checkValidPos(mazeArray, newPos)) { //����ġ�� ������ �˻�.
				*pStep = step + 1; //newPos�� �̵��� �� �ִ� ��ġ��� 1����.
				maze_BackTracking(mazeArray, endPos, newPos, pPath, pStep);
			}
		}
	}
}

//���� �̷��� ���¸� ���
void printMaze(int mazeArray[HEIGHT][WIDTH]) {
	int i, j;
	for (i = 0;i < HEIGHT;i++) {
		for (j = 0;j < WIDTH;j++) {
			if (mazeArray[i][j] == WALL) { //��
				printf("*");
			}
			else if (mazeArray[i][j] == VISIT) { //�湮�� ��
				printf("0");
			}
			else { //���
				printf(" ");
			}
		}
		printf("\n");
	}
}

//������ ��θ� ����ϴ� �Լ�.
void showPath(int mazeArray[HEIGHT][WIDTH], MapPosition *pPath, int step) {
	//�Է����� ���� ���� �̷� ���� mazeArray�� �̿��Ͽ� ���ο� �̷� �Լ� resultArray�� �ʱ�ȭ.
	int resultArray[HEIGHT][WIDTH] = { 0, };
	for (int i = 0;i < HEIGHT;i++) {
		for (int j = 0;j < WIDTH;j++) {
			if (mazeArray[i][j] == WALL) {
				resultArray[i][j] = WALL;
			}
		}
	}
	//���� ���� ��� ���� pPath�� �̿��Ͽ� ��� ������ ���
	for (int i = 0;i <= step;i++) {
		int x = pPath[i].x;
		int y = pPath[i].y;

		if (i > 0) {
			printf("->");
		}
		printf("(%d,%d)", y, x);
		//�̷� resultArray�� �湮 ������ ����.
		resultArray[y][x] = VISIT;
	}
	printf("\n");
	//�湮 ������ �߰��� �̷θ� ���.
	printMaze(resultArray);
}