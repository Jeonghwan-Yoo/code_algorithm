/*
7.3.2���� ���� �˰����� ����
*/

#ifndef closestpair_h
#define closestpair_h

typedef struct _point {
	int x, y;
}Point;

//���� ����� ������ ���ϴ� �Լ�
//�Է� �Ķ���ͷ� ������ ������ count�� �߰��� ����.
//���� �迭 points�� ���� ���� count�� �Է� �Ķ����.
double closestPair(Point points[], int count);

#endif