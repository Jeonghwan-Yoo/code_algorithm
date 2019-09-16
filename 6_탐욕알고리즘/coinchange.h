/*
6.2.2탐욕 알고리즘의 구현
06_01.c:예제 프로그램
coinchange.h:동전 거스름돈 구하기 관련 구조체와 함수 선언
coinchange.c:동전 거스름돈 구하기 관련 함수 구현

구조체 CoinItem은 동전의 가격 단위를 저장하는 value와 선택된 동전의 개수를 저장하는 selected로 구성.
*/

#ifndef coinchange_h
#define coinchange_h

#include <stdio.h>
#include <stdlib.h>

typedef struct CoinItem {
	int value;
	int selected;
}CoinItem;

//얼마짜리 동전이 있는지를 사용자에게서 입력 받습니다.
//입력 받은 동전들의 정보를 통해 거스름돈이 얼마인지 전달 받습니다.
//여기서 items는 입출력 파라미터이기 때문에 계산한 동전 개수는 items에 저장.
void inputItems(CoinItem *items, int item_count);
//실제 탐욕 알고리즘을 이용하여 각 동전의 종류별로 몇 개의 동전을 사용해야 하는지 계산.
//반환한 값은 동전으로 거스름돈을 만들고 남은 금액.
int getChange(int change_total, CoinItem *items, int item_count);
//앞서 구한 동전별 거스름돈 정보를 출력합니다.
void printResult(CoinItem *items, int item_count, int remained);

#endif
