#include "Core.h"
#include "StageManager.h"
#include "ShapeManager.h"

CCore* CCore::m_pInst = NULL;

CCore::CCore()
{
	srand((unsigned int)time(0));
}

CCore::~CCore()
{
	CShapeManager::DestroyInst();
	CStageManager::DestroyInst();
}

bool CCore::Init()
{
	// �ܼ�â �ڵ� ����
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (m_hConsole == INVALID_HANDLE_VALUE)
		return false;

	// �������� �����ڸ� �ʱ�ȭ�Ѵ�.
	if (!CStageManager::GetInst()->Init())
		return false;

	return true;
}

void CCore::Run()
{
	while (true)
	{
		system("cls");
		CShapeManager::GetInst()->Update();

		CStageManager::GetInst()->Run();
		CShapeManager::GetInst()->Render();

		Sleep(1000);
	}
}

void CCore::SetConsolePos(int x, int y)
{
	COORD	pos = {static_cast<short>(x * 2), static_cast<short>(y)};
	// coord�� F12�� �������� COORD ����ü ���ο� x�� y�� Ÿ����
	// SHORT Ÿ������ �̷�����ְ� intŸ�� �μ��� �޾ƿ����ֱ� ������ 
	// Ÿ��ĳ������ ������Ѵ�. �ƴϸ� �μ�Ÿ�� ��ü�� short�� �������.
	// ���� ���α׷��� Ư��(2byte), ����2��(1byte*2)�� ����� ��ĭ�� 2����Ʈ�� 
	// Ŀ���� ����(1byte)�� �������� �����̱� ������ *2�� ����� ��ĭ�� �ȴ�.
	// y�� ����� ����. Ư���̵� ����� ���Ʒ��� �ٲ�°� �����ϱ�.
	SetConsoleCursorPosition(m_hConsole, pos);
}
