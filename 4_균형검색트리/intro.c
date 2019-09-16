/*
균형 검색 트리는 검색 트리(Search Tree)의 한 종류로, 스스로 균형을 유지하는 검색 트리를 말합니다.
대표적인 것은 B트리.

균형 검색 트리는 많은 자료를 추가하고 삭제하는 환경에서도 빠른 검색 성능을 제공.
데이터베이스 시스템에 쓰인다.
많은 자료가 일시에 없어지기도 하고 또 한꺼번에 많은 자료가 새롭게 추가되기도 하는것에 빠른 검색이 가능.

4.1이진 검색 트리
Bynary search tree는 자식 노드가 2개 이하인 검색 트리를 말합니다.
이진 검색 트리는 왼쪽 서브트리의 모든 키 값이 현재 노드의 키 값보다 작습니다.
오른쪽 서브트리의 모든 키 값이 현재 노드의 키 값보다 큽니다.
때문에 모든 노드는 유일한 키 값을 가지고 효율적인 검색이 가능.
하지만, 자료가 추가되거나 삭제되었을 때 균형을 유지할 알고리즘이 없습니다.
불균형하게 되면 균형 상태에 비해서 검색 성능이 떨어지게 됩니다.

자료가 어느 한 쪽으로만 치우치지 않고 골고루 분포한 상태로 저장:균형 상태
자료가 추가되는 순서에 따라 균형 트리가 되기도 하고 불균형이 되기도 합니다.

균형이진 검색 트리는 불균형 이진 검색트리보다 검색 시간이 적게 걸립니다.
각 값을 검색하는데 필요한 횟수의 평균을 구해보면
균형:O(log n)
불균형:O(n)

불균형 상태라면 구조적으로는 리스트와 같은 선형 구조가 됩니다.
균형 상태라면 비선형 구조라는 트리의 본래 특성을 이용할 수 있어서 시간 복잡도가 O(log n)

불균형 문제를 해결할 자료구조로 AVL tree, Red-black tree등이 있습니다.
자료가 추가되거나 제거되는 순서에 상관없이 트리의 균형 상태를 유지합니다.
하지만, 여전히 이진 트리기 때문에 저장하는 자료의 개수가 증가함에 따라 트리의 높이가 높아집니다.
트리 높이가 특별히 검색 성능과 관련하여 문제가 될 때는 트리 노드가 디스크에 저장된 경우입니다.
예)데이터베이스에서 자료 1개의 크기가 커서 노드 단위로 디스크에 저장합니다.
그리고 비교 연산이 필요한 경우에 해당 노드를 디스크에서 읽어들여 메모리로 적재(Loading)합니다.
노드별 비교 연산을 위해서 먼저 디스크를 읽는 연산이 필요합니다.
트리가 높아지면 디스크에서 자료를 읽는 횟수가 증가하여 상당한 성능 저하가 일어날 수 있습니다.

이를 해결하기 위해 다윈 검색 트리가 있습니다.
다윈 검색 트리는 각 노드가 여러 개의 자료를 가질 수 있고 자식 노드의 개수 또한 2보다 큰 값으로 설정
할 수 있기 떄문에 이진 트리의 높이 문제를 해결할 수 있습니다.
예) .    4    .    8    .    12    .             15개 자료를 저장. 노드마다 최대 3개의 자료저장.
   /           \         \          \            각 노드는 자식 노드를 최대 4개까지
 '1'2'3'       '5'6'7'   '9'10'11'  '13'14'15'  높이는 2.

하지만 스스로 균형을 유지하지 못합니다. 자료를 추가하거나 삭제하는 순서에 따라 불균형이 발생.
결국, 대량의 자료를 일정한 속도로 빠르게 검색하려면 다윈 검색 트리인 동시에 스스로 균형을 유지
해야 합니다. 그것이 균형 다윈 검색 트리이고 B트리가 대표적인 예입니다.

이진 검색트리         자료 개수 증가      다윈 검색 트리
	| 균형 유지       ----------->             | 균형 유지
균형 이진 검색 트리    트리 높이 증가      균형 다윈 검색 트리
:AVL, 레드 블랙 트리                     :B트리

4.2다윈 검색 트리
다윈 검색 트리는 m-원 검색 트리(m-way search tree)라고도 합니다.
한 노드 안에 여러 개의 자료를 가질 수 있으며 자식 노드 또한 여러 개 가질 수 있습니다.
특성
1)각 노드는 0에서 최대 m개의 서브트리를 가진다.
2)k개의 자식 노드를 가지는 노드는 (k-1)개의 자료를 가진다. (단, k<=m)
3)각 노드 안에 있는 자료는 검색 키로 정렬된다.
key1<=key2<=...<=key(k-1)
4)다음 조건을 항상 만족한다.
key i<=(i번째 서브 트리 내의 모든 키 값)<key (i+1)
5)모든 서브트리는 m-원 검색 트리다.

1)m-원은 m개 혹은 어러 개라는 뜻입니다. 다윈 검색 트리에서 m이란 하나의 노드가 가질 수 있는
자식 노드의 최대 개수를 말합니다. 각 노드는 자식 노드를 최대 m까지 가질 수 있다는 뜻.
노드의 링크 부분도 m개라는 것을 의미.

2)자식 노드가 k개라면 저장할 수 있는 자료의 개수는 k-1개가 됩니다.
다윈 검색 트리에서 각 노드가 몇 개의 자료를 저장할 수 있는지에 대한 조건
k의 최댓값은 m이고, 각 노드가 저장할 수 있는 최대 자료의 개수는 m-1개입니다.

3)각 노드 안에 저장된 자료들은 정렬되어 있습니다. 오름차순이라고 가정하고 있습니다.
노드에 저장되는 키 값들도 오름차순으로 저장됩니다. 저장된 자료가 K1,K2,K3라면 K1<=K2<=K3.

4)핵심이 되는 부분
다윈 검색 트리의 i번째 서브트리는 부모 노드의 i번째 자료보다 크거나 같고 i+1번째 자료보다 작아야합니다.
......key K1.....key K2.....
			  |
		  K1<=key<K2

5)각 서브트리는 당연히 다윈 검색 트리가 됩니다.

4.3B-트리
다윈 검색 트리의 종류 중 하나로 자료를 추가하거나 삭제할 때 스스로 트리의 균형을 유지하는 균형 검색트리
특성
1)루트 노드는 단말(leaf) 노드거나 2개~m개의 서브트리를 가진다.
2)루트 노드를 제외한 모든 내부(internal)노드는 아래의 개수만큼 서브트리를 가진다.
올림(m/2)<=(서브트리의 개수)<=m
3)단말 노드는 아래의 개수만큼 자료를 가진다.
올림(m/2)-1<=(자료의 개수)<=m-1
4)모든 단말 노드는 같은 레벨에 있다. 즉 트리는 완전한 균형 상태에 있도록 한다.

1)B-트리의 루트 노드는 자식 노드가 없거나 있다면 2개에서 m개의 자식 노드를 가집니다.
자식 노드가 1개일 수는 없습니다.
다윈 검색 트리의 노드는 최대 m-1개의 자료를 저장할 수 있었습니다.
다윈 검색 트리의 노드가 저장할 수 있는 자료의 개수가 m-1개 이하라면 자식노드가 필요없습니다.
그러나 B트리에서 중요한 점은 루트 노드에 저장할 수 있는 자료의 개수가 m개라면
자식 노드는 2개가 되어야 한다는 점입니다.

3)올림(m/2)-1<=(자료의 개수)<=m-1
m=5이고 자료가 4개에서 한개가 추가가 되면
식에 따라 자료의 개수는 2이상 3이하여야 합니다. 루트에 1개(중간 값) 나머지 두 자식노드에 2개씩 분배.
루트 노드는 단말 노드가 아니기 때문에 1개의 자료만 저장할 수 있습니다.

4)B트리의 모든 단말 노드는 같은 레벨입니다.
B트리는 빠른 검색 속도를 위해서 완전한 균형 상태에 있어야합니다.

2)올림(m/2)<=서브트리의 개수)<=m
m의 값에 따라 노드에 저장되는 자료의 개수 및 서브트리의 개수가 정해집니다.
	서브트리의 개수	자료의 개수
m	최소   최대		최소	   최대
3    2      3        1      2
4    2      4        1      3
5    3		5        2      4
m 올림(m/2) m   올림(m/2)-1  m-1

4.4B-트리의 연산
4.4.1B-트리에서의 자료 추가
3단계로 나누어집니다. 저장할 위치를 찾는 단계, 실제자료를 저장하는 단계, 균형 유지 단계.

4.4.1위치 찾기
적절한 추가 위치를 찾기 위해 B-트리를 검색합니다.
추가하려는 자료의 값과 현재 노드에 저장된 자료의 값을 비교합니다.
새로운 값이 크면 오른쪽으로 한 칸 더 이동, 노드에 모든 자료보다 크면 오른쪽 서브트리로 이동.
더 이상 서브트리로 이동할 수 없는 곳에 새로운 자료를 추가.
Key i<=(i번째 서브트리 내의 모든 키 값)<Key (i+1)
결국 새로운 자료는 말단 노드에서만 저장할 수 있습니다.

4.4.1.2자료 저장
삽입하려는 노드에 공간이 있다면 자료 삽입
하지만, 꽉 찼다면 노드의 분할을 이용

4.4.1.3노드의 분할
1개의 노드를 여러 개의 노드로 나누어서 새로운 자료를 추가할 여유 공간을 확보하는 것.
먼저, 노드를 분할하기 전에 임의로 정한 새로운 키 값을 노드에 추가합니다. (가상으로)
그 다음, 노드의 중간값(Median)을 기준으로 기존 노드를 2개로 분할(Split)합니다.
단, 중간값은 부모 노드(Parent node)로 올려 보냅니다.
기존 노드가 이미 루트 노드일 때는 중간 값을 올려 보낼 부모 노드가 없습니다.
그럴 때는 새로운 루트 노드를 만들어서 자료를 추가합니다.
이렇게 중간값 노드를 올려 보내 새로운 루트 노드를 추가하면 트리의 깊이 혹은 높이가 1 증가합니다.
자식 노드에서 분할이 발생하여 부모 노드로 새로운 자료를 보낸 경우 순환적으로 분할이 발생할 수 있습니다.
만약, 최종적으로 더 이상 보낼 부모 노드가 없다면 새로운 루트 노드를 생성합니다.
새로운 루트 노드가 생성되면 트리의 전체 깊이 혹은 높이가 1씩 커집니다.
이러한 삽입과 분할 연산으로 균형 상태를 유지할 수 있습니다.

4.4.2B-트리에서의 자료 제거
3단계, 제거할 자료의 위치를 찾는 단계, 실제 자료를 삭제하는 단계, 균형 유지 단계

4.4.2.1위치 찾기
새로운 자료를 추가하는 연산에서 같은 검색 단계
노드에 저장된 자료의 값과 비교 연산을 통해 제거 대상을 찾습니다.

4.4.2.2자료 삭제
자료 삭제는 트리의 균형을 유지하기 위해 모두 말단 노드에서만 발생해야 합니다.
제거하려는 자료가 말단 노드에 있다면 단순히 자료만 제거하면 됩니다.
그다음 삭제한 자료의 오른쪽 자료를 왼쪽으로 한 칸씩 옮겨 주면 됩니다.

삭제하려는 자료가 내부 노드에 있다면 자료를 삭제한 빈자리로 대체 자료를 이동시켜야 하기 때문에
말단 노드에서 대체 자료를 먼저 찾아야 합니다.
왼쪽 서브트리의 가장 오른쪽 자료 혹은 오른쪽 서브트리의 가장 왼쪽 자료가 대체자료입니다.
대체자료를 올리게 되면 최소 자료 저장 개수가 부족할 수 있습니다.
그래서 자료의 삭제 후에 추가적인 균형 유지 연산이 필요합니다.
여기서 중요한 점은 왼쪽 서브트리의 가장 오른쪽 자료이기 때문에 단순히 자식 노드가 아니라,
후손 노드일 수 있다는 점입니다. 즉, 자식의 자식 노드도 고려해야 합니다.

물론 2번(서브트리수) 3번(자료의 개수)의 특성을 만족하면 유지하는 단계가 필요없습니다.

4.4.2.3균형 유지
B-트리는 노드에 저장하는 자료의 개수가 적은 경우, 균형 유지 연산은
1)왼쪽에서 빌리기, 2)오른쪽에서 빌리기, 3)병합의 3가지로 이루어집니다.

1)왼쪽에서 빌리기
  .  .  50  .  .
	/        \
  '10'20'30' '70'  '

a)오른쪽 노드의 자료를 오른쪽으로 1칸 이동
  .  .  50  .  .
	/        \
  '10'20'30' '  '70'
b)부모 노드에서 오른쪽 노드로 이동
  .  .      .  .
	/        \
  '10'20'30' '50'70'
c)왼쪽 노드에서 부모 노드로 이동
  .  .  30  .  .
	/        \
  '10'20'  ' '50'70'
결국 왼쪽 노드의 가장 오른쪽 자료를 부모 노드로 밀어내고, 부모 노드의 값은 오른쪽 노드로 밀어냅니다.

2)오른쪽에서 빌리기
  .  .  50  .  .
	/        \
  '10'  '   '60'70'80'

a)부모 노드에서 왼쪽 노드로 이동
  .  .      .  .
	/        \
  '10'50'   '60'70'80'
b)오른쪽 노드에서 부모 노드로 이동
  .  .  60  .  .
	/        \
  '10'50'   '  '70'80'
c)오른쪽 노드의 자료를 왼쪽으롤 이동
  .  .  60  .  .
	/        \
  '10'50'    '70'80'
결국 부모 노드의 값은 왼쪽 노드로 밀어내고 오른쪽 노드의 가장 왼쪽 자료를 부모 노드로 밀어냅니다.

만약 왼쪽이나 오른쪽 노드 모두 빌려줄 여유가 없다면 노드 병합을 이용해야합니다.

3)병합
노드 병합은 두 개의 자식 노드(Child node)와 부모 노드의 한 자료를 합쳐서 새로운 왼쪽 노드가 되는 것.
두 자식 노드의 부모 노드에서 한 자료란 이들 두 자식 노드를 서브트리로 가지는 자료입니다.(50)

  .  20  .  50  .  90  .
		/        \
	   /          \
	.40.42.      .60.
				/    \
			   /      \
			 .52.54. .62.64.

a)부모 자료를 왼쪽 노드로 이동
  .  20  .      .  90  .
		/        \
	   /          \
	.40.42.50.   .60.
			/ 	     \
		   /          \
		 .52.54.     .62.64.
이때 기존 오른쪽 노드의 왼쪽 서브트리를 새로 이동한 부모 자료의 오른쪽 서브트리로 변경합니다.

b)오른쪽 노드의 자료를 왼쪽 노드로 이동
  .  20  .      .  90  .
		/
	   /
	.40.42.50.60.
			/    \
		   /      \
		 .52.54. .62.64.

c)부모의 노드의 자료를 이동
  .  20  .  90  .
		/
	   /
	.40.42.50.60.
			/    \
		   /      \
		 .52.54. .62.64.

병합과정을 거치며 기존 루트 노드를 제거하면 트리의 전체 깊이 혹은 높이가 1감소합니다.
트리의 모든 노드가 균형을 유지할 때까지 균형 유지 연산은 여러 번 실행할 수 있습니다.

4.6간단한 형태의 B-트리

4.6.1 2-3 트리
차수 m이 3인 B-트리를 말합니다. 서브트리=2~3    자료의 개수=1~2
모든 단말 노드는 같은 레벨에 있습니다.
항상 완전한 균형 상태

4.6.2 2-3-4 트리
차수 m이 4인 B-트리를 말합니다. 서브트리=2~4    자료의 개수=1~3
항상 균형 상태.

4.7B-트리의 변형

4.7.1B+트리
B+트리는 저장된 자료에 순차적(Sequential) 접근할 수 있습니다.
B-트리가 빠른 검색 성능은 제공하지만, 저장된 자료에 차례대로 접근하기는 어렵습니다.
B-트리에서 순차적 접근을 하려면 중위 순환(Inorder)라는 트리 구조 내부를 오르락내리락하는 복잡한 과정.
이를 해결하기 위한 B+트리

1)모든 내부 노드는 (자료의)키 값만 저장하고 각 자료의 데이터는 오직 말단 노드에만 저장된다.
=>따라서 말단 노드에 저장된 키와 동일한 키를 저장하는 내부 노드도 있을 수 있다.
2)각 말단 노드는 다음 형제 노드에 대한 포인터를 가지고 있어, 순차적으로 접근할 수 있다.


말단 노드에서만 자료를 저장, 내부 노드(루트 노드)에서는 오직 키만 저장
각 말단 노드는 이웃한 노드와 연결되어 있어 순차적으로 접근.

                       .  .  19    .  63     .  .
				      /            |          \
					 /             |           \
				  ''9'12''----''19'36'39''-''63'65'89''
D:Data  		    D  D         D  D D      D   D  D
                        9-12-19-36-39-63-65-89

4.7.2B*트리
실제 시스템에서는 대용량의 자료를 저장하기 위해 차수 m이 5이상인 B-트리를 주로 사용합니다.
반면 실제로 운영해보면 전체 노드의 약 50%정도가 비게 됩니다.
왜냐하면 B-트리의 기본 특성에 따라 노드를 분할하기 때문입니다.
따라서 불필요한 공간(메모리)의 낭비가 발생하게 됩니다.
B*트리는 이러한 B-트리의 메모리 비효율성을 해결하기 위해 이런 특성을 갖습니다.
1)루트 노드가 아닌 노드는 최대 저장 공간의 2/3이상의 자료가 저장되어야 한다.
=>B-트리에서는 조건(올림(m/2)-1)에 따라 최소 1/2이상의 자료가 저장되어야 했다.
2)노드에 저장된 자료가 넘치는 경우(overflow), 형제 노드로 재분배시킨다.
모든 형제 노드가 가득 찼을 때만 분할이 발생한다.
=>B-트리는 중간값을 가지는 자료를 부모 노드로 올려 보내고 분할하였다.

          .   19   .   63   .                           .   21   .   63   .                    
		 /        /          \      +25  ---->         /        /          \
        /        /            \                       /        /            \
      '9'12'   '21'23'36'39'  '65'89'               '9'12'19''23'25'36'39' '65'89'
	                 
*/