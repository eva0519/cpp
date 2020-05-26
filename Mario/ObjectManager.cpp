#include "ObjectManager.h"
#include "Player.h"
#include "Bullet.h"

// ������������̱� ������ ���Ǻκ� �ʱ⿡ �ʱ�ȭ�����ش�.
CObjectManager* CObjectManager::m_pInst = NULL;

// ������Ʈ �Ŵ����� ������ �̴ϼȶ������� 
// ���漱���� m_pPlayer PlayerŬ���� ��ü �ʱ�ȭ.
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

// �ʱ�ȭ�Ҷ� CPlayer �����Ҵ��ؼ� �־��ְ�
// �� �ȿ� �������� �̴� �Լ��� �ʱ���ġ ������ �� Ʈ��.
// ���� �����ϴ� �ھ�Ŭ������ ����.
bool CObjectManager::Init()
{
	m_pPlayer = new CPlayer;

	m_pPlayer->Init();

	// 1�� ���ڿ� ���� ������ �޸� �ּҸ� �־��ش�.
	// 3�� ���ڴ� ���� ������ �޸� ũ�⸦ �־��ش�.
	// �̷��� ���ָ� 1���� �־��� �ּҺ��� 3���� �־��� �޸� ũ�⸸ŭ
	// 2�����ڿ� �� ������ �޸𸮸� �ʱ�ȭ���ش�.
	memset(m_pBullet, 0, sizeof(CBullet*) * BULLET_COUNT_MAX);
	// �ٵ� ������� �̹� �ʱ�ȭ�� �ؼ� ������ �ǹ̰� ������
	// ���߿� ������Ʈ �Ŵ��� �ʱ�ȭ�Լ����� ������ ����ؼ� ����.
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
}

bool CObjectManager::CreateBullet(POINT tPos)
{
	// �Ѿ� ������ �Ѿ��� �̹� �ִ�ġ��� ���̻� �������� �ʴ´�.
	if (m_iCurBulletCount == BULLET_COUNT_MAX)
		return false;
	
	// �Ѿ��� �����Ѵ�.
	CBullet* pBullet = new CBullet;

	// �Ѿ��� �ʱ�ȭ�Ѵ�. �Ѿ� �ʱ�ȭ ���н� ������ �Ѿ��� �����
	// false�� ��ȯ�Ѵ�.
	if (!pBullet->Init())
	{
		SAFE_DELETE(pBullet);
		return false;
	}

	// ���ڷ� ���� ��ġ�� �Ѿ��� ��ġ�� �����Ѵ�.
	pBullet->SetPos(tPos.x, tPos.y);

	m_pBullet[m_iCurBulletCount] = pBullet;
	++m_iCurBulletCount;

	return true;
}

// �� �Լ��� �ش� ��ġ�� �Ѿ��� �ִ����� �Ѿ˸�Ͽ��� �˻����ش�.
// ���� ��� true, ���� ��� false�� ��ȯ�ϰ� �Ͽ� �ش� ��ġ�� �Ѿ���
// �ִ����� �Ǵ��Ѵ�.
bool CObjectManager::CheckBullet(int x, int y)
{
	// ���� �Ѿ��� �߰��� ����ŭ �ݺ��ϸ� �� �Ѿ˵��� ��ġ�� üũ�Ѵ�.
	for (int i = 0; i < m_iCurBulletCount; i++)
	{
		// �Ѿ��� ��ġ�� ���ڷ� ���� ��ġ�� ���ٸ� �Ѿ��̹Ƿ� true��
		// �����Ѵ�.
		if (m_pBullet[i]->GetPos().x == x && m_pBullet[i]->GetPos().y == y)
			return true;
	}



	return false;
}
