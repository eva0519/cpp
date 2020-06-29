#include "ShapeManager.h"
#include "Rectangle.h"
#include "StageManager.h"
#include "Stage.h"
#include "ShapeGun.h"
#include "ShapeRGun.h"
#include "ShapeLine.h"
#include "ShapeZ.h"
#include "ShapeS.h"
#include "ShapeT.h"

CShapeManager* CShapeManager::m_pInst = NULL;

CShapeManager::CShapeManager():
	m_pCurShape(NULL),
	m_pNextShape(NULL)
{
	m_pCurShape = CreateRandomShape();
	m_pNextShape = CreateRandomShape();
	m_iSpeed = 0;
}

CShapeManager::~CShapeManager()
{
	SAFE_DELETE(m_pCurShape);
	SAFE_DELETE(m_pNextShape);
}

void CShapeManager::Update()
{
	CStage* pStage = CStageManager::GetInst()->GetCurrentStage();

	++m_iSpeed;

	if (pStage->GetSpeed() == m_iSpeed)
	{
		// true�� ��� �ٴڿ� ������Ƿ� ����Ʈ�� �߰��ϰ� ���� ������ ���� ��������
		// ������ش�. �� �Ŀ� ���� ������ �����Ѵ�.
		if (m_pCurShape->MoveDown())
		{
			// �����ֱ� ���� ���� �߰����ش�.
			pStage->AddBlock(m_pCurShape, m_pCurShape->GetPosition());

			SAFE_DELETE(m_pCurShape);

			m_pCurShape = m_pNextShape;
			m_pCurShape->SetPosition(4, 0);

			m_pNextShape = CreateRandomShape();
		}
		m_iSpeed = 0;
	}

	// GetAsyncKeyState �Լ��� �񵿱� ó��
	// GetKeyStage �Լ��� ȣ��� �������� �޽���ť�� ��ģ��.
	// GetAsyncKeyState �Լ��� Ű�� �ٷ� ������ ���ȴ°� Ȥ�� ������ �ִ°�
	// ������ �ʾҴ°��� 0x8000, 0x8001, 0x0001, 0x0000 �߿�
	// ������ ���ϵǾ��°��� ���� ������ �� �ִ�.
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_pCurShape->MoveLeft();
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_pCurShape->MoveRight();
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_pCurShape->Rotation();
	}
}

void CShapeManager::Render()
{
	m_pCurShape->Render();

	m_pNextShape->SetPosition(12, 4);
	m_pNextShape->RenderNext();
}

CShape* CShapeManager::CreateRandomShape()
{
	int iType = rand() % static_cast<int>(SHAPE_TYPE::ST_END);
	// start enum�� ������ �ʰ� end�� �������� ��������ν�
	// enum class type�� �߰��ɶ����� end�� ���� ������ ��
	// end�� ������ 0~end ���������� ��� ������ �����ϰ� ������ �Ѵ�.
	// start�� ������ start�� �������� �ϳ��� ���ԵǾ�����Ƿ� �����Ѱ�.
	// enum��� enum class�� ����� ���������ȯ�� �������ν� ��� �����Ѵ�.
	// (int)SHAPE_TYPE::ST_LINE; �׳� �̷��� ����ȯ ���൵ �ȴ�.
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

	case SHAPE_TYPE::ST_LINE:
		pShape = new CShapeLine;
		break;

	case SHAPE_TYPE::ST_GUN:
		pShape = new CShapeGun;
		break;

	case SHAPE_TYPE::ST_RGUN:
		pShape = new CShapeRGun;
		break;

	case SHAPE_TYPE::ST_T:
		pShape = new CShapeT;
		break;

	case SHAPE_TYPE::ST_Z:
		pShape = new CShapeZ;
		break;

	case SHAPE_TYPE::ST_S:
		pShape = new CShapeS;
		break;
	}

	if (!pShape->Init())
	{
		SAFE_DELETE(pShape);
		return NULL;
	}

	return pShape;
}
