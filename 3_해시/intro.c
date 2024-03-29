/*
해시는 검색 분야에서 많이 사용할 뿐 아니라 전자 서명과 같은 보안 분야에서도 사용합니다.
하나의 큰 자료를 작은 값으로 분해하고 조합해서 새로운 자료로 만든 것이 해시.
값이 작고, 새로운 값은 다른 값과 구별할 수 있는 독특한 값.
즉, 원래의 자료를 구별가능한 작은 값으로 만든 것이 해시.

3.1해시의 개념
해시(Hash)는 계산 과정을 거치면서 작아진 값.
해시는 어떤 과정을 거치면서 작아진 '값'이여서 해시값이라고도 한다. 또는 해시 코드.

3.1.1해시 함수
입력값->해시 함수->해시값
입력 값을 가지고, 더하기, 곱하기 등 여러 연산을 통해 고유한 해시를 만드는 것이 해시 함수.
이렇게 산출된 해시는 다른 해시와 구별되는 고유한 값이어야 합니다.
해싱(Hashing)은 해시값을 구하는 과정.

3.1.2해시 검색
해시 검색(Search by hashing)은 해시를 이용하여 검색한다.
다른 검색 알고리즘과 비교하여 검색 속도가 월등히 빠르다.
검색 키(Search key)란 내가 찾고자 하는 자료를 가리키는 값. 예)학번.
즉, 해시 검색은 검색 키에 대해 해시를 계산하여 검색하는 방법.
해시 함수로 계산한 주소에 따라 자료를 저장하는 자료 구조를 해시 테이블(Hash table).
보통 배열을 선호합니다.
해시 테이블은 N개의 버킷(Bucket)으로 이루어져 있습니다. 버킷은 해시 테이블에서 자료를 저장하는 단위.
즉, 해시 검색에서 해시는 이러한 버킷을 가리키는 주솟값.
검색 키(입력)->해시 함수->주소(해시)->해시 테이블에 있는 버킷.
하지만, 버킷은 저장 단위이므로, 여러 개의 자료를 저장할 수도 있습니다.
슬롯이란 버킷 내에서 여러 개의 자료를 저장할 경우 각 자료가 저장되는 단위.
1개의 버킷에 M개의 슬롯(Slot)이 있을 수 있다.

해시 함수는 검색 키를 입력 값으로 단순 계산만 하면 되기 때문에 최소 O(1)입니다.
즉, 가장 큰 장점은 자료의 개수 n과 상관없이 특정한 상수를 시간 내에 계산할 수 있다.
검색 키에 대해서 주소를 직접 계산하고 검색하는 것을 '계산 검색 방법' 
해시 이외에 순차 검색, B-트리 등은 검색 키 값을 하나씩 비교해서 찾습니다. '비교 검색 방법'
비교 검색 방법은 빨라도 평균 시간 복잡도 O(log n). 자료의 개수가 증가하면 개수에 비례하여 느려짐.
따라서 검색 성능 면에서는 해시 검색>비교 검색 하지만 제약이 있다.

3.1.3해시 검색의 과정
3.1.3.1자료 추가
해시 검색을 하려면 먼저 자료가 해시 테이블에 저장되어 있어야 합니다.
1단계는 전달 받은 '검색 키'로 자료를 저장할 버킷의 주소를 계산합니다.
2단계는 앞서 계산된 주소를 가지고 해시 테이블을 확인합니다.
자료가 없으면 바로 자료를 저장, 있어서 저장하지 못하는 경우는 충돌(Collision).
충돌에 대처하기 위한 다양한 방법이 존재.
3단계는 실제 해시 테이블에 자료를 저장하는 단계입니다.

3.1.3.2자료 검색
1단계는 해시 함수를 이용하여 검색 키에 대한 주소를 계산합니다.
2단계는 계산한 주소를 이용하여 해시 테이블에 정말 그자료가 저장되어 있는지 확인합니다.
있으면 성공 없으면 실패.

3.2해시 함수
해시 검색의 핵심은 해시 함수입니다. 성능을 결정하기 때문.
좋은 해시 함수는 해시의 충돌이 드물게 발생할수록 좋습니다. 충돌이 발생하면 주소를 다시 계산해 느려진다.
충돌이 안 발생하면 해시 테이블을 고르게 사용한다는 뜻이어서 공간 활용 측면에서도 좋습니다.
즉, 충돌 발생 빈도와 해시 테이블 사용률은 반비례 관계.
가능한 빨리 주소를 계산해야 검색 시간이 단축.
1. 낮은 충돌 발생 빈도, 2. 높은 해시 테이블 사용률, 3. 빠른 계산 시간.

3.2.1나머지(Division) 함수
가장 쉽게 사용할 수 있는 함수는 나머지 함수(Division function)입니다.
M개의 자료를 저장할 수 있는 해시 테이블과 검색 키가 k인 자료가 해시 함수로 계산한 주소는 k%M입니다.
나머지 함수는 어떤 크기의 해시 테이블에서도 사용할 수 있습니다.
다만, 테이블 크기 M이 소수(Prime number)일수록 충돌 발생 빈도가 낮아집니다. 사용률은 높아집니다.
따라서, 나머지 함수를 이용할 때는 가능한 한 테이블의 크기를 소수로 하는 것을 권장.
예로 테이블의 크기가 100이면 큰 소수인 101을 권장.

3.2.2접기(Folding) 함수
검색 키를 먼저 분해하고 분해된 부분들을 조합하여 해시를 만드는 함수 방법을 말합니다.
보통 검색 키의 크기가 해시 테이블의 크기보다 큰 경우에 사용.
세부 구현 방법에 따라서 다양한 적용이 가능.
접기 함수는 검색 키 값 k를 M의 자릿수와 같은 크기로 먼저 분해합니다. k>M
그런 다음 여러 개로 분해된 키 값들을 이용하여 하나의 해시로 조합합니다.

3.2.2.1이동 접기 함수(Shift folding function)
이동 접기 함수는 분해된 부분들을 이동시킨 다음에 각 부분을 조합하는 접기 방법을 말합니다.
분해된 각 부분은 보통 오른쪽 맞춤으로 정렬하여 끝자리를 기준으로 일렬이 되도록 만듭니다.
그리고 이렇게 일치시킨 부분들을 '더하기' 연산을 통해서 조합합니다.

예로 검색키 1234512345 10자리와 테이블의 크기 999로 3자리라고 합니다.
분해하기:123 451 234 5이렇게 테이블의 크기로 검색 키를 분해합니다.
이동하기 및 더하기:오른쪽으로 맞추고 전체 더한 값 813이 위치 값. 
넘치면 초과한 자리수를 버립니다. 예로 1234면 234로.

3.2.2.2경계 접기 함수(Boundary folding function)
이동하기 부분에서 차이가 있으며 분해하기 및 더하기는 같다.
핵심은 분할된 부분 중에서 '경계 부분'을 선택하여 '숫자 뒤집기' 처리를 합니다.
분해하기:123 451 234 5에서 기준은 가장 오른쪽에 5. 5전에 234가 경계 부분, 그 전전인 123가 경계 부분.
이동하기:오른쪽 맞춤으로 이동, 경계 부분은 먼저 '뒤집기'처리 321 451 432 5
뒤집는 것은 기존 숫자의 자리수를 변경함으로써 충돌 확률을 찾추기 위해서.
더하기:321+451+432+5=1209에서 초과된 자릿수는 버리고 209.

3.2.3중간 제곱 함수(Mid-square function)
검색 키의 일부분에서 해시를 채취하는 방법입니다.
그러나 원래의 검색 키에서 값을 추출하는 것이 아니라 먼저 검색 키의 제곱 값을 구합니다.
그리고는 제곱된 값 중에서 중간 부분을 잘라내어 해시 테이블 주소로 이용합니다.
예로 k;9415 M;9999 에서 k를 제곱하면 89321401. 중간의 4개 3214가 해시.

3.2.4숫자 분석 기반의 해시 함수
검색 키가 어떠한 특징이 있는지 검색 키의 특성을 알아낸다는 뜻.
즉, 해시 함수는 충돌이 발생할 가능성이 낮아지도록 검색 키가 가지는 '값의 분포'를 이용한 함수.
먼저 각 자릿수의 분포를 분석.
충돌 발생 가능성이 낮은 자릿수만 입력 값으로 사용합니다. '고르게 분포'되었다.
숫자 분석 기반의 해시 함수는 분석기법이어서 다른 기법을 사용하는 해시 함수와 함께 사용.
이외에도 진법 변환 함수, 비트 추출 함수, 가상 난수 기법 등을 해시 함수로 사용.

문자열인 경우는 문자마다 자신의 코드 값이 있기 때문에 코드 값을 이용합니다.
첫 번째 문자를 이용:ABC이면 A->65 충돌 확률 높음.
문자열을 이루는 모든 문자열의 코드 값을 더하는 방법:ABC이면 65+66+67=198. 순서 바뀌면 충돌
단순히 문자의 값만 더하기 때문에 문자열 내의 문자 위치가 제대로 반영되지 않는다.
문자열을 이루는 각 문자의 코드 값을 자신의 위치에 해당하는 값과 곱하여 더하는 방법으로,
보통 호너의 방법(Horner's method):ABC->((65*31)+66)*31+67=64578 31은 예
오버플로우가 발생할 수 있는데, 자릿수를 버림으로써 테이블 범위 내에 들어가도록 적절히 조치.

다양한 해시 함수 중에서도 문제에 적합한 해시 함수를 잘 선택해야만 충돌의 발생을 최소화할 수 있다.
아무리 좋아도 저장되는 자료의 특성 등에 따라 간혹 충돌이 발생할 수도 있습니다.
참고로, 자료들이 해시 테이블에 고르게 분포되지 않고 특정 주소들 주위로 뭉치게 되는 현상을 군집화.
군집화(클러스터링:Clustering)은 충돌에 의해 일어나는 현상이고 성능을 급속히 감소.

*/