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

	//���� ������ Y������ ����
	qsort(strip, count, sizeof(Point), compareY);

	//���� ������ Y���� �ּ� �Ÿ����� ���� ����� ���� ��.
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

	//���� 3�� ������ �� ó��
	if (count <= 1) {
		return 0;
	}
	else if (count == 2) {
		return dist(points[0], points[1]);
	}
	else if (count == 3) {
		return closestPairThreePoints(points[0], points[1], points[2]);
	}

	//�ӽ� �ڷ�� �ʱ�ȭ
	borders = (Point*)malloc(sizeof(Point)*count); //�߰� ���� ����
	if (borders == NULL) {
		return result;
	}

	//�̹� ������ ���ֱ� �������ܼ��� ������ ������ 2�� ���� ��.
	mid = count / 2;
	//���� ������ 4�� �̻��̸� ������ ���� �߰��� ���� ����
	Point midPoint = points[mid]; //���� ������

	//���� ������ ������ ������ ���� ��� ȣ�� ����
	dl = closestPairRecursive(points, mid);
	dr = closestPairRecursive(points+mid,count-mid);
	d = min(dl, dr); //�� �� ������ �ּ� �Ÿ� �߿��� �� ���� ���� �ּ� �Ÿ�. 

	//�߰� ���� ���� �� ���� ���� ���ϱ�
	for (i = 0;i < count;i++) {
		if (abs(points[i].x - midPoint.x) < d) {
			borders[border_count] = points[i];
			border_count++;
		}
	}

	//�߰� ���� ���鿡�� �ּ� �Ÿ��� ���ϰ� ���� �ּ� �Ÿ��� ��.
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
	//���� X��ǥ�� �������� ����
	qsort(points, count, sizeof(Point), compareX);

	return closestPairRecursive(points, count);
}