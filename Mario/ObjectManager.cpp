#include "ObjectManager.h"
#include "Player.h"

// 정적멤버변수이기 때문에 정의부분 초기에 초기화시켜준다.
CObjectManager* CObjectManager::m_pInst = NULL;

// 오브젝트 매니저의 생성자 이니셜라이저로 
// 전방선언한 m_pPlayer Player클래스 객체 초기화.
CObjectManager::CObjectManager() :
	m_pPlayer(NULL)
{
}

CObjectManager::~CObjectManager()
{
	SAFE_DELETE(m_pPlayer);
}

// 초기화할때 CPlayer 동적할당해서 넣어주고
// 그 안에 만들어놓은 이닛 함수로 초기위치 설정한 뒤 트루.
// 최종 관리하는 코어클래스랑 연결.
bool CObjectManager::Init()
{
	m_pPlayer = new CPlayer;

	m_pPlayer->Init();

	return true;
}
