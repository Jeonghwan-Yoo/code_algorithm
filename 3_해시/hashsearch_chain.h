/*
체이닝 기법으로 구현된 해시 테이블에서는 각 버킷이 연결 리스트로 구현.
만약 버킷에 새로운 자료를 추가하는 것은 버킷에 새로운 슬롯이 추가되는 것과 같다.
새로운 슬롯이 추가되는 것은 연결 리스트에 새로운 노드를 추가하는 것과 같다.
처음에는 해더 NULL, currentCount는 0.
*/

#ifndef _HASH_CHAIN
#define _HASH_CHAIN

#include "hashingdef.h"
#include "linkedlist.h"

typedef struct HashTableType {
	int bucketSize; //자료를 저장할 수 있는 버킷의 수, 해시 테이블의 크기
	int currentCount; //현재 저장된 자료의 개수를 저장
	struct LinkedListType **ppBucket; //연결 리스트들의 1차원 배열. 연결리스트 1개는 버킷 1개.
	//이중 포인터 변수는 배열의 각 원소는 연결 리스트에 대한 포인터가 됩니다.
}HashTable;

//해시 테이블 생성
HashTable* createHashTable(int bucketSize);

//자료 추가
int addData(HashTable* pHashTable, HashSlot slot);

//자료 제거
int removeData(HashTable* pHashTable, char* key);

//자료 검색
HashSlot* search(HashTable* pHashTable, char* key);

//해시 테이블 내용 표시
void displayHashTable(HashTable *pHashTable);

//해시 테이블의 현재 자료 개수
int getCount(HashTable *pHashTable);

//해시 테이블 삭제
void deleteHashTable(HashTable *pHashTable);

//그 외 내부적으로 사용되는 함수들
LinkedList* searchBucket(HashTable* pHashTable, char* key);
int addLinkedListDataLast(LinkedList* pBucket, HashSlot data);
int hashFunction(char *pKey, int bucketSize);
unsigned int stringToInt(char *pKey);
HashSlot* searchSlot(LinkedList* pList, char* key, int* pPosition);

#endif