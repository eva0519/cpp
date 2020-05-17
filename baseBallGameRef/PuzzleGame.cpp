#include <iostream>
#include <time.h>

// console input output 헤더파일이다. 콘솔창에서 입출력 하는 기능들을
// 제공해주는 헤더파일이다.
// 아래 _getch() 함수를 사용하기 위한 헤더파일.
#include <conio.h>

using namespace std;

int main()
{
	srand((unsigned int)time(0));

	int iNumber[25] = {};

	for (int i = 0; i < 24; ++i)
	{
		iNumber[i] = i + 1;
	}

	// 가장 마지막 칸은 공백으로 비워둔다. 공백을 의미하는 값으로 특수한 값을
	// 사용할건데 INT_MAX 라는 값을 사용할 것이다. INT_MAX는 이미 정의되어 있는 값으로
	// int로 표현할 수 있는 최대값이다.
	iNumber[24] = INT_MAX;
	// 값을 클릭하고 f12를 누르면 정의된 값으로 타고가서 볼 수 있다.

	// 별이 있는 위치를 저장할 변수를 만들어준다.
	int iStarIndex = 24;


	// 셔플 알고리즘
	// 마지막 공백을 제외하고 1 ~ 24 까지의 숫자만 섞어준다. 즉 인덱스는 0~23번
	// 인덱스 까지만 섞어준다.
	int iTemp, idx1, idx2;
	
	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 24;
		idx2 = rand() % 24;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}
	
	while (true)
	{
		system("cls");
		// !!중요 2D 게임에서 많이 활용하게 될 공식!!

		// 1차원 배열을 2차원 배열처럼 표로 출력.
		// 2d에서 아주 많이 사용하게 된다.

		// i for문이 세로줄을 의미한다.
		for (int i = 0; i < 5; ++i)
		{
			// j for문이 가로 칸을 의미한다.
			for (int j = 0; j < 5; ++j)
			{
				// i가 0일때 j는 0 ~ 4까지 반복한다. 이경우 0*5+(0~4)를 더하게 되서
				// 인덱스는 0,1,2,3,4가 나오게 된다.
				// i가 1일때 j는 0 ~ 4까지 반복한다. 이경우 1*5+(0~4)를 더하게 되서
				// 인덱스는 5,6,7,8,9가 나오게 된다
				// i가 2일때 j는 0 ~ 4까지 반복한다. 이경우 2*5+(0~4)를 더하게 되서
				// 인덱스는 10,11,12,13,14가 나오게 된다
				// i가 3일때 j는 0 ~ 4까지 반복한다. 이경우 3*5+(0~4)를 더하게 되서
				// 인덱스는 15,16,17,18,19가 나오게 된다
				// i가 4일때 j는 0 ~ 4까지 반복한다. 이경우 4*5+(0~4)를 더하게 되서
				// 인덱스는 20,21,22,23,24가 나오게 된다
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";

				else
					cout << iNumber[i * 5 + j] << "\t";
				// *(공식화)*	줄번호 * 가로개수 + 칸번호
				// i j는 자주쓰니 i * x + j 로 외우자.
				// x,y 좌표가 있으면 그곳의 배열 인덱스를 바로 구하는 식으로 사용. 
			}

			cout << endl; // j for문 끝나면 한줄 출력한거니까 개행
		}
		// 2차원 배열이면 그냥 [i][j]를 하면 간단히 출력할수 있지만
		// 1차원 배열을 표현한 것이라 2d 평면상에서 자주 사용된다.


		// true로 주어서 먼저 모두 맞췄다 라고 가정해둔다.
		bool bWin = true;

		// 퍼즐을 맞추었는지 체크한다.
		for (int i = 0; i < 24; ++i)
		{
			// i가 하나라도 !(아닐경우)! 
			//맞을 경우로 하면 하나만 맞아도 중지되니까 아닐 경우로 해야함
			if (iNumber[i] != i + 1) 
			{
				bWin = false;
				break;    // 정답이 아니므로 반복문 중지
			}
		}
		// bWin 변수가 여전히 true라면 위 체크반복문을 거치지 않은 것이 된다.
		// 고로 모든 수가 정렬되어 있음.
		if (bWin == true)
		{
			cout << "숫자를 모두 맞췄습니다." << endl;
			break;
		}
		// 기능이 정상적인지 확인해보려면 셔플 알고리즘을 안돌려보면 된다.


		cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료 : ";
		// _getch() 함수는 문자 1개를 입력받는 함수이다. 이 함수는 Enter를 치지
		// 않더라도 문자를 누르는 순간 바로 그 문자를 반환하고 종료된다. (입력버퍼 사용안함)
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		switch (cInput)
		{
		case 'w':
		case 'W':
			// 가장 윗줄일 때는 w를 눌러도 위로 올라가서는 안된다.
			if (iStarIndex > 4)
			{
				// 별이 있는 위치에 바로 위에 있는 값을 넣어준다.
				iNumber[iStarIndex] = iNumber[iStarIndex - 5];
				// 위의 위치에 별을 넣어주어서 2개의 값을 서로 교체한다.
				iNumber[iStarIndex - 5] = INT_MAX;
				// 별이 한칸 위로 올라갔으므로 한칸 위의 인덱스로 만들어준다.
				iStarIndex -= 5;
			}
			break;
		case 's':
		case 'S':
			// 가장 아래줄이 아닐 경우 움직인다.
			if (iStarIndex < 20)
			{
				iNumber[iStarIndex] = iNumber[iStarIndex + 5];
				iNumber[iStarIndex + 5] = INT_MAX;
				iStarIndex += 5;
			}
			break;
		case 'a':
		case 'A':
			if (iStarIndex % 5 != 0) // 0,5,10,15,20 아닐 경우
			{
				iNumber[iStarIndex] = iNumber[iStarIndex - 1];
				iNumber[iStarIndex - 1] = INT_MAX;
				--iStarIndex;
			}
			break;
		case 'd':
		case 'D':
			if (iStarIndex % 5 != 4) // 4,9,14,19,24 가 아닐 경우
			{
				iNumber[iStarIndex] = iNumber[iStarIndex + 1];
				iNumber[iStarIndex + 1] = INT_MAX;
				++iStarIndex;
			}
			break;
		}
	}

	cout << endl;
	cout << "게임을 종료합니다." << endl;

	return 0;
}