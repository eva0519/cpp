
#pragma once

#include "value.h"

enum JUMP_DIR
{
	JD_STOP,
	JD_UP,
	JD_DOWN
};

#define JUMP_BLOCK_MAX 2

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

private:
	POINT	m_tPos = {};
	bool	m_bJump = false;
	int		m_iJumpDir = JD_STOP;
	int		m_iJumpState = 0;
	int		m_iScore = 0;
	bool	m_bComplete = false;

public:
	int GetX()
	{
		return m_tPos.x;
	}

	int GetY()
	{
		return m_tPos.y;
	}

	int GetScore()
	{
		return m_iScore;
	}

	bool GetComplete()
	{
		return m_bComplete;
	}

public:
	void SetPos(int x, int y)
	{
		m_tPos.x = x;
		m_tPos.y = y;
	}

public:
	bool Init();
	void Update();
};

