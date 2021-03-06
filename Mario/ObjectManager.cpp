#include "ObjectManager.h"
#include "Player.h"
#include "Bullet.h"

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

	for (int i = 0; i < m_iCurBulletCount; ++i)
	{
		SAFE_DELETE(m_pBullet[i]);
	}
}

// 초기화할때 CPlayer 동적할당해서 넣어주고
// 그 안에 만들어놓은 이닛 함수로 초기위치 설정한 뒤 트루.
// 최종 관리하는 코어클래스랑 연결.
bool CObjectManager::Init()
{
	m_pPlayer = new CPlayer;

	m_pPlayer->Init();

	// 1번 인자에 값을 세팅할 메모리 주소를 넣어준다.
	// 3번 인자는 값을 세팅할 메모리 크기를 넣어준다.
	// 이렇게 해주면 1번에 넣어준 주소부터 3번에 넣어준 메모리 크기만큼
	// 2번인자에 들어간 값으로 메모리를 초기화해준다.
	memset(m_pBullet, 0, sizeof(CBullet*) * BULLET_COUNT_MAX);
	// 근데 헤더에서 이미 초기화를 해서 당장은 의미가 없지만
	// 나중에 오브젝트 매니저 초기화함수만을 쓸때를 대비해서 쓴다.
	m_iCurBulletCount = 0;

	return true;
}

void CObjectManager::Update()
{
	m_pPlayer->Update();

	for (int i = 0; i < m_iCurBulletCount; i++)
	{
		m_pBullet[i]->Update();
	}

	for (int i = 0; i < m_iCurBulletCount;)
	{
		// 총알이 삭제되어야 할 경우
		if (!m_pBullet[i]->GetEnable())
		{
			delete m_pBullet[i];

			for (int j = i; j < m_iCurBulletCount - 1; j++)
			{
				m_pBullet[j] = m_pBullet[j + 1];
			}

			// 가장 마지막 인덱스를 NULL로 초기화한다.
			m_pBullet[m_iCurBulletCount - 1] = NULL;

			--m_iCurBulletCount;
		}

		// 총알이 삭제되지 않을 경우 i를 증가시킨다.
		else
			++i;
		// 첫 for문에 i증감식이 있을경우 그리고 삭제할 총알이 있을 경우
		// 그 다음 반복문에서 삭제된 메모리주소를 건너 뛰어 버리므로 for문의
		// 증감식을 지우고, 총알이 삭제되지 않았을 경우에만 i 증감식이 작동하게 한다.
		// 예를들어 2번인덱스가 총알이라 지워지고 3번인덱스가 2번 인덱스가 되면
		// 앞에는 2번 인덱스를 검사한 뒤에 총알이라 판명하고 지웠을 것이기 때문에
		// 2번 인덱스에 대한 검사가 끝나게 된다. 하지만
		// 3번이 2번으로 온시점에서 2번 인덱스는 새로운 데이터가 되었기에
		// 새로 검사해야하는 것이다. 그렇기에 제자리에서 한번더 검사를 하고
		// 이미 이전 반복에서 사라졌기에 그 다음은 else문으로 가 증감식을 진행하게 한다.
	}
}

bool CObjectManager::CreateBullet(POINT tPos)
{
	// 총알 생성시 총알이 이미 최대치라면 더이상 생성하지 않는다.
	if (m_iCurBulletCount == BULLET_COUNT_MAX)
		return false;
	
	// 총알을 생성한다.
	CBullet* pBullet = new CBullet;

	// 총알을 초기화한다. 총알 초기화 실패시 생성한 총알을 지우고
	// false를 반환한다.
	if (!pBullet->Init())
	{
		SAFE_DELETE(pBullet);
		return false;
	}

	// 인자로 들어온 위치로 총알의 위치를 설정한다.
	pBullet->SetPos(tPos.x, tPos.y);

	m_pBullet[m_iCurBulletCount] = pBullet;
	++m_iCurBulletCount;

	return true;
}

// 이 함수는 해당 위치에 총알이 있는지를 총알목록에서 검사해준다.
// 있을 경우 true, 없을 경우 false를 반환하게 하여 해당 위치에 총알이
// 있는지를 판단한다.
bool CObjectManager::CheckBullet(int x, int y)
{
	// 실제 총알이 추가된 수만큼 반복하며 각 총알들의 위치를 체크한다.
	for (int i = 0; i < m_iCurBulletCount; i++)
	{
		// 총알의 위치와 인자로 들어온 위치가 같다면 총알이므로 true를
		// 리턴한다.
		if (m_pBullet[i]->GetPos().x == x && m_pBullet[i]->GetPos().y == y)
			return true;
	}



	return false;
}
