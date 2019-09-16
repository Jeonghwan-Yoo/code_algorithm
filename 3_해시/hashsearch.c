#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashsearch.h"

//해시 테이블 생성
HashTable* createHashTable(int bucketSize) {
	HashTable *pReturn = NULL;

	if (bucketSize <= 0) {
		printf("버킷 크기는 0보다 커야합니다\n");
		return NULL;
	}

	//해시 테이블에 대한 메모리 할당 및 검사
	pReturn = (HashTable*)malloc(sizeof(HashTable));
	if (pReturn != NULL) {
		//메모리 초기화
		pReturn->currentCount = 0;
		pReturn->bucketSize = bucketSize;
		pReturn->pBucket = NULL;
	}
	else {
		printf("오류, 첫번째 메모리할당, createHashTable()\n");
		return NULL;
	}

	//버킷에 대한 메모리 할당 및 검사
	pReturn->pBucket = (HashBucket*)malloc(sizeof(HashBucket)*bucketSize);
	
	if (pReturn->pBucket != NULL) {
		//EMTPY값이 0이기 때문에 모든 버킷이 EMPTY.
		memset(pReturn->pBucket, 0, sizeof(HashBucket)*bucketSize); //메모리 초기화.
	}
	else {
		if (pReturn != NULL) {
			free(pReturn);
		}
		printf("오류, 두번째 메모리할당, createHashTable()\n");
		return NULL;
	}
	return pReturn;
}
//버킷의 상태
//1. 비어있거나 제한된 경우:추가할 자료를 단순히 저장.
//2. 사용하고 있는 상태이고 검색 키와 같은 키를 가지는 자료:중복된 자료이므로 오류 처리 or 내용 추가.
//3. 사용하고 있는 상태이고 검색 키와 다른 키를 가지는 자료:새로운 주소에 추가할 자료를 저장.

//자료 추가에 성공하면 1을 반환하며 실패하면 0을 반환합니다.
//충돌이 발생했을 때 '선형 조사법'
int addData(HashTable* pHashTable, HashBucket bucket) {
	int ret = 0; //반환 값.
	HashBucket *pBucket = NULL;
	int bucketIndex = 0;
	int tempIndex = 0;
	int inc = 1; //충돌이 발생했을 때 키 값의 증가를 위해 사용(선형 조사법)

	if (pHashTable == NULL) {
		printf("오류 , NULL-해시 테이블입니다\n");
		ret = 0;
		return ret;
	}

	//저장하려는 자료의 해시 테이블에서 주소 계산 및 검증.
	bucketIndex = hashFunction(bucket.key, pHashTable->bucketSize);
	if (bucketIndex < 0 || bucketIndex >= pHashTable->bucketSize) {
		printf("오류, 잘못된 해시 테이블 주소가 계산되었습니다, addSHT()\n");
		ret = 0;
		return ret;
	}

	//해시 테이블에서의 주소 저장
	tempIndex = bucketIndex;

	do {
		pBucket = &(pHashTable->pBucket[tempIndex]);

		//1)빈 주소 혹은 제거된 주소인지 점검
		if (isEmptyOrDeletedBucket(pBucket) == 1) {
			//만약 빈 버킷이라면 해당 주소에 자료를 저장하고 종료한다.
			pHashTable->pBucket[tempIndex] = bucket;
			pHashTable->pBucket[tempIndex].status = USED;
			pHashTable->currentCount++;
			ret = 1;
			break;
		}
		//2)빈 버킷을 찾지 못한 경우
		else {
			//2-1)동일한 key가 이미 존재하는 경우
			if (strcmp(pBucket->key, bucket.key) == 0) {
				printf("오류, 중복된 키=[%s], addSHT()\n", bucket.key);
				ret = 0;
				break;
			}
			//2-2)동일하지 않은 key인 경우 다음 버킷으로 이동
			else {
				//기존 주소 tempIndex에 상수 inc값을 더한다.
				tempIndex = (tempIndex + inc) % pHashTable->bucketSize;

				//해시 테이블의 모든 버킷이 찬 경우
				//새로 구한 버킷 주소(TempIndex)가 해시 함수로 처음 계산된 주소와 같다면
				//해시 테이블의 남은 버킷이 없는 경우이다.
				if (tempIndex == bucketIndex) {
					printf("오류, 해시 테이블이 가득찼습니다\n");
					ret = 0;
					break;
				}
			}
		}
	} while (tempIndex != bucketIndex); //충돌이 여러번 발생한 경우 대비.

	return ret;
}

//나머지 연산으로 해시 함수를 구현한 해시 함수.
int hashFunction(char* pKey, int bucketSize) {
	int ret = -1;
	unsigned int temp_key = 0;

	if (pKey == NULL) {
		return ret;
	}

	//입력 값으로 전달된 문자열 키 값을 정수로 변환.
	temp_key = stringToInt(pKey);
	if (bucketSize > 0) {
		//나머지 연산으로 주소 계산
		ret = temp_key % bucketSize;
	}

	return ret;
}

//호너의 방법
unsigned int stringToInt(char *pKey) {
	unsigned int ret = 0;
	while (*pKey != '\0') {
		ret = (ret * 31) + (*pKey);
		pKey++;
	}
	return ret;
}

//비어있거나 제거된 상태:1
//그렇지 않으면:0
int isEmptyOrDeletedBucket(HashBucket* pBucket) {
	int ret = 0;

	if (pBucket != NULL) {
		//현재 해당 버킷이 제거된 상태인지 점검. 새로운 자료 저장 가능.
		if (pBucket->status == EMPTY || pBucket->status == DELETED) {
			ret = 1;
		}
	}
	return ret;
}

HashBucket* search(HashTable* pHashTable, char* key) {
	HashBucket* pReturn = NULL;
	HashBucket* pBucket = NULL;
	int bucketIndex = 0;
	int tempIndex = 0;

	if (pHashTable == NULL) {
		printf("오류, NULL-해시 테이블입니다\n");
		pReturn = NULL;
		return pReturn;
	}

	//저장하려는 자료의 해시 테이블에서 주소 계산 및 검증
	bucketIndex = hashFunction(key, pHashTable->bucketSize);
	if (bucketIndex < 0) {
		printf("오류, 잘못된 해시 테이블 주소가 계산되었습니다\n");
		pReturn = NULL;
		return pReturn;
	}

	//해시 테이블에서 주소 저장
	tempIndex = bucketIndex;

	do {
		//빈 버킷인지 점검
		pBucket = &(pHashTable->pBucket[tempIndex]);

		//1)빈 버킷을 찾은 경우 검색 실패
		if (isEmptyBucket(pBucket) == 1) {
			printf("검색 실패, 검색키-[%s]는 존재하지 않습니다\n", key);
			pReturn = NULL;
			break;
		}
		else {
			//2-1)동일한 key를 찾은 경우 검색 성공
			if (pBucket->status == USED && strcmp(pBucket->key, key) == 0) {
				pReturn = pBucket;
				break;
			}
			else {
				//2-2)동일하지 않는 key인 경우 다음 주소로 이동
				//충돌 때문에 다른 위치에 저장된 자료가 없는지 검사.
			
				tempIndex = (tempIndex + 1) % pHashTable->bucketSize;

				//해시 테이블의 모든 버킷을 검사한 경우
				if (tempIndex == bucketIndex) {
					printf("검색 실패, 검색키-[%s]는 존재하지 않습니다\n", key);
					pReturn = NULL;
					break;
				}
			}
		}
	} while (tempIndex != bucketIndex);

	return pReturn;
}

//버킷의 상태가 DELETED일 때는 '다음 주소'의 버킷을 계산하여 검색 키에 해당하는
//자료가 없는지 점검해야 합니다.(개방 주소법)
//버킷이 비어있는지 그 상태를 점검하는 함수
//제거되었다고 해도 다음 버킷을 검사해야한다.
int isEmptyBucket(HashBucket* pBucket) {
	int ret = 0;
	if (pBucket != NULL) {
		if (pBucket->status == EMPTY) {
			ret = 1;
		}
	}
	return ret;
}

//제거 성공:1
//제거 실패:0
int removeData(HashTable* pHashTable, char* key) {
	int ret = 0;
	HashBucket* pBucket = NULL;

	if (pHashTable != NULL) {
		pBucket = search(pHashTable, key); //검색 키로 검색
		//검색 성공인 경우, 해당 버킷의 상태를 'DELETED'로 변경하고 버켓에 저장된 내용을 초기화.
		if (pBucket != NULL) {
			pBucket->status = DELETED;
			pBucket->key[0] = '\0';
			pBucket->value = 0;
			pHashTable->currentCount--;
			ret = 1;
		}
		else {
			printf("제거 실패, 검색키-[%s]는 존재하지 않습니다\n", key);
		}
	}
	return ret;
}

//해시 테이블 삭제
void deleteHashTable(HashTable* pHashTable) {
	if (pHashTable != NULL) {
		free(pHashTable->pBucket);
	}
	free(pHashTable);
}

//해시 테이블의 현재 자료 개수
int getCount(HashTable* pHashTable) {
	int ret = 0;

	if (pHashTable != NULL) {
		ret = pHashTable->currentCount;
	}
	return ret;
}

//해시 테이블 내용 출력
void displayHashTable(HashTable* pHashTable) {
	int i = 0;
	int bucketIndex = 0;

	HashBucket* pBucket = NULL;
	if (pHashTable != NULL) {
		printf("-----------------------------\n");

		for (i = 0;i < pHashTable->bucketSize;i++) {
			printf("[%d],", i);

			pBucket = &(pHashTable->pBucket[i]);
			if (pBucket->key[0] != '\0') {
				bucketIndex = hashFunction(pBucket->key, pHashTable->bucketSize);

				printf("%s, (%d->%d), [%d]\n", pBucket->key, bucketIndex, i, pBucket->value);
			}
			else {
				printf("비었습니다\n");
			}
		}
		printf("-----------------------------\n");
	}
	else {
		printf("NULL-해시 테이블입니다\n");
	}
}