#include <iostream>
#include <time.h>

using namespace std;

int main() 
{

	/*
	배열 : 여러개의 변수를 한번에 생성해줄 수 있는 기능이다.
	형태 : 변수타입 배열명[개수]; 의 형태로 선언할 수 있다.
	배열의 특징 : 배열은 연속된 메모리 블럭에 공간이 할당된다.
	배열은 인덱스를 이용해서 원하는 부분에 접근하여 값을 저장할 수 있다.
	인덱스는 0부터 개수-1 까지이다. 즉, 10개라면 0~9까지의 총 10개의 인덱스를 가지게 된다.
	*/

	//배열 뿐만 아니라 일반 변수들도 선언만 하고 값을 초기화하지 않을 경우 
	//쓰레기 값이 들어간다.
	/* 초기화 방법
	int iArray[10] = { 1,2,3,4,5,6,7,8,9,10 };	순서대로 0~9번 인덱스까지 대입
	int iArray[10] = {1,2,3,4,5};	0~4번까지 1,2,3,4,5 넣고 나머지는 0으로 초기화.
	int iArray[10] = {};	모두 0으로 초기화.
	*/
	int iArray[10] = {};

	iArray[1] = 1234;

	cout << iArray[5] << endl;

	for (int i = 0; i < 10; i++)
	{
		cout << iArray[i] << endl;
	}

	/*
	배열 개수를 2개 지정하면 이차원 배열이 된다. 3개 지정하면 3차원 배열이 된다.
	2차원 배열의 개수는 앞의수 * 뒤의수 만큼 처리가 된다. 아래는 10 * 10개의 배열이
	생성이 된다.
	*/
	//위처럼 전체초기화도 가능하고 부분부분 초기화도 가능하다.
	int iArray2[10][10] = { {1,2,3},{4,5,6} };
	//iArray[0][0~2]는 1,2,3이 대입되고, iArray[1][0~2]는 4,5,6이 대입되는식
	//괄호를 기준으로 앞배열 순서라고 보면 된다.

	//출력
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			cout << iArray2[i][j] << '\t';
		}
		cout << endl;
	}

	system("cls");
	


	srand((unsigned int)time(0));

	// Lotto Program
	// ** 카드게임류에 가장 많이 사용하는 스왑 알고리즘 + 셔플 알고리즘을 쓴다. **
	int iLotto[45] = {};

	// 1~45까지의 숫자를 차례대로 넣어준다.
	for (int i = 0; i < 45; ++i)
	{
		iLotto[i] = i + 1;
	}

	// Swap 알고리즘  예 (값 위치 변경)
	int iNum1 = 1, iNum2 = 2, iNum3;
	iNum3 = iNum1;
	iNum1 = iNum2;
	iNum2 = iNum3;
	//빈 변수를 확용해 1과 2의 값의 위치를 바꾼것

	// Shuffle
	int iTemp, idx1, idx2;

	for (int i = 0; i < 100; ++i) // 100번 쉐킷쉐킷
	{
		idx1 = rand() % 45;
		idx2 = rand() % 45;  // 0~44의 난수 즉 배열의 랜덤위치를 얻는다.

		iTemp = iLotto[idx1];
		iLotto[idx1] = iLotto[idx2];
		iLotto[idx2] = iTemp;  // Swap 알고리즘
	}

	for (int i = 0; i < 6; ++i)
	{
		cout << iLotto[i] << '\t';
	}

	cout << "보너스번호 : " << iLotto[6] << endl;


	return 0;
}