#include "ShapeGun.h"

CShapeGun::CShapeGun()
{
}

CShapeGun::~CShapeGun()
{
}

bool CShapeGun::Init()
{
	if (!CShape::Init())
		return false;

	m_cShape[2][0] = '0';
	m_cShape[2][1] = '0';
	m_cShape[2][2] = '0';
	m_cShape[3][2] = '0';

	m_iWidthCount = 3;
	m_tPos.x = 4;
	m_tPos.y = 0;

	m_iDir = (int)ROTATION_DIR::RD_LEFT;

	return true;
}

void CShapeGun::Rotation()
{
	++m_iDir;

	m_iDir %= (int)ROTATION_DIR::RD_END;
	// m_iDir 이 end에 도달하면 다시 RD_UP~이 되도록 한다.
	// RandomShape에서 사용한 방법과 같다.

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_cShape[i][j] = '1';
		}
	}

	switch (m_iDir)
	{
	case (int)ROTATION_DIR::RD_UP:
		m_cShape[1][1] = '0';
		m_cShape[2][1] = '0';
		m_cShape[3][0] = '0';
		m_cShape[3][1] = '0';
		m_iWidthCount = 2;
		break;
	case (int)ROTATION_DIR::RD_RIGHT:
		m_cShape[2][0] = '0';
		m_cShape[3][0] = '0';
		m_cShape[3][1] = '0';
		m_cShape[3][2] = '0';
		m_iWidthCount = 3;
		break;
	case (int)ROTATION_DIR::RD_DOWN:
		m_cShape[1][0] = '0';
		m_cShape[2][0] = '0';
		m_cShape[3][0] = '0';
		m_cShape[1][1] = '0';
		m_iWidthCount = 2;
		break;
	case (int)ROTATION_DIR::RD_LEFT:
		m_cShape[2][0] = '0';
		m_cShape[2][1] = '0';
		m_cShape[2][2] = '0';
		m_cShape[3][2] = '0';
		m_iWidthCount = 3;
		break;
	}
}
