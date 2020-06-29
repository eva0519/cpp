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
		// true일 경우 바닥에 닿았으므로 리스트에 추가하고 다음 도형을 현재 도형으로
		// 만들어준다. 그 후에 다음 도형을 생성한다.
		if (m_pCurShape->MoveDown())
		{
			// 지워주기 전에 블럭을 추가해준다.
			pStage->AddBlock(m_pCurShape, m_pCurShape->GetPosition());

			SAFE_DELETE(m_pCurShape);

			m_pCurShape = m_pNextShape;
			m_pCurShape->SetPosition(4, 0);

			m_pNextShape = CreateRandomShape();
		}
		m_iSpeed = 0;
	}

	// GetAsyncKeyState 함수는 비동기 처리
	// GetKeyStage 함수는 호출된 시점에서 메시지큐를 거친다.
	// GetAsyncKeyState 함수는 키가 바로 이전에 눌렸는가 혹은 눌려져 있는가
	// 누르지 않았는가를 0x8000, 0x8001, 0x0001, 0x0000 중에
	// 무엇이 리턴되었는가를 통해 제어할 수 있다.
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
	// start enum을 만들지 않고 end의 나머지를 사용함으로써
	// enum class type이 추가될때마다 end로 나눈 나머지 즉
	// end를 제외한 0~end 이전까지의 모든 도형중 랜덤하게 나오게 한다.
	// start가 있으면 start도 랜덤수중 하나로 포함되어버리므로 제외한것.
	// enum대신 enum class를 사용해 명시적형변환을 해줌으로써 경고를 제거한다.
	// (int)SHAPE_TYPE::ST_LINE; 그냥 이렇게 형변환 해줘도 된다.
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
