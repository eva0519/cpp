
#include "Core.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "Player.h"

CCore* CCore::m_pInst = NULL;

// cpp ���Ͽ��� Ŭ������ �����κ��� �ִ�.
CCore::CCore()
{
	srand((unsigned int)time(0));
}

CCore::~CCore()
{
	CMapManager::DestroyInst();
	CObjectManager::DestroyInst();
}

CCore* CCore::GetInst()
{
	if (!m_pInst)
		m_pInst = new CCore;

	return m_pInst;
}

void CCore::DestroyInst()
{
	SAFE_DELETE(m_pInst);
}

bool CCore::Init()
{
	// �� ������ GetInst ��������Լ����� ������� m_pInst ������������� ��
	// �����Ҵ� Ŭ������ �� ��ü ���� �Ϲݸ���Լ� init�� ������
	// ���ڰ� �����ϴ� �����͸� �ʱ�ȭ�Ͽ� �ް� �ʱ�ȭ ���θ� �Ǵ��Ͽ�
	// ���� �������� CCore ���� ��ü������ �ʱ�ȭ�Ѵ�.
	// ��������,�÷��̾� Ŭ���� ���� -> �� �����ڰ� Ȯ���ؼ� �����Ҵ��ϰ� ������ �ʱ�ȭ
	// -> �ھ �� �����ڰ� �����Ҵ��ϰ� �ʱ�ȭ�Ѱ� Ȯ���ؼ� ��ü �ʱ�ȭ.

	// �� �����ڸ� �ʱ�ȭ�Ѵ�. ���н� false�� �����Ѵ�.
	if (!CMapManager::GetInst()->Init())
		return false;

	// ������Ʈ ������ �ʱ�ȭ
	if (!CObjectManager::GetInst()->Init())
		return false;

	return true;
}

void CCore::Run()
{
	// �̷� �ڵ� ���̸� �� �Լ��� �� ��ȯ�ϴ��� �����ϸ� �м��ϱ� ���ϴ�.
	// CMapManager::GetInst()->Render();

	while (true)
	{
		int iStage = OutputMenu();

		if (iStage == 4)
			break;

		else if (iStage == 0)
			continue;

		CMapManager::GetInst()->Run(iStage - 1);
	}

}

int CCore::OutputMenu()
{
	system("cls");
	cout << "1. Stage1" << endl;
	cout << "2. Stage2" << endl;
	cout << "3. Stage3" << endl;
	cout << "4. ����" << endl;
	cout << "Input Stage : ";
	int iInput = InputInt();

	if (iInput < 1 || iInput > 4)
		return 0;

	return iInput;
}
