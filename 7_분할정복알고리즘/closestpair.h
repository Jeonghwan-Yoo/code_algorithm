/*
7.3.2분할 정복 알고리즘의 구현
*/

#ifndef closestpair_h
#define closestpair_h

typedef struct _point {
	int x, y;
}Point;

//가장 가까운 두점을 구하는 함수
//입력 파라미터로 점들의 개수인 count를 추가로 전달.
//점의 배열 points와 점의 개수 count를 입력 파라미터.
double closestPair(Point points[], int count);

#endif