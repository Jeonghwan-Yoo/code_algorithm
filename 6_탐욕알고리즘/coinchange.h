/*
6.2.2Ž�� �˰����� ����
06_01.c:���� ���α׷�
coinchange.h:���� �Ž����� ���ϱ� ���� ����ü�� �Լ� ����
coinchange.c:���� �Ž����� ���ϱ� ���� �Լ� ����

����ü CoinItem�� ������ ���� ������ �����ϴ� value�� ���õ� ������ ������ �����ϴ� selected�� ����.
*/

#ifndef coinchange_h
#define coinchange_h

#include <stdio.h>
#include <stdlib.h>

typedef struct CoinItem {
	int value;
	int selected;
}CoinItem;

//��¥�� ������ �ִ����� ����ڿ��Լ� �Է� �޽��ϴ�.
//�Է� ���� �������� ������ ���� �Ž������� ������ ���� �޽��ϴ�.
//���⼭ items�� ����� �Ķ�����̱� ������ ����� ���� ������ items�� ����.
void inputItems(CoinItem *items, int item_count);
//���� Ž�� �˰����� �̿��Ͽ� �� ������ �������� �� ���� ������ ����ؾ� �ϴ��� ���.
//��ȯ�� ���� �������� �Ž������� ����� ���� �ݾ�.
int getChange(int change_total, CoinItem *items, int item_count);
//�ռ� ���� ������ �Ž����� ������ ����մϴ�.
void printResult(CoinItem *items, int item_count, int remained);

#endif
