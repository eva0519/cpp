
#include "Stage.h"
#include "FileStream.h"
#include "Player.h"
#include "ObjectManager.h"
#include "string"
#include "Monster.h"

CStage::CStage():
	m_pMonsterArray(NULL),
	m_iMonsterCount(0),
	m_iMonsterArrayCount(0)
{
}

CStage::~CStage()
{
}

bool CStage::Init()
{
	return true;
}

bool CStage::Init(char* pFileName)
{
	CFileStream file;

	if (!file.Open(pFileName, "rt"))
		return false;

	for (int i = 0; i < 10; i++)
	{
		int iSize = 0;
		file.ReadLine(m_cOriginStage[i], iSize);

		for (int j = 0; j < 50; j++)
		{
			m_cStage[i][j] = m_cOriginStage[i][j];

			if (m_cOriginStage[i][j] == SBT_START)
			{
				m_tStart.x = j;
				m_tStart.y = i;
			}

			else if (m_cOriginStage[i][j] == SBT_END)
			{
				m_tEnd.x = j;
				m_tEnd.y = i;
			}

			else if (m_cOriginStage[i][j] == SBT_MONSTER)
			{
				CreateMonster(j, i);
			}
		}

	}


	return true;
}

void CStage::Render()
{
	/* 
	맵은 스크롤 처리를 해야한다. 그렇기 때문에 현재 플레이어가
	이동한 위치로부터 맵을 출력해주어야 한다. 출력 크기는 세로4칸
	가로 10칸으로 해준다. 지금은 플레이어가 처음에 있다 라고 가정하고
	처음 4 x 10 출력을 해준다.
	 0 : 벽 1 : 길 2 : 시작점 3 : 도착점 4 : 코인
	*/

	CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();

	// 플레이어의 x, y 좌표를 얻어온다.
	int iX = pPlayer->GetX();
	int iY = pPlayer->GetY();

	// 맵의 출력은 플레이어의 위치를 중심으로 출력한다.
	// 세로는 플레이어 2칸 위부터 한칸 아래까지 출력한다.
	// 총 5줄이 출력되는 것이다.
	// 가로는 플레이어 위치부터 오른쪽 10칸까지 출력한다.

	// 맵의 골인 지점까지만 스크롤되다가 표시되도록 제한한다
	// 출력될 블럭수를 2로 나누어주어서 출력될 가장 아래쪽 인덱스를
	// 구해준다. 플레이어 위치보다 2칸 아래까지 출력해야 하기 때문이다.
	int iYCount = iY + (RENDER_BLOCK_Y / 2);
	// 2로 나누는 이유는 점프를 했을때도 생각을 해야한다.
	// 위아래 2칸. 플레이어와 스테이지쪽 두 함수가 반복되고 있기 때문에
	// 점프했을때 현재 위치에 기반해 위로 두칸이 보이고 아래로 두칸이
	// 보이게 만드는 것.

	// 만약 출력될 아래 2칸이 맵의 가장 아래쪽 개수보다 크거나 같다면
	// 출력될 아래 인덱스를 가장 마지막 인덱스로 제한한다.
	if (iYCount >= BLOCK_Y)
		iYCount = BLOCK_Y - 1;

	// 출력해야 할 최소 인덱스를 구해준다.
	// 출력해야 할 가장 아래쪽 인덱스에서 출력해야 할 개수 - 1개를 빼주게 되면
	// 출력해야할 가장 아래쪽 인덱스가 9이고 5개 출력시 9 - 4 가 되므로
	// 5 ~ 9까지 반복이 돌 수 있도록 최소값을 잡아준다.
	int iYMin = iYCount - (RENDER_BLOCK_Y - 1);

	// 만약 최소값이 0보다 작다면 인덱스가 없으므로 0으로 제한해준다.
	if (iYMin < 0)
		iYMin = 0;
	// 플레이어의 현재 y값을 2라고 가정하고 위아래 2칸씩 보여야하므로
	// 0,1,3,4가 위아래 인덱스이다. 플레이어 현재값이 2일때
	// 위아래 카운트를 위한 iYCount가 4가 되고 - 4를 하면 0이 되므로
	// 플레이어 y가 2에서 -된다(더 위로 올라간다)해도 맨위 천장인 0까지만
	// 출력이되도록 최소값을 정해버리는 것.

	// 가로줄 최대 출력수는 현재 플레이어 위치 + 출력해야할 가로개수 이다.
	int iXCount = iX + RENDER_BLOCK_X;

	// 출력해야 할 가로 인덱스르 최대치가 전체 블럭 수보다 크다면
	// 잘못된 인덱스이므로 최대 블럭수로 제한해준다.
	// 아래 for문에서 구해준 이 값보다 작을때까지만 돌리기 때문이다.
	if (iXCount > BLOCK_X)
		iXCount = BLOCK_X;

	// X의 최소 인덱스는 플레이어의 위치이다.
	int iXMin = iX;
	// 가장 마지막길 10칸은 모두 보여주기 위해서 반복문의 최소값을
	// 블럭 전체길이 - 출력될 블럭으로 처리해준다.
	if (iXMin > BLOCK_X - RENDER_BLOCK_X)
		iXMin = BLOCK_X - RENDER_BLOCK_X;
	// 캐릭터의 현재위치(iX)가 블럭 마지막 10칸에 도달하면
	// iXMin 변수는 더이상 iX 값을 보지않고 마지막 10칸부터 랜더를
	// 하게 만드는 것. 항상 이 랜더 함수는 업데이트 함수와 함께 0.1초
	// 단위로 반복되고 있다는 것을 생각해야 한다.

	// 이제 define 값을 바꾸는 것만으로 설정변경이 가능하다.

	for (int i = iYMin; i <= iYCount; i++)
	{

		for (int j = iXMin; j < iXCount; j++)
		{
			if ((i == iY || (i == iY - 1 && pPlayer->GetBigItemEnable())) 
				&& j == iX)
				cout << "§";

			// 현재 위치에 총알이 있을 경우 총알로 출력한다.
			else if (CObjectManager::GetInst()->CheckBullet(j, i))
				cout << "★";

			else if (m_cStage[i][j] == SBT_WALL)
				cout << "■";

			else if (m_cStage[i][j] == SBT_ROAD)
				cout << "  ";

			else if (m_cStage[i][j] == SBT_START)
				cout << "◑";

			else if (m_cStage[i][j] == SBT_END)
				cout << "◐";

			else if (m_cStage[i][j] == SBT_COIN)
				cout << "＠";

			else if (m_cStage[i][j] == SBT_ITEM_BULLET)
				cout << "♥";

			else if (m_cStage[i][j] == SBT_ITEM_BIG)
				cout << "◎";

			else if (m_cStage[i][j] == SBT_MONSTER)
				cout << "◆";
		}

		cout << endl;

	}
}

void CStage::ResetStage()
{
	for (int i = 0; i < BLOCK_Y; i++)
	{
		for (int j = 0; j < BLOCK_X; j++)
		{
			m_cStage[i][j] = m_cOriginStage[i][j];
		}
	}
}

CMonster* CStage::CreateMonster(int x, int y)
{
	// 배열이 동적할당 되지 않았을 경우 동적할당 해준다.
	if (!m_pMonsterArray)
	{
		m_iMonsterArrayCount = 2;
		m_pMonsterArray = new CMonster * [m_iMonsterArrayCount];
	}

	// 만약 몬스터가 꽉 차있을 경우 배열을 늘려준다.
	if (m_iMonsterCount == m_iMonsterArrayCount)
	{
		// 공간을 늘려서 할당해준다.
		m_iMonsterArrayCount *= 2;
		CMonster** ppArray = new CMonster * [m_iMonsterArrayCount];

		// 기존에 있는 주소 정보를 이 배열로 옮겨준다.
		// memcpy : 메모리 복사 함수이다.
		// 1번인자에 들어간 메모리 주소에 2번인자에 들어간 메모리 주소로부터
		// 3번인자에 들어간 바이트 수만큼 메모리를 복사한다.
		// 몬스터가 꽉찼다면 기존 배열은 이미 가득 차있다.
		// 그래서 위에서 공간을 2배만큼 동적배열로 할당해주고
		// 아래에서 새로 할당한 공간이 예를 들어 20개라면 기존 공간은
		// 10개이다. 기존 공간의(2번인자) 동적할당된 메모리 주소들을
		// 새로 할당된 공간으로 10개만큼 복사해주는 것이다.
		memcpy(ppArray, m_pMonsterArray, sizeof(CMonster*) * m_iMonsterCount);
		delete[]	m_pMonsterArray;

		m_pMonsterArray = ppArray;
	}

	// 실제 몬스터 객체를 할당한다.
	CMonster* pMonster = new CMonster;

	if (!pMonster->Init())
	{
		SAFE_DELETE(pMonster);
		return NULL;
	}

	// 몬스터 위치정보를 설정한다.
	pMonster->SetPos(x, y);

	// 몬스터 배열에 넣어준다.
	m_pMonsterArray[m_iMonsterCount] = pMonster;
	++m_iMonsterCount;

	return pMonster;
}
