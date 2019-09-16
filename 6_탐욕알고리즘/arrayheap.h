/*
������ Ʈ���� ������� ���� �Լ��� �ʿ��մϴ�.
���� ������ �̿��Ͽ����� �迭 ����� �ּ� ������ �̿��Ͽ� ���� ����� ���.
*/

#ifndef _ARRAY_HEAP_
#define _ARRAY_HEAP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HeapNodeType {
	int frequency;
	void *pData; //HuffmanTreeNode�� ����Ŵ
}HeapNode;

typedef struct ArrayHeapType {
	int maxCount; //�ִ� ��� ����
	int currentCount; //���� ��� ����
	HeapNode *pData; //��� ������ ���� 1���� �迭
}ArrayMaxHeap, ArrayMinHeap;

//�ּ� ������ ����� �Լ�.
ArrayMaxHeap* createArrayHeap(int maxCount);
//�ڷ���� �߰�
int insertMinHeapAH(ArrayMaxHeap* pHeap, HeapNode value);
//���� ũ��(frequency)�� ���� ���� ��带 ��ȯ.
//������ �󵵼��� ���� ���� 2���� ���ڸ� �� ��.
HeapNode* deleteMinHeapAH(ArrayMaxHeap* pHeap);
void deleteArrayHeap(ArrayMaxHeap* pHeap);
void displayArrayHeap(ArrayMaxHeap* pHeap);

#endif