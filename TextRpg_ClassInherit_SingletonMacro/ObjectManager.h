#pragma once

#include "value.h"

class CObjectManager
{
private:
	// map은 기본적으로 key, value로 구성되어 있다.
	// 첫번째 template 타입이 key, 두번째 template 타입이 value이다.
	// 그래서 타입을 2개를 지정해주고 key를 이용해서 탐색을 하게 된다.
	// 실제 값은 value에 지정된 타입의 값을 저장하는 것이다.
	unordered_map<string, class CObj*> m_mapObj;

	// CObj를 include 하진 않았기 때문에 전방선언으로 값을 넣어준다.
	// 선언만 해두기에 실제 사용은 못해서 객체 생성은 못한다. 그래서 포인터 선언만 가능하다.

public:
	bool Init();
	CObj* CreateObject(const string& strkey, OBJECT_TYPE eType);
	CObj* FindObject(const string& strkey);

	DECLARE_SINGLE(CObjectManager);
};

