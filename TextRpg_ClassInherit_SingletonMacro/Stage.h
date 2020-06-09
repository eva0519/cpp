#pragma once

#include "value.h"

class CStage
{
public:
	CStage();
	virtual ~CStage();

public:
	// 현재 벡터는 근본적으로 부모 포인터변수이기 때문에 각 자식(스테이지)별로 
	// 개별적인 기능을 가진 함수를 만들어주고 싶다면 순수가상함수를
	// 선언해서 추상클래스로 만들고 각 자식마다 순수가상함수의 재정의를 만들어줘야한다.
	virtual bool Init() = 0;
	virtual void Run() = 0;
};