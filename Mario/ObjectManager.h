#pragma once

#include "value.h"

// static을 붙이면 클래스 객체가 만들어져도 한개의 static 변수나 함수를 공유한다.
// 정적할당으로 따로 메모리 영역을 차지해 프로그램 실행시 불러오고 종료시 해제되기 
// 때문에 다른 멤버변수, 함수와 메모리 영역이 달라 클래스 객체가 하나도 
// 존재하지 않아도 클래스명::정적멤버변수 or 함수로 호출이 가능하다.
// 클래스 내부 및 상속 클래스 외에도 쓰고싶으면 public으로 선언해주면 된다.

/*
정적 멤버 함수
1. 객체를 생성하지 않고 클래스 이름만으로 호출할 수 있습니다.
2. 객체를 생성하지 않으므로, this 포인터를 가지지 않습니다.
3. 특정 객체와 결합하지 않으므로, 정적 멤버 변수밖에 사용할 수 없습니다.
*/

class CObjectManager
{
private:
	CObjectManager();
	~CObjectManager();

private:
	static CObjectManager* m_pInst;

public:
	static CObjectManager* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CObjectManager;
		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	// 가장 위에 하는 것이 아닌 해당 타입을 사용하고자 할때 전방선언을
	// 해줄 수도 있다.
	class CPlayer* m_pPlayer;

public:
	class CPlayer* GetPlayer()
	{
		return m_pPlayer;
	}

public:
	bool Init();
};

