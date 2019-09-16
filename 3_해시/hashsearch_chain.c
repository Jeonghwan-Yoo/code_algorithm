#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashsearch_chain.h"

//�ؽ� ���̺� ����
HashTable* createHashTable(int bucketSize) {
	HashTable* pReturn = NULL;
	int i = 0;

	if (bucketSize <= 0) {
		printf("��Ŷ ũ��� 0���� Ŀ���մϴ�\n");
		return NULL;
	}

	pReturn = (HashTable*)malloc(sizeof(HashTable));
	if (pReturn != NULL) {
		pReturn->bucketSize = bucketSize;
		pReturn->ppBucket = NULL;
	}
	else {
		printf("����, ù��° �޸��Ҵ�, createHashTable()\n");
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
		printf("����, �ι�° malloc(), createHashTable()\n");
		return NULL;
	}
	return pReturn;
}

//�ؽ� ���̺� ���ο� �ڷḦ �߰��ϴ� �Լ�
int addData(HashTable* pHashTable, HashSlot slot) {
	int ret = 0;
	LinkedList* pBucket = NULL;

	if (pHashTable != NULL) {
		pBucket = searchBucket(pHashTable, slot.key); //������ ��Ŷ�� ã�´�.
		if (pBucket != NULL) {
			addLinkedListDataLast(pBucket, slot); //���� �������� �ڷḦ �߰�.
			pHashTable->currentCount++;
		}
		else {
			printf("����, �߸��� �ؽ� ���̺� �ּҰ� ���Ǿ����ϴ�\n");
		}
	}
	return ret;
}

//�ؽ� ���̺��� �ش� ��Ŷ�� ã�� �Լ�
//�ش� ��Ŷ�� ���� ����Ʈ �ּҸ� ��ȯ�� pReturn.
LinkedList* searchBucket(HashTable* pHashTable, char* key) {
	LinkedList* pReturn = NULL;
	int bucketIndex = 0;

	if (pHashTable != NULL) {
		bucketIndex = hashFunction(key, pHashTable->bucketSize);
		if (bucketIndex >= 0) {
			pReturn = pHashTable->ppBucket[bucketIndex];
		}
		else {
			printf("����, �߸��� �ؽ� ���̺� �ּҰ� ���Ǿ����ϴ�,\n");
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

//���ڿ��� ���ڷ� ��ȯ
unsigned int stringToInt(char* pKey) {
	unsigned int ret = 0;
	while (*pKey != '\0') {
		ret = (ret * 31) + (*pKey);
		pKey++;
	}
	return ret;
}

//����Ʈ ���� �������� �߰�.
int addLinkedListDataLast(LinkedList* pBucket, HashSlot data) {
	int ret = 0;
	if (pBucket != NULL) {
		int position = pBucket->currentCount;
		ret = addLinkedListData(pBucket, position, data);
	}
	return ret;
}

//�˻� Ű�� �ؽ� ���̺��� �ڷḦ �˻��ϴ� �Լ�
//���������� �˻� Ű�� �̿��Ͽ� ���� ��Ŷ�� �˻��ϰ� �˻��� ��Ŷ�� ������� ������ �˻��մϴ�.
//�˻��ؼ� �߰ߵ� ���Կ� ���� ������(HashSlot*)�� ��ȯ�մϴ�.
HashSlot* search(HashTable* pHashTable, char* key) {
	HashSlot* pReturn = NULL;
	LinkedList* pList = NULL;
	int position = 0;

	pList = searchBucket(pHashTable, key);
	if (pList != NULL) {
		//���� ����Ʈ�� ������ pList�� �˻� Ű key�� �Է� �Ķ���ͷ� �����ϸ�
		//�˻��� �ڷ�(����)�� ���� ������(HashSlot*)�� ��ȯ�մϴ�.
		//�߰��� position�� �ּҸ� �����մϴ�.
		//��� �Ķ���ʹ� ���� ����Ʈ���� �߰ߵ� �ڷ��� ��ġ ���� �����ϴ� ���� ����.
		pReturn = searchSlot(pList, key, &position);
	}
	return pReturn;
}

//Ư�� ���Ḯ��Ʈ(��Ŷ)���� �˻��� ����.
HashSlot* searchSlot(LinkedList* pList, char* key, int* pPosition) {
	HashSlot* pReturn = NULL;
	LinkedListNode* pSlot = NULL;
	int index = 0;

	if (pList != NULL && pPosition != NULL) {
		pSlot = pList->headerNode.pLink;

		//ù ��° ������ �����Ͽ� ������ ��忡 �����ϱ���� ������ ���鼭 �˻� �ڷ��� �ڷḦ ����.
		while (pSlot != NULL) {
			//�ڷḦ �߰��ϸ� �ش� �ڷḦ ��ȯ.
			if (strcmp(pSlot->data.key, key) == 0) {
				pReturn = &(pSlot->data);
				*pPosition = index; //*pPosition�� ���� ����Ʈ���� �߰ߵ� �˻� �ڷ��� ��ġ���� ����.
				break;
			}
			pSlot = pSlot->pLink;
			index++;
		}
		if (pReturn == NULL) {
			printf("�˻� ����, �˻�Ű-[%s]�� �������� �ʽ��ϴ�\n", key);
		}
	}
	return pReturn;
}

//�˻� Ű�� �ؽ� ���̺� �ش� �ڷḦ �����ϴ� �Լ�
int removeData(HashTable* pHashTable, char* key) {
	int ret = 0;
	HashSlot *pSlot = NULL;
	LinkedList* pList = NULL;
	int position = 0;

	//���������� �˻� Ű�� �̿��Ͽ� ���� ��Ŷ�� �˻�.
	pList = searchBucket(pHashTable, key);
	if (pList != NULL) {
		//�˻��� ��Ŷ�� ������� ������ �˻�.
		pSlot = searchSlot(pList, key, &position);
		if (pSlot != NULL) {
			//���� ����Ʈ(��Ŷ)���� �ش� �ڷḦ �����մϴ�.
			//��, �̶� ���� ����Ʈ���� �ڷḦ �����ϴ� ���̱� ������ ��ġ ���� position�� �ʿ�.
			removeLinkedListData(pList, position);
			pHashTable->currentCount--;
			ret = 1;
		}
	}
	return ret;
}

//�ؽ� ���̺� ����
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

///�ؽ� ���̺��� ���� �ڷ� ����
int getCount(HashTable* pHashTable) {
	int ret = 0;

	if (pHashTable != NULL) {
		ret = pHashTable->currentCount;
	}
	return ret;
}

//�ؽ� ���̺� ���� ���
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