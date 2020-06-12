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
	
	// CreateObject �Լ��� ���͸� �����ϰ� CObj* Ÿ���� �����Ѵ�.
	// �׷��� ������ �⺻ �������� ������ Ŭ������ character Ŭ������ ������ �����Ƿ�
	// ������ Ŭ������ ����ȯ�Ͽ� �����صΰ� ����� ����ϵ��� �Ѵ�.
	CMonster* pMonster = (CMonster*)CreateObject("Goblin", OT_MONSTER);

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

CObj* CObjectManager::FindObject(const string& strkey)
{
	// map�� find �Լ��� �������ش�. find �Լ��� key�� �־��ָ� �ش� Ű�� Ž���Ͽ�
	// ���� ��� �ش� Ű�� iterator �� ��ȯ�ϰ� ���� ��� end()�� ��ȯ�Ѵ�.
	unordered_map<string, CObj*>::iterator iter = m_mapObj.find(strkey);

	// end() �� ���� ã�� ���ߴٴ� ���̴�.
	if (iter == m_mapObj.end())
		return NULL; // NULL�� 0�̹Ƿ� ã�� ���ߴٴ� �ǹ̷� ����.

	return iter->second;
}
