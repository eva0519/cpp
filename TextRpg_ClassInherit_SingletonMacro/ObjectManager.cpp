#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"

// �̰������� ���� ��ü������ ���־�� �ϹǷ� ���漱���� �ƴ�
// include�� �����Ѵ�. cpp�� include�� �ϸ� ������� include�ϴ� ��Ȳ��
// ������ �� �ֱ� ������ ��������� �ַ� �����͸� Ȱ���� ���漱���� �ϰ�
// cpp���� include�� �ϴ� ���̴�.

DEFINITION_SINGLE(CObjectManager);

CObjectManager::CObjectManager()
{

}

CObjectManager::~CObjectManager()
{

}

bool CObjectManager::Init()
{
	// �÷��̾ �����Ѵ�.
	CObj* pPlayer = CreateObject("Player", OT_PLAYER);

	return true;
}

CObj* CObjectManager::CreateObject(const string& strkey, OBJECT_TYPE eType)
{
	CObj* pObj = NULL;

	switch (eType)
	{
	case OT_PLAYER:
		pObj = new CPlayer;
		break;
	case OT_MONSTER:
		pObj = new CMonster;
		break;
	}

	if (!pObj->init())
	{
		SAFE_DELETE(pObj);
		return NULL;
	}

	// ���� key�� value�� �̿��ؼ� �����͸� �����ϱ� ������
	// make_pair�� �̿��ؼ� key�� value�� ��� �ʿ� insert �Ѵ�.
	m_mapObj.insert(make_pair(strkey, pObj));

	return pObj;
}
