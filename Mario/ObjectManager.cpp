#include "ObjectManager.h"
#include "Player.h"

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
}

// �ʱ�ȭ�Ҷ� CPlayer �����Ҵ��ؼ� �־��ְ�
// �� �ȿ� �������� �̴� �Լ��� �ʱ���ġ ������ �� Ʈ��.
// ���� �����ϴ� �ھ�Ŭ������ ����.
bool CObjectManager::Init()
{
	m_pPlayer = new CPlayer;

	m_pPlayer->Init();

	return true;
}
