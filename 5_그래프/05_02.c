#include <stdio.h>
#include <stdlib.h>
#include "linkedgraph2.h"
#include "all_pairs_sp.h"

int main(int argc, char* argv[]) {
	LinkedGraph *pG = NULL;
	int **ppResult = NULL;
	int i = 0;

	//그래프 생성
	pG = createLinkedGraph(LINKED_GRAPH_TYPE_DIRECT, 3);
	if (pG != NULL) {
		//그래프 초기화:간선 추가
		addEdgeLG(pG, 0, 1, 2);
		addEdgeLG(pG, 0, 2, 4);
		addEdgeLG(pG, 2, 0, 4);
		addEdgeLG(pG, 1, 2, 1);

		printf("G5:\n");
		displayGraphLG(pG);

		printf("\n플로이드(Floyd) 알고리즘:\n");
		ppResult = shortestPathFloyd(pG);

		if (NULL != ppResult) {
			printf("\n결과:\n");
			printMatrix(ppResult, pG->nodeCount);

			for (i = 0;i < pG->nodeCount;i++) {
				if (NULL != ppResult) {
					free(ppResult[i]);
				}
			}
			free(ppResult);
		}
		deleteGraphLG(pG);
	}
	return 0;
}
