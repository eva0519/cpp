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

	// 1~25���� ���ڸ� �־��ش�
	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
	}

	// ���ڸ� �����ش�
	int iTemp, idx1 = 0, idx2 = 0;
	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;


		// AI ���ڵ� �����ش�
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iAINumber[idx1];
		iAINumber[idx1] = iAINumber[idx2];
		iAINumber[idx2] = iTemp;
	}

	int iBingo = 0, iAIBingo = 0;
	int iAIMode;

	// AI ���̵��� �����Ѵ�.
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


	//AI�� ���� ����
	//���þȵ� ��� �迭�� ������ش�.
	int iNoneSelect[25] = {};
	//���þȵ� ���� ������ �����Ѵ�.
	int iNoneSelectCount = 0;


	while (true)
	{
		system("cls");

		// ���ڸ� 5 x 5�� ����Ѵ�
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


		// AI ���� ���� ����Ѵ�.
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

		// AI ���� �� ���� ����Ѵ�.
		cout << "AIBingo Line : " << iAIBingo << endl << endl;

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
		bool bAcc = true;

		// ��� ���ڸ� ���ʴ�� �˻��ؼ� �Է��� ���ڿ� ���� �����ڰ�
		// �ִ����� ã�Ƴ���
		for (int i = 0; i < 25; ++i)
		{
			// ���� ���ڰ� ���� ���
			if (iInput == iNumber[i])
			{
				// ���ڸ� ã���� ��� �ߺ��� ���ڰ� �ƴϹǷ�
				// bAcc ������ false�� ������ش�.
				bAcc = false;
				
				// ���ڸ� *�� �����ϱ� ���� Ư���� ���� INT_MAX�� ���ش�.
				iNumber[i] = INT_MAX;

				// ���̻� �ٸ� ���ڸ� ã�ƺ� �ʿ䰡 �����Ƿ�
				// for ���� ����������.
				break;
				// ��� ���ڰ� �ߺ����� �����Ƿ� �� ã�� �ʿ䰡 ���� ��.
			}
		}

		// bAcc ������ true�� ��� �ߺ��� ���ڸ� �Է��ؼ� ���ڸ� *��
		// �ٲ��� �������Ƿ� �ٽ� �Է¹ް� continue ���ش�.
		if (bAcc)
			continue;

		//�ߺ��� �ƴ϶�� AI�� ���ڵ� ã�Ƽ� *�� �ٲ��ش�
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == iInput)
			{
				iAINumber[i] = INT_MAX;
			break;
			}
		}


		// AI�� ������ �Ѵ�. AI�� �����ϴ� ���� AI ��忡 ���� �޶�����.
		iNoneSelectCount = 0;
		switch (iAIMode)
		{
			/*
			AI Easy ���� ���� AI�� ���ڸ���� *�� �ٲ��� ���� ���� ����� ����
			�� ����� �ϳ��� �����ϰ� �Ѵ�.(�����ϰ�)
			*/
		case AM_EASY:
			// ���þȵ� ���ڸ���� ������ش�.
			// ���þȵ� ���� ������ ����� ���鶧 ī�������ش�.
			for (int i = 0; i < 25; ++i)
			{
				//���� ���ڰ� *�� �ƴ� ���
				if (iAINumber[i] != INT_MAX)
				{
					// *�� �ƴ� ������ ��� iNoneSelectCount�� �ε����� Ȱ���Ѵ�.
					// ���� �ȵ� ��Ͽ� �߰��Ҷ����� ������ 1�� ����
					// ���Ѽ� �� ���þȵ� ������ �����ش�.
					// �׷��� 0���� ī��Ʈ�� �����̹Ƿ� 0���� ++�ؼ� 1��
					// �߰��Ǿ��ٶ�� ���ش�.
					iNoneSelect[iNoneSelectCount] = iAINumber[i];
					++iNoneSelectCount;
				}
			}
			// for ���� ���������� �Ǹ� ���þȵ� ����� ���������
			// ���þȵ� ����� ������ ��������� �ȴ�.
			// ���þȵ� ����� ������ ������ �ϳ��� ���ڸ� ������ ����
			// �ε����� �����ϰ� �����ش�.
			iInput = iNoneSelect[rand() % iNoneSelectCount];
			break;

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
					if (iAINumber[i * G_Line + j] == INT_MAX)
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
					if (iAINumber[j * G_Line + i] == INT_MAX)
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
			// ������ -> ���� �밢�� üũ
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
					if (iAINumber[iLine * G_Line + i] != INT_MAX)
					{
						iInput = iAINumber[iLine * G_Line + i];
						break;
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



		// AI�� ���ڸ� ���������Ƿ� �÷��̾�� AI�� ���ڸ� *�� �ٲ��ش�.
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


		// ���� �� ���� üũ�ϴ� ���� �Ź� ���ڸ� �Է��Ҷ����� ó������
		// ���� ī��Ʈ�� �� ���̴�. �׷��Ƿ� iBingo ������ 0���� �Ź�
		// �ʱ�ȭ�ϰ� ���Ӱ� �� ���� �����ֵ��� �Ѵ�.
		iBingo = 0;
		iAIBingo = 0;

		// ����, ���� �� ���� �����ش�.
		int iStar1 = 0, iStar2 = 0;
		int iAIStar1 = 0, iAIStar2 = 0;
		for (int i = 0; i < G_Line; ++i)
		{
			// ������ üũ�ϱ� ���� ���� 0���� �� ������ �ʱ�ȭ�Ѵ�.
			// i �ݺ����� ���� ������ üũ�ϱ� ������ �ʱ�ȭ���� ������ 
			// iStar�� �����ٱ��� üũ�Ѵ�.
			iStar1 = iStar2 = 0;
			iAIStar1 = iAIStar2 = 0;
			for (int j = 0; j < G_Line; ++j)
			{
				// ���� �� ������ �����ش�.
				if (iNumber[i * G_Line + j] == INT_MAX)
					++iStar1;
				// ���� �� ������ �����ش�.
				if (iNumber[j * G_Line + i] == INT_MAX)
					++iStar2;
				// AI �� üũ
				if (iAINumber[i * G_Line + j] == INT_MAX)
					++iAIStar1;
				if (iAINumber[j * G_Line + i] == INT_MAX)
					++iAIStar2;
			}
			// j for ���� ���������� ���� ���� ���� ���� �� ������ �����
			// iStar1 ������ ���Եȴ�. ������ �ʱ�ȭ ��Ű�� �� �̺κп���
			// �������� üũ�� ���� ������� �Ѵٴ°�.
			if (iStar1 == G_Line)
				++iBingo;
			if (iStar2 == G_Line)
				++iBingo;
			if (iAIStar1 == G_Line)
				++iAIBingo;
			if (iAIStar2 == G_Line)
				++iAIBingo;
		}

		// ���� ��� -> ������ �ϴ� �밢�� üũ
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

		// ������ ��� -> ���� �ϴ� �밢�� üũ
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

// ; �� �����ϴ�. ����