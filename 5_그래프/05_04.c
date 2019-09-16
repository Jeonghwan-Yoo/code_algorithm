#include <stdio.h>
#include <stdlib.h>

#include "linkedgraph4.h"
#include "mst_prim.h"

int main(int argc, char *argv[]) {
	LinkedGraph *pG3 = NULL;
	LinkedGraph *pMST1 = NULL;

	//�׷��� ����
	pG3 = createLinkedGraph(LINKED_GRAPH_TYPE_UNDIRECT, 6);
	if (pG3 != NULL) {
		//�׷��� �ʱ�ȭ:���� �߰�
		addEdgeLG(pG3, 0, 1, 4);
		addEdgeLG(pG3, 0, 2, 3);
		addEdgeLG(pG3, 1, 2, 2);
		addEdgeLG(pG3, 2, 3, 1);
		addEdgeLG(pG3, 3, 4, 1);
		addEdgeLG(pG3, 3, 5, 5);
		addEdgeLG(pG3, 4, 5, 6);

		printf("G3:\n");
		displayGraphLG(pG3);

		//���� �˰������� MST ����
		printf("\nPrim MST:\n");
		pMST1 = mstPrim(pG3, 1);
		displayGraphLG(pMST1);

		//�׷��� ����
		deleteGraphLG(pG3);
		deleteGraphLG(pMST1);
	}
	return 0;
}