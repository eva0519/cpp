#include <iostream>
#include <time.h>
#include <conio.h>

enum GameProps
{
	G_Line = 5
};

enum AI_Mode
{
	AM_EASY = 1,
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

// �Լ��� ����� ���� �κ����� ���� �� �ִ�.
void SetNumber(int* pArray);
void Shuffle(int* pArray);
AI_Mode SelectAIMode();
void OutputNumber(int* pArray, int iBingo);
bool ChangeNumber(int* pArray, int iInput);
int SelectAINumber(int* pArray, AI_Mode eMode);
int BingoCounting(int* pArray);
int BingoCountingH(int* pArray);
int BingoCountingV(int* pArray);
int BingoCountingLTD(int* pArray);
int BingoCountingRTD(int* pArray);

using namespace std;

int main()
{
	srand((unsigned int)time(0));

	int iNumber[25] = {};
	int iAINumber[25] = {};

	SetNumber(iNumber);
	SetNumber(iAINumber);

	// ���ڸ� �����ش�
	Shuffle(iNumber);
	Shuffle(iAINumber);

	int iBingo = 0, iAIBingo = 0;

	// AI ���̵��� �����Ѵ�.
	AI_Mode eAIMode = SelectAIMode();


	while (true)
	{
		system("cls");

		// ���ڸ� 5 x 5�� ����Ѵ�
		cout << "================= Player =================" << endl;
		OutputNumber(iNumber, iBingo);


		// AI ���� ���� ����Ѵ�.
		cout << "==================== AI ====================" << endl;

		switch (eAIMode)
		{
		case AM_EASY:
			cout << "AIMode : Easy" << endl;
			break;
		case AM_HARD:
			cout << "AIMode : Hard" << endl;
			break;
		}

		OutputNumber(iAINumber, iAIBingo);


		// �ټ��� 5 �̻��� ��� ������ �����Ѵ�.
		if (iBingo >= G_Line)
		{
			cout << "Player �¸�" << endl;
			break;
		}
		else if (iAIBingo >= G_Line)
		{
			cout << "AI �¸�" << endl;
			break;
		}

		cout << "���ڸ� �Է��ϼ���(0 : ����) : ";
		int iInput;
		cin >> iInput;

		if (iInput == 0)
			break;

		else if (iInput < 1 || iInput > 25)
			continue;

		// �ߺ��Է��� üũ�ϱ� ���� �����̴�. �⺻������ �ߺ��Ǿ��ٶ��
		// �ϱ� ���� true�� ����־���.
		bool bAcc = ChangeNumber(iNumber, iInput);

		if (bAcc)
			continue;

		// �ߺ��� �ƴ϶�� AI�� ���ڵ� ã�Ƽ� *�� �ٲ��ش�
		ChangeNumber(iAINumber, iInput);


		// AI�� ���ڸ� �����Ѵ�. AI��忡 ���缭 ���õǵ��� �Լ��� �����Ǿ��ִ�.
		iInput = SelectAINumber(iAINumber, eAIMode);
		

		// AI�� ���ڸ� ���������Ƿ� �÷��̾�� AI�� ���ڸ� *�� �ٲ��ش�.
		ChangeNumber(iNumber, iInput);
		ChangeNumber(iAINumber, iInput);


		// ���� �� ���� üũ�ϴ� ���� �Ź� ���ڸ� �Է��Ҷ����� ó������
		// ���� ī��Ʈ�� �� ���̴�. �׷��Ƿ� iBingo ������ 0���� �Ź�
		// �ʱ�ȭ�ϰ� ���Ӱ� �� ���� �����ֵ��� �Ѵ�.
		iBingo = BingoCounting(iNumber);
		iAIBingo = BingoCounting(iAINumber);
	}

	return 0;
}

void SetNumber(int *pArray)
{
	for (int i = 0; i < 25; ++i)
	{
		pArray[i] = i + 1;
	}
}

void Shuffle(int* pArray)
{
	int iTemp, idx1 = 0, idx2 = 0;
	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = pArray[idx1];
		pArray[idx1] = pArray[idx2];
		pArray[idx2] = iTemp;

	}
}

AI_Mode SelectAIMode()
{
	int iAIMode;
	while (true)
	{
		system("cls");
		cout << "1. Easy" << endl;
		cout << "2. Hard" << endl;
		cout << "AI ��带 �����ϼ��� : " << endl;
		cin >> iAIMode;

		if (iAIMode >= AM_EASY || iAIMode <= AM_HARD)
			break;
	}

	return (AI_Mode)iAIMode;
}

void OutputNumber(int* pArray, int iBingo)
{
	for (int i = 0; i < G_Line; ++i)
	{
		for (int j = 0; j < G_Line; ++j)
		{
			if (pArray[i * G_Line + j] == INT_MAX)
			{
				cout << "*\t";
			}
			else
				cout << pArray[i * G_Line + j] << '\t';
		}
		cout << endl;
	}

	cout << "Bingo Line : " << iBingo << endl << endl;
}

bool ChangeNumber(int* pArray, int iInput)
{
	// ��� ���ڸ� ���ʴ�� �˻��ؼ� �Է��� ���ڿ� ���� ���ڰ�
	// �ִ����� ã�Ƴ���
	for (int i = 0; i < 25; ++i)
	{
		// ���� ���ڰ� ���� ���
		if (iInput == pArray[i])
		{
			// ���ڸ� ã���� ��� �ߺ��� ���ڰ� �ƴϹǷ�
			// bAcc ������ false�� ������ش�.

			// ���ڸ� *�� �����ϱ� ���� Ư���� ���� INT_MAX�� ���ش�.
			pArray[i] = INT_MAX;

			// ���̻� �ٸ� ���ڸ� ã�ƺ� �ʿ䰡 �����Ƿ�
			// for ���� ����������.
			return false;
			// ��� ���ڰ� �ߺ����� �����Ƿ� �� ã�� �ʿ䰡 ���� ��.
		}
	}
	// ������� ���ԵǸ� return false �� ���� �ȵ� ���̹Ƿ� ���� ���ڰ� 
	// ���ٴ� ���̴�. ��, �ߺ��� ���ڸ� �Է��߱� ������ true�� �����Ѵ�.
	return true;
}

int SelectAINumber(int* pArray, AI_Mode eMode)
{
	//���þȵ� ��� �迭�� ������ش�.
	int iNoneSelect[25] = {};
	//���þȵ� ���� ������ �����Ѵ�.
	int iNoneSelectCount = 0;

	// AI�� ������ �Ѵ�. AI�� �����ϴ� ���� AI ��忡 ���� �޶�����.
	switch (eMode)
	{
		/*
		AI Easy ���� ���� AI�� ���ڸ���� *�� �ٲ��� ���� ���� ����� ����
		�� ����� �ϳ��� �����ϰ� �Ѵ�.(�����ϰ�)
		*/
	case AM_EASY:
		// ���þȵ� ���ڸ���� ������ش�.
		// ���þȵ� ���� ������ ����� ���鶧 ī�������ش�.
		iNoneSelectCount = 0;
		for (int i = 0; i < 25; ++i)
		{
			//���� ���ڰ� *�� �ƴ� ���
			if (pArray[i] != INT_MAX)
			{
				// *�� �ƴ� ������ ��� iNoneSelectCount�� �ε����� Ȱ���Ѵ�.
				// ���� �ȵ� ��Ͽ� �߰��Ҷ����� ������ 1�� ����
				// ���Ѽ� �� ���þȵ� ������ �����ش�.
				// �׷��� 0���� ī��Ʈ�� �����̹Ƿ� 0���� ++�ؼ� 1��
				// �߰��Ǿ��ٶ�� ���ش�.
				iNoneSelect[iNoneSelectCount] = pArray[i];
				++iNoneSelectCount;
			}
		}
		// for ���� ���������� �Ǹ� ���þȵ� ����� ���������
		// ���þȵ� ����� ������ ��������� �ȴ�.
		// ���þȵ� ����� ������ ������ �ϳ��� ���ڸ� ������ ����
		// �ε����� �����ϰ� �����ش�.
		return iNoneSelect[rand() % iNoneSelectCount];
		// ���þȵ� �迭�� �� ������ �� �ϳ��� iInput���� �������ش�.

	case AM_HARD:
		// �ϵ���� ���� ������ ������ �ϼ� ���ɼ��� ���� ���� ����
		// ã�Ƽ� �� �ٿ� �ִ� ������ �ϳ��� *�� ������ش�.
		int iLine = 0;
		int iStarCount = 0;
		int iSaveCount = 0;

		// ���� ���� �� ���� *�� ���� ������ ã�Ƴ���.
		for (int i = 0; i < 5; ++i)
		{
			iStarCount = 0;
			for (int j = 0; j < 5; ++j)
			{
				if (pArray[i * G_Line + j] == INT_MAX)
					++iStarCount;
			}

			// ���� 5�� �̸��̾�� ���� ���� �ƴϰ� ������ ���� ����
			// ����(iSaveCount)�� ������ Ŀ�� ���� ���� ���� �����̹Ƿ�
			// ��ü���ְ� ����� �� ���� ��ü�Ѵ�.
			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				// ����� ���� ������ ���� ���� ���� ������ üũ�ϴ�
				// ���̴�. ���ζ����� 0 ~ 4�� �ǹ̸� �ο��ߴ�. �ǹ̺ο���°� �������������� ���ڴ����� ���� �����ϸ� �ȴ�.
				iLine = i;
				iSaveCount = iStarCount;
			}
		}
		//���� ������ ���� ���� ���� ������ �̹� ���ߴ�.
		//�� ���� ���� ���ε��� ���Ͽ� ���� ���� ������ ���Ѵ�.
		for (int i = 0; i < 5; ++i)
		{
			iStarCount = 0;
			for (int j = 0; j < 5; ++j)
			{
				if (pArray[j * G_Line + i] == INT_MAX)
					++iStarCount;
			}

			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				// ���ζ����� 5 ~ 9�� �ǹ̸� �ο��ߴ�.
				// iLine�� ������ �ǹ̺ο��� ���� ���� ���� ����� �� ��ġ�� ���Ǵ� ���̴�.
				iLine = i + 5;
				iSaveCount = iStarCount;
				// �� ���ǹ��� ���°� ��ü�� �̹� ���� ������ �� �������� ���ٴ� ���̹Ƿ�
				// ���� ���� ���� ������ ���� �� ������ �ٽ� iSaveCount�� �����Ѵ�.
			}
		}

		// ���� -> ������ �밢�� üũ
		iStarCount = 0;
		for (int i = 0; i < 25; i += G_Line + 1)
		{
			if (pArray[i] == INT_MAX)
			{
				++iStarCount;
			}
		}
		if (iStarCount < 5 && iSaveCount < iStarCount)
		{
			iLine = LN_LT;
			iSaveCount = iStarCount;
		}
		// ������ -> ���� �밢�� üũ
		iStarCount = 0;
		for (int i = 4; i < 21; i += G_Line - 1)
		{
			if (pArray[i] == INT_MAX)
			{
				++iStarCount;
			}
		}
		if (iStarCount < 5 && iSaveCount < iStarCount)
		{
			iLine = LN_RT;
			iSaveCount = iStarCount;
		}

		// ��� ������ ���������� iLine�� ���ɼ��� ���� ����(���� ���� ����) �� ��ȣ��
		// ����Ǿ���.
		// �� �ٿ� �ִ� *�� �ƴ� ���� �� �ϳ��� �����ϰ� �Ѵ�.
		// �������� ���
		if (iLine <= LN_H5)
		{
			// �������� ��� iLine�� 0 ~ 4 ������ ���̴�.
			for (int i = 0; i < G_Line; ++i)
			{
				//���� �ٿ��� *�� �ƴ� ���ڸ� ã�Ƴ���.
				if (pArray[iLine * G_Line + i] != INT_MAX)
				{
					return pArray[iLine * G_Line + i];
				}
			}
		}
		// �������� ���. ������ h5 �������� �̹� üũ�� ������
		// ������ �̹� ó���� �����״� v5���� �������� �ص� �ȴ�.
		else if (iLine <= LN_V5)
		{
			// ������ ��� iLine�� 5 ~ 9 ������ ���̴�.
			for (int i = 0; i < G_Line; ++i)
			{
				//���� �ٿ��� *�� �ƴ� ���ڸ� ã�Ƴ���.
				if (pArray[i * G_Line + (iLine - 5)] != INT_MAX)
				{
					return pArray[i * G_Line + (iLine - 5)];
				}
			}
		}

		else if (iLine == LN_LT)
		{
			for (int i = 0; i < 25; i += G_Line + 1)
			{
				if (pArray[i] != INT_MAX)
				{
					return pArray[i];
				}
			}
		}

		else if (iLine == LN_RT)
		{
			for (int i = 0; i < 21; i += G_Line - 1)
			{
				if (pArray[i] != INT_MAX)
				{
					return pArray[i];
				}
			}
		}
		break;

	}

	return -1;
	// �߸����� ��� -1�� �������ش�.
}

int BingoCounting(int* pArray)
{
	int iBingo = 0;

	// ������ üũ
	iBingo += BingoCountingH(pArray);
	// ������ üũ
	iBingo += BingoCountingV(pArray);
	// ���� ��� �밢�� üũ
	iBingo += BingoCountingLTD(pArray);
	// ������ ��� �밢�� üũ
	iBingo += BingoCountingRTD(pArray);

	return iBingo;
}

int BingoCountingH(int* pArray)
{
	// ���� �� ���� �����ش�.
	int iStar1 = 0, iBingo = 0;
	for (int i = 0; i < G_Line; ++i)
	{
		iStar1 =  0;
		for (int j = 0; j < G_Line; ++j)
		{
			// ���� �� ������ �����ش�.
			if (pArray[i * G_Line + j] == INT_MAX)
				++iStar1;
		}
		// j for ���� ���������� ���� ���� ���� ���� �� ������ �����
		// iStar1 ������ ���Եȴ�. ������ �ʱ�ȭ ��Ű�� �� �̺κп���
		// �������� üũ�� ���� ������� �Ѵٴ°�.
		if (iStar1 == G_Line)
			++iBingo;
	}

	return iBingo;
}

int BingoCountingV(int* pArray)
{
	// ���� �� ���� �����ش�.
	int iStar1 = 0, iBingo = 0;
	for (int i = 0; i < G_Line; ++i)
	{
		iStar1 = 0;
		for (int j = 0; j < G_Line; ++j)
		{
			// ���� �� ������ �����ش�.
			if (pArray[j * G_Line + i] == INT_MAX)
				++iStar1;
		}
		if (iStar1 == G_Line)
			++iBingo;
	}

	return iBingo;
}

int BingoCountingLTD(int* pArray)
{
	// ���� ��� -> ������ �ϴ� �밢�� üũ
	int iStar1 = 0, iBingo = 0;
	for (int i = 0; i < 25; i += G_Line + 1)
	{
		if (pArray[i] == INT_MAX)
			++iStar1;
	}
	if (iStar1 == G_Line)
		++iBingo;

	return iBingo;
}

int BingoCountingRTD(int* pArray)
{
	// ������ �ϴ� -> ���� ��� �밢�� üũ
	int iStar1 = 0, iBingo = 0;
	for (int i = 0; i < 21; i += G_Line - 1)
	{
		if (pArray[i] == INT_MAX)
			++iStar1;
	}
	if (iStar1 == G_Line)
		++iBingo;

	return iBingo;
}