#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btreedef.h"
#include "btlinkedstack.h"

LinkedStack* createLinkedStack()
{
	LinkedStack *pReturn = NULL;
	pReturn = (LinkedStack *)malloc(sizeof(LinkedStack));
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(LinkedStack));
	}
	else {
		printf("오류, 메모리할당,createLinkedStack()\n");
		return NULL;
	}

	return pReturn;
}

int pushLS(LinkedStack* pStack, struct BTreeNodeType* data)
{
	int ret = 0;
	LinkedStackNode *pNode = NULL;

	if (pStack != NULL) {
		pNode = (LinkedStackNode *)malloc(sizeof(LinkedStackNode));
		if (pNode != NULL) {
			pNode->data = data;
			pNode->pLink = pStack->pTop;
			pStack->pTop = pNode;

			pStack->currentCount++;
			ret = 1;
		}
		else {
			printf("오류, 메모리할당,pushLS()\n");
		}
	}

	return ret;
}

LinkedStackNode* popLS(LinkedStack* pStack)
{
	LinkedStackNode* pReturn = NULL;
	if (pStack != NULL) {
		if (isLinkedStackEmpty(pStack) == 0) {
			pReturn = pStack->pTop;
			pStack->pTop = pReturn->pLink;
			pReturn->pLink = NULL;

			pStack->currentCount--;
		}
	}

	return pReturn;
}

LinkedStackNode* peekLS(LinkedStack* pStack)
{
	LinkedStackNode* pReturn = NULL;
	if (pStack != NULL) {
		if (isLinkedStackEmpty(pStack) == 0) {
			pReturn = pStack->pTop;
		}
	}

	return pReturn;
}

void deleteLinkedStack(LinkedStack* pStack)
{
	LinkedStackNode *pNode = NULL;
	LinkedStackNode *pDelNode = NULL;

	if (pStack != NULL) {
		pNode = pStack->pTop;
		while (pNode != NULL) {
			pDelNode = pNode;
			pNode = pNode->pLink;
			free(pDelNode);
		}
		free(pStack);
	}
}

int isLinkedStackFull(LinkedStack* pStack)
{
	int ret = 0;
	return ret;
}

int isLinkedStackEmpty(LinkedStack* pStack)
{
	int ret = 0;

	if (pStack != NULL) {
		if (pStack->currentCount == 0) {
			ret = 1;
		}
	}

	return ret;
}
