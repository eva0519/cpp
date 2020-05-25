#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	m_iX = 0;
	m_iY = 8;

	m_bJump = false;
	m_iJumpDir = JD_STOP;
	m_iJumpState = 0;

	return true;
}

void CPlayer::Update()
{
	// Ű �Է��� �޴´�.
	// GetAsyncKeyState �Լ��� Win32 API ���� �����Ǵ� Ű �Է� �Լ��̴�.
	// WŰ�� �������� �ٷ� �����ϰ� �ϱ� ���ؼ� 0x8000 �� &������ �Ͽ�
	// ������ ��� true�� ������ �ȴ�.
	if (GetAsyncKeyState('A') & 0x8000)
	{
		--m_iX;

		if (m_iX < 0)
			m_iX = 0;
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		++m_iX;
		if (m_iX >= 50)
			m_iX = 49;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && !m_bJump)
	{
		m_bJump = true;
		m_iJumpDir = JD_UP;
		m_iJumpState = 0;
	}

	if (m_bJump)
	{
		switch (m_iJumpDir)
		{
		case JD_UP:
			++m_iJumpState;

			if (m_iJumpState > JUMP_BLOCK_MAX)
			{
				m_iJumpState = JUMP_BLOCK_MAX;
				m_iJumpDir = JD_DOWN;
			}

			else
			{
				--m_iY;
			}

			break;

		case JD_DOWN:
			--m_iJumpState;

			break;
		}
	}
}
