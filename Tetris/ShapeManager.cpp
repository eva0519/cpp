#include "ShapeManager.h"
#include "Rectangle.h"
#include "StageManager.h"
#include "Stage.h"

CShapeManager* CShapeManager::m_pInst = NULL;

CShapeManager::CShapeManager():
	m_pCurShape(NULL),
	m_pNextShape(NULL)
{
	m_pCurShape = CreateRandomShape();
	m_iSpeed = 0;
}

CShapeManager::~CShapeManager()
{
	list<CShape*>::iterator iterEnd = m_ShapeList.end();
	// 위와 같이 미리 end 함수를 호출해 넣어두면 아래에서는 그냥 가져다 쓰기만 하면 
	// 되므로 반복문에서 번번이 end()함수를 호출할 필요가 없어진다. 
	// 때문에 시간복잡도가 1이냐 n이냐의 차이로 최적화가 가능하다.
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
	CStage* pStage = CStageManager::GetInst()->GetCurrentStage();

	++m_iSpeed;

	if (pStage->GetSpeed() == m_iSpeed)
	{
		m_pCurShape->MoveDown();
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
	// start enum을 만들지 않고 end의 나머지를 사용함으로써
	// enum class type이 추가될때마다 end로 나눈 나머지 즉
	// end를 제외한 0~end 이전까지의 모든 도형중 랜덤하게 나오게 한다.
	// start가 있으면 start도 랜덤수중 하나로 포함되어버리므로 제외한것.
	// enum대신 enum class를 사용해 명시적형변환을 해줌으로써 경고를 제거한다.

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
