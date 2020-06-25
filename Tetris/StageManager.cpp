#include "StageManager.h"
#include "Stage.h"

CStageManager* CStageManager::m_pInst = NULL;
// static ������ ��� Ŭ���� �ܺο��� ��������� �Ѵ�.
// static�� ���������� ������ ������ ������ �����Ϳ����� �Ҵ�Ǳ� �����ε�
// static ������ Ŭ���� ���ο� �����ϰ� �����ڿ��� �ʱ�ȭ�Ѵٰ� �����ϸ�
// ��ü�� �����ɶ����� ���������� �ʱ�ȭ�Ǿ������ ���� �ǹǷ� �����ջ��� �ȴ�.
// �����޸� �������� �������� ����� �����޸𸮸� �ǵ�� ������ ���̱� ������
// �Ϲ� ��������� �ٸ��� ��ó�� �ʱ�ȭ�� ���ִ� ���̴�.
// �����ϰ� ���Ǹ� ���������� ������� �����ͺ��� ���� �ѵ� 
// �ּҰ� �������� �ʱ� ������ �ܺ����� ������ �߰Եȴ�.

CStageManager::CStageManager():
	m_pCurStage(NULL)
{
}

CStageManager::~CStageManager()
{
}

bool CStageManager::Init()
{
	// �⺻ ���������� �����Ѵ�.
	m_pCurStage = new CStage;

	if (!m_pCurStage->Init())
		return false;

	return true;
}

void CStageManager::Run()
{
	m_pCurStage->Render();
}