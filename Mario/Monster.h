#pragma once

#include "value.h"

class CMonster
{
public:
	CMonster();
	~CMonster();

private:
	POINT	m_tPos = {};
	int		m_iDir = 0; // 움직일 방향이다.
	int		m_iSpeed = 0;
	int		m_iFrameCount = 0;

public:
	void SetPos(int x, int y)
	{
		m_tPos.x = x;
		m_tPos.y = y;
	}

public:
	POINT GetPos()
	{
		return m_tPos;
	}

public:
	bool Init();
	void Update();
};

