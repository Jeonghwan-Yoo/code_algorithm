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
		printf("오류, 메모리 할당(1), makeHuffmanTree()\n");
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

//트리의 내용을 출력만
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

//실제 트리의 중위 순회를 담당합니다.
//순회를 하면서 트리의 노드에 인코딩 결과인 이진수 비트 문자열을 저장합니다.
//단말 노드를 만난 경우에는 지금까지 구한 최종 이진수 비트 문자열을 허프만 코드 테이블에 저장.
void inorderTraversalAndupdateBitstring(HuffmanTreeNode *pNode, HuffmanCode *pHuffmanCodeTable) {
	if (pNode != NULL) {
		//왼쪽 자식 트리를 순회
		if (pNode->pLeftChild != NULL) {
			//왼쪽 자식 '0'추가
			sprintf(pNode->pLeftChild->bitString, "%s0", pNode->bitString);
			inorderTraversalAndupdateBitstring(pNode->pLeftChild, pHuffmanCodeTable);
		}
		//현재 노드를 방문
		//단말 노드이면 현재 단말 노드에 저장된 비트 문자열을 테이블에 저장.
		if (pNode->pLeftChild == NULL && pNode->pRightChild == NULL) {
			int index = (int)pNode->data;
			strcpy(pHuffmanCodeTable[index].bitString, pNode->bitString);
		}
		//이후에 오른쪽 자식 트리를 순회.
		if (pNode->pRightChild != NULL) {
			//오른쪽 자식 '1'추가
			sprintf(pNode->pRightChild->bitString, "%s1", pNode->bitString);
			inorderTraversalAndupdateBitstring(pNode->pRightChild, pHuffmanCodeTable);
		}
	}
}

//각 문자를 계산한 결과를 허프만 코드 테이블에 다시 저장하는 역할.
//비트 문자열은 이진 트리인 허프만 트리를 순회해야되고 중위 순회를 이용했습니다.
void applyBitstring(HuffmanTree *pHuffmanTree, HuffmanCode *pHuffmanCodeTable) {
	if (pHuffmanTree != NULL) {
		pHuffmanTree->pRootNode->bitString[0] = 0;
		inorderTraversalAndupdateBitstring(pHuffmanTree->pRootNode, pHuffmanCodeTable);
	}
}

//입력 문자열을 전달 받아 각 문자의 빈도수를 계산하는 함수
//pSourceCode는 HuffmanCode 타입의 1차원 배열입니다.
//문자 번호0부터 최대 문자 번호(codeCount-1)번까지 모두 codeCount개의 문자에 대한 자료를 저장.
void checkFrequency(char *pSourceString, HuffmanCode *pSourceCode, int codeCount) {
	long count = 0, i = 0;

	if (pSourceString == NULL || pSourceCode == NULL) {
		return;
	}

	memset(pSourceCode, 0, sizeof(HuffmanCode)*codeCount);
	for (i = 0;i < codeCount;i++) {
		pSourceCode[i].data = (char)i; //테이블 data에 문자를 순서대로 대입. 나머진 0.
	}

	count = strlen(pSourceString);
	for (i = 0;i < count;i++) {
		int asc = pSourceString[i]; //테이블에서의 위치 인덱스.
		pSourceCode[asc].frequency++; //asc위치에 저장된 빈도수를 1증가.
	}
}

//문자별 빈도수 정보를 이용한 실제 허프만 트리를 만드는 함수
HuffmanTree *buildHuffmanTree(HuffmanCode *pCodes) {
	HuffmanTree *pHuffmanTree = NULL;
	ArrayMinHeap* pHeap = NULL;
	HeapNode *pLastHeapNode = NULL;
	int i = 0, unique_char_num = 0;

	pHeap = createArrayHeap(COUNT_ASC); //최소 히프를 생성
	if (pHeap == NULL) {
		return pHuffmanTree;
	}

	//허프만 코드 테이블에 저장된 문자들을 히프에 추가.
	for (i = 0;i < COUNT_ASC;i++) {
		if (pCodes[i].frequency > 0) {
			HeapNode heapNode = { 0 };
			heapNode.frequency = pCodes[i].frequency;
			heapNode.pData = makeNewHuffmanTreeNode(pCodes[i].data);

			insertMinHeapAH(pHeap, heapNode);
		}
	}

	unique_char_num = pHeap->currentCount;
	//문자 2개마다 부모 노드 1개씩 만들어지기 때문에 저장된 문자 개수 -1만큼 루프.
	for (i = 0;i < unique_char_num - 1;i++) {
		//이후 루프를 돌면서 최소 빈도수 노드를 2개씩 꺼내어
		HeapNode *pLeft = deleteMinHeapAH(pHeap);
		HeapNode *pRight = deleteMinHeapAH(pHeap);
		if (pRight != NULL && pLeft != NULL) {
			//부모 노드를 만들고
			HeapNode heapNode = { 0 };
			HuffmanTreeNode *pHuffmanNode = NULL;

			pHuffmanNode = makeNewHuffmanTreeNode('?');
			pHuffmanNode->pLeftChild = pLeft->pData;
			pHuffmanNode->pRightChild = pRight->pData;

			heapNode.frequency = pRight->frequency + pLeft->frequency;
			heapNode.pData = pHuffmanNode;
			//다시 히프에 추가.
			insertMinHeapAH(pHeap, heapNode);

			free(pRight);
			free(pLeft);
		}
	}
	//루프를 돌고 나면 최종적으로 오직 1개의 부모 노드가 히프에 저장.
	pLastHeapNode = deleteMinHeapAH(pHeap); 
	if (pLastHeapNode != NULL) {
		//이 노드로 루트 노드를 가지는 트리로 만들면
		pHuffmanTree = makeHuffmanTree(pLastHeapNode->pData);
	}

	deleteArrayHeap(pHeap);

	//생성된 허프만 트리를 반환.
	return pHuffmanTree; 
}

//원본 문자열을 입력 파라미터로 전달 받아 허프만 코딩된 압축 문자열을 반환.
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
			int index = (int)pSourceString[i]; //문자의 코드 값을 가져와서
			//그 문자에 해당하는 비트 문자열을 결과 문자열에 덧붙입니다.
			strcat(pReturn, pHuffmanCodeTable[index].bitString); 
		}
	}
	return pReturn;
}

//허프만 코드로 인코딩된 문자열을 원래의 문자열로 변환하는 함수
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