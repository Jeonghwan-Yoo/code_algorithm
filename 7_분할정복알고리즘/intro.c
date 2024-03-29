/*
분할 정복 알고리즘(Divide and conquer algorithm)
어떻게 풀어야 할지 도저히 모를 어려운 문제도 분할 정복 알고리즘을 이용하면 쉽게 해결
큰 문제를 작은 여러 개의 문제로 쪼개서 쉽게 푸는 방법.
하나의 어렵고 큰 문제를 여러 개의 쉽고 작은 문제로 분할하기 때문에 결국 쉽게 해결.

7.1이진 검색을 통해 알아보는 분할 정복 알고리즘
이진 검색(Binary search)은 분할 정복 알고리즘의 개념을 적용한 대표적인 사례
문제를 2개의 부분 문제로 나누어서 검색 문제를 해결합니다.
검색 범위를 반씩 감소시키면서 검색 키를 찾습니다. 반씩 감소시키는 것이 분할에 해당.
분할된 2개의 부분 중에서 하나는 버리고 남은 한 부분을 대상으로 다시 검색.
단, 자료의 절반을 버리려면 먼저 자료들이 정렬되어 있어야 합니다.

이진의 핵심은 '절반씩 버린다'입니다. 버리려면 중간의 위치를 구해야 합니다.
중간 위치의 자료 값과 검색 키를 비교해서 검색 키 값이 중간 값보다 크다면 왼쪽을 버립니다.
버린 상태에서 다시 새로운 중간 위치를 정합니다.
이러한 분할과 비교 연산을 반복하여 검색 대상이 되는 자료를 찾습니다.
마지막 남은 자료가 찾으려는 검색 키와 같다면 검색이 성공하고 아니면 실패한 경우.

예로 오름차순으로 정렬된 6개의 자료 {10,20,50,60,70,80}에서 키 값이 60인 자료를 찾는다고 가정.
중간위치=(시작위치+마지막위치)/2

Step-1:중간 위치에 있는 자료:50
인덱스가 0~5까지. 중간위치=(0+5)/2=2.5=2
50<60이므로 왼쪽을 버리고 오른쪽에서 검색.

Step-2:중간 위치에 있는 자료:70
인덱스 3~5까지. 중간위치=(3+5)/2=4
70>60이므로 오른쪽을 버리고 왼쪽에서 검색.

Step-3:중간 위치에 있는 자료:60
인덱스 3~3까지. 중간위치=(3+3)/2=3
60==60이므로 검색은 성공.

만약 65를 찾는다고 하면, 검색 키 값은 65이며 남은 자료는 60이되는데,
두 값이 일치하지 않기 때문에 검색이 실패.

이진 검색의 의사코드
value:검색 대상 자료
start:시작 위치
end:마지막 위치
key:검색 키
binarySearchRecursive(value,start,end,key){
	result<-FAIL

	if(start<=end){
		middle=(start+end)/2
		if(key==value[middle]){
			result<-middle
			break;
		}
		else if(key<value[middle]){
			result<-binarySearchRecursive(value,start,middle-1,key)
		}
		else{
			tempStart<-binarySearchRecursive(value,middle+1,end,key)
		}
	}
	return result
}

분할 정복을 구현하는 방법:재귀 호출
'자기 자신을 다시 호출하는 것'
자기 자신을 내부에서 다시 호출하는 함수가 재귀 호출을 구현한 함수.
분할 정복 알고리즘은 재귀 호출뿐 아니라 반복 호출을 통해서도 구현할 수 있습니다.
반복 호출이란 for문 혹은 while문 등의 반복문을 이용하여 구현하는 방법
단, 재귀 호출에서 주의해야 할 점은 루프가 종료되지 않고 계속 실행되는 무한루프에 빠지지 않도록 구현.
무한 루프는 버그에 해당. 프로그램이 종료되지 않고 계속 실행만 되는 상태.
두 가지 원칙
1)호출될 때마다 문제의 범위가 줄어들어야 한다.
2)종료 조건이 있어야 한다.
이진 검색은 검색 범위를 분할하여 절반을 버리는 방식이므로 범위가 1/2씩 줄어듭니다.
마지막 남은 중간 위치의 값에 따라 검색이 성공 혹은 실패로 끝납니다.

7.2팩토리얼(Factorial) 문제
정수 n에 대한 n!(n 팩토리얼)은 n이 1보다 크면 n!은 1부터 n개의 정수를 모두 곱한 것입니다.
팩토리얼을 자기 자신을 호출하는 재귀 호출 방식으로 표현할 수 있습니다.
n!=       1, if n=1
  =n*(n-1)!, if n>=2
주의할 점은 다시 자기 자신을 호출하면서 문제의 범위가 줄어들었다는 점입니다. n에서 n-1로
분할 정복 알고리즘이 팩토리얼에 적용되면 원래의 문제를 크기가 더 작은 부분 문제로 쪼개집니다.
n이 1인 경우에 더 이상 쪼갤 수 없습니다.
정복이란 n과 하위 문제의 답을 곱하는 것.
분할                      정복
        1 2 3 4               1   2
		 /   \                 \ /
      1 2 3   4            2!  1 2  3
	   / \                       \ /
     1 2  3                3!   1 2 3  4
	 / \                           \  /
	1   2                  4!     1 2 3 4

7.3가장 가까운 두점 찾기(Closest pair problem) 문제
"최근접 점의 쌍 찾기 문제" 혹은 "최근점 점쌍 문제"라고도 합니다.
가장 간단한 방법은 '모든 경우를 다 점검해 보는 것' 즉, 모든 점 사이의 거리를 구해보는 것.
만약 점의 개수가 n개라면 두 점의 쌍이 가능한 모든 경우의 수는 n(n-1)/2이 됩니다.
결론적으로 시간 복잡도가 n^2가 됩니다.
하지만, 분할 정복 알고리즘을 사용하면 이보다 더 빨리 '가장 가까운 두 점'을 찾을 수 있습니다.

7.3.1분할 정복 알고리즘의 적용
왼쪽과 오른쪽 2부분으로 나누어 가장 가까운 두점을 찾습니다.
왼쪽 부분 문제에서 구한 가장 가까운 두점의 거리를 dL이라고 하고 오른쪽은 dR이라고 합니다.
dL과 dR을 비교해서 더 작은 값이 전체 문제의 답이 될 것입니다. d=min{dL, dR}
그러나 두 부분 문제 사이에 걸쳐 있는 중간 영역을 고려하지 않았습니다.
중간 영역에 속한 점 중에서 가장 가까운 거리를 dC라고 했을 때
가장 가까운 거리는 dL, dR, dC 중 가장 작은 값이 됩니다. d=min{dL, dR, dC}
왼쪽 부분 문제에 대해서 재귀 호출을 이용하여 다시금 분할 정복 알고리즘을 적용할 수 있습니다.
오른쪽 부분도 같은 방식으로 하고, 분할된 영역에 점이 2개 혹은 3개가 있으면 더 이상 할 쪼갤 필요 없다.\
점이 2개면 거리는 오직 1가지, 3개면 모두 3가지.
각 부분 문제의 결과값을 비교하기만 하면 정복 과정이 끝납니다.

분할 정복 알고리즘의 의사코드
points:점들의 배열(단 ,x좌표에 오름차순으로 정렬되어 있음)
closestPairRecursive(points){
	if(점들의 개수<=3){
		result<-모든 경우에 대해 최소 거리를 계산
	}

	가운데 점을 기준으로 points를 points_L와 points_R로 분할

	dL<-closestPairRecursive(points_L)
	dR<-closestPairRecursive(points_R)
	dC<-중간 영역의 점들에서 가장 가까운 거리 구하기

	result<-min{dL, dR, dC}

	return result;
}

시간 복잡도는 O(nlong n)으로 향상됩니다.

7.4연쇄 행렬 곱셈 문제(Maxtrix chain multiplication problem)
여러 개의 행렬을 곱할 때 어떤 순서로 곱셈을 하는 것이 더 좋은지 찾는 문제.
더 좋은 순서란 결국 곱셈 횟수가 가장 적은 것을 말합니다.

7.4.1연쇄 행렬 곱셈 문제란?
행렬의 곱셈은 결합법칙이 성립한다. 즉, 계산하는 순서를 바꿔도 결과는 같다.
하지만, 실제 곱하기 연산의 수행 횟수에는 상당히 큰 차이가 있습니다.

예로 행렬A(1x100)*행렬B(100x1)*행렬C(1x100)일 때,
(AB)C를 계산하는데 100+100=200번이지만 A(BC)를 계산하는데 10000+10000=20000번입니다.

곱셈 연산의 횟수는 어떻게 구하나요?
행렬 A1(p0xp1) 행렬 A2(p1xp2)라고 하면, 곱셈 연산의 횟수는 p0*p1*p2입니다.
반복문을 통해서 구현해 보면 앞 행렬의 행과 열의 개수만큼 루프를 돌면서 
내부적으로 뒤 행렬의 열의 개수만큼 루프를 돌아야 하기 때문에 숫자 3개의 곱으로 계산합니다.

7.4.2분할 정복 알고리즘의 적용:행렬이 4개인 경우
예로 4개의 행렬 A, B, C, D 중 A와 C는 100x1, 행렬 B와 D는 1x100행렬이라고 가정.
'마지막으로 곱한 행렬을 어떻게 정하느냐'를 탐색의 기준으로.
D, CD, BCD가 마지막으로 곱할 수 있습니다.
하지만 ABC, BCD는 다시 곱셈 순서가 여러개 있을 수 있습니다.
이 경우에도 '마지막 곱셈 행렬을 어떻게 정하느냐'가 하위 문제로 쪼개는 기준.
합치면 행렬이 4개인 경우 모두 5가지의 경우가 있습니다.
마지막이 D:((AB)C)D, (A(BC))D
마지막이 CD:(AB)(CD)
마지막이 BCD:A((BC)D) A(B(CD))

반드시 2개의 항이 필요한 곱하기 연산의 특성상 행렬을 2개 이하로는 더 나눌 수 없습니다.
이렇게 분할된 하위 문제를 차례로 정복할 단계입니다.
앞서 구한 각 하위 문제에 몇 번의 곱셈 연산이 필요한지 계산합니다.
그리고 구한 곱셈 횟수를 비교하여 연산 횟수가 가장 작은 순서대로 병합합니다.
A(BC), (BC)D가 곱셈 연산 횟수 200번으로 각각 선택됩니다.
그다음 단계의 병합 과정을 통해 (A(BC))D, A((BC)D)가 10200번씩 최소 곱셈 연산으로 선택됩니다.

7.4.3일반적인 경우에 분할 정복 알고리즘의 적용
행렬의 개수가 n개라면 n가지 경우로 나눌 수 있습니다.
마지막으로 곱할 행렬:An, (An-1An), .., (A3...An), (A2A3...An)
Ci,j:행렬 Ai부터 행렬 Aj까지의 최소 곱셈 연산 횟수
n개의 연쇄 행렬에 대한 곱셈 문제가 2개의 하위 문제로 나누어졌을 때 가장 일반적인 경우는
k와 n-k로 나뉜 경우입니다:(A1...Ak)(Ak+1...An)
C1,k+Ck+1,n+행렬(A1...Ak)와 행렬(Ak+1...An)을 곱할 때 곱셈 연산 횟수
C1,k와 Ck+1,n은 앞 행렬과 뒤 행렬 자체에 대한 곱셈 연산 횟수.
마지막은 앞 행렬과 뒤 행렬을 서로 곱할 때 필요한 곱셈 연산 횟수.

행렬Ai의 행의 개수:pi-1
행렬Ai의 열의 개수:pi
2개의 행렬을 곱하려면 앞 행렬의 열의 개수와 뒤 행렬의 행의 개수가 같아야 합니다.
행렬 A1과 A2를 곱할 때 필요한 곱셈 연산 횟수:p0*p1*p2
(A1,...,Ak)와 (Ak+1,...,An)을 곱할 때 필요한 곱셈 연산은
앞의 행의 개수:p0(A1의 행의 개수)   열의 개수:pk(Ak의 열의 개수)
뒤의 행의 개수:pk(Ak+1의 행의 개수) 열의 개수:pn(An의 열의 개수)
따라서 p0*pk*pn
'연쇄 행렬 자체'의 행의 개수는 가장 앞 행렬의 행의 개수이고 열의 개수는 가장 뒤 행렬의 열의 개수.

모든 하위 문제에 대해서 곱셈 연산 횟수를 구하고 그중에서 최솟값을 택한다는 뜻
C1,n=min(1<=k<=n){C1,k+Ck+1,n+p0*pk*pn}
이 식에서 k가 1부터 n까지 바뀌면서 n가지의 경우의 수가 나옵니다.
n가지의 경우 각각에 대해서 최소 곱셈 연산 횟수를 구합니다.
그리고 min{} 식을 통해 최솟값을 구합니다.
즉, n개의 행렬을 '마지막 행렬 곱셈의 기준'에 따라 나누어지는 각각의 하위 문제들 중에서 최솟값을 선택
다시 바꿔 Ci,j=                                 0, i=j 행렬이 1개이므로 곱셈 연산이 필요 없다.
             =min(i<=k<=j){C1,k+Ck+1,j+pi-1*pk*pj}, i<j

분할 정복 알고리즘의 의사코드
p:행렬의 행과 열 개수가 저장된 배열
i:시작 행렬의 인덱스
j:마지막 행렬의 인덱스
minimumMatrixChainRecursive(p,i,j){
	if(i==j){
		result<-0
		return result
	}

	for(k:i부터 j-1까지){
		value<-minimumMatrixChainRecursive(p,i,k)
			+minimumMatrixChainRecursive(p,k+1,j)
			+p[i-1]*p[k]*p[j]

		if(value<result){
			result<-value
		}
	}
	return result
}
		
분할 정복 알고리즘의 성능은 행렬의 개수 n에 대해서 지수적으로 증가합니다.
재귀 호출의 중복 문제로 시간 복잡도가 O(2^n)입니다.
같은 재귀 호출로 인해 같은 하위 문제가 여러 개 생기면서 실제 함수 수행 시간이 비약적으로 커지는 현상.
뒤에 동적 계획법이 이러한 분할 정복 알고리즘의 약점을 보완할 수 있습니다.

퀵정렬과 병합 정렬이 분할 정복 알고리즘입니다.
병합 정렬은 더 이상 쪼갤 수 없을 때까지 자료를 나눈 다음 이를 차례로 병합하면서 정렬을 수행
퀵 정렬은 피봇을 기준으로 분할과 정복을 수행
피봇을 중심으로 왼쪽은 피봇보다 작은 값이, 오른쪽은 피봇보다 큰 값이 오도록 자료의 위치를 교환.
피봇을 중심으로 2개의 부분 집합으로 쪼개면서 각 부분 집합에 대해 다시 퀵 정렬을 수행하면서 정복을 실시

*/