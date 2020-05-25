
#include "Core.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "Player.h"

CCore* CCore::m_pInst = NULL;

// cpp ���Ͽ��� Ŭ������ �����κ��� �ִ�.
CCore::CCore()
{
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
	//CMapManager::GetInst()->Render();
	CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();

	while (true)
	{
		system("cls");

		CMapManager::GetInst()->Run();

		pPlayer->Update();

		CMapManager::GetInst()->Render();

		// Win32 API �Լ��� millonSecond ���� ������ ���߶�� ����̴�.
		Sleep(100);
	}

}