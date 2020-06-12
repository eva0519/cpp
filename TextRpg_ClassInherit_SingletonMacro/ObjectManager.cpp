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
	
	// CreateObject 함수는 몬스터를 생성하고 CObj* 타입을 리턴한다.
	// 그런데 몬스터의 기본 변수들은 몬스터의 클래스나 character 클래스가 가지고 있으므로
	// 몬스터의 클래스로 형변환하여 저장해두고 기능을 사용하도록 한다.
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

	// 맵은 key와 value를 이용해서 데이터를 관리하기 때문에
	// make_pair를 이용해서 key와 value를 묶어서 맵에 insert 한다.
	m_mapObj.insert(make_pair(strkey, pObj));

	return pObj;
}

CObj* CObjectManager::FindObject(const string& strkey)
{
	// map은 find 함수를 제공해준다. find 함수에 key를 넣어주면 해당 키를 탐색하여
	// 있을 경우 해당 키의 iterator 를 반환하고 없을 경우 end()를 반환한다.
	unordered_map<string, CObj*>::iterator iter = m_mapObj.find(strkey);

	// end() 일 경우는 찾지 못했다는 것이다.
	if (iter == m_mapObj.end())
		return NULL; // NULL은 0이므로 찾지 못했다는 의미로 쓴다.

	return iter->second;
}
