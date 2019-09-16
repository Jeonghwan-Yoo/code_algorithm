#include <stdio.h>
#include "mazebacktracking.h"

int main(int argc, char *argv[]) {
	MapPosition startPos = { 0 }, endPos = { 0 };
	MapPosition *pPath = NULL;
	int step = 0;

	//2차원 배열로 지도를 정의.
	int mazeArray[HEIGHT][WIDTH] = {
		{0, 0, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 1, 1, 1, 1},
		{1, 1, 1, 0, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 0}
	};

	//출발 위치와 도착 위치를 설정.
	startPos.x = 0;
	startPos.y = 0;
	endPos.x = 7;
	endPos.y = 7;

	//경로 정보를 저장할 변수에 대해 메모리를 할당.
	//여기서 경로의 원소 개수를 지도를 구성하는 블록의 전체 개수인 HEIGHT*WIDTH로 설정.
	pPath = (MapPosition*)malloc(sizeof(MapPosition)*HEIGHT*WIDTH);
	if (pPath != NULL) {
		memset(pPath, 0, sizeof(MapPosition)*HEIGHT*WIDTH);

		printf("미로\n");
		//지도 정보를 출력
		printMaze(mazeArray);

		//실제 경로를 찾은 뒤
		maze_BackTracking(mazeArray, endPos, startPos, pPath, &step);
		printf("\n경로\n");
		//마지막으로 구한 경로를 출력.
		showPath(mazeArray, pPath, step);

		free(pPath);
	}
	return 0;
}