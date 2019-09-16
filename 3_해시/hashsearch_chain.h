/*
ü�̴� ������� ������ �ؽ� ���̺����� �� ��Ŷ�� ���� ����Ʈ�� ����.
���� ��Ŷ�� ���ο� �ڷḦ �߰��ϴ� ���� ��Ŷ�� ���ο� ������ �߰��Ǵ� �Ͱ� ����.
���ο� ������ �߰��Ǵ� ���� ���� ����Ʈ�� ���ο� ��带 �߰��ϴ� �Ͱ� ����.
ó������ �ش� NULL, currentCount�� 0.
*/

#ifndef _HASH_CHAIN
#define _HASH_CHAIN

#include "hashingdef.h"
#include "linkedlist.h"

typedef struct HashTableType {
	int bucketSize; //�ڷḦ ������ �� �ִ� ��Ŷ�� ��, �ؽ� ���̺��� ũ��
	int currentCount; //���� ����� �ڷ��� ������ ����
	struct LinkedListType **ppBucket; //���� ����Ʈ���� 1���� �迭. ���Ḯ��Ʈ 1���� ��Ŷ 1��.
	//���� ������ ������ �迭�� �� ���Ҵ� ���� ����Ʈ�� ���� �����Ͱ� �˴ϴ�.
}HashTable;

//�ؽ� ���̺� ����
HashTable* createHashTable(int bucketSize);

//�ڷ� �߰�
int addData(HashTable* pHashTable, HashSlot slot);

//�ڷ� ����
int removeData(HashTable* pHashTable, char* key);

//�ڷ� �˻�
HashSlot* search(HashTable* pHashTable, char* key);

//�ؽ� ���̺� ���� ǥ��
void displayHashTable(HashTable *pHashTable);

//�ؽ� ���̺��� ���� �ڷ� ����
int getCount(HashTable *pHashTable);

//�ؽ� ���̺� ����
void deleteHashTable(HashTable *pHashTable);

//�� �� ���������� ���Ǵ� �Լ���
LinkedList* searchBucket(HashTable* pHashTable, char* key);
int addLinkedListDataLast(LinkedList* pBucket, HashSlot data);
int hashFunction(char *pKey, int bucketSize);
unsigned int stringToInt(char *pKey);
HashSlot* searchSlot(LinkedList* pList, char* key, int* pPosition);

#endif