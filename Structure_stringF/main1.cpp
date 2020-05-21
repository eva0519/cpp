#include <iostream>

// ctrl + spacebar�� �ڵ��ϼ� ����� ����ϸ� ���ϰ� ������.
// ���ǵǰų� ����ü�� �����״ٸ� �ҹ��ڷ� ġ�� �ڵ��ϼ��� ����.
// ctrl ���콺��Ŭ������ �ܾ�ä�� ���ð����ϴ�.
// ctrl + alt + ��Ŭ�� ���ϴ� ���� ��������
// alt + �巡�� ���ϴ� ���� �ٺ��� ��������

using namespace std;

#define NAME_SIZE 32
#define ADDRESS_SIZE 128
#define PHONE_SIZE 14  // 000-0000-0000+(null��) 14��Ʈ
#define STUDENT_MAX 10

struct _tagStudent
{
	char	strName[NAME_SIZE];
	char	strAddress[ADDRESS_SIZE];
	char	strPhoneNumber[PHONE_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
};

enum MENU
{
	MENU_NONE,
	MENU_INSERT,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT
};

int main()
{
	_tagStudent tStudentArr[STUDENT_MAX] = {};
	// �迭�� �߰��� ������ ������ ������ ������ش�.
	int iStudentCount = 0;
	int iStdNumber = 1;
	char	strName[NAME_SIZE] = {};

	while (true)
	{
		system("cls");

		// �޴��� ����Ѵ�.
		cout << "1. �л����" << endl;
		cout << "2. �л�����" << endl;
		cout << "3. �л�Ž��" << endl;
		cout << "4. �л����" << endl;
		cout << "5. ����" << endl;
		cout << "�޴��� �����ϼ��� : ";
		int iMenu;
		cin >> iMenu;

		// cin�� ���� �����ʿ� int������ ���� ������ �Է��ؾ� �Ѵ�. �����ʿ�
		// ���� ���� Ÿ�Կ� ���缭 ���� �Է��ؾ� �ϴµ� �Ǽ��� ������ �ƴ�
		// ���ڸ� �Է��� ��� ������ �߻��Ѵ�. �׷��� ������ ����ó���� ������
		// �߻��ߴ����� ���⿡�� üũ�Ͽ� ������ �߻��ϸ� cin ������ �������۸�
		// ����ְ� cin ���ο� �Է¹��۰� �ִµ� �Է¹��۴� �Է��� ���� ����
		// �س��� �� ���� ������ �־��ִ� ������ �Ѵ�. �� �Է¹��ۿ� \n ��
		// ���������Ƿ� ���۸� ��ȸ�Ͽ� \n�� �������Ѵ�.
		// ���� : �ӽ�������� �̴�.
		// ���� ������ üũ�Ѵ�. cin.fail() �� ������ �Է� ������ �߻�����
		// ��� true�� ��ȯ�Ѵ�.
		if (cin.fail())
		{
			// �������۸� ����ش�.
			cin.clear();

			// �Է¹��ۿ� \n�� ���������Ƿ� �Է¹��۸� �˻��Ͽ� \n�� �����ش�.
			// ù��°���� �˻��ϰ��� �ϴ� ���� ũ�⸦ �����Ѵ�. �˳��ϰ� 1024
			// ����Ʈ���� �������־���. 2��°�� ã���� �ϴ� ���ڸ� �־��ش�.
			// �׷��� �Է¹��� ó������ \n�� �ִ� ������ ã�Ƽ� �� �κ��� ���
			// �����༭ �ٽ� �Է¹��� �� �ֵ��� ���ش�.
			cin.ignore(1024, '\n');
			continue;
			// �߸� �Է��� ���̴� �ٽ� �϶�� continue
		}

		// ����ó���� ����ġ ���� ���� break�� switch���� ���������� break�̹Ƿ�
		// while���� ���������� break�� if������ ó������� �Ѵ�.
		if (iMenu == MENU_EXIT)
			break;
		
		switch (iMenu)
		{
		case MENU_INSERT:
			system("cls");
			cout << "================ �л��߰� ================" << endl;

			// ��ϵ� �л��� ����� �� �ִ� �ִ�ġ�� ��� ���̻� �����
			// �ȵǰ� ���´�.
			if (iStudentCount == STUDENT_MAX)
				break;

			// �л������� �߰��Ѵ�. �л������� �̸�, �ּ�, ��ȭ��ȣ,
			// ����, ����, ���� ������ �Է¹ް� �й�, ���� ����� ������
			// ���� ������ش�.
			cout << "�̸� : ";
			cin >> tStudentArr[iStudentCount].strName;

			cin.ignore(1024, '\n');
			//cin ���Ŀ� getline �Լ��� �Բ� ���� cin�� ����� �Է��� �Է¹��ۿ� 
			//\n�� �����ֱ� ������ getline�� ���ͷ� ���� �׳� �Ѿ������. 
			//\n�� ã�� �ʱ�ȭ.

			cout << "�ּ� : ";
			cin.getline(tStudentArr[iStudentCount].strAddress, ADDRESS_SIZE);
			//cin.getline(�Է¹�������,�Է¹����ִ��ġ)
			//�����̽��ٸ� null��(���ڿ��� ��)���� �ν����� �ʰ� ���ڿ��� �ν���
			//��ü ���ڿ��� �޾ƿ��� �Լ���. cin���� �ϸ� �����̽��� �ڷδ� �߸�.
			
			cout << "��ȭ��ȣ : ";
			cin.getline(tStudentArr[iStudentCount].strPhoneNumber, PHONE_SIZE);

			cout << "���� : ";
			cin >> tStudentArr[iStudentCount].iKor;

			cout << "���� : ";
			cin >> tStudentArr[iStudentCount].iEng;

			cout << "���� : ";
			cin >> tStudentArr[iStudentCount].iMath;

			tStudentArr[iStudentCount].iTotal =
				tStudentArr[iStudentCount].iKor +
				tStudentArr[iStudentCount].iEng +
				tStudentArr[iStudentCount].iMath;
			tStudentArr[iStudentCount].fAvg =
				tStudentArr[iStudentCount].iTotal / 3.f;

			tStudentArr[iStudentCount].iNumber = iStdNumber;
			++iStdNumber;
			++iStudentCount;

			cout << "�л� �߰� �Ϸ�" << endl;
			break;
		case MENU_DELETE:
			system("cls");

			cout << "================ �л����� ================" << endl;

			cin.ignore(1024, '\n');
			cout << "������ �̸��� �Է��ϼ��� : ";
			cin.getline(strName, NAME_SIZE);

			// ��ϵǾ��ִ� �л� ����ŭ �ݺ��ϸ� �л��� ã�´�.
			for (int i = 0; i < iStudentCount; ++i)
			{
				// �л��� ã���� ���
				if (strcmp(tStudentArr[i].strName, strName) == 0)
				{
					// !�߿�! ������⺸�� ���� ������ ������ ����ٴ� ����. ������ ���.
					for (int j = i; j < iStudentCount - 1; ++j) 
					{
						tStudentArr[i] = tStudentArr[i + 1];
					}
					// ��� ���迭�� ���迭�� �ߺ��Ǳ��ϳ� ������ �Ʒ� --�� ī��Ʈ��
					// ���̱⿡ ������ �ԷµǴ� �����Ͱ� �ߺ��� ���迭�� �����.
					// �Դٰ� iStudentCount ��ŭ�� ����ϱ� ������ �ߺ� �迭�� �� �ϵ� ����.

					--iStudentCount;

					cout << "�л��� �����Ͽ����ϴ�." << endl;
					break;
				}
			}

			break;
		case MENU_SEARCH:
			system("cls");

			cout << "================ �л�Ž�� ================" << endl;

			cin.ignore(1024, '\n');
			cout << "Ž���� �̸��� �Է��ϼ��� : ";
			cin.getline(strName, NAME_SIZE);

			// ��ϵǾ��ִ� �л� ����ŭ �ݺ��ϸ� �л��� ã�´�.
			for (int i = 0; i < iStudentCount; i++)
			{
				// �л��� ã���� ���
				if (strcmp(tStudentArr[i].strName, strName) == 0)
				{
					cout << "�̸� : " << tStudentArr[i].strName << endl;
					cout << "��ȭ��ȣ : " << tStudentArr[i].strPhoneNumber << endl;
					cout << "�ּ� : " << tStudentArr[i].strAddress << endl;
					cout << "�й� : " << tStudentArr[i].iNumber << endl;
					cout << "���� : " << tStudentArr[i].iKor << endl;
					cout << "���� : " << tStudentArr[i].iEng << endl;
					cout << "���� : " << tStudentArr[i].iMath << endl;
					cout << "���� : " << tStudentArr[i].iTotal << endl;
					cout << "��� : " << tStudentArr[i].fAvg << endl << endl;
					break;
				}
			}
			break;
		case MENU_OUTPUT:
			system("cls");

			cout << "================ �л���� ================" << endl;

			// ��ϵ� �л� ����ŭ �ݺ��ϸ� �л������� ����Ѵ�.
			for (int i = 0; i < iStudentCount; ++i)
			{
				cout << "�̸� : " << tStudentArr[i].strName << endl;
				cout << "��ȭ��ȣ : " << tStudentArr[i].strPhoneNumber << endl;
				cout << "�ּ� : " << tStudentArr[i].strAddress << endl;
				cout << "�й� : " << tStudentArr[i].iNumber << endl;
				cout << "���� : " << tStudentArr[i].iKor << endl;
				cout << "���� : " << tStudentArr[i].iEng << endl;
				cout << "���� : " << tStudentArr[i].iMath << endl;
				cout << "���� : " << tStudentArr[i].iTotal << endl;
				cout << "��� : " << tStudentArr[i].fAvg << endl << endl;
			}
			break;
		default:
			cout << "�޴��� �߸� �����ϼ̽��ϴ�" << endl;
			break;
		}

		system("pause");
		// pause ���Ѿ� ������ cls�ؼ� "�߸������ϼ̽��ϴ�" ������ �������°� ���´�.
	}

	return 0;
}