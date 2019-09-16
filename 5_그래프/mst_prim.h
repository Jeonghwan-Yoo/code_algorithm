/*
5.3.4.4���� �ҽ�
mst_prim.h:'�ּ� ��� ���� Ʈ��' ����ü�� �Լ� ����(���� �˰���)
mst_prim.c:'�ּ� ��� ���� Ʈ��' ����ü�� �Լ� ����(���� �˰���)
05_04.c:���� ���α׷�
linkedgraph4.h:���� ����Ʈ�� ������ �׷����� ����ü�� �Լ� ����
linkedgraph4.c:���� ����Ʈ�� ������ �׷����� �Լ� ����
linkedlist4.h:���� ����Ʈ�� ���� ����ü�� �Լ� ����
linkedlist4.c:���� ����Ʈ�� ���� �Լ� ����
linkedstack4.h:���� ����Ʈ�� ������ ������ ����ü�� �Լ� ����
linkedstack4.c:���� ����Ʈ�� ������ ������ �Լ� ����

*/

#ifndef _GRAPH_MST_PRIM_
#define _GRAPH_MST_PRIM_

#define MAX_INT 99999

//���۳��� ���� ����� ������ ��� �ʿ��ؼ� �ٽ� ����ü ����.
typedef struct PrimGraphEdgeType {
	int fromNodeID; //���� ��� ID
	int toNodeID; //�߷� ��� ID
	int weight; //����ġ
}PrimGraphEdge;

//���� �˰���
LinkedGraph *mstPrim(LinkedGraph* pGraph, int startNodeID);

//���(fromNodeID)�� ����� ���� �߿���
//����ġ ���� �����鼭 ��ȯ�� �߻���Ű�� �ʴ� ���� ����
void getMinWeightEdge(LinkedGraph* pGraph, LinkedGraph* pMST,
	int fromNodeID, PrimGraphEdge *pMinWegithEdge);

//��ȯ �˻�
int checkCycle(LinkedGraph* pGraph, int fromNodeID, int toNodeID);

//������ �̹� �ִ� �������� �˻�
int checkEdge(LinkedGraph* pGraph, int fromNodeID, int toNodeID);

#endif