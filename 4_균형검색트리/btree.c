#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btree.h"

// B-Ʈ�� ����
//B-Ʈ���� ���� �����ϸ� �ʱ�ȭ�� ���� ��Ʈ ��� �����Ϳ� NULL�� �Ҵ�˴ϴ�.
BTree* createBTree()
{
	BTree *pReturn = NULL;

	pReturn = (BTree *)malloc(sizeof(BTree)); //�޸� �Ҵ�
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(BTree)); //�޸� �ʱ�ȭ
	}
	else {
		printf("����, �޸��Ҵ� in createBTree()\n");
		return NULL;
	}

	return pReturn;
}

//Ű ������ ��带 ã�� Ž�� ����
BTreeNodeData* searchBT(BTree* pBTree, int key)
{
	BTreeNodeData* pReturn = NULL;
	BTreeNode* pCurrentNode = NULL;
	int i = 0;

	if (pBTree != NULL) {
		pCurrentNode = pBTree->pRootNode;
		while (pCurrentNode != NULL) { //���� ��尡 ���� ������ ����.
			for (i = 0; i < pCurrentNode->count; i++) {
				int currentKey = pCurrentNode->data[i].key;
				if (key == currentKey) { //�˻� ����� ã�� ���
					pReturn = &pCurrentNode->data[i];
					return pReturn;
				}
				else if (key < currentKey) { //�˻� Ű ���� ���� �� ��� Ű ������ ���� ���
					break;
				}
			}
			pCurrentNode = pCurrentNode->children[i]; //�ڽĳ��� �������� �ٽ� �˻� ����.
		}
	}

	return pReturn; //�������� �� NULL.
}

// �ڷ� �߰�.
//���ο� �ڷḦ �߰��Ϸ��� �˻��� �����ؾ� �մϴ�.=>���� ��尡 NULL�� ������ �������� ��.
int addDataBT(BTree* pBTree, BTreeNodeData data)
{
	int ret = 1;
	int i = 0;
	BTreeNode *pParentNode = NULL, *pCurrentNode = NULL;
	LinkedStack* pStack = NULL;

	if (pBTree == NULL) {
		ret = 0;
		return ret;
	}
	pStack = createLinkedStack(); //������ �����̱��� ���� ���꿡 �ʿ�.
	if (pStack == NULL) {
		ret = 0;
		return ret;
	}
	// INSERT�� leaf node ã��.
	pCurrentNode = pBTree->pRootNode;
	while (pCurrentNode != NULL) {
		//�ܰ躰�� �ش� ��忡 ���� �����͸� ���ÿ� Ǫ��. ��带 ����ϱ� ����.
		pushLS(pStack, pCurrentNode); //���ÿ� ���� ��带 Ǫ��
		pParentNode = pCurrentNode; //ParentNode�� ������� �缳��.

		for (i = 0; i < pCurrentNode->count; i++) {
			int currentKey = pCurrentNode->data[i].key;
			if (data.key == currentKey) { //�˻�Ű�� ���� Ű�� ������ �ߺ�
				printf("����,�ߺ��� Ű-[%d]\n", data.key);
				ret = 0;
				deleteLinkedStack(pStack);
				return ret;
			}
			else if (data.key < currentKey) {
				break;
			}
		}
		pCurrentNode = pCurrentNode->children[i];
	}
	if (pParentNode == NULL) {	// ROOT ��尡 ���� ���� ���.
		pBTree->pRootNode = createBTreeNode(data); //���� ���ο� ��带 �����ϰ� �ڷ� �߰�.
	}
	else {
		//�ڷ� ����
		addNodeBT(pParentNode, data, NULL); //ã�� ��忡 �ڷ� �߰�

		//��� ����
		splitNodeBT(pBTree, pStack); //�ʿ��� ��� ��� ����.
	}
	ret = 1;
	deleteLinkedStack(pStack);

	return ret;
}

void splitNodeBT(BTree* pBTree, LinkedStack* pStack)
{
	LinkedStackNode* pParentStackNode = NULL;
	LinkedStackNode* pCurrentStackNode = NULL;

	BTreeNode* pCurrentBTreeNode = NULL;
	BTreeNode* pNewBTreeNode = NULL;
	BTreeNodeData pivotElement = { 0, };
	int pivotIndex = BTREE_ORDER / 2;
	int i = 0;

	if (pStack == NULL) {
		return;
	}
	pCurrentStackNode = popLS(pStack);
	while (pCurrentStackNode != NULL) {
		pCurrentBTreeNode = pCurrentStackNode->data;
		if (pCurrentBTreeNode->count >= BTREE_ORDER) {
			pNewBTreeNode = (BTreeNode *)malloc(sizeof(BTreeNode));
			if (pNewBTreeNode != NULL) {
				memset(pNewBTreeNode, 0, sizeof(BTreeNode));
			}
			else {
				printf("Error, malloc() in splitNodeBT()\n");
				break;
			}

			pivotElement = pCurrentBTreeNode->data[pivotIndex];
			memset(&pCurrentBTreeNode->data[pivotIndex], 0, sizeof(BTreeNodeData));

			for (i = pivotIndex + 1; i < BTREE_ORDER; i++) {
				pNewBTreeNode->data[i - pivotIndex - 1] = pCurrentBTreeNode->data[i];
				pNewBTreeNode->children[i - pivotIndex - 1] = pCurrentBTreeNode->children[i];

				memset(&pCurrentBTreeNode->data[i], 0, sizeof(BTreeNodeData));
				pCurrentBTreeNode->children[i] = NULL;
			}
			pNewBTreeNode->children[i - pivotIndex - 1] = pCurrentBTreeNode->children[i];
			pCurrentBTreeNode->children[i] = NULL;
			pNewBTreeNode->count = BTREE_ORDER - pivotIndex - 1;
			pCurrentBTreeNode->count = pivotIndex;

			pParentStackNode = popLS(pStack);
			if (pParentStackNode != NULL) {
				addNodeBT(pParentStackNode->data, pivotElement, pNewBTreeNode);
			}
			else {
				// Ʈ�� ��ü Depth�� 1����.
				pBTree->pRootNode = createBTreeNode(pivotElement);
				pBTree->pRootNode->children[0] = pCurrentBTreeNode;
				pBTree->pRootNode->children[1] = pNewBTreeNode;
			}
		}

		if (pCurrentStackNode != NULL) {
			free(pCurrentStackNode);
		}
		pCurrentStackNode = pParentStackNode;
		pParentStackNode = NULL;
	}

	if (pCurrentStackNode != NULL) free(pCurrentStackNode);
	if (pParentStackNode != NULL) free(pParentStackNode);
}

BTreeNode* createBTreeNode(BTreeNodeData data)
{
	BTreeNode* pReturn = NULL;

	pReturn = (BTreeNode *)malloc(sizeof(BTreeNode));
	if (pReturn != NULL) {	// �޸� �Ҵ� ���� ����
		// ������ �ʱ�ȭ.
		memset(pReturn, 0, sizeof(BTreeNode));
		pReturn->data[0] = data;
		pReturn->count = 1;
	}
	else {
		printf("Error, malloc() in createBTreeNode()\n");
	}

	return pReturn;
}

//���� ��忡 ���ο� �ڷḦ �߰�.
void addNodeBT(BTreeNode* pCurrentNode,
	BTreeNodeData data,
	BTreeNode* pRChildNode) {
	int i = 0;
	for (i = pCurrentNode->count - 1; i >= 0; i--) {
		int tempKey = pCurrentNode->data[i].key;
		if (data.key < tempKey) {
			pCurrentNode->data[i + 1] = pCurrentNode->data[i];
			pCurrentNode->children[i + 2] = pCurrentNode->children[i + 1];
		}
		else {
			break;
		}
	}
	pCurrentNode->data[i + 1] = data;
	pCurrentNode->children[i + 2] = pRChildNode;
	pCurrentNode->count++;
}

// �ڷ� ����.
int removeDataBT(BTree* pBTree, int key)
{
	int ret = 1;
	int i = 0;
	int isFind = 0;

	BTreeNode* pParentNode = NULL;
	BTreeNode* pCurrentNode = NULL;

	LinkedStack* pStack = NULL;

	if (pBTree == NULL) {
		ret = 0;
		return ret;
	}

	pStack = createLinkedStack();
	if (pStack == NULL) {
		ret = 0;
		return ret;
	}

	// ������ node ã��.
	pCurrentNode = pBTree->pRootNode;
	while (pCurrentNode != NULL && isFind == 0) {
		pParentNode = pCurrentNode;
		pushLS(pStack, pParentNode); //��ȸ�ϴ� �ܰ躰�� �ش� ��忡 ���� �����͸� ���ÿ� Ǫ��.

		for (i = 0; i < pCurrentNode->count; i++) {
			int currentKey = pCurrentNode->data[i].key;
			if (key == currentKey) {
				isFind = 1;
				break;
			}
			else if (key < currentKey) {
				break;
			}
		}
		pCurrentNode = pCurrentNode->children[i];
	}

	if (isFind == 1) { //�߰������ �޸� ã�ƾ� ���� ����.
		if (isLeafNode(pParentNode) == 0) { //�ܸ� ��尡 �ƴ϶�� ��ü ���� �ڷḦ ��ȯ�Ͽ� ����.
			//���� ����� ã�Ҵٸ� ��� ����.
			pParentNode = replaceLeafNodeBT(pBTree, pParentNode, i, pStack);
		}
		else { //�ܸ� ����� �ٷ� ����
			deleteKeyBT(pParentNode, i);
		}
		//���� ������ �ʿ��ϸ� ���� ������ ����
		//���� ����� �ڷ� ������ �˻��Ͽ� ���ذ����� ���� ��� ���� ���� ������ ����.
		if (pParentNode->count < (BTREE_ORDER / 2)) {
			balanceBTree(pBTree, pStack);
		}

		ret = 1;
	}
	else {
		ret = 0;
		printf("����,�˻�Ű-[%d]�� �߰ߵ��� �ʽ��ϴ�,removeDataBT()\n", key);

	}
	deleteLinkedStack(pStack);

	return ret;
}

void balanceBTree(BTree *pBTree, LinkedStack* pStack)
{
	LinkedStackNode* pParentStackNode = NULL;
	LinkedStackNode* pCurrentStackNode = NULL;
	BTreeNode* pParentBTreeNode = NULL;
	BTreeNode* pCurrentBTreeNode = NULL;

	int index = 0;

	if (pStack == NULL) {
		return;
	}
	pCurrentStackNode = popLS(pStack);
	if (pCurrentStackNode == NULL) {
		return;
	}

	pCurrentBTreeNode = pCurrentStackNode->data;
	if (pCurrentBTreeNode->count >= (BTREE_ORDER / 2)) {
		free(pCurrentStackNode);
		return;
	}

	pParentStackNode = popLS(pStack);
	if (pParentStackNode == NULL) {
		free(pCurrentStackNode);
		return;
	}

	pParentBTreeNode = pParentStackNode->data;
	index = getIndexInfo(pParentBTreeNode, pCurrentBTreeNode);

	// �����ʿ��� ������.
	if (index < pParentBTreeNode->count
		&& pParentBTreeNode->children[index + 1]->count >= (BTREE_ORDER / 2 + 1)) {
		borrowRightNodeBT(pParentBTreeNode, pCurrentBTreeNode, index, pParentBTreeNode->children[index + 1]);
		// ���ʿ��� ������.
	}
	else if (index > 0
		&& pParentBTreeNode->children[index - 1]->count >= (BTREE_ORDER / 2 + 1)) {
		borrowLeftNodeBT(pParentBTreeNode, pCurrentBTreeNode, index, pParentBTreeNode->children[index - 1]);
	}
	else {
		// ����.
		mergeNodeBT(pBTree, pStack, pParentBTreeNode, pCurrentBTreeNode, index);
	}

	if (pCurrentStackNode != NULL) {
		free(pCurrentStackNode);
	}
	if (pParentStackNode != NULL) {
		free(pParentStackNode);
	}
}

void borrowRightNodeBT(BTreeNode* pParentNode,
	BTreeNode* pCurrentNode, int index,
	BTreeNode* pRightNode)
{
	int count = 0;

	if (pParentNode == NULL || pCurrentNode == NULL || pRightNode == NULL) {
		return;
	}

	// Parent ��忡�� �ڷ� �� �� ��������.
	count = pCurrentNode->count;
	pCurrentNode->data[count] = pParentNode->data[index];
	pCurrentNode->count++;

	// ������ ����� ���� ���� �ڷ� ��������.
	pParentNode->data[index] = pRightNode->data[0];

	// ������ ��� �������� ��ĭ�� Shift.
	deleteKeyBT(pRightNode, 0);
}

void borrowLeftNodeBT(BTreeNode* pParentNode,
	BTreeNode* pCurrentNode, int index,
	BTreeNode* pLeftNode)
{
	int count = 0;
	BTreeNodeData leftElement = { 0, };
	BTreeNodeData parentElement = { 0, };

	if (pParentNode == NULL || pCurrentNode == NULL || pLeftNode == NULL) {
		return;
	}

	//���� ����� ���� ������ �ڷḦ �θ� ���� �̵�.
	count = pLeftNode->count;
	leftElement = pLeftNode->data[count - 1];
	parentElement = pParentNode->data[index - 1];
	deleteKeyBT(pLeftNode, count - 1);

	pParentNode->data[index - 1] = leftElement;

	// Parent ����� �ڷḦ ������ ����� ���� �������� insert�ϱ�.
	addNodeBT(pCurrentNode,
		parentElement,
		NULL);
}

void mergeNodeBT(BTree *pBTree, LinkedStack* pStack,
	BTreeNode* pParentBTreeNode,
	BTreeNode* pCurrentBTreeNode, int index)
{
	LinkedStackNode* pParentStackNode = NULL;
	BTreeNode* pParentParentNode = NULL;
	BTreeNode* pLeftNode = NULL;
	BTreeNode* pRightNode = NULL;
	BTreeNodeData parentElement = { 0, };
	int i = 0;
	int pivotIndex = 0;

	if (pBTree == NULL || pStack == NULL
		|| pParentBTreeNode == NULL || pCurrentBTreeNode == NULL) {
		return;
	}

	// ������ ���� ����.
	if (index < pParentBTreeNode->count) {
		pLeftNode = pCurrentBTreeNode;
		pRightNode = pParentBTreeNode->children[index + 1];
		pivotIndex = index;
		parentElement = pParentBTreeNode->data[pivotIndex];
	}
	else {
		//���� ���� ����.
		pLeftNode = pParentBTreeNode->children[index - 1];
		pRightNode = pCurrentBTreeNode;
		pivotIndex = index - 1;
		parentElement = pParentBTreeNode->data[pivotIndex];
	}

	// ���� ��忡 Parent �ڷ� �߰�.
	addNodeBT(pLeftNode, parentElement, pRightNode->children[0]);

	// ���� ��忡 ������ ��� �ڷ�� �߰�.
	for (i = 0; i < pRightNode->count; i++) {
		addNodeBT(pLeftNode, pRightNode->data[i], pRightNode->children[i + 1]);
	}
	deleteKeyBT(pParentBTreeNode, pivotIndex);
	free(pRightNode);

	if (pParentBTreeNode->count < (BTREE_ORDER / 2)) {
		int index = 0;
		pParentStackNode = popLS(pStack);
		if (pParentStackNode != NULL) {
			pParentParentNode = pParentStackNode->data;
			index = getIndexInfo(pParentParentNode, pParentBTreeNode);

			//displayBTree(pBTree);

			mergeNodeBT(pBTree, pStack,
				pParentParentNode,
				pParentBTreeNode, index);

			free(pParentStackNode);
		}
		else {
			if (pParentBTreeNode->count == 0) {
				free(pBTree->pRootNode);
				pBTree->pRootNode = pLeftNode;
				//printf("LAST: %d, %c", pLeftNode->data[0].key, pLeftNode->data[0].value);
			}
		}
	}
}

BTreeNode* replaceLeafNodeBT(BTree *pBTree, BTreeNode* pDelNode, int index,
	LinkedStack* pStack)
{
	BTreeNode* pReturn = NULL;
	BTreeNodeData leafNodeElement = { 0, };
	BTreeNode *pChildNode = NULL;
	BTreeNode* pParentNode = pDelNode;
	int count = index;

	if (pBTree == NULL || pDelNode == NULL) {
		return pReturn;
	}

	do {
		pChildNode = pParentNode->children[count];
		pushLS(pStack, pChildNode);

		count = pChildNode->count;
		pParentNode = pChildNode;
	} while (pChildNode->children[count] != NULL);

	leafNodeElement = pChildNode->data[count - 1];
	pDelNode->data[index] = leafNodeElement;
	deleteKeyBT(pChildNode, count - 1);

	pReturn = pChildNode;

	return pReturn;
}

int isLeafNode(BTreeNode* pParentNode)
{
	int ret = 0;

	if (pParentNode != NULL) {
		if (pParentNode->children[0] == NULL) {
			ret = 1;
		}
	}

	return ret;
}

int getIndexInfo(BTreeNode* pParentNode, BTreeNode* pCurrentNode)
{
	int ret = 0;
	int i = 0;

	if (pParentNode != NULL) {
		for (i = 0; i <= pParentNode->count; i++) {
			if (pParentNode->children[i] == pCurrentNode) {
				ret = i;
				break;
			}
		}
	}

	return ret;
}

void deleteKeyBT(BTreeNode* pNode, int index)
{
	int i = 0;
	if (pNode != NULL) {
		for (i = index + 1; i < pNode->count; i++) {
			pNode->data[i - 1] = pNode->data[i];
			pNode->children[i] = pNode->children[i + 1];
		}
		memset(&pNode->data[pNode->count - 1], 0, sizeof(BTreeNodeData));
		pNode->children[pNode->count] = NULL;

		pNode->count--;
	}
}

// Ʈ�� ����.
void deleteBTree(BTree* pBTree)
{
	if (pBTree != NULL) {
		deleteBTreeNode(pBTree->pRootNode);
		free(pBTree);
	}
}

// Ʈ�� ����� ����(�����).
void deleteBTreeNode(BTreeNode* pBTreeNode)
{
	int i = 0;
	if (pBTreeNode != NULL) {
		for (i = 0; i <= pBTreeNode->count; i++) {
			deleteBTreeNode(pBTreeNode->children[i]);
		}
		free(pBTreeNode);
	}
}

void displayBTree(BTree *pTree)
{
	if (pTree != NULL) {
		displayBTreeNode(pTree->pRootNode);
	}
}

void displayBTreeNode(BTreeNode *pNode)
{
	int i;
	static int x = 0; //���̸� static���� ����.
	if (pNode != NULL) {
		x += 2;
		for (i = 2; i < x; i++) { //���̸�ŭ ��ĭ�� ����ϰ�
			printf("   ");
		}
		for (i = 0; i < pNode->count; i++) { //�ڽ��� ������ �ڷḦ ����ϰ�
			printf("(%d,%c) ", pNode->data[i].key, pNode->data[i].value);
		}
		printf("\n");
		for (i = 0; i < pNode->count + 1; i++) { //���������� ����Ʈ���� ���ؼ� ��������� ȣ��
			displayBTreeNode(pNode->children[i]);
		}
		x -= 2;
	}
}