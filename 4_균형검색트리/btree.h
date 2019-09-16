#ifndef _B_TREE_
#define _B_TREE_

#include "btreedef.h"
#include "btlinkedstack.h"

typedef struct BTreeType {
	BTreeNode *pRootNode;
}BTree;

//B-Ʈ�� ����
BTree* createBTree();

//B-Ʈ�� ����
void deleteBTree(BTree* pBTree);

//�˻�
BTreeNodeData* searchBT(BTree* pBTree, int key);

//�ڷ� �߰�
int addDataBT(BTree* pBTree, BTreeNodeData data);

//�ڷ� ����
int removeDataBT(BTree* pBTree, int key);

//B-Ʈ�� ǥ��
void displayBTree(BTree *pTree);

//�� �� ���� �Լ���
BTreeNode* createBTreeNode(BTreeNodeData data);

void addNodeBT(BTreeNode* pCurrentNode, BTreeNodeData data, BTreeNode* pRChildNode);

void splitNodeBT(BTree* pBTree, LinkedStack* pStack);

int isLeafNode(BTreeNode* pParentNode);

BTreeNode* replaceLeafNodeBT(BTree *pBTree, BTreeNode* pDelNode, int index, LinkedStack* pStack);

void deleteBTreeNode(BTreeNode* pBTreeNode);

void deleteKeyBT(BTreeNode* pNode, int index);

void balanceBTree(BTree* pParentNode, BTreeNode* pCurrentNode);

void borrowRightNodeBT(BTreeNode* pParentNode, BTreeNode* pCurrentNode,
	int index, BTreeNode* pRightNode);

void borrowLeftNodeBT(BTreeNode* pParentNode, BTreeNode* pCurrentNode,
	int index, BTreeNode* pLeftNode);

void mergeNodeBT(BTree *pBTree, LinkedStack* pStack, BTreeNode* pParentBTreeNode,
	BTreeNode* pCurrentBTreeNode, int index);

void displayBTreeNode(BTreeNode *pNode);

#endif