#pragma once

#include "value.h"

class CStageManager
{
private:
	CStageManager();
	~CStageManager();

private:
	static CStageManager* m_pInst;

public:
	static CStageManager* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CStageManager;
		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

public:
	bool Init();
	void Run();
};