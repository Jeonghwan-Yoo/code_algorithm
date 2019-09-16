/*
9.3.2백트래킹의 구현
09_03.c:예제 프로그램
mazebacktracking.h:미로의 경로 구하기 관련 상수, 구조체 및 함수 선언
mazebacktracking.c:미로의 경로 구하기 관련 함수 구현

미로를 2차원 정수(int)배열로 나타냅니다.
미로를 구성하는 각각의 블록은 벽 혹은 통로일 수 있습니다.
22111111
12000001
11101111
11101111
10000001
10111111
10000000
11111110

*/

#ifndef mazebacktracking_h
#define mazebacktracking_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//미로의 크기
#define WIDTH 8
#define HEIGHT 8

//미로에서의 위치 정보를 저장하는 구조체
typedef struct MapPositionType {
	int x; //현재 위치 x좌표
	int y; //현재 위치 y좌표
}MapPosition;

//미로 내에서 이동할 수 있는 방향을 표현하는 배열 변수
//프로그램에서 유일하게 1개의 인스턴스를 가지도록 하기 위해 static
//static이 아니라면 전체 소스에서 DIRECTION_OFFSETS[]은 한 번만 선언
//헤더 파일이 아니라 c파일에 위치해야 합니다
//이럴 경우 다른 곳에서 이 변수를 참조하기가 상당히 불편합니다.
//글로벌 변수로 사용하기 위해 static
static int DIRECTION_OFFSETS[][2] = {
	{0, -1}, //위쪽으로 이동 [0]
	{1, 0}, //오른쪽으로 이동 [1]
	{0, 1}, //아래로 이동 [2]
	{-1, 0} //왼쪽으로 이동 [3]
};

//이동할 수 있는 방향의 개수
#define NUM_DIRECTIONS sizeof(DIRECTION_OFFSETS)/sizeof(int[2])

//미로를 구성하는 각 위치에 대한 상태 정보
//방문하지 않은 통로 0, 벽은 1, 이미 방문한 통로 2.
enum PosStatus {
	NOT_VISIT=0, WALL=1, VISIT=2
};

//미로를 출력하는 함수
//입력 파라미터로 미로 정보를 나타내느 2차원 정수 배열 mazeArray를 전달
void printMaze(int mazeArray[HEIGHT][WIDTH]);
//백트래킹을 이용하여 미로에서 경로를 찾는 함수
//입력으로 mazeArray, 출구 위치 endPos, 현재 위치 currentPos
//입출력으로 현재까지의 경로를 저장하는 pPath와 pStep.
//pStep은 경로에 위치가 추가될 때마다 1씩 증가시켜 pPath가 몇 개의 위치로 이루어져있는지 저장.
void maze_BackTracking(int mazeArray[HEIGHT][WIDTH], MapPosition endPos,
	MapPosition currentPos, MapPosition *pPath, int *pStep);
//구해진 경로를 출력하는 함수.
void showPath(int mazeArray[HEIGHT][WIDTH], MapPosition *pPath, int step);

#endif
