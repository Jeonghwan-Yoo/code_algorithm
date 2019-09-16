#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashsearch_chain.h"

//해시 테이블 생성
HashTable* createHashTable(int bucketSize) {
	HashTable* pReturn = NULL;
	int i = 0;

	if (bucketSize <= 0) {
		printf("버킷 크기는 0보다 커야합니다\n");
		return NULL;
	}

	pReturn = (HashTable*)malloc(sizeof(HashTable));
	if (pReturn != NULL) {
		pReturn->bucketSize = bucketSize;
		pReturn->ppBucket = NULL;
	}
	else {
		printf("오류, 첫번째 메모리할당, createHashTable()\n");
		return NULL;
	}

	pReturn->ppBucket = (LinkedList**)malloc(sizeof(LinkedList*)*bucketSize);
	if (pReturn->ppBucket != NULL) {
		memset(pReturn->ppBucket, 0, sizeof(LinkedList*)*bucketSize);

		for (i = 0;i < bucketSize;i++) {
			pReturn->ppBucket[i] = createLinkedList();
		}
	}
	else {
		printf("오류, 두번째 malloc(), createHashTable()\n");
		return NULL;
	}
	return pReturn;
}

//해시 테이블에 새로운 자료를 추가하는 함수
int addData(HashTable* pHashTable, HashSlot slot) {
	int ret = 0;
	LinkedList* pBucket = NULL;

	if (pHashTable != NULL) {
		pBucket = searchBucket(pHashTable, slot.key); //저장할 버킷을 찾는다.
		if (pBucket != NULL) {
			addLinkedListDataLast(pBucket, slot); //제일 마지막에 자료를 추가.
			pHashTable->currentCount++;
		}
		else {
			printf("오류, 잘못된 해시 테이블 주소가 계산되었습니다\n");
		}
	}
	return ret;
}

//해시 테이블에서 해당 버킷을 찾는 함수
//해당 버킷의 연결 리스트 주소를 반환값 pReturn.
LinkedList* searchBucket(HashTable* pHashTable, char* key) {
	LinkedList* pReturn = NULL;
	int bucketIndex = 0;

	if (pHashTable != NULL) {
		bucketIndex = hashFunction(key, pHashTable->bucketSize);
		if (bucketIndex >= 0) {
			pReturn = pHashTable->ppBucket[bucketIndex];
		}
		else {
			printf("오류, 잘못된 해시 테이블 주소가 계산되었습니다,\n");
		}
	}
	return pReturn;
}

int hashFunction(char* pKey, int bucketSize) {
	int ret = -1;
	unsigned int temp_key = 0;

	if (pKey == NULL) {
		return ret;
	}

	temp_key = stringToInt(pKey);
	if (bucketSize > 0) {
		ret = temp_key % bucketSize;
	}
	return ret;
}

//문자열을 숫자로 변환
unsigned int stringToInt(char* pKey) {
	unsigned int ret = 0;
	while (*pKey != '\0') {
		ret = (ret * 31) + (*pKey);
		pKey++;
	}
	return ret;
}

//리스트 제일 마지막에 추가.
int addLinkedListDataLast(LinkedList* pBucket, HashSlot data) {
	int ret = 0;
	if (pBucket != NULL) {
		int position = pBucket->currentCount;
		ret = addLinkedListData(pBucket, position, data);
	}
	return ret;
}

//검색 키로 해시 테이블에서 자료를 검색하는 함수
//내부적으로 검색 키를 이용하여 먼저 버킷을 검색하고 검색된 버킷을 대상으로 슬롯을 검색합니다.
//검색해서 발견된 슬롯에 대한 포인터(HashSlot*)을 반환합니다.
HashSlot* search(HashTable* pHashTable, char* key) {
	HashSlot* pReturn = NULL;
	LinkedList* pList = NULL;
	int position = 0;

	pList = searchBucket(pHashTable, key);
	if (pList != NULL) {
		//연결 리스트의 포인터 pList와 검색 키 key를 입력 파라미터로 전달하면
		//검색한 자료(슬롯)에 대한 포인터(HashSlot*)를 반환합니다.
		//추가로 position의 주소를 전달합니다.
		//출력 파라미터는 연결 리스트에서 발견된 자료의 위치 값을 저장하는 것이 목적.
		pReturn = searchSlot(pList, key, &position);
	}
	return pReturn;
}

//특정 연결리스트(버킷)에서 검색을 수행.
HashSlot* searchSlot(LinkedList* pList, char* key, int* pPosition) {
	HashSlot* pReturn = NULL;
	LinkedListNode* pSlot = NULL;
	int index = 0;

	if (pList != NULL && pPosition != NULL) {
		pSlot = pList->headerNode.pLink;

		//첫 번째 노드부터 시작하여 마지막 노드에 도달하기까지 루프를 돌면서 검색 자료대상 자료를 점검.
		while (pSlot != NULL) {
			//자료를 발견하면 해당 자료를 반환.
			if (strcmp(pSlot->data.key, key) == 0) {
				pReturn = &(pSlot->data);
				*pPosition = index; //*pPosition에 연결 리스트에서 발견된 검색 자료의 위치값을 대입.
				break;
			}
			pSlot = pSlot->pLink;
			index++;
		}
		if (pReturn == NULL) {
			printf("검색 실패, 검색키-[%s]는 존재하지 않습니다\n", key);
		}
	}
	return pReturn;
}

//검색 키로 해시 테이블에 해당 자료를 제거하는 함수
int removeData(HashTable* pHashTable, char* key) {
	int ret = 0;
	HashSlot *pSlot = NULL;
	LinkedList* pList = NULL;
	int position = 0;

	//내부적으로 검색 키를 이용하여 먼저 버킷을 검색.
	pList = searchBucket(pHashTable, key);
	if (pList != NULL) {
		//검색된 버킷을 대상으로 슬롯을 검색.
		pSlot = searchSlot(pList, key, &position);
		if (pSlot != NULL) {
			//연결 리스트(버킷)에서 해당 자료를 제거합니다.
			//단, 이때 연결 리스트에서 자료를 제거하는 것이기 때문에 위치 정보 position이 필요.
			removeLinkedListData(pList, position);
			pHashTable->currentCount--;
			ret = 1;
		}
	}
	return ret;
}

//해시 테이블 삭제
void deleteHashTable(HashTable* pHashTable) {
	int i = 0;
	if (pHashTable != NULL) {
		if (pHashTable->ppBucket != NULL) {
			for (i = 0;i < pHashTable->bucketSize;i++) {
				deleteLinkedList(pHashTable->ppBucket[i]);
			}
			free(pHashTable->ppBucket);
		}
		free(pHashTable);
	}
}

///해시 테이블의 현재 자료 개수
int getCount(HashTable* pHashTable) {
	int ret = 0;

	if (pHashTable != NULL) {
		ret = pHashTable->currentCount;
	}
	return ret;
}

//해시 테이블 내용 출력
void displayHashTable(HashTable* pHashTable) {
	int i = 0, j = 0;
	int slotSize = 0;
	LinkedList* pList = NULL;
	LinkedListNode* pNode = NULL;

	if (pHashTable != NULL) {
		for (i = 0;i < pHashTable->bucketSize;i++) {
			printf("[%d]", i);

			pList = pHashTable->ppBucket[i];
			slotSize = getLinkedListLength(pList);
			if (slotSize == 0) {
				printf(", Empty\n");
			}
			else {
				pNode = pList->headerNode.pLink;
				for (j = 0;j < slotSize;j++) {
					printf(", (%s, %d) ", pNode->data.key, pNode->data.value);
					pNode = pNode->pLink;
				}
				printf("\n");
			}
		}
	}
}