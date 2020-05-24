
#pragma once

#include "value.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

private:
	int m_iX;
	int m_iY;

public:
	int GetX()
	{
		return m_iX;
	}

	int GetY()
	{
		return m_iY;
	}

public:
	bool Init();

};

