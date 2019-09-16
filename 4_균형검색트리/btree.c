#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btree.h"

// B-트리 생성
//B-트리를 최초 생성하면 초기화로 인해 루트 노드 포인터에 NULL이 할당됩니다.
BTree* createBTree()
{
	BTree *pReturn = NULL;

	pReturn = (BTree *)malloc(sizeof(BTree)); //메모리 할당
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(BTree)); //메모리 초기화
	}
	else {
		printf("오류, 메모리할당 in createBTree()\n");
		return NULL;
	}

	return pReturn;
}

//키 값으로 노드를 찾는 탐색 연산
BTreeNodeData* searchBT(BTree* pBTree, int key)
{
	BTreeNodeData* pReturn = NULL;
	BTreeNode* pCurrentNode = NULL;
	int i = 0;

	if (pBTree != NULL) {
		pCurrentNode = pBTree->pRootNode;
		while (pCurrentNode != NULL) { //다음 노드가 없을 때까지 루프.
			for (i = 0; i < pCurrentNode->count; i++) {
				int currentKey = pCurrentNode->data[i].key;
				if (key == currentKey) { //검색 대상을 찾은 경우
					pReturn = &pCurrentNode->data[i];
					return pReturn;
				}
				else if (key < currentKey) { //검색 키 값이 현재 비교 대상 키 값보다 작은 경우
					break;
				}
			}
			pCurrentNode = pCurrentNode->children[i]; //자식노드로 내려가서 다시 검색 수행.
		}
	}

	return pReturn; //실패했을 때 NULL.
}

// 자료 추가.
//새로운 자료를 추가하려면 검색에 실패해야 합니다.=>현재 노드가 NULL로 루프를 빠져나올 때.
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
	pStack = createLinkedStack(); //스택의 생서이균형 유지 연산에 필요.
	if (pStack == NULL) {
		ret = 0;
		return ret;
	}
	// INSERT할 leaf node 찾기.
	pCurrentNode = pBTree->pRootNode;
	while (pCurrentNode != NULL) {
		//단계별로 해당 노드에 대한 포인터를 스택에 푸시. 노드를 기억하기 위해.
		pushLS(pStack, pCurrentNode); //스택에 현재 노드를 푸시
		pParentNode = pCurrentNode; //ParentNode를 현재노드로 재설정.

		for (i = 0; i < pCurrentNode->count; i++) {
			int currentKey = pCurrentNode->data[i].key;
			if (data.key == currentKey) { //검색키와 같은 키를 가지면 중복
				printf("오류,중복된 키-[%d]\n", data.key);
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
	if (pParentNode == NULL) {	// ROOT 노드가 아직 없는 경우.
		pBTree->pRootNode = createBTreeNode(data); //먼저 새로운 노드를 생성하고 자료 추가.
	}
	else {
		//자료 저장
		addNodeBT(pParentNode, data, NULL); //찾은 노드에 자료 추가

		//노드 분할
		splitNodeBT(pBTree, pStack); //필요할 경우 노드 분할.
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
				// 트리 전체 Depth가 1증가.
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
	if (pReturn != NULL) {	// 메모리 할당 성공 검증
		// 데이터 초기화.
		memset(pReturn, 0, sizeof(BTreeNode));
		pReturn->data[0] = data;
		pReturn->count = 1;
	}
	else {
		printf("Error, malloc() in createBTreeNode()\n");
	}

	return pReturn;
}

//기존 노드에 새로운 자료를 추가.
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

// 자료 제거.
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

	// 제거할 node 찾기.
	pCurrentNode = pBTree->pRootNode;
	while (pCurrentNode != NULL && isFind == 0) {
		pParentNode = pCurrentNode;
		pushLS(pStack, pParentNode); //순회하는 단계별로 해당 노드에 대한 포인터를 스택에 푸시.

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

	if (isFind == 1) { //추가연산과 달리 찾아야 삭제 가능.
		if (isLeafNode(pParentNode) == 0) { //단말 노드가 아니라면 대체 노드와 자료를 교환하여 제거.
			//삭제 대상을 찾았다면 노드 삭제.
			pParentNode = replaceLeafNodeBT(pBTree, pParentNode, i, pStack);
		}
		else { //단말 노드라면 바로 삭제
			deleteKeyBT(pParentNode, i);
		}
		//균형 연산이 필요하면 균형 연산을 실행
		//현재 노드의 자료 개수를 검사하여 기준값보다 작은 경우 균형 유지 연산을 실행.
		if (pParentNode->count < (BTREE_ORDER / 2)) {
			balanceBTree(pBTree, pStack);
		}

		ret = 1;
	}
	else {
		ret = 0;
		printf("오류,검색키-[%d]가 발견되지 않습니다,removeDataBT()\n", key);

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

	// 오른쪽에서 빌려옴.
	if (index < pParentBTreeNode->count
		&& pParentBTreeNode->children[index + 1]->count >= (BTREE_ORDER / 2 + 1)) {
		borrowRightNodeBT(pParentBTreeNode, pCurrentBTreeNode, index, pParentBTreeNode->children[index + 1]);
		// 왼쪽에서 빌려옴.
	}
	else if (index > 0
		&& pParentBTreeNode->children[index - 1]->count >= (BTREE_ORDER / 2 + 1)) {
		borrowLeftNodeBT(pParentBTreeNode, pCurrentBTreeNode, index, pParentBTreeNode->children[index - 1]);
	}
	else {
		// 병합.
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

	// Parent 노드에서 자료 한 개 가져오기.
	count = pCurrentNode->count;
	pCurrentNode->data[count] = pParentNode->data[index];
	pCurrentNode->count++;

	// 오른쪽 노드의 가장 왼쪽 자료 가져오기.
	pParentNode->data[index] = pRightNode->data[0];

	// 오른쪽 노드 왼쪽으로 한칸씩 Shift.
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

	//왼쪽 노드의 가장 오른쪽 자료를 부모 노드로 이동.
	count = pLeftNode->count;
	leftElement = pLeftNode->data[count - 1];
	parentElement = pParentNode->data[index - 1];
	deleteKeyBT(pLeftNode, count - 1);

	pParentNode->data[index - 1] = leftElement;

	// Parent 노드의 자료를 오른쪽 노드의 가장 왼쪽으로 insert하기.
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

	// 오른쪽 노드와 병합.
	if (index < pParentBTreeNode->count) {
		pLeftNode = pCurrentBTreeNode;
		pRightNode = pParentBTreeNode->children[index + 1];
		pivotIndex = index;
		parentElement = pParentBTreeNode->data[pivotIndex];
	}
	else {
		//왼쪽 노드와 병합.
		pLeftNode = pParentBTreeNode->children[index - 1];
		pRightNode = pCurrentBTreeNode;
		pivotIndex = index - 1;
		parentElement = pParentBTreeNode->data[pivotIndex];
	}

	// 왼쪽 노드에 Parent 자료 추가.
	addNodeBT(pLeftNode, parentElement, pRightNode->children[0]);

	// 왼쪽 노드에 오른쪽 노드 자료들 추가.
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

// 트리 삭제.
void deleteBTree(BTree* pBTree)
{
	if (pBTree != NULL) {
		deleteBTreeNode(pBTree->pRootNode);
		free(pBTree);
	}
}

// 트리 노드의 삭제(재귀적).
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
	static int x = 0; //깊이를 static으로 저장.
	if (pNode != NULL) {
		x += 2;
		for (i = 2; i < x; i++) { //깊이만큼 빈칸을 출력하고서
			printf("   ");
		}
		for (i = 0; i < pNode->count; i++) { //자신이 저장한 자료를 출력하고
			printf("(%d,%c) ", pNode->data[i].key, pNode->data[i].value);
		}
		printf("\n");
		for (i = 0; i < pNode->count + 1; i++) { //마지막으로 서브트리에 대해서 재귀적으로 호출
			displayBTreeNode(pNode->children[i]);
		}
		x -= 2;
	}
}