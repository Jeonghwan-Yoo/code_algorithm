#include "mazebacktracking.h"

//가지치기 조건을 검사하는 함수.
int checkValidPos(int mazeArray[HEIGHT][WIDTH], MapPosition pos) {
	//x는 0보다 크거나 같고 가로 크기보다 작아야합니다.
	//y는 0보다 크거나 같고 세로 크기보다 작아야합니다.
	if (pos.x >= 0 && pos.x < WIDTH&&pos.y >= 0 && pos.y < HEIGHT) {
		//벽으로는 이동할 수 없고 이미 방문한 곳도 갈 수 없습니다.
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
			//이동 가능한 위치 중에서 한 위치를 선택하기 위해
			//DIRECTION_OFFSETS[i]는 2개의 정수, [i][0]은 x방향 [i][1]은 y방향으로 얼만큼 이동하는지
			MapPosition newPos = { 0 };
			newPos.x = currentPos.x + DIRECTION_OFFSETS[i][0];
			newPos.y = currentPos.y + DIRECTION_OFFSETS[i][1];
			
			if (checkValidPos(mazeArray, newPos)) { //가지치기 조건을 검사.
				*pStep = step + 1; //newPos가 이동할 수 있는 위치라면 1증가.
				maze_BackTracking(mazeArray, endPos, newPos, pPath, pStep);
			}
		}
	}
}

//현재 미로의 상태를 출력
void printMaze(int mazeArray[HEIGHT][WIDTH]) {
	int i, j;
	for (i = 0;i < HEIGHT;i++) {
		for (j = 0;j < WIDTH;j++) {
			if (mazeArray[i][j] == WALL) { //벽
				printf("*");
			}
			else if (mazeArray[i][j] == VISIT) { //방문한 곳
				printf("0");
			}
			else { //통로
				printf(" ");
			}
		}
		printf("\n");
	}
}

//구해진 경로를 출력하는 함수.
void showPath(int mazeArray[HEIGHT][WIDTH], MapPosition *pPath, int step) {
	//입력으로 전달 받은 미로 정보 mazeArray를 이용하여 새로운 미로 함수 resultArray를 초기화.
	int resultArray[HEIGHT][WIDTH] = { 0, };
	for (int i = 0;i < HEIGHT;i++) {
		for (int j = 0;j < WIDTH;j++) {
			if (mazeArray[i][j] == WALL) {
				resultArray[i][j] = WALL;
			}
		}
	}
	//전달 받은 경로 정보 pPath를 이용하여 경로 정보를 출력
	for (int i = 0;i <= step;i++) {
		int x = pPath[i].x;
		int y = pPath[i].y;

		if (i > 0) {
			printf("->");
		}
		printf("(%d,%d)", y, x);
		//미로 resultArray에 방문 정보를 설정.
		resultArray[y][x] = VISIT;
	}
	printf("\n");
	//방문 정보가 추가된 미로를 출력.
	printMaze(resultArray);
}