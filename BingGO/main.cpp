#include <iostream>
#include <time.h>
#include <conio.h>

enum GameProps
{
	G_Line = 5
};

enum AI_Mode
{
	AM_EASY=1,
	AM_HARD
};

enum LINE_NUMBER
{
	LN_H1,
	LN_H2,
	LN_H3,
	LN_H4,
	LN_H5,
	LN_V1,
	LN_V2,
	LN_V3,
	LN_V4,
	LN_V5,
	LN_LT,
	LN_RT
};

using namespace std;

int main()
{ 
	srand((unsigned int)time(0));

	int iNumber[25] = {};
	int iAINumber[25] = {};

	// 1~25까지 숫자를 넣어준다
	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
	}

	// 숫자를 섞어준다
	int iTemp, idx1 = 0, idx2 = 0;
	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;


		// AI 숫자도 섞어준다
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iAINumber[idx1];
		iAINumber[idx1] = iAINumber[idx2];
		iAINumber[idx2] = iTemp;
	}

	int iBingo = 0, iAIBingo = 0;
	int iAIMode;

	// AI 난이도를 선택한다.
	while (true)
	{
		system("cls");
		cout << "1. Easy" << endl;
		cout << "2. Hard" << endl;
		cout << "AI 모드를 선택하세요 : " << endl;
		cin >> iAIMode;

		if (iAIMode >= AM_EASY || iAIMode <= AM_HARD)
			break;
	}


	//AI를 위한 설정
	//선택안된 목록 배열을 만들어준다.
	int iNoneSelect[25] = {};
	//선택안된 숫자 개수를 저장한다.
	int iNoneSelectCount = 0;


	while (true)
	{
		system("cls");

		// 숫자를 5 x 5로 출력한다
		cout << "================= Player =================" << endl;
		for (int i = 0; i < G_Line; ++i)
		{
			for (int j = 0; j < G_Line; ++j)
			{
				if (iNumber[i * G_Line + j] == INT_MAX)
				{
					cout << "*\t";
				}
				else
					cout << iNumber[i * G_Line + j] << '\t';
			}
			cout << endl;
		}
		
		cout << "Bingo Line : " << iBingo << endl << endl;


		// AI 빙고 판을 출력한다.
		cout << "==================== AI ====================" << endl;

		switch (iAIMode)
		{
		case AM_EASY:
			cout << "AIMode : Easy" << endl;
			break;
		case AM_HARD:
			cout << "AIMode : Hard" << endl;
			break;
		}

		for (int i = 0; i < G_Line; ++i)
		{
			for (int j = 0; j < G_Line; ++j)
			{
				if (iAINumber[i * G_Line + j] == INT_MAX)
					cout << "*\t";
				else
					cout << iAINumber[i * G_Line + j] << '\t';
			}
			cout << endl;
		}

		// AI 빙고 줄 수를 출력한다.
		cout << "AIBingo Line : " << iAIBingo << endl << endl;

		// 줄수가 5 이상일 경우 게임을 종료한다.
		if (iBingo >= G_Line)
		{
			cout << "Player 승리" << endl;
			break;
		}
		else if (iAIBingo >= G_Line)
		{
			cout << "AI 승리" << endl;
			break;
		}

		cout << "숫자를 입력하세요(0 : 종료) : ";
		int iInput;
		cin >> iInput;
		
		if (iInput == 0)
			break;

		else if (iInput < 1 || iInput > 25)
			continue;

		// 중복입력을 체크하기 위한 변수이다. 기본적으로 중복되었다라고
		// 하기 위해 true로 잡아주었다.
		bool bAcc = true;

		// 모든 숫자를 차례대로 검사해서 입력한 숫자와 같으 ㄴ숫자가
		// 있는지를 찾아낸다
		for (int i = 0; i < 25; ++i)
		{
			// 같은 숫자가 있을 경우
			if (iInput == iNumber[i])
			{
				// 숫자를 찾았을 경우 중복된 숫자가 아니므로
				// bAcc 변수를 false로 만들어준다.
				bAcc = false;
				
				// 숫자를 *로 변경하기 위해 특수한 값인 INT_MAX로 해준다.
				iNumber[i] = INT_MAX;

				// 더이상 다른 숫자를 찾아볼 필요가 없으므로
				// for 문을 빠져나간다.
				break;
				// 모든 숫자가 중복되지 않으므로 더 찾을 필요가 없는 것.
			}
		}

		// bAcc 변수가 true일 경우 중복된 숫자를 입력해서 숫자를 *로
		// 바꾸지 못했으므로 다시 입력받게 continue 해준다.
		if (bAcc)
			continue;

		//중복이 아니라면 AI의 숫자도 찾아서 *로 바꿔준다
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == iInput)
			{
				iAINumber[i] = INT_MAX;
			break;
			}
		}


		// AI가 선택을 한다. AI가 선택하는 것은 AI 모드에 따라서 달라진다.
		iNoneSelectCount = 0;
		switch (iAIMode)
		{
			/*
			AI Easy 모드는 현재 AI의 숫자목록중 *로 바뀌지 않은 숫자 목록을 만들어서
			그 목록중 하나를 선택하게 한다.(랜덤하게)
			*/
		case AM_EASY:
			// 선택안된 숫자목록을 만들어준다.
			// 선택안된 숫자 개수는 목록을 만들때 카운팅해준다.
			for (int i = 0; i < 25; ++i)
			{
				//현재 숫자가 *이 아닐 경우
				if (iAINumber[i] != INT_MAX)
				{
					// *이 아닌 숫자일 경우 iNoneSelectCount를 인덱스로 활용한다.
					// 선택 안된 목록에 추가할때마다 개수를 1씩 증가
					// 시켜서 총 선택안된 개수를 구해준다.
					// 그런데 0부터 카운트가 시작이므로 0번에 ++해서 1개
					// 추가되었다라고 해준다.
					iNoneSelect[iNoneSelectCount] = iAINumber[i];
					++iNoneSelectCount;
				}
			}
			// for 문을 빠져나오게 되면 선택안된 목록이 만들어지고
			// 선택안된 목록의 개수가 만들어지게 된다.
			// 선택안된 목록의 숫자중 랜덤한 하나의 숫자를 얻어오기 위해
			// 인덱스를 랜덤하게 구해준다.
			iInput = iNoneSelect[rand() % iNoneSelectCount];
			break;

		case AM_HARD:
			// 하드모드는 현재 숫자중 빙고줄 완성 가능성이 가장 높은 줄을
			// 찾아서 그 줄에 있는 숫자중 하나를 *로 만들어준다.
			int iLine = 0;
			int iStarCount = 0;
			int iSaveCount = 0;

			// 가로 라인 중 가장 *이 많은 라인을 찾아낸다.
			for (int i = 0; i < 5; ++i)
			{
				iStarCount = 0;
				for (int j = 0; j < 5; ++j)
				{
					if (iAINumber[i * G_Line + j] == INT_MAX)
						++iStarCount;
				}

				// 별이 5개 미만이어야 빙고 줄이 아니고 기존에 가장 많은
				// 라인(iSaveCount)의 별보다 커야 가장 별이 많은 라인이므로
				// 교체해주고 저장된 별 수를 교체한다.
				if (iStarCount < 5 && iSaveCount < iStarCount)
				{
					// 여기는 가로 라인중 가장 별이 많은 라인을 체크하는
					// 곳이다. 가로라인은 0 ~ 4로 의미를 부여했다. 의미부여라는게 가위바위보에서 숫자대입할 때를 생각하면 된다.
					iLine = i;
					iSaveCount = iStarCount;
				}
			}
			//가로 라인중 가장 별이 많은 라인은 이미 구했다.
			//이 값과 세로 라인들을 비교하여 가장 많은 라인을 구한다.
			for (int i = 0; i < 5; ++i)
			{
				iStarCount = 0;
				for (int j = 0; j < 5; ++j)
				{
					if (iAINumber[j * G_Line + i] == INT_MAX)
						++iStarCount;
				}

				if (iStarCount < 5 && iSaveCount < iStarCount)
				{
					// 세로라인은 5 ~ 9로 의미를 부여했다.
					// iLine에 꾸준히 의미부여한 가장 별이 많은 장소의 줄 위치가 기억되는 중이다.
					iLine = i + 5;
					iSaveCount = iStarCount;
					// 이 조건문에 들어온것 자체가 이미 이전 라인의 별 개수보다 많다는 것이므로
					// 가장 별이 많은 상태의 라인 별 갯수를 다시 iSaveCount에 저장한다.
				}
			}

			// 왼쪽 -> 오른쪽 대각선 체크
			iStarCount = 0;
			for (int i = 0; i < 25; i += G_Line + 1)
			{
				if (iAINumber[i] == INT_MAX)
				{
					++iStarCount;
				}
			}
			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				iLine = LN_LT;
				iSaveCount = iStarCount;
			}
			// 오른쪽 -> 왼쪽 대각선 체크
			iStarCount = 0;
			for (int i = 4; i < 21; i += G_Line - 1)
			{
				if (iAINumber[i] == INT_MAX)
				{
					++iStarCount;
				}
			}
			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				iLine = LN_RT;
				iSaveCount = iStarCount;
			}

			// 모든 라인을 조사했으면 iLine에 가능성이 가장 높은(별이 가장 많은) 줄 번호가
			// 저장되었다.
			// 그 줄에 있는 *이 아닌 숫자 중 하나를 선택하게 한다.
			// 가로줄일 경우
			if (iLine <= LN_H5)
			{
				// 가로줄일 경우 iLine이 0 ~ 4 사이의 값이다.
				for (int i = 0; i < G_Line; ++i)
				{
					//현재 줄에서 *이 아닌 숫자를 찾아낸다.
					if (iAINumber[iLine * G_Line + i] != INT_MAX)
					{
						iInput = iAINumber[iLine * G_Line + i];
						break;
					}
				}
			}
			// 세로줄일 경우. 위에서 h5 낮은수는 이미 체크를 했으니
			// 위에서 이미 처리가 됬을테니 v5보다 작을경우로 해도 된다.
			else if (iLine <= LN_V5)
			{
				// 세로줄 경우 iLine이 5 ~ 9 사이의 값이다.
				for (int i = 0; i < G_Line; ++i)
				{
					//현재 줄에서 *이 아닌 숫자를 찾아낸다.
					if (iAINumber[i * G_Line + (iLine - 5)] != INT_MAX)
					{
						iInput = iAINumber[i * G_Line + (iLine - 5)];
						break;
					}
				}
			}
			
			else if (iLine == LN_LT)
			{
				for (int i = 0; i < 25; i += G_Line + 1)
				{
					if (iAINumber[i] != INT_MAX)
					{
						iInput = iAINumber[i];
						break;
					}
				}
			}

			else if (iLine == LN_RT)
			{
				for (int i = 0; i < 21; i += G_Line - 1)
				{
					if (iAINumber[i] != INT_MAX)
					{
						iInput = iAINumber[i];
						break;
					}
				}
			}

			break;
		}



		// AI가 숫자를 선택했으므로 플레이어와 AI의 숫자를 *로 바꿔준다.
		for (int i = 0; i < 25; ++i)
		{
			if (iNumber[i] == iInput)
			{
				iNumber[i] = INT_MAX;
				break;
			}
		}
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == iInput)
			{
				iAINumber[i] = INT_MAX;
				break;
			}
		}


		// 빙고 줄 수를 체크하는 것은 매번 숫자를 입력할때마다 처음부터
		// 새로 카운트를 할 것이다. 그러므로 iBingo 변수를 0으로 매번
		// 초기화하고 새롭게 줄 수를 구해주도록 한다.
		iBingo = 0;
		iAIBingo = 0;

		// 가로, 세로 줄 수를 구해준다.
		int iStar1 = 0, iStar2 = 0;
		int iAIStar1 = 0, iAIStar2 = 0;
		for (int i = 0; i < G_Line; ++i)
		{
			// 한줄을 체크하기 전에 먼저 0으로 별 개수를 초기화한다.
			// i 반복에서 한줄 한줄을 체크하기 때문에 초기화하지 않으면 
			// iStar가 다음줄까지 체크한다.
			iStar1 = iStar2 = 0;
			iAIStar1 = iAIStar2 = 0;
			for (int j = 0; j < G_Line; ++j)
			{
				// 가로 별 개수를 구해준다.
				if (iNumber[i * G_Line + j] == INT_MAX)
					++iStar1;
				// 세로 별 개수를 구해준다.
				if (iNumber[j * G_Line + i] == INT_MAX)
					++iStar2;
				// AI 줄 체크
				if (iAINumber[i * G_Line + j] == INT_MAX)
					++iAIStar1;
				if (iAINumber[j * G_Line + i] == INT_MAX)
					++iAIStar2;
			}
			// j for 문을 빠져나오고 나면 현재 줄의 가로 별 개수가 몇개인지
			// iStar1 변수에 들어가게된다. 요컨데 초기화 시키기 전 이부분에서
			// 별개수를 체크해 빙고를 더해줘야 한다는것.
			if (iStar1 == G_Line)
				++iBingo;
			if (iStar2 == G_Line)
				++iBingo;
			if (iAIStar1 == G_Line)
				++iAIBingo;
			if (iAIStar2 == G_Line)
				++iAIBingo;
		}

		// 왼쪽 상단 -> 오른쪽 하단 대각선 체크
		iStar1 = 0;
		iAIStar1 = 0;
		for (int i = 0; i < 25; i += G_Line + 1)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;
			if (iAINumber[i] == INT_MAX)
				++iAIStar1;
		}
		if (iStar1 == G_Line)
			++iBingo;
		if (iAIStar1 == G_Line)
			++iAIBingo;

		// 오른쪽 상단 -> 왼쪽 하단 대각선 체크
		iStar1 = 0;
		iAIStar1 = 0;
		for (int i = 4; i < 21; i += G_Line - 1)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;
			if (iAINumber[i] == INT_MAX)
				++iAIStar1;
		}
		if (iStar1 == G_Line)
			++iBingo;
		if (iAIStar1 == G_Line)
			++iAIBingo;
	}

	return 0;
}

// ; 은 위험하다. 조심