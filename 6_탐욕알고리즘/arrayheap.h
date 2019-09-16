/*
허프만 트리를 만드려면 정렬 함수가 필요합니다.
히프 정렬을 이용하였으며 배열 기반의 최소 히프를 이용하여 정렬 기능을 사용.
*/

#ifndef _ARRAY_HEAP_
#define _ARRAY_HEAP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HeapNodeType {
	int frequency;
	void *pData; //HuffmanTreeNode를 가리킴
}HeapNode;

typedef struct ArrayHeapType {
	int maxCount; //최대 노드 개수
	int currentCount; //현재 노드 개수
	HeapNode *pData; //노드 저장을 위한 1차원 배열
}ArrayMaxHeap, ArrayMinHeap;

//최소 히프를 만드는 함수.
ArrayMaxHeap* createArrayHeap(int maxCount);
//자료들을 추가
int insertMinHeapAH(ArrayMaxHeap* pHeap, HeapNode value);
//현재 크기(frequency)가 가장 작은 노드를 반환.
//문자의 빈도수가 가장 작은 2개의 문자를 고를 때.
HeapNode* deleteMinHeapAH(ArrayMaxHeap* pHeap);
void deleteArrayHeap(ArrayMaxHeap* pHeap);
void displayArrayHeap(ArrayMaxHeap* pHeap);

#endif