#ifndef _LINKEDLIST_
#define _LINKEDLIST_

#include "hashingdef.h"

typedef struct LinkedListNodeType {
	HashSlot data;
	struct LinkedListNodeType *pLink;
}LinkedListNode;

typedef struct LinkedListType {
	LinkedListNode headerNode;
	int currentCount;
}LinkedList;

LinkedList* createLinkedList();
HashSlot* getLinkedListData(LinkedList* pList, int position);
int addLinkedListData(LinkedList* pLIst, int position, HashSlot data);
int removeLinkedListData(LinkedList* pList, int position);
void deleteLinkedList(LinkedList* pList);
int getLinkedListLength(LinkedList* pList);

#endif