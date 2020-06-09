#pragma once

#include "value.h"

class CStage
{
public:
	CStage();
	virtual ~CStage();

public:
	// ���� ���ʹ� �ٺ������� �θ� �����ͺ����̱� ������ �� �ڽ�(��������)���� 
	// �������� ����� ���� �Լ��� ������ְ� �ʹٸ� ���������Լ���
	// �����ؼ� �߻�Ŭ������ ����� �� �ڽĸ��� ���������Լ��� �����Ǹ� ���������Ѵ�.
	virtual bool Init() = 0;
	virtual void Run() = 0;
};