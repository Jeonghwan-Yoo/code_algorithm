#include <stdio.h>
#include <stdlib.h>
#include "linkedgraph1.h"
#include "single_source_sp.h"

int main(int argc, char* argv[]) {
	LinkedGraph *pG = NULL;
	int *pResult = NULL;
	int i = 0;

	//�׷��� ����
	pG = createLinkedGraph(LINKED_GRAPH_TYPE_DIRECT, 6);
	if (pG != NULL) {
		//�׷��� �ʱ�ȭ:���� �߰�
		addEdgeLG(pG, 0, 1, 2);
		addEdgeLG(pG, 0, 2, 4);
		addEdgeLG(pG, 2, 0, 4);
		addEdgeLG(pG, 1, 2, 1);
		addEdgeLG(pG, 2, 3, 7);
		addEdgeLG(pG, 3, 2, 5);
		addEdgeLG(pG, 3, 4, 2);
		addEdgeLG(pG, 3, 5, 6);
		addEdgeLG(pG, 4, 5, 3);
		addEdgeLG(pG, 5, 3, 6);
		printf("G3:\n");
		displayGraphLG(pG);

		printf("\n���ͽ�Ʈ��(Dijkstra) �˰���:\n");
		pResult = shortestPathDijkstra(pG, 0); //���� ���:0
		if (NULL != pResult) {
			printf("\n���:\n");
			for (i = 0;i < pG->nodeCount;i++) {
				printf("%d ������ %d ������ �ɸ��� �ִ� �Ÿ�:%d\n", 0, i, pResult[i]);
			}
			free(pResult);
		}
		deleteGraphLG(pG);
	}
	return 0;
}