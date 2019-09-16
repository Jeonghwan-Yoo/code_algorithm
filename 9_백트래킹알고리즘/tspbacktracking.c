#include "tspbacktracking.h"

//pPath�� ������ ���
//��� ���� �� ���� ���� ������ �ִ��� ���� ������ step���� ����. ������� ��� ������ cost��
void printPath(int pGraph[][NUM_OF_NODE], int *pPath, int step, int cost) {
	for (int i = 0;i <= step;i++) {
		if (i > 0) {
			printf(" -(%d)-> ", pGraph[pPath[i - 1]][pPath[i]]);
		}
		printf("%c", 'A' + pPath[i]);
	}
	printf("\t���:%d\n", cost);
}

//���� �ֱٿ� �߰��� ���ð� Ȥ�� �ߺ��� �������� ����.
//step�� ���� �������� �湮�� ���ø� �ǹ�.
int checkValidPath(int pPath[], int step) {
	//���� �߰��� step��° ���ð� �̹� �湮�� �������� �����Ѵ�.
	for (int i = 0;i < step;i++) {
		if (pPath[i] == pPath[step]) {
			return 0;
		}
	}
	return 1;
}

//��� ���� ���
//int �迭�� �湮�� ������ �ε��� ������ �����ϴ� ������� ��θ� ����.
//�̶� �� ���� ���ø� �湮�ߴ����� ������ ���� step���� ����.
//A->B->D�̸� ���� �迭���� ��ġ ���� 0,1,3�� ���ʷ� ����.
//���� ���ø� ������ �湮 ������ ������ 2��, ��θ� ��Ÿ���� �迭 pPath�� ������ ���Ҹ� ����Ŵ.

//�׷��� ���� pGraph, ���� �湮�� ���� ���� step, ��������� �湮 ��� cost
//���� �湮 ��� pPath�� ������Ķ����. ���� ��ο� �������� �湮�� ���ø� �߰�.
//������ ��ΰ� ������ ��ζ�� �Ǵܵ� �� ������ ��θ� ��ȯ�ϴ� pOptimalPath, �ּ� �湮 ��� pMinCost.
void TSP_BackTracking(int pGraph[][NUM_OF_NODE], int step, int cost, int pPath[],
	int pOptimalPath[], int* pMinCost) {
	int next_node = 0, current_node = 0, total_cost = 0;
	if (checkValidPath(pPath, step)) { //��ȿ�� ������� ����(���� �ֱٿ� �߰��� ���ð� �ߺ�����)
		current_node = pPath[step];

		//������ ����� ��� ���� ��尡 ���� ���
		//���� ���� ���� ��ΰ� �������� ��ζ�� ������ ������ ����.
		//���� ���ø� �����ϰ� ���� �湮�� ������ ������ 3�̸� ������ ���ñ��� �湮�� ���.
		if (step == NUM_OF_NODE - 1) {
			//�ٽ� ���� ���� ����
			next_node = pPath[0];
			pPath[step + 1] = next_node;
			total_cost = cost + pGraph[current_node][next_node];
			//���� �ذ� ���� �����غ��� �� ���� ��� ������ ����
			if (total_cost < *pMinCost) {
				*pMinCost = total_cost;
				memcpy(pOptimalPath, pPath, sizeof(int)*NUM_OF_NODE);
				printf("*"); //�����ذ� ����Ǿ��ٴ� ���� ǥ��.
			}
			//������ �ظ� ���Ӱ� �ϳ� ���߱� ������ ���� ���� �ظ� ���
			printPath(pGraph, pPath, NUM_OF_NODE, total_cost);
		}
		//������ �ذ� �ƴ϶�� ������ �ظ� ���ϱ� ���� ���� ���ø� �湮.
		else {
			//���� ���ø� ������ ������ ���õ鿡 ���ؼ� ����
			for (int toNode = 1;toNode < NUM_OF_NODE;toNode++) {
				next_node = toNode;
				pPath[step + 1] = next_node; //toNode�� ��ο� �߰�.
				total_cost = cost + pGraph[current_node][next_node]; //��뵵 �߰�.
				//����� ȣ���ؼ� ��Ʈ��ŷ�� ����.
				TSP_BackTracking(pGraph, step + 1, total_cost, pPath, pOptimalPath, pMinCost);
			}
		}
	}
}