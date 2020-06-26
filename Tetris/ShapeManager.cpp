#include "ShapeManager.h"
#include "Rectangle.h"

CShapeManager* CShapeManager::m_pInst = NULL;

CShapeManager::CShapeManager():
	m_pCurShape(NULL),
	m_pNextShape(NULL)
{
	m_pCurShape = CreateRandomShape();
}

CShapeManager::~CShapeManager()
{
	list<CShape*>::iterator iterEnd = m_ShapeList.end();
	// ���� ���� �̸� end �Լ��� ȣ���� �־�θ� �Ʒ������� �׳� ������ ���⸸ �ϸ� 
	// �ǹǷ� �ݺ������� ������ end()�Լ��� ȣ���� �ʿ䰡 ��������. 
	// ������ �ð����⵵�� 1�̳� n�̳��� ���̷� ����ȭ�� �����ϴ�.
	for (list<CShape*>::iterator iter = m_ShapeList.begin(); iter != iterEnd; 
		iter++)
	{
		SAFE_DELETE(*iter);
	}

	SAFE_DELETE(m_pCurShape);
	SAFE_DELETE(m_pNextShape);
}

void CShapeManager::Update()
{
	m_pCurShape->MoveDown();
}

void CShapeManager::Render()
{
	list<CShape*>::iterator iterEnd = m_ShapeList.end();
	for (list<CShape*>::iterator iter = m_ShapeList.begin(); iter != iterEnd;
		iter++)
	{
		(*iter)->Render();
	}

	m_pCurShape->Render();
}

CShape* CShapeManager::CreateRandomShape()
{
	int iType = rand() % static_cast<int>(SHAPE_TYPE::ST_END);
	// start enum class �� ������ �ʰ� end�� �������� ��������ν�
	// enum class type�� �߰��ɶ����� end�� ���� ������ ��
	// end�� ������ 0~end ���������� ��� ������ �����ϰ� ������ �Ѵ�.
	// start�� ������ start�� �������� �ϳ��� ���ԵǾ�����Ƿ� �����Ѱ�.
	// enum��� enum class�� ����� ���������ȯ�� �������ν� ��� �����Ѵ�.

	return CreateShape((SHAPE_TYPE)iType);
}

CShape* CShapeManager::CreateShape(SHAPE_TYPE eType)
{
	CShape* pShape = NULL;

	switch (eType)
	{
	case SHAPE_TYPE::ST_RECT:
		pShape = new CRectangle;
		break;
	}

	if (!pShape->Init())
	{
		SAFE_DELETE(pShape);
		return NULL;
	}

	return pShape;
}
