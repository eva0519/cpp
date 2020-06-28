#include "Stage.h"
#include "Core.h"
#include "Shape.h"

CStage::CStage() :
	m_iSpeed(2)
{
}

CStage::~CStage()
{
}

void CStage::AddBlock(class CShape* pShape, const POSITION& tPos)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (pShape->GetBlock(j,i) == '0')
			{
				m_Stage[tPos.y - (3 - i)][tPos.x + j] = '0';
			}
		}
	}
}

bool CStage::CheckBlock(int x, int y)
{
	// 바닥에 닿았을 경우에도 true를 리턴한다.
	if (y >= STAGE_HEIGHT)
		return true;

	else if (x < 0 || x >= STAGE_WIDTH)
		return true;

	return m_Stage[y][x] == '0';
}

bool CStage::Init()
{
	for (int i = 0; i < STAGE_HEIGHT; ++i)
	{
		for (int j = 0; j < STAGE_WIDTH; ++j)
		{
			m_Stage[i][j] = '1';
		}
	}

	return true;
}

void CStage::Render()
{
	for (int i = 0; i < STAGE_HEIGHT + 1; ++i)
	{
		for (int j = 0; j < STAGE_WIDTH + 2; ++j)
		{
			if (i == 0 && (j == 0 || j == STAGE_WIDTH + 1))
				cout << "■";

			else if (j == 0)
				cout << "■";

			else if (i == STAGE_HEIGHT)
				cout << "■";

			else if (j == STAGE_WIDTH + 1)
				cout << "■";

			else
			{
				if (m_Stage[i][j - 1] == '1')
					cout << "  ";

				else
					cout << "■";
			}
		}

		cout << endl;
	}

	for (int i = 0; i < 7; i++)
	{
		CCore::GetInst()->SetConsolePos(17, i);
		cout << "■";

		for (int j = 0; j < 6; j++)
		{
			CCore::GetInst()->SetConsolePos(11 + i, 6);
			cout << "■";
		}
	}
}
