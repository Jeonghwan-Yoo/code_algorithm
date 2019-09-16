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

	pHuffmanTree = buildHuffmanTree(pHuffmanCodeTable); //허프만 트리를 생성
	applyBitstring(pHuffmanTree, pHuffmanCodeTable); //허프만 테이블 내에 있는 비트 문자열 업데이트
	printHuffmanTree(pHuffmanTree);

	pEncodedString = getEncodedString(sourceString, pHuffmanCodeTable);
	pDecodedString = getDecodedString(pEncodedString, pHuffmanTree);

	printf("원본 문자열:%s\n", sourceString);
	printf("허프만 인코딩 문자열:%s\n", pEncodedString);
	printf("허프만 디코딩 문자열:%s\n", pDecodedString);

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