#include <iostream>
#include <time.h>
#include <string>

using namespace std;

int main()
{
	while (true)
	{
		unsigned short iUserInput[3] = {};
		unsigned short iAiNumb[3] = {};
		unsigned short iShuffle[9] = {}, idx1, idx2, idx3;
		unsigned short iCount = 0, iScore = 1;
		unsigned short iStrike = 0, iBall = 0, iOut = 0;
		unsigned short iCurrentValue = 0;
		char cExitConfirm = 'n', cRetry = 'n';

		cout << "숫자 야구 게임입니다" << endl;
		cout << "1~9까지의 숫자 중 서로 다른 숫자 3개를 선택해 순서대로 입력해주세요" << endl;
		cout << "게임을 종료하려면 0을 입력해주세요" << endl;
		cout << endl;

		//중복되지 않는 1~9까지의 숫자중 3개를 뽑아낸다
		//상용 프로그램에도 사용되는 스왑 알고리즘 + 셔플 알고리즘 사용
		srand((unsigned int)time(0));

		for (int i = 0; i < 9; ++i)
		{
			iShuffle[i] = i + 1;
		}
		//3개의 숫자만 있어도 되지만 1~9까지의 경우의 수가 있기 때문에
		//1~9까지의 모든 난수를 보유한 상태의 배열 생성


		//스왑 알고리즘 + 셔플 알고리즘
		for (int i = 0; i < 100; ++i)
		{
			idx1 = rand() % 9;
			idx2 = rand() % 9;

			idx3 = iShuffle[idx1];
			iShuffle[idx1] = iShuffle[idx2];
			iShuffle[idx2] = idx3;
		}
		//9개의 각기 다른 값을 가진 배열을 섞어준다.
		//즉 9가지의 서로 다른 경우의 수를 100번 정도 무작위로 섞어준다.
		//rand 함수에서 가져오는 값은 인덱스의 위치값을 가져오기 때문에
		//idx1,2에 중복된 값이 와도 내부값은 절대 변하지 않는다.


		//이렇게 생긴 9개짜리 난수 배열을 3개짜리 실제 사용될 AI에 부여한다.
		for (int i = 0; i < 3; ++i)
		{
			iAiNumb[i] = iShuffle[i];
			cout << iAiNumb[i] << '\t';
		}

		cout << endl;
		cout << endl;



		cout << "중복되지 않는 1~9까지의 숫자를 순서대로 입력해주세요." << endl;

		while (true)
		{
			cout << "스코어 : " << iScore << "회전" << endl;

			if (cExitConfirm == 'y' || cExitConfirm == 'Y')
			{
				system("exit");
				break;
			}
			//플레이어의 숫자 입력

			//3개 까지의 숫자만을 입력받을 것이고
			//그 외의 경우의 수로는
			/*
			1. 3개의 숫자만 허용된다. 3번의 입력을 통해 암시적 규칙을 인지시킨다.
			그러나 n번째의 입력에서 1개 초과의 숫자를 입력할 수 있는 부분을 예외처리한다.
			2. 0을 입력할 경우 프로그램이 종료되게된다. (루프에서 빠져나오게 되거나 종료)
			키패드의 입력정보를 읽어오는 방법은 아직 수업에 나온 부분이 아니므로 제외한다.
			3. 동일 숫자 입력 방지
			*/
			for (int i = 0; i < 3; ++i)
			{
				cout << endl;
				cout << i + 1 << "번째 숫자를 입력해주세요" << endl;
				cin >> iUserInput[i];

				//1번 예외 처리
				if (iUserInput[i] < 0 && iUserInput[i] >= 10)
				{
					cout << "잘못 입력하셨습니다. 다시 입력해주세요." << endl;
					i -= 1;
					continue;
				}

				//2번 예외 처리
				if (iUserInput[i] == 0)
				{
					cout << endl;
					cout << "게임을 종료하시겠습니까? ( Y , N )" << endl;
					cin >> cExitConfirm;

					if (cExitConfirm == 'y' || cExitConfirm == 'Y')
					{
						break;
					}
					else
					{
						i -= 1;
						continue;
					}
				}

				//3번 예외 처리
					if (iCurrentValue == iUserInput[i])
					{
						cout << "동일한 숫자는 입력할 수 없습니다." << endl;
						i -= 1;
						continue;
					}
					iCurrentValue = iUserInput[i];
				//이렇게만 끝내면 3 5 3 같은 경우는 막을 수가 없으므로 

					if (iUserInput[0] == iUserInput[2])
					{
						cout << "동일한 숫자는 입력할 수 없습니다." << endl;
						i -= 1;
						continue;
					}
			}
			if (cExitConfirm == 'y' || cExitConfirm == 'Y')
			{
				system("exit");
				break;
			}

			//집계 부분
			for (int i = 0; i < 3; ++i)
			{
				if (iUserInput[i] == iAiNumb[i])
				{
					iStrike += 1;
				}
				else if (iUserInput[i] != iAiNumb[i])
				{
					iOut += 1;
				}
			}

			if (iUserInput[0] == iAiNumb[1])
				iBall += 1;
			if (iUserInput[1] == iAiNumb[2])
				iBall += 1;
			if (iUserInput[2] == iAiNumb[0])
				iBall += 1;

			cout << "스트라이크 : " << iStrike << '\t' << "볼 : "
				<< iBall << '\t' << "아웃 : " << iOut << endl;

			if (iStrike == 3)
			{
				cout << endl;
				cout << "모두 맞추셨습니다!" << endl;
				break;
			}
			else
			{
				iStrike = 0;
				iBall = 0;
				iOut = 0;
				iScore++;
				continue;
			}
		}

		if (cExitConfirm == 'y' || cExitConfirm == 'Y')
		{
			system("exit");
			break;
		}

		cout << endl;
		cout << "다시 플레이 하시겠습니까? ( Y , N )" << endl;
		cin >> cRetry;

		if (cRetry == 'y' || cRetry == 'Y')
		{
			continue;
		}
		else
		{
			break;
		}
	}
	return 0;
}