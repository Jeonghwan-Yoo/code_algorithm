/*
9.3.2��Ʈ��ŷ�� ����
09_03.c:���� ���α׷�
mazebacktracking.h:�̷��� ��� ���ϱ� ���� ���, ����ü �� �Լ� ����
mazebacktracking.c:�̷��� ��� ���ϱ� ���� �Լ� ����

�̷θ� 2���� ����(int)�迭�� ��Ÿ���ϴ�.
�̷θ� �����ϴ� ������ ����� �� Ȥ�� ����� �� �ֽ��ϴ�.
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

//�̷��� ũ��
#define WIDTH 8
#define HEIGHT 8

//�̷ο����� ��ġ ������ �����ϴ� ����ü
typedef struct MapPositionType {
	int x; //���� ��ġ x��ǥ
	int y; //���� ��ġ y��ǥ
}MapPosition;

//�̷� ������ �̵��� �� �ִ� ������ ǥ���ϴ� �迭 ����
//���α׷����� �����ϰ� 1���� �ν��Ͻ��� �������� �ϱ� ���� static
//static�� �ƴ϶�� ��ü �ҽ����� DIRECTION_OFFSETS[]�� �� ���� ����
//��� ������ �ƴ϶� c���Ͽ� ��ġ�ؾ� �մϴ�
//�̷� ��� �ٸ� ������ �� ������ �����ϱⰡ ����� �����մϴ�.
//�۷ι� ������ ����ϱ� ���� static
static int DIRECTION_OFFSETS[][2] = {
	{0, -1}, //�������� �̵� [0]
	{1, 0}, //���������� �̵� [1]
	{0, 1}, //�Ʒ��� �̵� [2]
	{-1, 0} //�������� �̵� [3]
};

//�̵��� �� �ִ� ������ ����
#define NUM_DIRECTIONS sizeof(DIRECTION_OFFSETS)/sizeof(int[2])

//�̷θ� �����ϴ� �� ��ġ�� ���� ���� ����
//�湮���� ���� ��� 0, ���� 1, �̹� �湮�� ��� 2.
enum PosStatus {
	NOT_VISIT=0, WALL=1, VISIT=2
};

//�̷θ� ����ϴ� �Լ�
//�Է� �Ķ���ͷ� �̷� ������ ��Ÿ���� 2���� ���� �迭 mazeArray�� ����
void printMaze(int mazeArray[HEIGHT][WIDTH]);
//��Ʈ��ŷ�� �̿��Ͽ� �̷ο��� ��θ� ã�� �Լ�
//�Է����� mazeArray, �ⱸ ��ġ endPos, ���� ��ġ currentPos
//��������� ��������� ��θ� �����ϴ� pPath�� pStep.
//pStep�� ��ο� ��ġ�� �߰��� ������ 1�� �������� pPath�� �� ���� ��ġ�� �̷�����ִ��� ����.
void maze_BackTracking(int mazeArray[HEIGHT][WIDTH], MapPosition endPos,
	MapPosition currentPos, MapPosition *pPath, int *pStep);
//������ ��θ� ����ϴ� �Լ�.
void showPath(int mazeArray[HEIGHT][WIDTH], MapPosition *pPath, int step);

#endif
