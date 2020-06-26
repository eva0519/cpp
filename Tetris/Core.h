#pragma once

#include "value.h"

class CCore
{
private:
	CCore();
	~CCore();

private:
	static CCore* m_pInst;

public:
	static CCore* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CCore;
		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	HANDLE	m_hConsole = {};

public:
	bool Init();
	void Run();
	void SetConsolePos(int x, int y);
};

