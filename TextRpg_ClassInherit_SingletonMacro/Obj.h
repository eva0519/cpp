#pragma once

#include "value.h"

// �Ϲ��Լ��� ��� ���������Լ��� ����� �ش� ������Ͽ� ���Ǹ� �ؼ� �ȵ�����
// �Ҹ����� ��쿣 ���Ǹ� ����� �Ѵ�. ������ �����̹Ƿ� �˾Ƶ���.

class CObj
{
protected:
	CObj();
	virtual ~CObj() = 0;

private:
	friend class CObjectManager;

public:
	virtual bool init();
};

