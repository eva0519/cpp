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
	// 콘솔창 핸들 생성
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (m_hConsole == INVALID_HANDLE_VALUE)
		return false;

	// 스테이지 관리자를 초기화한다.
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
	// coord에 F12를 눌러보면 COORD 구조체 내부에 x와 y의 타입은
	// SHORT 타입으로 이루어져있고 int타입 인수로 받아오고있기 때문에 
	// 타입캐스팅을 해줘야한다. 아니면 인수타입 자체를 short로 잡아주자.
	// 현재 프로그램은 특문(2byte), 공백2개(1byte*2)을 사용해 한칸이 2바이트로 
	// 커서는 영문(1byte)를 기준으로 움직이기 때문에 *2를 해줘야 한칸이 된다.
	// y는 상관이 없다. 특문이든 영어든 위아래줄 바뀌는건 같으니까.
	SetConsoleCursorPosition(m_hConsole, pos);
}
