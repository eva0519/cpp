#pragma once

#include "value.h"

// 일반함수의 경우 순수가상함수로 만들면 해당 헤더파일에 정의를 해선 안되지만
// 소멸자의 경우엔 정의를 해줘야 한다. 문법의 차이이므로 알아두자.

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

