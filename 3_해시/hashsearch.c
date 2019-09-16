#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashsearch.h"

//�ؽ� ���̺� ����
HashTable* createHashTable(int bucketSize) {
	HashTable *pReturn = NULL;

	if (bucketSize <= 0) {
		printf("��Ŷ ũ��� 0���� Ŀ���մϴ�\n");
		return NULL;
	}

	//�ؽ� ���̺� ���� �޸� �Ҵ� �� �˻�
	pReturn = (HashTable*)malloc(sizeof(HashTable));
	if (pReturn != NULL) {
		//�޸� �ʱ�ȭ
		pReturn->currentCount = 0;
		pReturn->bucketSize = bucketSize;
		pReturn->pBucket = NULL;
	}
	else {
		printf("����, ù��° �޸��Ҵ�, createHashTable()\n");
		return NULL;
	}

	//��Ŷ�� ���� �޸� �Ҵ� �� �˻�
	pReturn->pBucket = (HashBucket*)malloc(sizeof(HashBucket)*bucketSize);
	
	if (pReturn->pBucket != NULL) {
		//EMTPY���� 0�̱� ������ ��� ��Ŷ�� EMPTY.
		memset(pReturn->pBucket, 0, sizeof(HashBucket)*bucketSize); //�޸� �ʱ�ȭ.
	}
	else {
		if (pReturn != NULL) {
			free(pReturn);
		}
		printf("����, �ι�° �޸��Ҵ�, createHashTable()\n");
		return NULL;
	}
	return pReturn;
}
//��Ŷ�� ����
//1. ����ְų� ���ѵ� ���:�߰��� �ڷḦ �ܼ��� ����.
//2. ����ϰ� �ִ� �����̰� �˻� Ű�� ���� Ű�� ������ �ڷ�:�ߺ��� �ڷ��̹Ƿ� ���� ó�� or ���� �߰�.
//3. ����ϰ� �ִ� �����̰� �˻� Ű�� �ٸ� Ű�� ������ �ڷ�:���ο� �ּҿ� �߰��� �ڷḦ ����.

//�ڷ� �߰��� �����ϸ� 1�� ��ȯ�ϸ� �����ϸ� 0�� ��ȯ�մϴ�.
//�浹�� �߻����� �� '���� �����'
int addData(HashTable* pHashTable, HashBucket bucket) {
	int ret = 0; //��ȯ ��.
	HashBucket *pBucket = NULL;
	int bucketIndex = 0;
	int tempIndex = 0;
	int inc = 1; //�浹�� �߻����� �� Ű ���� ������ ���� ���(���� �����)

	if (pHashTable == NULL) {
		printf("���� , NULL-�ؽ� ���̺��Դϴ�\n");
		ret = 0;
		return ret;
	}

	//�����Ϸ��� �ڷ��� �ؽ� ���̺��� �ּ� ��� �� ����.
	bucketIndex = hashFunction(bucket.key, pHashTable->bucketSize);
	if (bucketIndex < 0 || bucketIndex >= pHashTable->bucketSize) {
		printf("����, �߸��� �ؽ� ���̺� �ּҰ� ���Ǿ����ϴ�, addSHT()\n");
		ret = 0;
		return ret;
	}

	//�ؽ� ���̺����� �ּ� ����
	tempIndex = bucketIndex;

	do {
		pBucket = &(pHashTable->pBucket[tempIndex]);

		//1)�� �ּ� Ȥ�� ���ŵ� �ּ����� ����
		if (isEmptyOrDeletedBucket(pBucket) == 1) {
			//���� �� ��Ŷ�̶�� �ش� �ּҿ� �ڷḦ �����ϰ� �����Ѵ�.
			pHashTable->pBucket[tempIndex] = bucket;
			pHashTable->pBucket[tempIndex].status = USED;
			pHashTable->currentCount++;
			ret = 1;
			break;
		}
		//2)�� ��Ŷ�� ã�� ���� ���
		else {
			//2-1)������ key�� �̹� �����ϴ� ���
			if (strcmp(pBucket->key, bucket.key) == 0) {
				printf("����, �ߺ��� Ű=[%s], addSHT()\n", bucket.key);
				ret = 0;
				break;
			}
			//2-2)�������� ���� key�� ��� ���� ��Ŷ���� �̵�
			else {
				//���� �ּ� tempIndex�� ��� inc���� ���Ѵ�.
				tempIndex = (tempIndex + inc) % pHashTable->bucketSize;

				//�ؽ� ���̺��� ��� ��Ŷ�� �� ���
				//���� ���� ��Ŷ �ּ�(TempIndex)�� �ؽ� �Լ��� ó�� ���� �ּҿ� ���ٸ�
				//�ؽ� ���̺��� ���� ��Ŷ�� ���� ����̴�.
				if (tempIndex == bucketIndex) {
					printf("����, �ؽ� ���̺��� ����á���ϴ�\n");
					ret = 0;
					break;
				}
			}
		}
	} while (tempIndex != bucketIndex); //�浹�� ������ �߻��� ��� ���.

	return ret;
}

//������ �������� �ؽ� �Լ��� ������ �ؽ� �Լ�.
int hashFunction(char* pKey, int bucketSize) {
	int ret = -1;
	unsigned int temp_key = 0;

	if (pKey == NULL) {
		return ret;
	}

	//�Է� ������ ���޵� ���ڿ� Ű ���� ������ ��ȯ.
	temp_key = stringToInt(pKey);
	if (bucketSize > 0) {
		//������ �������� �ּ� ���
		ret = temp_key % bucketSize;
	}

	return ret;
}

//ȣ���� ���
unsigned int stringToInt(char *pKey) {
	unsigned int ret = 0;
	while (*pKey != '\0') {
		ret = (ret * 31) + (*pKey);
		pKey++;
	}
	return ret;
}

//����ְų� ���ŵ� ����:1
//�׷��� ������:0
int isEmptyOrDeletedBucket(HashBucket* pBucket) {
	int ret = 0;

	if (pBucket != NULL) {
		//���� �ش� ��Ŷ�� ���ŵ� �������� ����. ���ο� �ڷ� ���� ����.
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
		printf("����, NULL-�ؽ� ���̺��Դϴ�\n");
		pReturn = NULL;
		return pReturn;
	}

	//�����Ϸ��� �ڷ��� �ؽ� ���̺��� �ּ� ��� �� ����
	bucketIndex = hashFunction(key, pHashTable->bucketSize);
	if (bucketIndex < 0) {
		printf("����, �߸��� �ؽ� ���̺� �ּҰ� ���Ǿ����ϴ�\n");
		pReturn = NULL;
		return pReturn;
	}

	//�ؽ� ���̺��� �ּ� ����
	tempIndex = bucketIndex;

	do {
		//�� ��Ŷ���� ����
		pBucket = &(pHashTable->pBucket[tempIndex]);

		//1)�� ��Ŷ�� ã�� ��� �˻� ����
		if (isEmptyBucket(pBucket) == 1) {
			printf("�˻� ����, �˻�Ű-[%s]�� �������� �ʽ��ϴ�\n", key);
			pReturn = NULL;
			break;
		}
		else {
			//2-1)������ key�� ã�� ��� �˻� ����
			if (pBucket->status == USED && strcmp(pBucket->key, key) == 0) {
				pReturn = pBucket;
				break;
			}
			else {
				//2-2)�������� �ʴ� key�� ��� ���� �ּҷ� �̵�
				//�浹 ������ �ٸ� ��ġ�� ����� �ڷᰡ ������ �˻�.
			
				tempIndex = (tempIndex + 1) % pHashTable->bucketSize;

				//�ؽ� ���̺��� ��� ��Ŷ�� �˻��� ���
				if (tempIndex == bucketIndex) {
					printf("�˻� ����, �˻�Ű-[%s]�� �������� �ʽ��ϴ�\n", key);
					pReturn = NULL;
					break;
				}
			}
		}
	} while (tempIndex != bucketIndex);

	return pReturn;
}

//��Ŷ�� ���°� DELETED�� ���� '���� �ּ�'�� ��Ŷ�� ����Ͽ� �˻� Ű�� �ش��ϴ�
//�ڷᰡ ������ �����ؾ� �մϴ�.(���� �ּҹ�)
//��Ŷ�� ����ִ��� �� ���¸� �����ϴ� �Լ�
//���ŵǾ��ٰ� �ص� ���� ��Ŷ�� �˻��ؾ��Ѵ�.
int isEmptyBucket(HashBucket* pBucket) {
	int ret = 0;
	if (pBucket != NULL) {
		if (pBucket->status == EMPTY) {
			ret = 1;
		}
	}
	return ret;
}

//���� ����:1
//���� ����:0
int removeData(HashTable* pHashTable, char* key) {
	int ret = 0;
	HashBucket* pBucket = NULL;

	if (pHashTable != NULL) {
		pBucket = search(pHashTable, key); //�˻� Ű�� �˻�
		//�˻� ������ ���, �ش� ��Ŷ�� ���¸� 'DELETED'�� �����ϰ� ���Ͽ� ����� ������ �ʱ�ȭ.
		if (pBucket != NULL) {
			pBucket->status = DELETED;
			pBucket->key[0] = '\0';
			pBucket->value = 0;
			pHashTable->currentCount--;
			ret = 1;
		}
		else {
			printf("���� ����, �˻�Ű-[%s]�� �������� �ʽ��ϴ�\n", key);
		}
	}
	return ret;
}

//�ؽ� ���̺� ����
void deleteHashTable(HashTable* pHashTable) {
	if (pHashTable != NULL) {
		free(pHashTable->pBucket);
	}
	free(pHashTable);
}

//�ؽ� ���̺��� ���� �ڷ� ����
int getCount(HashTable* pHashTable) {
	int ret = 0;

	if (pHashTable != NULL) {
		ret = pHashTable->currentCount;
	}
	return ret;
}

//�ؽ� ���̺� ���� ���
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
				printf("������ϴ�\n");
			}
		}
		printf("-----------------------------\n");
	}
	else {
		printf("NULL-�ؽ� ���̺��Դϴ�\n");
	}
}