
#include "List.h"

void OutputStudent(const PSTUDENT pStudent)
{
	cout << "�̸� : " << pStudent->strName << "\t�й� : " << pStudent->iNumber << endl;
	cout << "���� : " << pStudent->iKor << "\t���� : " << pStudent->iEng << endl;
	cout << "���� : " << pStudent->iMath << endl;
	cout << "���� : " << pStudent->iTotal << "\t��� : " << pStudent->fAvg << endl;
	cout << endl;
}

void InitList(PLIST pList)
{
	pList->iSize = 0;

	pList->pBegin = new NODE;
	pList->pEnd = new NODE;

	// ���۳���� �������� ������ ����̴�.
	pList->pBegin->pNext = pList->pEnd;

	// ����������� ���� ���� ���۳���̴�.
	pList->pEnd->pPrev = pList->pBegin;

	// ������ ����� ���� ���� �����Ƿ� NULL�� ���ش�.
	pList->pEnd->pNext = NULL;

	// ���� ����� ���� ���� �����Ƿ� NULL�� ���ش�.
	pList->pBegin->pPrev = NULL;
}

void DestroyList(PLIST pList)
{
	PNODE	pNode = pList->pBegin;

	while (pNode != NULL)
	{
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}

	pList->iSize = 0;
	pList->pBegin = NULL;
	pList->pEnd = NULL;
}

void Push_Back(PLIST pList)
{
	system("cls");
	cout << "========================== �л��߰� ====================" << endl;

	STUDENT tStudent = {};

	cout << "�̸� : ";
	InputString(tStudent.strName, NAME_SIZE);

	cout << "�й� : ";
	tStudent.iNumber = InputInt();

	cout << "���� : ";
	tStudent.iKor = InputInt();

	cout << "���� : ";
	tStudent.iEng = InputInt();

	cout << "���� : ";
	tStudent.iMath = InputInt();

	tStudent.iTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
	tStudent.fAvg = tStudent.iTotal / 3.f;

	PNODE	pNode = new NODE;

	pNode->tStudent = tStudent;

	// ���� �߰��Ǵ� ���� End����� �������� End��� ���̿� �߰��ؾ� �Ѵ�.
	// �׷��� pEnd �� prev ��带 ���س��´�.
	PNODE	pPrev = pList->pEnd->pPrev;

	// pEnd ��� ���� ����� �������� �߰��� ��带 �����Ѵ�.
	pPrev->pNext = pNode;
	// �߰��� ����� ���� ���� End�� ���� ��带 �����Ѵ�.
	pNode->pPrev = pPrev;
	
	// ���� �߰��� ����� ���� ��带 pEnd�� �����Ѵ�.
	pNode->pNext = pList->pEnd;

	// pEnd ����� ���� ���� ���� �߰��� ��带 �����Ѵ�.
	pList->pEnd->pPrev = pNode;

	++pList->iSize;
}

void Push_Front(PLIST pList)
{
}

void Output(PLIST pList)
{
	int iMenu;

	while (true)
	{
		system("cls");
		cout << "========================== �л���� ====================" << endl;
		cout << "1. ������ ���" << endl;
		cout << "2. ������ ���" << endl;
		cout << "�޴��� �����ϼ��� : ";
		iMenu = InputInt();

		if (iMenu > OT_NONE || iMenu <= OT_INVERSE)
			break;
	}

	PNODE pNode = NULL;

	switch (iMenu)
	{
	case OT_OUTPUT:
		// �߰��Ǵ� ������ begin�� end ���̿� ��ġ�ȴ�. �׷��Ƿ� begin�� ���� ��带
		// ���´�.
		pNode = pList->pBegin->pNext;

		// ��尡 End���� �������� ���̻� ����� ��尡 �����Ƿ� �ݺ��� �����Ѵ�.
		while (pNode != pList->pEnd)
		{
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pNext;
		}
		break;
	case OT_INVERSE:
		// ���������� ����Ҷ��� end�� ���� ��带 ������ ��� �������� �����Ѵ�.
		// begin �� ������ ��� �ݺ��� �����Ѵ�.
		pNode = pList->pEnd->pPrev;

		// ���������� ���� ������ ��尡 begin�� �������� ���̻� ����� ��尡 �����Ƿ�
		// �ݺ��� �����Ѵ�.
		while (pNode != pList->pBegin)
		{
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pPrev;
		}
		break;
	}

	cout << "�л��� : " << pList->iSize << endl;
	system("pause");
}

void Search(PLIST pList)
{
	system("cls");
	cout << "========================== �л�Ž�� ====================" << endl;

	cout << "Ž���� �̸��� �Է��ϼ��� : ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE pNode = pList->pBegin->pNext;

	while (pNode != pList->pEnd)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			OutputStudent(&pNode->tStudent);
			system("pause");
			return;
		}

		pNode = pNode->pNext;
	}

	cout << "�л��� ã�� �� �����ϴ�." << endl;
	system("pause");
}

void Delete(PLIST pList)
{
	system("cls");
	cout << "========================== �л����� ====================" << endl;

	cout << "������ �̸��� �Է��ϼ��� : ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE	pNode = pList->pBegin->pNext;

	while (pNode != pList->pEnd)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			// ���� ���� ����� ��������� ������ ���� ���� ���� �Ǿ��ִ�.
			// �׷��� ���� ���� �������� �ϱ� ������ ��������� ������带
			// ���� ����� ���� ���� �ش�.
			// ���� ����� ������ ���� ����ε� �������� �ش�.
			pNode->pPrev->pNext = pNode->pNext;
			pNode->pNext->pPrev = pNode->pPrev;
			delete pNode;
			cout << strName << "  �л��� �����Ͽ����ϴ�." << endl;
			system("pause");
			return;
		}

		pNode = pNode->pNext;
	}

	cout << "������ ����� ã�� �� �����ϴ�." << endl;
	system("pause");
}

void Sort(PLIST pList)
{
	system("cls");
	cout << "========================== �л����� ====================" << endl;
	cout << "1. �й�����" << endl;
	cout << "2. ��ձ���" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int iInput = InputInt();

	if (iInput <= ST_NONE || iInput > ST_AVG)
	{	
		cout << "�߸� �����Ͽ����ϴ�." << endl;
		system("pause");
		return;
	}

	cout << endl;
	cout << "1. ��������" << endl;
	cout << "2. ��������" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int iOption = InputInt();

	if (iOption <= SO_NONE || iOption > SO_DESCRIVE)
	{
		cout << "�߸� �����Ͽ����ϴ�." << endl;
		system("pause");
		return;
	}

	PNODE	pFirst = pList->pBegin->pNext;
	PNODE	pSecond = pFirst->pNext;

	// ���� ���� �˰�����
	// First�� End�� ���� ���� �������� �Ǹ� ���̻� ���� ��尡 �����Ƿ�
	// �����Ѵ�.
	while (pFirst != pList->pEnd->pPrev)
	{
		// Second�� ������ First ��� ���� ������ �˻縦 �����Ѵ�.
		pSecond = pFirst->pNext;

		// Second�� End ���� ���� �ݺ��ؾ� �ϹǷ� End�� �ƴҵ��ȸ� �ݺ��Ѵ�.
		while (pSecond != pList->pEnd)
		{
			bool	bSwap = false;

			switch (iInput)
			{
			case ST_NUMBER:
				switch (iOption)
				{
				case SO_CRIVE:
					if (pFirst->tStudent.iNumber > pSecond->tStudent.iNumber)
						bSwap = true;
					break;
				case SO_DESCRIVE:
					if (pFirst->tStudent.iNumber < pSecond->tStudent.iNumber)
						bSwap = true;
					break;
				}
				break;
			case ST_AVG:
				switch (iOption)
				{
				case SO_CRIVE:
					if (pFirst->tStudent.fAvg > pSecond->tStudent.fAvg)
						bSwap = true;
					break;
				case SO_DESCRIVE:
					if (pFirst->tStudent.fAvg < pSecond->tStudent.fAvg)
						bSwap = true;
					break;
				}
				break;
			}

			// bool���� bSwap�� true�� ��� �� ��带 �ٲ�� �Ѵٴ� ���̴�.
			if (bSwap)
			{
				// First ����� ������ ������带 �����Ѵ�.
				PNODE	pFirstPrev = pFirst->pPrev;
				PNODE	pFirstNext = pFirst->pNext;

				// Second ����� ������ ������带 �����Ѵ�.
				PNODE	pSecondPrev = pSecond->pPrev;
				PNODE	pSecondNext = pSecond->pNext;

				// ������ �� ��尡 ���� �ٲ����Ƿ� ����Ǿ��ִ� pNext�� pPrev�� �ٲ�
				// �־�� �Ѵ�. �׷��� pFirstPrev ����� �������� �ٲ� pFirst�� �����ϰ�
				// �ٲ� pFirst �� ���� ���� pFirstPrev��带 �������ش�.
				// ���� ���鵵 ���������� ��ü�� �־���Ѵ�.
				pFirstPrev->pNext = pSecond;
				pSecond->pPrev = pFirstPrev;

				// �ٲٷ��� �� ��尡 �پ����� ���� ���
				if (pSecond != pFirstNext)
				{
					pFirstNext->pPrev = pSecond;
					pSecond ->pNext = pFirstNext;

					pSecondPrev->pNext = pFirst;
					pFirst->pPrev = pSecondPrev;
				}

				// ��尡 �پ��ִٸ�
				else
				{
					pSecond->pNext = pFirst;
					pFirst->pPrev = pSecond;
				}

				pSecondNext->pPrev = pFirst;
				pFirst->pNext = pSecondNext;

				// �� ��带 �ٲ��ش�.
				PNODE	pTemp = pFirst;
				pFirst = pSecond;
				pSecond = pTemp; 
			}

			pSecond = pSecond->pNext;
		}

		pFirst = pFirst->pNext;
	}

	cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
	system("pause");
}