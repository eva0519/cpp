
#include "Stage.h"
#include "FileStream.h"
#include "Player.h"
#include "ObjectManager.h"
#include "string"

CStage::CStage()
{
}

CStage::~CStage()
{
}

bool CStage::Init()
{
	return true;
}

bool CStage::Init(char* pFileName)
{
	CFileStream file;

	if (!file.Open(pFileName, "rt"))
		return false;

	for (int i = 0; i < 10; i++)
	{
		int iSize = 0;
		file.ReadLine(m_cOriginStage[i], iSize);

		for (int j = 0; j < 50; j++)
		{
			m_cStage[i][j] = m_cOriginStage[i][j];

			if (m_cOriginStage[i][j] == SBT_START)
			{
				m_tStart.x = j;
				m_tStart.y = i;
			}

			else if (m_cOriginStage[i][j] == SBT_END)
			{
				m_tEnd.x = j;
				m_tEnd.y = i;
			}
		}

	}


	return true;
}

void CStage::Render()
{
	/* 
	���� ��ũ�� ó���� �ؾ��Ѵ�. �׷��� ������ ���� �÷��̾
	�̵��� ��ġ�κ��� ���� ������־�� �Ѵ�. ��� ũ��� ����4ĭ
	���� 10ĭ���� ���ش�. ������ �÷��̾ ó���� �ִ� ��� �����ϰ�
	ó�� 4 x 10 ����� ���ش�.
	 0 : �� 1 : �� 2 : ������ 3 : ������ 4 : ����
	*/

	CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();

	// �÷��̾��� x, y ��ǥ�� ���´�.
	int iX = pPlayer->GetX();
	int iY = pPlayer->GetY();

	// ���� ����� �÷��̾��� ��ġ�� �߽����� ����Ѵ�.
	// ���δ� �÷��̾� 2ĭ ������ ��ĭ �Ʒ����� ����Ѵ�.
	// �� 5���� ��µǴ� ���̴�.
	// ���δ� �÷��̾� ��ġ���� ������ 10ĭ���� ����Ѵ�.

	// ���� ���� ���������� ��ũ�ѵǴٰ� ǥ�õǵ��� �����Ѵ�
	// ��µ� ������ 2�� �������־ ��µ� ���� �Ʒ��� �ε�����
	// �����ش�. �÷��̾� ��ġ���� 2ĭ �Ʒ����� ����ؾ� �ϱ� �����̴�.
	int iYCount = iY + (RENDER_BLOCK_Y / 2);
	// 2�� ������ ������ ������ �������� ������ �ؾ��Ѵ�.
	// ���Ʒ� 2ĭ. �÷��̾�� ���������� �� �Լ��� �ݺ��ǰ� �ֱ� ������
	// ���������� ���� ��ġ�� ����� ���� ��ĭ�� ���̰� �Ʒ��� ��ĭ��
	// ���̰� ����� ��.

	// ���� ��µ� �Ʒ� 2ĭ�� ���� ���� �Ʒ��� �������� ũ�ų� ���ٸ�
	// ��µ� �Ʒ� �ε����� ���� ������ �ε����� �����Ѵ�.
	if (iYCount >= BLOCK_Y)
		iYCount = BLOCK_Y - 1;

	// ����ؾ� �� �ּ� �ε����� �����ش�.
	// ����ؾ� �� ���� �Ʒ��� �ε������� ����ؾ� �� ���� - 1���� ���ְ� �Ǹ�
	// ����ؾ��� ���� �Ʒ��� �ε����� 9�̰� 5�� ��½� 9 - 4 �� �ǹǷ�
	// 5 ~ 9���� �ݺ��� �� �� �ֵ��� �ּҰ��� ����ش�.
	int iYMin = iYCount - (RENDER_BLOCK_Y - 1);

	// ���� �ּҰ��� 0���� �۴ٸ� �ε����� �����Ƿ� 0���� �������ش�.
	if (iYMin < 0)
		iYMin = 0;
	// �÷��̾��� ���� y���� 2��� �����ϰ� ���Ʒ� 2ĭ�� �������ϹǷ�
	// 0,1,3,4�� ���Ʒ� �ε����̴�. �÷��̾� ���簪�� 2�϶�
	// ���Ʒ� ī��Ʈ�� ���� iYCount�� 4�� �ǰ� - 4�� �ϸ� 0�� �ǹǷ�
	// �÷��̾� y�� 2���� -�ȴ�(�� ���� �ö󰣴�)�ص� ���� õ���� 0������
	// ����̵ǵ��� �ּҰ��� ���ع����� ��.

	// ������ �ִ� ��¼��� ���� �÷��̾� ��ġ + ����ؾ��� ���ΰ��� �̴�.
	int iXCount = iX + RENDER_BLOCK_X;

	// ����ؾ� �� ���� �ε����� �ִ�ġ�� ��ü �� ������ ũ�ٸ�
	// �߸��� �ε����̹Ƿ� �ִ� ������ �������ش�.
	// �Ʒ� for������ ������ �� ������ ������������ ������ �����̴�.
	if (iXCount > BLOCK_X)
		iXCount = BLOCK_X;

	// X�� �ּ� �ε����� �÷��̾��� ��ġ�̴�.
	int iXMin = iX;
	// ���� �������� 10ĭ�� ��� �����ֱ� ���ؼ� �ݺ����� �ּҰ���
	// �� ��ü���� - ��µ� ������ ó�����ش�.
	if (iXMin > BLOCK_X - RENDER_BLOCK_X)
		iXMin = BLOCK_X - RENDER_BLOCK_X;
	// ĳ������ ������ġ(iX)�� �� ������ 10ĭ�� �����ϸ�
	// iXMin ������ ���̻� iX ���� �����ʰ� ������ 10ĭ���� ������
	// �ϰ� ����� ��. �׻� �� ���� �Լ��� ������Ʈ �Լ��� �Բ� 0.1��
	// ������ �ݺ��ǰ� �ִٴ� ���� �����ؾ� �Ѵ�.

	// ���� define ���� �ٲٴ� �͸����� ���������� �����ϴ�.

	for (int i = iYMin; i <= iYCount; i++)
	{

		for (int j = iXMin; j < iXCount; j++)
		{
			if (i == iY && j == iX)
				cout << "��";

			// ���� ��ġ�� �Ѿ��� ���� ��� �Ѿ˷� ����Ѵ�.
			else if (CObjectManager::GetInst()->CheckBullet(j, i))
				cout << "��";

			else if (m_cStage[i][j] == SBT_WALL)
				cout << "��";

			else if (m_cStage[i][j] == SBT_ROAD)
				cout << "  ";

			else if (m_cStage[i][j] == SBT_START)
				cout << "��";

			else if (m_cStage[i][j] == SBT_END)
				cout << "��";

			else if (m_cStage[i][j] == SBT_COIN)
				cout << "��";

			else if (m_cStage[i][j] == SBT_ITEM_BULLET)
				cout << "��";

			else if (m_cStage[i][j] == SBT_ITEM_BIG)
				cout << "��";
		}

		cout << endl;

	}
}

void CStage::ResetStage()
{
	for (int i = 0; i < BLOCK_Y; i++)
	{
		for (int j = 0; j < BLOCK_X; j++)
		{
			m_cStage[i][j] = m_cOriginStage[i][j];
		}
	}
}
