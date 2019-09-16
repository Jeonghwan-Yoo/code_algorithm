/*
3.3첫 번째 충돌 해결 방법:개방 주소법
개방 주소법(Open Addressing)은 조사법(Probing)이라고도 하며, 해시 함수가 계산한 주소가 
비어 있지 않은 경우에 그다음 주소가 비었는지 조사하는 방법.
비어 있으면 해당 자료를 바로 저장하면 됩니다.
비어 있는 주소가 아니라면 다음 주소로 이동하여 빈주소인지를 다시 점검.
꽉 찬 경우에는 자료를 저장할 수 없다.
'다음 주소'를 계산할지에 따라서 선형 조사법, 제곱 조사법, 이중 해시 등의 기법

3.3.1선형 조사법
선형 조사법(Linear probing)은 충돌이 발생한 경우 주소를 일정한 상수만큼 증가시켜 다시 조사하는 방법.
해시 테이블의 모든 주소가 차있어서 자료를 저장할 공간이 없는 경우에 실패로 끝난다.
h(k)=(k+try_count)mod M
k->(충돌)->(k+1)->(충돌)->(k+2)->(충돌)...
단, 충돌이 발생한 주소가 시작 주소가 됩니다. 따라서 일단 한 번 충돌이 발생하면 발생한 주소 주위로
뭉치는 군집화 현상이 발생. 선형 조사법은 군집화 현상이 발생할 가능성이 크다는 단점.
즉, 비교적 간단한 계산으로 빈 주소를 찾는 방법이지만 차례로 값을 더하기 떄문에 군집화 현상이 쉽게 발생.

3.3.2제곱 조사법
제곱 조사법(Quadric probing)은 충돌이 발생할 경우 주소를 조사 횟수의 제곱만큼 증가시켜 다시 조사하는 방법.
h(k)=(k+try_count*try_count)mod M
k->(충돌)->(k+1)->(충돌)->(k+4)->(충돌)->(k+9)...
군집화 현상이 좀 나아지긴 하지만 발생 가능성이 있다.
그리고 해시 테이블의 모든 주소를 조사하려면 해시 테이블의 크기가 반드시 소수여야한다는 제약(제곱할떄 돌려면).

3.3.3이중 해시
이중 해시(Double hashing)은 충돌이 발생하면 원래의 해시 함수와는 다른 추가적인 해시 함수를 이용해
주소를 증가시켜 다시 조사합니다. 다양한 기법이 존재하나, 조사 간격을 이용하는 방법이 있습니다.
(조사 간격)=M-(kmod M), 새로운 주소h(k)=(이전 충돌이 발생한 주소+조사간격)mod M
ex)조사간격=5-(13-mod5)=5-3=2 이전 충돌  주소=3, 새로운 주소는 h(k)=(3+2)mod5=0(2차 충돌 발생)
이전 충돌이 발생한 주소=0, 새로운 주소 h(k)=(0+2)mod5=2.
추가 해시 함수를 사용함으로써 같은 해시 함수 값을 가지더라도 조사 순서를 달리하여
군집화가 발생할 가능성을 줄여주는 장점.

3.4해시 테이블의 추상 자료형
해시 검색을 구현하려면 해시 테이블에 대한 자료 구조가 정의되어야 합니다. 결국 테이블에 저장된 자료를 검색.
'추상 자료형'이란 자료 구조를 구현하고자 자료 구조가 제공해야 하는 연산을 정리한 것.
해시 테이블 생성 createHashTable(), in:해시 테이블의 크기, out:해시 테이블 h.
최대 n개의 원소를 가질 수 있는 해시 테이블 h를 생성
해시 테이블 삭제 deleteHashTable() in:해시 테이블 h, out:N/A
해시 테이블 삭제(메모리 해제)
자료 추가 addData(), in:해시 테이블 h 자료 e, out:성공/실패
해시 테이블에 새로운 자료를 추가
자료 제거 removeData(), in:해시 테이블 h 검색 키 k, out:성공/실패
해시 테이블에 검색 키k에 해당하는 자료를 제거
자료 검색 search(), in:해시 테이블 h 검색 키 k, out:자료 e
해시 테이블에 검색 키 k에 해당하는 자료를 반환
자료 개수 반환 getCount(), int:해시 테이블 h, out:저장된 자료 개수
해시 테이블에 저장된 자료의 개수를 반환

3.5해시 검색의 첫 번째 구현:개방 주소법 사용
검색 키는 문자열이기 때문에 문자열을 정수로 변환하여 검색에 사용합니다. 호너의 방법과 나머지 방법

*/

#ifndef _HASH_SEARCH_
#define _HASH_SEARCH_

#define HASH_KEY_SIZE 30

//버킷에 대한 상태 정의
typedef enum HashBucketStatusType {
	EMPTY=0, USED, DELETED //비어있는 상태, 사용되고 있는 상태, 사용되었다가 제거된 상태.
}HashBucketStatus;

//버킷에 대한 구조체.
typedef struct HashBucketType {
	char key[HASH_KEY_SIZE + 1]; //검색 키
	int value; //저장되는 자료
	HashBucketStatus status; //버킷의 상태
}HashBucket;

//해시 테이블에 대한 구조체.
typedef struct HashTableType {
	int bucketSize; //테이블의 크기
	int currentCount; //현재 저장된 자료의 개수
	HashBucket *pBucket; //버킷 배열을 가리킴.
}HashTable;

//해시 테이블의 생성
HashTable* createHashTable(int bucketSize);

//자료 추가
int addData(HashTable* pHashTable, HashBucket bucket);

//자료 제거
int removeData(HashTable* pHashTable, char* key);

//자료 검색
HashBucket* search(HashTable* pHashTable, char* key);

//해시 테이블 내용 표시
void displayHashTable(HashTable *pHashTable);

//해시 테이블의 현재 자료 개수
int getCount(HashTable *pHashTable);

//해시 테이블 삭제
void deleteHashTable(HashTable *pHashTable);

//나머지 내부에서 사용되는 함수들
int hashFunction(char *pKey, int bucketSize);
unsigned int stringToInt(char *pKey);
int isEmptyBucket(HashBucket* pBucket);
int isEmptyOrDeletedBucket(HashBucket* pBucket);

#endif