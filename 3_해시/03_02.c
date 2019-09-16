#include <stdio.h>
#include <stdlib.h>

#include "hashsearch_chain.h"

int main(int argc, char* argv[]) {
	HashTable *pHashTable = NULL;
	HashSlot slot1 = { "january",1 };
	HashSlot slot2 = { "february",2 };
	HashSlot slot3 = { "march",3 };
	HashSlot slot4 = { "april",4 };
	HashSlot slot5 = { "may",5 };
	HashSlot slot6 = { "june",6 };
	HashSlot slot7 = { "july",7 };
	HashSlot slot8 = { "august",8 };
	HashSlot slot9 = { "september",9 };
	HashSlot slot10 = { "october",10 };
	HashSlot slot11 = { "november",11 };
	HashSlot slot12 = { "december",12 };
	HashSlot *pSlot = NULL;
	HashSlot *pSlot2 = NULL;

	//�ؽ� ���̺� ����
	pHashTable = createHashTable(13);
	if (pHashTable != NULL) {
		addData(pHashTable, slot1);
		addData(pHashTable, slot2);
		addData(pHashTable, slot3);
		addData(pHashTable, slot4);
		addData(pHashTable, slot5);
		addData(pHashTable, slot6);
		addData(pHashTable, slot7);
		addData(pHashTable, slot8);
		addData(pHashTable, slot9);
		addData(pHashTable, slot10);
		addData(pHashTable, slot11);
		addData(pHashTable, slot12);

		printf("�ؽ� ���̺� ����:\n");
		displayHashTable(pHashTable);

		pSlot = search(pHashTable, "april");
		if (pSlot != NULL) {
			printf("�˻�Ű-%s, �˻� ���-%d\n", pSlot->key, pSlot->value);
			
			removeData(pHashTable, "april");
			printf("�˻�Ű[%s]�� �ڷ� ����\n", "april");

			printf("�ؽ� ���̺� ����:\n");
			displayHashTable(pHashTable);

			pSlot2 = search(pHashTable, "april");
			if (pSlot2 != NULL) {
				printf("�˻�Ű-%s, �˻� ���-%d\n", pSlot2->key, pSlot2->value);
			}

			pSlot2 = search(pHashTable, "june");
			if(pSlot2 != NULL) {
				printf("�˻�Ű-%s, �˻� ���-%d\n", pSlot2->key, pSlot2->value);
			}
		}
		else {
			printf("Not fount\n");
		}
		deleteHashTable(pHashTable);
	}
	return 0;
}