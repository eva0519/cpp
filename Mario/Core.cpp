
#include "Core.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "Player.h"

CCore* CCore::m_pInst = NULL;

// cpp 파일에는 클래스의 구현부분이 있다.
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
	// 각 관리자 GetInst 정적멤버함수에서 만들어져 m_pInst 정적멤버변수에 들어간
	// 동적할당 클래스가 각 객체 내의 일반멤버함수 init을 실행해
	// 각자가 관리하는 데이터를 초기화하여 받고 초기화 여부를 판단하여
	// 최종 관리자인 CCore 에서 전체적으로 초기화한다.
	// 스테이지,플레이어 클래스 생성 -> 각 관리자가 확인해서 동적할당하고 데이터 초기화
	// -> 코어가 각 관리자가 동적할당하고 초기화한거 확인해서 전체 초기화.

	// 맵 관리자를 초기화한다. 실패시 false를 리턴한다.
	if (!CMapManager::GetInst()->Init())
		return false;

	// 오브젝트 관리자 초기화
	if (!CObjectManager::GetInst()->Init())
		return false;

	return true;
}

void CCore::Run()
{
	// 이런 코드 보이면 각 함수가 뭘 반환하는지 생각하면 분석하기 편하다.
	//CMapManager::GetInst()->Render();
	CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();

	while (true)
	{
		system("cls");

		CMapManager::GetInst()->Run();

		pPlayer->Update();

		CMapManager::GetInst()->Render();

		// Win32 API 함수로 millonSecond 인자 단위로 멈추라는 명령이다.
		Sleep(100);
	}

}