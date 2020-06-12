#pragma once

#include "value.h"

class CObjectManager
{
private:
	// map�� �⺻������ key, value�� �����Ǿ� �ִ�.
	// ù��° template Ÿ���� key, �ι�° template Ÿ���� value�̴�.
	// �׷��� Ÿ���� 2���� �������ְ� key�� �̿��ؼ� Ž���� �ϰ� �ȴ�.
	// ���� ���� value�� ������ Ÿ���� ���� �����ϴ� ���̴�.
	unordered_map<string, class CObj*> m_mapObj;

	// CObj�� include ���� �ʾұ� ������ ���漱������ ���� �־��ش�.
	// ���� �صα⿡ ���� ����� ���ؼ� ��ü ������ ���Ѵ�. �׷��� ������ ���� �����ϴ�.

public:
	bool Init();
	CObj* CreateObject(const string& strkey, OBJECT_TYPE eType);
	CObj* FindObject(const string& strkey);

	DECLARE_SINGLE(CObjectManager);
};

