/*
4.5B-트리의 구현

			 이름            in                 out         설명
B-트리 생성   createBTree()                                 공백 B-트리 b를 생성
B-트리 삭제   deleteBTree()   B-트리 b           B-트리 b    B-트리 제거(메모리 해제)
검색          search()        B-트리 b, 키 값 k  N/A         B-트리에서 키 값 k를 가지는 자료를 반환
자료 추가     addData()       B-트리 b, 자료 d               B-트리에 새로운 자료를 추가
자료 제거     removeData()    B-트리 b, 키 값 k  성공/실패    B-트리에서 키 값 k를 가지는 자료를 제거
B-트리 표시   displayBTree()  B-트리 b           N/A         B-트리에 저장된 원소를 화면에 표시

btreedef.h:상수와 구조체 선언
btlinkedstack.h:B-트리 구현을 위한 스택의 구조체와 함수 선언
btlinkedstack.c:B-트리 구현을 위한 스택의 함수 구현
btree.h:최대 B-트리에 관한 구조체와 함수 선언
btree.c:최대 B-트리에 관한 함수 구현
04_01.c:예제 프로그램.

균형 유지 연산을 구현할 때 내부적으로 스택을 사용합니다.
새로운 노드의 추가 혹은 삭제 등으로 분할, 병합과 같이 구조 변화가 일어날 때 말단 노드부터 시작하여
루트 노드까지 순차적으로 처리해야 되기 때문입니다.

*/

#ifndef _BTREE_DEF_
#define _BTREE_DEF_

#define BTREE_ORDER 5 //자료의 개수=5

typedef struct BTreeNodeDataType { //트리 노드에 저장되는 자료의 구조체 선언
	int key;
	char value;
}BTreeNodeData;

//자료 m개, 서브트리m+1개. 구현의 편의성 때문에.
//배열에 여유 공간을 두어 노드의 분할 등을 편리하게 구현하기 위해서.
//별도의 구조체에 자료를 저장함으로써 저장되는 변수의 종류와 개수가 변경되어도 
//소스 자체의 변경 범위 최소화
typedef struct BTreeNodeType { //트리 노드의 구조체 선언
	int count; //노드에 저장되는 자료의 개수
	BTreeNodeData data[BTREE_ORDER]; //자료를 저장하는 배열
	struct BTreeNodeType* children[BTREE_ORDER + 1]; //자식 노드들에 대한 포인터 배열
}BTreeNode;

#endif