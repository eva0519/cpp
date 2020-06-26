#pragma once

#include "value.h"

class CShapeManager
{
private:
	CShapeManager();
	~CShapeManager();

private:
	static CShapeManager* m_pInst;

public:
	static CShapeManager* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CShapeManager;
		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	// �ٴڿ� ���� ������ ǥ���Ѵ�.
	list<class CShape*> m_ShapeList;

	// ���� �����ִ� ������ ǥ���Ѵ�.
	class CShape* m_pCurShape;

	// ������ ���� ������ ǥ���Ѵ�.
	class CShape* m_pNextShape;

public:
	void Update();
	void Render();
	class CShape* CreateRandomShape();
	class CShape* CreateShape(SHAPE_TYPE eType);

};
