#include "StageManager.h"
#include "Stage.h"

CStageManager* CStageManager::m_pInst = NULL;
// static 변수의 경우 클래스 외부에서 정의해줘야 한다.
// static은 전역변수의 성질도 가지기 때문에 데이터영역에 할당되기 때문인데
// static 변수를 클래스 내부에 설정하고 생성자에서 초기화한다고 가정하면
// 객체가 생성될때마다 전역변수가 초기화되어버리는 것이 되므로 오류뿜뿜이 된다.
// 동적메모리 영역에서 전역으로 사용할 정적메모리를 건드려 버리는 것이기 때문에
// 일반 멤버변수와 다르게 위처럼 초기화를 해주는 것이다.
// 선언만하고 정의를 하지않으면 헤더에서 포인터변수 선언만 한뒤 
// 주소가 존재하지 않기 때문에 외부참조 오류가 뜨게된다.

CStageManager::CStageManager():
	m_pCurStage(NULL)
{
}

CStageManager::~CStageManager()
{
}

bool CStageManager::Init()
{
	// 기본 스테이지를 생성한다.
	m_pCurStage = new CStage;

	if (!m_pCurStage->Init())
		return false;

	return true;
}

void CStageManager::Run()
{
	m_pCurStage->Render();
}