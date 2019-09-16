#include <stdio.h>
#include <stdlib.h>

#include "btree.h"

int main(int argc, char* argv[]) {
	BTree *pTree = NULL;
	BTreeNodeData *pSearchData = NULL;
	int key = 0;

	BTreeNodeData eA = { 9,'A' };
	BTreeNodeData eB = { 12,'B' };
	BTreeNodeData eC = { 19,'C' };
	BTreeNodeData eD = { 39,'D' };
	BTreeNodeData eE = { 65,'E' };
	BTreeNodeData eF = { 53,'F' };
	BTreeNodeData eG = { 63,'G' };
	BTreeNodeData eH = { 89,'H' };
	BTreeNodeData eI = { 48,'I' };
	BTreeNodeData eJ = { 36,'J' };

	pTree = createBTree();
	if (pTree != NULL) {
		addDataBT(pTree, eA);
		addDataBT(pTree, eB);
		addDataBT(pTree, eC);
		addDataBT(pTree, eD);
		printf("\n01-�ڷ� �߰���\n");
		displayBTree(pTree);

		addDataBT(pTree, eE);
		printf("\n02-�ڷ� �߰���\n");
		displayBTree(pTree);

		addDataBT(pTree, eF);
		addDataBT(pTree, eG);
		addDataBT(pTree, eH);
		printf("\n03-�ڷ� �߰���\n");
		displayBTree(pTree);

		addDataBT(pTree, eI);
		addDataBT(pTree, eJ);

		printf("\n�ڷ� �߰��� �������ϴ�\n");
		displayBTree(pTree);

		removeDataBT(pTree, 9);
		printf("\n�˻� Ű 9�� �����Ǿ����ϴ�\n");
		displayBTree(pTree);

		removeDataBT(pTree, 89);
		printf("\n�˻� Ű 89�� �����Ǿ����ϴ�\n");
		displayBTree(pTree);

		removeDataBT(pTree, 39);
		printf("\n�˻� Ű 39�� �����Ǿ����ϴ�\n");
		displayBTree(pTree);

		removeDataBT(pTree, 63);
		removeDataBT(pTree, 53);
		printf("\n�˻� Ű 63, 53�� �����Ǿ����ϴ�\n");
		displayBTree(pTree);

		removeDataBT(pTree, 36);
		printf("\n�˻� Ű 36�� �����Ǿ����ϴ�\n");
		displayBTree(pTree);

		key = 19;
		pSearchData = searchBT(pTree, key);
		if (pSearchData != NULL) {
			printf("�˻� Ű-[%d], ���-[%c]\n", key, pSearchData->value);
		}
		else {
			printf("�˻� Ű-[%d], ��� ����\n", key);
		}
		deleteBTree(pTree);
	}
	return 0;


}