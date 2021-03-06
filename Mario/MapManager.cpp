
#include "MapManager.h"
#include "Stage.h"
#include "Player.h"
#include "ObjectManager.h"

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

void CMapManager::Run(int iStage)
{
	CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();
	m_iEnableStage = iStage;

	m_pStage[iStage]->ResetStage();
	
	pPlayer->SetPos(m_pStage[iStage]->GetStart().x,
		m_pStage[iStage]->GetStart().y);

	while (true)
	{
		system("cls");
		// 출력수가 많을땐 아래 방법으로
		// 콘솔 커서를 처음으로 옮겨 다음 출력될 데이터를 덮어씌우는 방식으로
		// 깜박거림을 줄일 수 있다. 하지만 뒤에 올 출력문구가
		// 앞의 반복 출력문보다 짧을 경우엔 모두 지워지지 않는다.
		/*COORD pos = { 0,0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);*/

		if (GetAsyncKeyState('Q') & 0x8000)
			break;

		CObjectManager::GetInst()->Update();
		/*pPlayer->Update();*/
		m_pStage[iStage]->Update();
		m_pStage[iStage]->Render();
		cout << "Score : " << pPlayer->GetScore() << endl;

		if (pPlayer->GetComplete())
		{
			cout << "완료" << endl;
			pPlayer->Reset();
			system("pause");
			break;
		}

		// Win32 API 함수로 millonSecond 인자 단위로 멈추라는 명령이다.
		Sleep(100);
	}
}

void CMapManager::Render()
{
	m_pStage[0]->Render();
}
