#include "huffman.h"
#pragma warning(disable:4996)

HuffmanTreeNode* makeNewHuffmanTreeNode(char data) {
	HuffmanTreeNode* pReturn = (HuffmanTreeNode*)malloc(sizeof(HuffmanTreeNode));
	if (pReturn != NULL) {
		pReturn->data = data;
		pReturn->pLeftChild = NULL;
		pReturn->pRightChild = NULL;
	}
	return pReturn;
}

HuffmanTree* makeHuffmanTree(HuffmanTreeNode *pRootNode) {
	HuffmanTree *pReturn = NULL;
	pReturn = (HuffmanTree*)malloc(sizeof(HuffmanTree));
	if (pReturn != NULL) {
		pReturn->pRootNode = pRootNode;
	}
	else {
		printf("����, �޸� �Ҵ�(1), makeHuffmanTree()\n");
		return pReturn;
	}
}

void deleteBinTreeNode(HuffmanTreeNode* pNode) {
	if (pNode != NULL) {
		deleteBinTreeNode(pNode->pLeftChild);
		deleteBinTreeNode(pNode->pRightChild);
		free(pNode);
	}
}

void deleteHuffmanTree(HuffmanTree* pBinTree) {
	if (pBinTree != NULL) {
		deleteBinTreeNode(pBinTree->pRootNode);
		free(pBinTree);
	}
}

//Ʈ���� ������ ��¸�
void inorderTraversalAndPrintNode(HuffmanTreeNode *pNode) {
	if (pNode != NULL) {
		if (pNode->pLeftChild != NULL) {
			sprintf(pNode->pLeftChild->bitString, "%s0", pNode->bitString);
			inorderTraversalAndPrintNode(pNode->pLeftChild);
		}
		if (pNode->pLeftChild == NULL && pNode->pRightChild == NULL) {
			printf("%c:%s\n", pNode->data, pNode->bitString);
		}
		if (pNode->pRightChild != NULL) {
			sprintf(pNode->pRightChild->bitString, "%s1", pNode->bitString);
			inorderTraversalAndPrintNode(pNode->pRightChild);
		}
	}
}

void printHuffmanTree(HuffmanTree *pBinTree) {
	if (pBinTree != NULL) {
		pBinTree->pRootNode->bitString[0] = 0;
		inorderTraversalAndPrintNode(pBinTree->pRootNode);
		printf("\n");
	}
}

//���� Ʈ���� ���� ��ȸ�� ����մϴ�.
//��ȸ�� �ϸ鼭 Ʈ���� ��忡 ���ڵ� ����� ������ ��Ʈ ���ڿ��� �����մϴ�.
//�ܸ� ��带 ���� ��쿡�� ���ݱ��� ���� ���� ������ ��Ʈ ���ڿ��� ������ �ڵ� ���̺� ����.
void inorderTraversalAndupdateBitstring(HuffmanTreeNode *pNode, HuffmanCode *pHuffmanCodeTable) {
	if (pNode != NULL) {
		//���� �ڽ� Ʈ���� ��ȸ
		if (pNode->pLeftChild != NULL) {
			//���� �ڽ� '0'�߰�
			sprintf(pNode->pLeftChild->bitString, "%s0", pNode->bitString);
			inorderTraversalAndupdateBitstring(pNode->pLeftChild, pHuffmanCodeTable);
		}
		//���� ��带 �湮
		//�ܸ� ����̸� ���� �ܸ� ��忡 ����� ��Ʈ ���ڿ��� ���̺� ����.
		if (pNode->pLeftChild == NULL && pNode->pRightChild == NULL) {
			int index = (int)pNode->data;
			strcpy(pHuffmanCodeTable[index].bitString, pNode->bitString);
		}
		//���Ŀ� ������ �ڽ� Ʈ���� ��ȸ.
		if (pNode->pRightChild != NULL) {
			//������ �ڽ� '1'�߰�
			sprintf(pNode->pRightChild->bitString, "%s1", pNode->bitString);
			inorderTraversalAndupdateBitstring(pNode->pRightChild, pHuffmanCodeTable);
		}
	}
}

//�� ���ڸ� ����� ����� ������ �ڵ� ���̺� �ٽ� �����ϴ� ����.
//��Ʈ ���ڿ��� ���� Ʈ���� ������ Ʈ���� ��ȸ�ؾߵǰ� ���� ��ȸ�� �̿��߽��ϴ�.
void applyBitstring(HuffmanTree *pHuffmanTree, HuffmanCode *pHuffmanCodeTable) {
	if (pHuffmanTree != NULL) {
		pHuffmanTree->pRootNode->bitString[0] = 0;
		inorderTraversalAndupdateBitstring(pHuffmanTree->pRootNode, pHuffmanCodeTable);
	}
}

//�Է� ���ڿ��� ���� �޾� �� ������ �󵵼��� ����ϴ� �Լ�
//pSourceCode�� HuffmanCode Ÿ���� 1���� �迭�Դϴ�.
//���� ��ȣ0���� �ִ� ���� ��ȣ(codeCount-1)������ ��� codeCount���� ���ڿ� ���� �ڷḦ ����.
void checkFrequency(char *pSourceString, HuffmanCode *pSourceCode, int codeCount) {
	long count = 0, i = 0;

	if (pSourceString == NULL || pSourceCode == NULL) {
		return;
	}

	memset(pSourceCode, 0, sizeof(HuffmanCode)*codeCount);
	for (i = 0;i < codeCount;i++) {
		pSourceCode[i].data = (char)i; //���̺� data�� ���ڸ� ������� ����. ������ 0.
	}

	count = strlen(pSourceString);
	for (i = 0;i < count;i++) {
		int asc = pSourceString[i]; //���̺����� ��ġ �ε���.
		pSourceCode[asc].frequency++; //asc��ġ�� ����� �󵵼��� 1����.
	}
}

//���ں� �󵵼� ������ �̿��� ���� ������ Ʈ���� ����� �Լ�
HuffmanTree *buildHuffmanTree(HuffmanCode *pCodes) {
	HuffmanTree *pHuffmanTree = NULL;
	ArrayMinHeap* pHeap = NULL;
	HeapNode *pLastHeapNode = NULL;
	int i = 0, unique_char_num = 0;

	pHeap = createArrayHeap(COUNT_ASC); //�ּ� ������ ����
	if (pHeap == NULL) {
		return pHuffmanTree;
	}

	//������ �ڵ� ���̺� ����� ���ڵ��� ������ �߰�.
	for (i = 0;i < COUNT_ASC;i++) {
		if (pCodes[i].frequency > 0) {
			HeapNode heapNode = { 0 };
			heapNode.frequency = pCodes[i].frequency;
			heapNode.pData = makeNewHuffmanTreeNode(pCodes[i].data);

			insertMinHeapAH(pHeap, heapNode);
		}
	}

	unique_char_num = pHeap->currentCount;
	//���� 2������ �θ� ��� 1���� ��������� ������ ����� ���� ���� -1��ŭ ����.
	for (i = 0;i < unique_char_num - 1;i++) {
		//���� ������ ���鼭 �ּ� �󵵼� ��带 2���� ������
		HeapNode *pLeft = deleteMinHeapAH(pHeap);
		HeapNode *pRight = deleteMinHeapAH(pHeap);
		if (pRight != NULL && pLeft != NULL) {
			//�θ� ��带 �����
			HeapNode heapNode = { 0 };
			HuffmanTreeNode *pHuffmanNode = NULL;

			pHuffmanNode = makeNewHuffmanTreeNode('?');
			pHuffmanNode->pLeftChild = pLeft->pData;
			pHuffmanNode->pRightChild = pRight->pData;

			heapNode.frequency = pRight->frequency + pLeft->frequency;
			heapNode.pData = pHuffmanNode;
			//�ٽ� ������ �߰�.
			insertMinHeapAH(pHeap, heapNode);

			free(pRight);
			free(pLeft);
		}
	}
	//������ ���� ���� ���������� ���� 1���� �θ� ��尡 ������ ����.
	pLastHeapNode = deleteMinHeapAH(pHeap); 
	if (pLastHeapNode != NULL) {
		//�� ���� ��Ʈ ��带 ������ Ʈ���� �����
		pHuffmanTree = makeHuffmanTree(pLastHeapNode->pData);
	}

	deleteArrayHeap(pHeap);

	//������ ������ Ʈ���� ��ȯ.
	return pHuffmanTree; 
}

//���� ���ڿ��� �Է� �Ķ���ͷ� ���� �޾� ������ �ڵ��� ���� ���ڿ��� ��ȯ.
char* getEncodedString(char *pSourceString, HuffmanCode* pHuffmanCodeTable) {
	char *pReturn = NULL;
	long count = 0, i = 0;

	if (pSourceString == NULL || pHuffmanCodeTable == NULL) {
		return pReturn;
	}

	count = strlen(pSourceString);
	pReturn = (char*)malloc(sizeof(char)*count*(MAX_BIT_SIZE + 1));

	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(char)*count*(MAX_BIT_SIZE + 1));
		for (i = 0;i < count;i++) {
			int index = (int)pSourceString[i]; //������ �ڵ� ���� �����ͼ�
			//�� ���ڿ� �ش��ϴ� ��Ʈ ���ڿ��� ��� ���ڿ��� �����Դϴ�.
			strcat(pReturn, pHuffmanCodeTable[index].bitString); 
		}
	}
	return pReturn;
}

//������ �ڵ�� ���ڵ��� ���ڿ��� ������ ���ڿ��� ��ȯ�ϴ� �Լ�
char* getDecodedString(char *pSourceString, HuffmanTree *pHuffmanTree) {
	char *pReturn = NULL;
	HuffmanTreeNode *pNode = NULL;
	long count = 0, i = 0;

	if (pSourceString == NULL || pHuffmanTree == NULL) {
		return pReturn;
	}

	count = strlen(pSourceString);
	pReturn = (char*)malloc(sizeof(char)*count);
	if (pReturn != NULL) {
		memset(pReturn, 0, sizeof(char)*count);

		pNode = pHuffmanTree->pRootNode;
		for (i = 0;i < count;i++) {
			char bit = (char)pSourceString[i];

			if ('0' == bit) {
				pNode = pNode->pLeftChild;
			}
			else {
				pNode = pNode->pRightChild;
			}
			if (pNode->pLeftChild == NULL && pNode->pRightChild == NULL) {
				sprintf(pReturn, "%s%c", pReturn, pNode->data);
				pNode = pHuffmanTree->pRootNode;
			}
		}
	}
	return pReturn;
}