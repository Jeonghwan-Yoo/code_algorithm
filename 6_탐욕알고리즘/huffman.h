/*
06_03.c:���� ���α׷�
huffman.h:������ �ڵ� ���� ����ü�� �Լ� ����
huffman.c:������ �ڵ� ���� �Լ� ����
arrayheap.h:���� ������ ������ �Լ� ����
arrayheap.c:���� ������ ������ �Լ� ����

���ڿ� pString->checkFrequency()->������ �ڵ� ���̺� pSourceCode->buildHuffmanTree()->������ Ʈ��
������ Ʈ��+���̺�->applyBitstring()->������ Ʈ��+���̺�
pString+HuffmanCodeTable->getEncodedString()->���ڵ� ���ڿ�,+pHuffmanTree->getDecodedString()
->���ڵ� ���ڿ�
*/

#ifndef huffman_h
#define huffman_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arrayheap.h"

#define MAX_BIT_SIZE 8
#define COUNT_ASC 128

typedef struct HuffmanTreeNodeType {
	char data; //����
	char bitString[MAX_BIT_SIZE + 1]; //���ڵ� ���

	struct HuffmanTreeNodeType* pLeftChild;
	struct HuffmanTreeNodeType* pRightChild;
}HuffmanTreeNode;

typedef struct HuffmanTreeType {
	struct HuffmanTreeNodeType* pRootNode;
}HuffmanTree;

//������ �ڵ� ���̺��� 1���� ��(row)������ �մϴ�.
//������ �ڵ� ���̺��� '������ �ڵ�' ������ 1���� �迭�� ����Ǿ� ������ Ʈ���� ����� �Է� ������ ���.
//�� ���ں��� ���ڵ��� ��� ���� ����Ǿ��ֱ� ������ ���� ���ڿ��� ������ ���ڵ��� ���� ���.
typedef struct HuffmanCodeType {
	char data; //� ��������
	int frequency; //������ �󵵼�
	char bitString[MAX_BIT_SIZE + 1]; //���ڵ� ���
}HuffmanCode;

//�󵵼� ������ ����� �Լ�.
//������ ���� ���ڵ��� ���� ��Ʈ ���ڿ� bitString�� ����ֽ��ϴ�.
void checkFrequency(char *pSourceString, HuffmanCode *pSourceCode, int codeCount);
//������ Ʈ�� ��ü�� ����� �Լ�. Ʈ���� ���� ���� ���ڵ��� �󵵼� ���� pCodes�� �ʿ��ϴ�.
//ȣ�� ����� ������ ������ Ʈ���� ��ȯ�˴ϴ�.
HuffmanTree *buildHuffmanTree(HuffmanCode *pCodes);
//������ �ڵ� ����� ������ ���̺� �����ϴ� �Լ�. ��������� ������ Ʈ���� ���̺��� ���޹޽��ϴ�.
//������ Ʈ���� �̿��Ͽ� ������ �ڵ� ���̺��� ���ڵ� ����� �����մϴ�.
void applyBitstring(HuffmanTree *pHuffmanTree, HuffmanCode *pHuffmanCodeTable);
void printHuffmanTree(HuffmanTree *pBinTree);
void deleteHuffmanTree();

//���� ���� ������ ���̺��� ���.
//���� ���ڿ��� �Է� �Ķ���ͷ� ���� �޾� ������ �ڵ��� ���� ���ڿ��� ��ȯ
char* getEncodedString(char *pSourceString, HuffmanCode* pHuffmanCodeTable);
//������ �ڵ��� ���ڿ��� ������ ���ڿ��� ���� �����ϴ� �Լ�.
char* getDecodedString(char *pBitString, HuffmanTree *pHuffmanTree);

#endif