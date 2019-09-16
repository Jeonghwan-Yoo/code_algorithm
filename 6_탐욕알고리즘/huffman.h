/*
06_03.c:예제 프로그램
huffman.h:허프만 코딩 관련 구조체와 함수 선언
huffman.c:허프만 코딩 관련 함수 구현
arrayheap.h:히프 정렬을 구현한 함수 선언
arrayheap.c:히프 정렬을 구현한 함수 구현

문자열 pString->checkFrequency()->허프만 코드 테이블 pSourceCode->buildHuffmanTree()->허프만 트리
허프만 트리+테이블->applyBitstring()->허프만 트리+테이블
pString+HuffmanCodeTable->getEncodedString()->인코딩 문자열,+pHuffmanTree->getDecodedString()
->디코딩 문자열
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
	char data; //문자
	char bitString[MAX_BIT_SIZE + 1]; //인코딩 결과

	struct HuffmanTreeNodeType* pLeftChild;
	struct HuffmanTreeNodeType* pRightChild;
}HuffmanTreeNode;

typedef struct HuffmanTreeType {
	struct HuffmanTreeNodeType* pRootNode;
}HuffmanTree;

//허프만 코드 테이블에서 1개의 행(row)역할을 합니다.
//허프만 코드 테이블은 '허프만 코드' 정보가 1차원 배열로 저장되어 허프만 트리를 만드는 입력 값으로 사용.
//각 문자별로 인코딩된 결과 또한 저장되어있기 때문에 원본 문자열을 실제로 인코딩할 때도 사용.
typedef struct HuffmanCodeType {
	char data; //어떤 문자인지
	int frequency; //문자의 빈도수
	char bitString[MAX_BIT_SIZE + 1]; //인코딩 결과
}HuffmanCode;

//빈도수 정보를 만드는 함수.
//하지만 아직 인코딩된 이진 비트 문자열 bitString은 비어있습니다.
void checkFrequency(char *pSourceString, HuffmanCode *pSourceCode, int codeCount);
//허프만 트리 자체를 만드는 함수. 트리를 만들 때는 문자들의 빈도수 정보 pCodes가 필요하다.
//호출 결과로 생성된 허프만 트리가 반환됩니다.
HuffmanTree *buildHuffmanTree(HuffmanCode *pCodes);
//허프만 코딩 결과를 허프만 테이블에 저장하는 함수. 입출력으로 허프만 트리와 테이블을 전달받습니다.
//허프만 트리를 이용하여 허프만 코드 테이블의 인코딩 결과를 저장합니다.
void applyBitstring(HuffmanTree *pHuffmanTree, HuffmanCode *pHuffmanCodeTable);
void printHuffmanTree(HuffmanTree *pBinTree);
void deleteHuffmanTree();

//위에 구한 허프만 테이블을 사용.
//원본 문자열을 입력 파라미터로 전달 받아 허프만 코딩된 압축 문자열을 반환
char* getEncodedString(char *pSourceString, HuffmanCode* pHuffmanCodeTable);
//허프만 코딩된 문자열을 원래의 문자열로 압축 해제하는 함수.
char* getDecodedString(char *pBitString, HuffmanTree *pHuffmanTree);

#endif