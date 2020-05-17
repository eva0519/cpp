#include <iostream>
#include <time.h>

using namespace std;

int main() {

	srand((unsigned int)time(0));

	int iNumber[9] = {};

	// 1~9까지 숫자를 배열에 설정한다.
	for (int i = 0; i < 9; ++i) {
		iNumber[i] = i + 1;
	}

	// 설정된 숫자를 섞어준다.
	int idx1 = 0, idx2 = 0, iTemp;
	for (int i = 0; i < 100; ++i) {
		idx1 = rand() % 9;
		idx2 = rand() % 9;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}

	cout << "*\t*\t*\t" << endl;
	/*cout << iNumber[0] << '\t' << iNumber[1] << '\t' << iNumber[2] << endl;*/

	int iStrike = 0, iBall = 0;
	int iInput[3];
	int iGameCount = 1;

	while (true) {

		cout << iGameCount << " 회" << endl;

		cout << "1 ~ 9 사이의 숫자중 숫자 3개를 입력하세요(0 : 종료) : ";
		cin >> iInput[0] >> iInput[1] >> iInput[2];

		if (iInput[0] == 0 || iInput[1] == 0 || iInput[2] == 0)
			break;

		else if (iInput[0] < 0 || iInput[0] > 9 || iInput[1] < 0 || iInput[1] > 9 ||
			iInput[2] < 0 || iInput[2] > 9) 
		{
			cout << "잘못된 숫자를 입력하였습니다" << endl;
			continue;
		}

		else if (iInput[0] == iInput[1] || iInput[1] == iInput[2] || iInput[0] == iInput[2])
		{
			cout << "중복된 숫자를 입력하였습니다" << endl;
			continue;
		}

		// 매번 strike와 ball의 수가 달라지기 떄문에 0으로 초기화하고 다시 계산한다.
		iStrike = iBall = 0;
		//동시 초기화 문법 기억. 집계 조건문 전에 초기화하는 개념 이해.
		

		// !!가장 중요한 부분!!
		// i for문은 맞춰야 할 숫자의 인덱스를 구한다.
		for (int i = 0; i < 3; ++i) 
		{
			// j for 문은 입력받은 숫자의 인덱스를 구한다.
			for (int j = 0; j < 3; ++j) 
			{
				// i 가 0일때 j는 0 ~ 2 까지 반복하게 된다. 즉, 맞춰야할 숫자의
				// 첫번째 값과 입력받은 숫자의 첫,두,세번째를 차례대로 비교하여
				// 같은 값이 있는지를 찾아낸다.
				if (iNumber[i] == iInput[j])
				{
					// 값이 같은 것이 있을 경우 Strike 아니면 Ball 이므로 자리가 같은
					// 지를 체크해본다. i와 j는 현재 맞춰야할 숫자의 인덱스와
					// 입력받은 숫자의 인덱스이고 두 값이 같으므로 이 인덱스가
					// 곧 위치가 된다. 인덱스가 서로 같은 경우라면 자리까지 같다는
					// 의미이므로 strike를 증가하고 그게 아니라면 자리가 다르다는
					// 의미이므로 ball을 증가하게 한다.
					if (i == j)
						++iStrike;
					else
						++iBall;

					// 입력받은 숫자와 맞춰야할 숫자를 비교할때 같은 수가 있으면
					// 이 뒤로는 더 이상 같은 수가 없으므로 다음 맞춰야할 숫자로
					// 바로 비교하면 된다. 그래서 break를 해서 j for문을 빠져나가고
					// ++i 가 되게 하여 다음 맞춰야할 숫자와 다시 비교하게 한다.
					break;
				}
			}
		}

		if (iStrike == 3)
		{
			cout << "정답입니다" << endl;
			break;
		}

		else if (iStrike == 0 && iBall == 0)
			cout << "Out" << endl;

		else
			cout << iStrike << " strike  " << iBall << " ball  " << endl;

		++iGameCount;
	}

	return 0;
}