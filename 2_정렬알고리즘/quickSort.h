/*
2.4퀵 정렬(Quick sort)
중심 값(pivot)을 기준으로 두 자료의 키 값을 비교하여 위치를 교환(Exchange)하는 정렬 방법.
오름차순 정렬이라면 왼쪽은 피봇보다 작은 값이, 오른쪽은 피봇보다 큰 값이 오도록 자료의 위치를 교환
먼저, Left는 가장 왼쪽에서 오른쪽으로 이동하면서 피봇보다 큰 수를 찾습니다.
반대로, Right는 가장 오른쪽에서 왼쪽으로 이동하면서 피봇보다 작은 수를 찾습니다.
발견하면 두 자료의 위치를 교환합니다.
그런 다음 키 값 교환을 위해 계속 Left와 Right를 이동.
즉, 왼쪽은 피봇보다 작은 값ㅇ시, 오른쪽이 피봇보다 큰 값이 오도록 합니다.
단, Left는 Right보다 오른쪽으로 갈 수 없고 Right는 Left보다 왼쪽으로 갈 수 없습니다.

이렇게 진행하다 보면 결국 Left와 Right가 만나게 됩니다.
그러면, Left&Right와 피봇이 가리키는 자료를 서로 교환합니다.
단, 퀵 정렬은 이렇게 위치 교환이 끝난 다음에 피봇을 기준으로 값을 2개의 부분 집합으로 나눕니다.
그러고 나누어진 부분 집합에 대해 다시 퀵 정렬을 실행합니다.
피봇을 중심으로는 나누어졌지만, 각 부분 집합 내부는 아직 정렬되지 않은 상태이기 때문입니다.

단, 나누어진 2개의 부분 집합은 자료의 개수가 2개 이상인 경우에 대해서만 퀵 정렬을 실행합니다.
원소 개수가 없거나 혹은 1개인 경우에는 퀵 정렬을 다시 실행할 필요가 없습니다.

즉, 피봇을 기준으로 키 위치 교환->새로운 피봇의 교환->2개 부분 집합에 대해 퀵정렬 실행

퀵 정렬 알고리즘은 원래의 문제를 더 작은 크기의 하위 문제로 쪼개어 해결한다고 해서
분할 정복(Divide and Conquer)알고리즘.

2.4.1퀵 정렬의 과정

2.4.2퀵 정렬의 구현
count는 전체 배열의 크기. 단, 실제 정렬의 범위는 위치 인덱스 start부터 end까지.
start는 0이고, end는 count-1.
분할 정복 기법을 사용하기 때문에, 일부 부분 집합에 대해서도 정렬할 수 있어야 합니다.

2.4.3퀵 정렬의 특성
피봇을 기준으롤 2개의 부분 집합으로 나누어 자료의 위치를 교환하기 때문에 n개의 자료에 대해 
평균 O(nlog n)번 만에 정렬하는 효율성을 가집니다.
즉, n개의 자료가 균일하게 분포되었다면 정렬 횟수가 n/2, n/4,...와 같이 줄어 들기 때문에
평균 log2 n의 연산 횟수가 필요합니다.
다만, 매번 정렬을 할 때마다 모두 n번의 비교가 필요하기 때문에 평균 비교 횟수는 nlog2 n이 됩니다.
즉, 퀵 정렬의 효율성은 평균 O(nlog n)입니다.
또한, 자료의 이동 연산은 비교 연산보다 상대적으로 적게 발생한다는 장점.

단, 피봇을 기준으로 부분 집합에 계속 불균형이 발생한다면 최악의 경우 O(n^2)의 효율성을 가지는 단점.
최선, 평균:O(nlog n)
최악:O(n^2)

특히 기존에 사용한 피봇을 다시 사용하지 않기 때문에 불필요한 자료의 이동을 줄였으며
먼 거리의 자료를 교환하는 등 효율성이 후수하다는 특성.
최악의 경우를 대비해 기존 자료 중 중간값(Median)을 피봇으로 선택하여 수행하기도 합니다.
자료의 교환이 계속 일어나기 때문에 아쉽게도 정렬의 안정성은 유지하지 못합니다.
*/

#ifndef _QUICK_SORT_h
#define _QUICK_SORT_h

void quickSort(int value[], int start, int end);

#endif
