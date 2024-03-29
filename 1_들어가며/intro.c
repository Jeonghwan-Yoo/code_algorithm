/*
알고리즘은 문제를 해결하기 위한 '효율적인' 절차를 말합니다.

1.1이 책에서 다루는 알고리즘
주로 문제가 미리 정해져 있고 그에 따른 효율적인 해결책을 제시하는 알고리즘들
문제를 해결하는 방법.

1.2알고리즘의 성능 평가
성능이란 얼마만큼 빨리 문제를 풀었는지를 의미합니다.
즉, 알고리즘의 성능을 평가하는 대표적 기준은 바로 시간입니다.

1.2.1시간 복잡도
객관적인 지표=>시간복잡도
입력 값에 따라 알고리즘의 실행에 걸리는 시간을 말하는데 연산의 실행 횟수를 말한다.
만약 입력 값으로 n(자료의 개수)이 주어졌다면 알고리즘을 실행하는 데 필요한 연산의 실행 횟수.
시간 복잡도:입력 값에 따른 연산의 실행 횟수.

1.2.2점근적 표기:빅-오 표기법
시간 복잡도 함수 중에서 가장 큰 영향력을 주는 'n에 대한 항'만을 표시.
또한, 최고차항들의 증가율 특성 때문에 '점근적 표기'에서는 보통 최고 차항에 붙은 계수 또한 무시.
O(1) > O(log n) > O(n) > O(nlog n) > O(n^2) > O(2^n) > O(n!)

1.2.3점근적 표기의 다른 방법들
빅-오:상한 표기(upper bound); 성능이 빅오보다 더 좋다
빅-오메가:하한 표기(lower bound); 성능이 빅오메가보다 더 나쁘다
빅-세타:상한과 하한을 동시 표기; 성능이 빅세타 범위 안에 있다
알고리즘은 얼만큼 빠른가가 중요하고 성능의 상한은 빠름의 한계. 따라서 빅오를 많이 씁니다.
빅오의 수학적 정의.
두 개의 함수 f(n)과 g(n)이 주어졌을 때 모든 n>=n0에 대해 |f(n)|<=c|g(n)|을 만족하는 
2개의 상수 c와 n0가 존재하면 f(n)=O(g(n))이다.
n0보다 큰 값에 대해 시간 복잡도 함수 f(n)보다 항상 성능이 나쁜 상한을 정의하고 있습니다.
공간 복잡도는 알고리즘 실행에 필요한 저장  공간이 얼마만큼 필요한지를 나타낸 것.
*/