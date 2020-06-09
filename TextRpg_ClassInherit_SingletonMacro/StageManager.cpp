#include "StageManager.h"
#include "StageEasy.h"
#include "StageNormal.h"
#include "StageHard.h"

DEFINITION_SINGLE(CStageManager)

CStageManager::CStageManager()
{

}
CStageManager::~CStageManager()
{
	Safe_Delete_VecList(m_vecStage);
}

bool CStageManager::Init()
{
	if (!CreateStage(ST_EASY))
		return false;

	if (!CreateStage(ST_NORMAL))
		return false;

	if (!CreateStage(ST_HARD))
		return false;


	return true;
}

void CStageManager::Run()
{
	m_vecStage[0]->Run();
}

bool CStageManager::CreateStage(STAGE_TYPE eType)
{
	CStage* pStage = NULL;

	switch (eType)
	{
	case ST_EASY:
		pStage = new CStageEasy;
		break;
	case ST_NORMAL:
		pStage = new CStageNormal;
		break;
	case ST_HARD:
		pStage = new CStageHard;
		break;
	}

	// stage를 추상클래스로 만들어 가상함수를 선언했기 때문에
	// 어떤 stage 동적할당 인스턴스를 생성했건 각자가 보유한 init() 함수를
	// 실행하게 된다.
	if (!pStage->Init())
	{
		SAFE_DELETE(pStage);
		return false;
	}

	m_vecStage.push_back(pStage);

	return true;
}
