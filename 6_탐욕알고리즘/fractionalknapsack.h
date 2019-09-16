/*
6.3.2탐욕 알고리즘의 구현
06_02:예제 프로그램
fractionalknapsack.h:부분 배낭 문제 해결 관련 구조체와 함수 선언
fractionalknapsack.c:부분 배낭 문제 해결 관련 함수 구현

구조체는 물건의 이름을 저장하는 멤버 변수 name, 무게를 저장하는 멤버 변수 weight, 
가격을 저장하는 멤버 변수 profit, 선택된 물건의 무게를 저장하는 멤버 변수 selected로 구성.

*/

#ifndef fractionalknapsack_h
#define fractionalknapsack_h

#include <stdio.h>
#include <stdlib.h>

typedef struct _KnapsackItem {
	char name[100];
	double weight;
	double profit;
	double selected;
}KnapsackItem;

//배낭에 담길 물건들의 정보를 사용자에게서 입력 받습니다. 몇가지 인지 item_count를 통해 전달 받음.
void inputItems(KnapsackItem *items, int item_count);
//실제 탐욕 알고리즘을 이용하여 부분 배낭 문제에 대한 최적해를 구하는 함수. items는 입출력 파라미터.
//각 물건이 배낭에 얼마만큼 담겼는지 선택된 무게 정보 또한 items에 저장됩니다.
//반환된 값은 배낭에 담긴 물건들의 총 가치(가격)을 나타냅니다.
double fractionalKnapsack(double capacity, KnapsackItem *items, int item_count);
//앞서 구한 각 물건이 얼마만큼 배낭에 담겨 있는지를 출력.
void printResult(KnapsackItem *items, int item_count, double max_profit);

#endif
