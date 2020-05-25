#pragma once

#include "value.h"

// static�� ���̸� Ŭ���� ��ü�� ��������� �Ѱ��� static ������ �Լ��� �����Ѵ�.
// �����Ҵ����� ���� �޸� ������ ������ ���α׷� ����� �ҷ����� ����� �����Ǳ� 
// ������ �ٸ� �������, �Լ��� �޸� ������ �޶� Ŭ���� ��ü�� �ϳ��� 
// �������� �ʾƵ� Ŭ������::����������� or �Լ��� ȣ���� �����ϴ�.
// Ŭ���� ���� �� ��� Ŭ���� �ܿ��� ��������� public���� �������ָ� �ȴ�.

/*
���� ��� �Լ�
1. ��ü�� �������� �ʰ� Ŭ���� �̸������� ȣ���� �� �ֽ��ϴ�.
2. ��ü�� �������� �����Ƿ�, this �����͸� ������ �ʽ��ϴ�.
3. Ư�� ��ü�� �������� �����Ƿ�, ���� ��� �����ۿ� ����� �� �����ϴ�.
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
	// ���� ���� �ϴ� ���� �ƴ� �ش� Ÿ���� ����ϰ��� �Ҷ� ���漱����
	// ���� ���� �ִ�.
	class CPlayer* m_pPlayer;

public:
	class CPlayer* GetPlayer()
	{
		return m_pPlayer;
	}

public:
	bool Init();
};

