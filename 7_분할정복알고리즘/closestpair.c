#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "closestpair.h"

#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif

int compareX(const void* a, const void* b) {
	Point *p1 = (Point*)a, *p2 = (Point*)b;
	return (p1->x - p2->x);
}

int compareY(const void* a, const void* b) {
	Point *p1 = (Point*)a, *p2 = (Point*)b;
	return (p1->y - p2->y);
}

double dist(Point p1, Point p2) {
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

double closestPairThreePoints(Point p0, Point p1, Point p2) {
	double min = 0;
	double p01 = dist(p0, p1);
	double p02 = dist(p0, p2);
	double p12 = dist(p1, p2);

	min = min(min(p01, p02), p12);

	return min;
}

double borderClosest(Point strip[], int count, double d) {
	double min = d;

	//먼저 점들의 Y값으로 정렬
	qsort(strip, count, sizeof(Point), compareY);

	//점들 사이의 Y값이 최소 거리보다 작은 경우일 때만 비교.
	for (int i = 0;i < count;++i) {
		for (int j = i + 1;j < count && (strip[j].y - strip[i].y) < min;++j) {
			if (dist(strip[i], strip[j]) < min) {
				min = dist(strip[i], strip[j]);
			}
		}
	}
	return min;
}

double closestPairRecursive(Point points[], int count) {
	int mid = 0, i = 0, border_count = 0;
	double dl = 0, dr = 0, d = 0, dc = 0, result = 0;
	Point *borders = NULL;

	//점이 3개 이하일 때 처리
	if (count <= 1) {
		return 0;
	}
	else if (count == 2) {
		return dist(points[0], points[1]);
	}
	else if (count == 3) {
		return closestPairThreePoints(points[0], points[1], points[2]);
	}

	//임시 자료들 초기화
	borders = (Point*)malloc(sizeof(Point)*count); //중간 영역 점들
	if (borders == NULL) {
		return result;
	}

	//이미 정렬이 되있기 때문에단순히 점들의 개수를 2로 나눈 값.
	mid = count / 2;
	//점의 개수가 4개 이상이면 분할을 위해 중간의 점을 선택
	Point midPoint = points[mid]; //분할 기준점

	//왼쪽 영역과 오른쪽 영역에 대해 재귀 호출 수행
	dl = closestPairRecursive(points, mid);
	dr = closestPairRecursive(points+mid,count-mid);
	d = min(dl, dr); //이 두 영역의 최소 거리 중에서 더 작은 값이 최소 거리. 

	//중간 영역 점들 중 작은 값만 구하기
	for (i = 0;i < count;i++) {
		if (abs(points[i].x - midPoint.x) < d) {
			borders[border_count] = points[i];
			border_count++;
		}
	}

	//중간 영역 점들에서 최소 거리를 구하고 기존 최소 거리와 비교.
	if (border_count > 0) {
		dc = borderClosest(borders, border_count, d);
		result = min(d, dc); 
	}
	else {
		result = d;
	}

	free(borders);

	return result;
}

double closestPair(Point points[], int count) {
	//점의 X좌표를 기준으로 정렬
	qsort(points, count, sizeof(Point), compareX);

	return closestPairRecursive(points, count);
}