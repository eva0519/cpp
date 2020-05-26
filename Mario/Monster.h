#pragma once

#include "value.h"

class CMonster
{
public:
	CMonster();
	~CMonster();

private:
	POINT m_tPos = {};

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
};

