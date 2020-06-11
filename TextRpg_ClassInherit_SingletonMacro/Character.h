#pragma once
#include "Obj.h"
class CCharacter :
	public CObj
{
protected:
	CCharacter();
	virtual ~CCharacter() = 0;

public:
	virtual bool init();
};

