#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"

// 이곳에서는 실제 객체생성을 해주어야 하므로 전방선언이 아닌
// include가 들어가야한다. cpp에 include를 하면 헤더끼리 include하는 상황을
// 방지할 수 있기 때문에 헤더에서는 주로 포인터를 활용해 전방선언을 하고
// cpp에서 include를 하는 것이다.

DEFINITION_SINGLE(CObjectManager);

CObjectManager::CObjectManager()
{

}

CObjectManager::~CObjectManager()
{

}

bool CObjectManager::Init()
{
	// 플레이어를 생성한다.
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

	// 맵은 key와 value를 이용해서 데이터를 관리하기 때문에
	// make_pair를 이용해서 key와 value를 묶어서 맵에 insert 한다.
	m_mapObj.insert(make_pair(strkey, pObj));

	return pObj;
}
