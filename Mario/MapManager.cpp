
#include "MapManager.h"
#include "Stage.h"

CMapManager* CMapManager::m_pInst = NULL;

CMapManager::CMapManager()
{
	for (int i = 0; i < STAGE_MAX_COUNT; ++i)
	{
		m_pStage[i] = NULL;
	}
}

CMapManager::~CMapManager()
{
	// 스테이지 메모리 해제
	for (int i = 0; i < STAGE_MAX_COUNT; ++i)
	{
		SAFE_DELETE(m_pStage[i]);
	}
}

CMapManager* CMapManager::GetInst()
{
	if (!m_pInst)
		m_pInst = new CMapManager;

	return m_pInst;
}

void CMapManager::DestroyInst()
{
	SAFE_DELETE(m_pInst);
}

bool CMapManager::Init()
{
	char* pStageFile[3] = { "Stage1.txt", "Stage2.txt", "Stage3.txt" };

	for (int i = 0; i < STAGE_MAX_COUNT; ++i)
	{
		m_pStage[i] = new CStage;

		if (!m_pStage[i]->Init(pStageFile[i]))
			return false;
	}

	return true;
}

void CMapManager::Run()
{
	while (true)
	{
		m_iEnableStage = OutputMenu();

		if (m_iEnableStage == 4)
			break;
	}
}

void CMapManager::Render()
{
	m_pStage[0]->Render();
}

int CMapManager::OutputMenu()
{
	system("cls");
	cout << "1. Stage1" << endl;
	cout << "2. Stage2" << endl;
	cout << "3. Stage3" << endl;
	cout << "4. 종료" << endl;
	cout << "Input Stage : ";
	int iInput = InputInt();

	if (iInput < 1 || iInput > 4)
		return 0;

	return iInput;
}
