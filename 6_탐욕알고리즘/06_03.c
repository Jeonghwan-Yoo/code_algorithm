#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"

int main() {
	HuffmanTree* pHuffmanTree = NULL;
	HuffmanCode *pHuffmanCodeTable = NULL;

	char sourceString[] = "ABCDABCABA";
	char *pEncodedString = NULL;
	char *pDecodedString = NULL;
	
	pHuffmanCodeTable = (HuffmanCode*)malloc(sizeof(HuffmanCode)*COUNT_ASC);
	checkFrequency(sourceString, pHuffmanCodeTable, COUNT_ASC);

	pHuffmanTree = buildHuffmanTree(pHuffmanCodeTable); //������ Ʈ���� ����
	applyBitstring(pHuffmanTree, pHuffmanCodeTable); //������ ���̺� ���� �ִ� ��Ʈ ���ڿ� ������Ʈ
	printHuffmanTree(pHuffmanTree);

	pEncodedString = getEncodedString(sourceString, pHuffmanCodeTable);
	pDecodedString = getDecodedString(pEncodedString, pHuffmanTree);

	printf("���� ���ڿ�:%s\n", sourceString);
	printf("������ ���ڵ� ���ڿ�:%s\n", pEncodedString);
	printf("������ ���ڵ� ���ڿ�:%s\n", pDecodedString);

	if (pDecodedString != NULL) {
		free(pDecodedString);
	}
	if (pEncodedString != NULL) {
		free(pEncodedString);
	}
	deleteHuffmanTree(pHuffmanTree);
	if (pHuffmanCodeTable != NULL) {
		free(pHuffmanCodeTable);
	}
	return 0;
}