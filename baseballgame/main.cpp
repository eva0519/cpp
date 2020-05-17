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

		cout << "���� �߱� �����Դϴ�" << endl;
		cout << "1~9������ ���� �� ���� �ٸ� ���� 3���� ������ ������� �Է����ּ���" << endl;
		cout << "������ �����Ϸ��� 0�� �Է����ּ���" << endl;
		cout << endl;

		//�ߺ����� �ʴ� 1~9������ ������ 3���� �̾Ƴ���
		//��� ���α׷����� ���Ǵ� ���� �˰��� + ���� �˰��� ���
		srand((unsigned int)time(0));

		for (int i = 0; i < 9; ++i)
		{
			iShuffle[i] = i + 1;
		}
		//3���� ���ڸ� �־ ������ 1~9������ ����� ���� �ֱ� ������
		//1~9������ ��� ������ ������ ������ �迭 ����


		//���� �˰��� + ���� �˰���
		for (int i = 0; i < 100; ++i)
		{
			idx1 = rand() % 9;
			idx2 = rand() % 9;

			idx3 = iShuffle[idx1];
			iShuffle[idx1] = iShuffle[idx2];
			iShuffle[idx2] = idx3;
		}
		//9���� ���� �ٸ� ���� ���� �迭�� �����ش�.
		//�� 9������ ���� �ٸ� ����� ���� 100�� ���� �������� �����ش�.
		//rand �Լ����� �������� ���� �ε����� ��ġ���� �������� ������
		//idx1,2�� �ߺ��� ���� �͵� ���ΰ��� ���� ������ �ʴ´�.


		//�̷��� ���� 9��¥�� ���� �迭�� 3��¥�� ���� ���� AI�� �ο��Ѵ�.
		for (int i = 0; i < 3; ++i)
		{
			iAiNumb[i] = iShuffle[i];
			cout << iAiNumb[i] << '\t';
		}

		cout << endl;
		cout << endl;



		cout << "�ߺ����� �ʴ� 1~9������ ���ڸ� ������� �Է����ּ���." << endl;

		while (true)
		{
			cout << "���ھ� : " << iScore << "ȸ��" << endl;

			if (cExitConfirm == 'y' || cExitConfirm == 'Y')
			{
				system("exit");
				break;
			}
			//�÷��̾��� ���� �Է�

			//3�� ������ ���ڸ��� �Է¹��� ���̰�
			//�� ���� ����� ���δ�
			/*
			1. 3���� ���ڸ� ���ȴ�. 3���� �Է��� ���� �Ͻ��� ��Ģ�� ������Ų��.
			�׷��� n��°�� �Է¿��� 1�� �ʰ��� ���ڸ� �Է��� �� �ִ� �κ��� ����ó���Ѵ�.
			2. 0�� �Է��� ��� ���α׷��� ����ǰԵȴ�. (�������� ���������� �ǰų� ����)
			Ű�е��� �Է������� �о���� ����� ���� ������ ���� �κ��� �ƴϹǷ� �����Ѵ�.
			3. ���� ���� �Է� ����
			*/
			for (int i = 0; i < 3; ++i)
			{
				cout << endl;
				cout << i + 1 << "��° ���ڸ� �Է����ּ���" << endl;
				cin >> iUserInput[i];

				//1�� ���� ó��
				if (iUserInput[i] < 0 && iUserInput[i] >= 10)
				{
					cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���." << endl;
					i -= 1;
					continue;
				}

				//2�� ���� ó��
				if (iUserInput[i] == 0)
				{
					cout << endl;
					cout << "������ �����Ͻðڽ��ϱ�? ( Y , N )" << endl;
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

				//3�� ���� ó��
					if (iCurrentValue == iUserInput[i])
					{
						cout << "������ ���ڴ� �Է��� �� �����ϴ�." << endl;
						i -= 1;
						continue;
					}
					iCurrentValue = iUserInput[i];
				//�̷��Ը� ������ 3 5 3 ���� ���� ���� ���� �����Ƿ� 

					if (iUserInput[0] == iUserInput[2])
					{
						cout << "������ ���ڴ� �Է��� �� �����ϴ�." << endl;
						i -= 1;
						continue;
					}
			}
			if (cExitConfirm == 'y' || cExitConfirm == 'Y')
			{
				system("exit");
				break;
			}

			//���� �κ�
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

			cout << "��Ʈ����ũ : " << iStrike << '\t' << "�� : "
				<< iBall << '\t' << "�ƿ� : " << iOut << endl;

			if (iStrike == 3)
			{
				cout << endl;
				cout << "��� ���߼̽��ϴ�!" << endl;
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
		cout << "�ٽ� �÷��� �Ͻðڽ��ϱ�? ( Y , N )" << endl;
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