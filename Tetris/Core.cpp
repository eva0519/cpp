#include "Core.h"
#include "StageManager.h"
#include "ShapeManager.h"

CCore* CCore::m_pInst = NULL;

CCore::CCore() :
	m_bLoop(true)
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
	while (m_bLoop)
	{
		system("cls");
		CShapeManager::GetInst()->Update();

		CStageManager::GetInst()->Run();
		CShapeManager::GetInst()->Render();

		Sleep(100);
	}
}

void CCore::SetConsolePos(int x, int y)
{
	// coord�� F12�� �������� COORD ����ü ���ο� x�� y�� Ÿ����
	// SHORT Ÿ������ �̷�����ְ� intŸ�� �μ��� �޾ƿ����ֱ� ������ 
	// Ÿ��ĳ������ ������Ѵ�. �ƴϸ� �μ�Ÿ�� ��ü�� short�� �������.
	// ���� ���α׷��� Ư��(2byte), ����2��(1byte*2)�� ����� ��ĭ�� 2����Ʈ�� 
	// Ŀ���� ����(1byte)�� �������� �����̱� ������ *2�� ����� ��ĭ�� �ȴ�.
	// y�� ����� ����. Ư���̵� ����� ���Ʒ��� �ٲ�°� �����ϱ�.
	// x+1�� �Ѱ��� ���������� �����Ҷ� �ݺ������� i�� 0�� ���� �������� ������
	// ���� ������� �ʵ��� ó������ ���̴�.
	COORD	pos = { static_cast<short>((x + 1) * 2), static_cast<short>(y) };
	SetConsoleCursorPosition(m_hConsole, pos);
}
