#include <stdio.h>
#include "closestpair.h"

int main() {
	int count = 0;
	double min_dist = 0;
	Point points[] = { {2,5},{15,30},{40,50},{5,2},{15,10},{10,5} };

	count = sizeof(points) / sizeof(Point);
	min_dist = closestPair(points, count);
	printf("������ ��� %d���̸� ���� ����� �� ���� �Ÿ��� %f �Դϴ�\n", count, min_dist);

	return 0;
}