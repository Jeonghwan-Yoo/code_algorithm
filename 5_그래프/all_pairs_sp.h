/*
5.2.2.4���� �ҽ�
all_pairs_sp.h:�ִ� ��θ� ���ϴ� �Լ� ����(�÷��̵� �˰���)
all_pairs_sp.c:�ִ� ��θ� ���ϴ� �Լ� ����(�÷��̵� �˰���)
05_02.c:���� ���α׷�
linkedgraph2.h:���� ����Ʈ�� ������ �׷����� ����ü�� �Լ� ����
linkedgraph2.c:���� ����Ʈ�� ������ �׷����� �Լ� ����
linkedlist.h:���� ����Ʈ�� ���� ����ü�� �Լ� ����
linkedlist.c:���� ����Ʈ�� ���� �Լ� ����

shortestPathFloyd()�� �߿��� �Լ�
�Է� �Ķ���ͷ� �׷����� ���� �����͸� �����ϸ� �������� �Ҵ�� int Ÿ���� 2���� �迭�� ��ȯ.
2���� �迭�� �÷��̵� �˰������� ���� �ִ� ����� �Ÿ����� �����ϰ� �ֽ��ϴ�.
�׷����� �ִ� ��� ��� ������ �ִ� �Ÿ��� ���� ���� 2���� ���� �迭 ppDistance�� ��� ��ȯ�մϴ�.
�׷����� ��� ��� ������ �Ÿ��̱� ������ 2���� �迭.
*/

#ifndef _GRAPH_ALL_PAIRS_SP_
#define _GRAPH_ALL_PAIRS_SP_

#define MAX_INT 99999

//�÷��̵�(Floyd)�˰���
int** shortestPathFloyd(LinkedGraph* pGraph);
void printMatrix(int **ppDistance, int nodeCount);

#endif