
#include "Stage.h"
#include "FileStream.h"
#include "Player.h"
#include "ObjectManager.h"
#include "string"
#include "Monster.h"

CStage::CStage():
	m_pMonsterArray(NULL),
	m_iMonsterCount(0),
	m_iMonsterArrayCount(0)
{
}

CStage::~CStage()
{
	for (int i = 0; i < m_iMonsterCount; i++)
	{
		SAFE_DELETE(m_pMonsterArray[i]);
	}

	delete[]	m_pMonsterArray;
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

			else if (m_cOriginStage[i][j] == SBT_MONSTER)
			{
				CreateMonster(j, i);

				// 7�� �κ��� üũ�Ͽ� ���� ������ �ϰ� ROAD��
				// ���� ���� �ٲ��ش�.
				m_cStage[i][j] = SBT_ROAD;
			}
		}

	}


	return true;
}

void CStage::Update()
{
	for (int i = 0; i < m_iMonsterCount; i++)
	{
		m_pMonsterArray[i]->Update();
	}
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
			if ((i == iY || (i == iY - 1 && pPlayer->GetBigItemEnable()))
				&& j == iX)
				cout << "��";

			// ���� ��ġ�� �Ѿ��� ���� ��� �Ѿ˷� ����Ѵ�.
			else if (CObjectManager::GetInst()->CheckBullet(j, i))
				cout << "��";

			// ���Ͱ� ���� ��ġ�� �ִٸ� ���ͷ� ����Ѵ�.
			else if (CheckMonster(j, i))
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
	for (int i = 0; i < m_iMonsterCount; i++)
	{
		SAFE_DELETE(m_pMonsterArray[i]);
	}

	m_iMonsterCount = 0;

	for (int i = 0; i < BLOCK_Y; i++)
	{
		for (int j = 0; j < BLOCK_X; j++)
		{
			m_cStage[i][j] = m_cOriginStage[i][j];

			if (m_cOriginStage[i][j] == SBT_MONSTER)
			{
				CreateMonster(j, i);
				// 7�� �κ��� üũ�Ͽ� ���� ������ �ϰ� ROAD��
				// ���� ���� �ٲ��ش�.
				m_cStage[i][j] = SBT_ROAD;
			}
		}
	}
}

CMonster* CStage::CreateMonster(int x, int y)
{
	// �迭�� �����Ҵ� ���� �ʾ��� ��� �����Ҵ� ���ش�.
	if (!m_pMonsterArray)
	{
		m_iMonsterArrayCount = 2;
		m_pMonsterArray = new CMonster * [m_iMonsterArrayCount];
	}

	// ���� ���Ͱ� �� ������ ��� �迭�� �÷��ش�.
	if (m_iMonsterCount == m_iMonsterArrayCount)
	{
		// ������ �÷��� �Ҵ����ش�.
		m_iMonsterArrayCount *= 2;
		CMonster** ppArray = new CMonster * [m_iMonsterArrayCount];

		// ������ �ִ� �ּ� ������ �� �迭�� �Ű��ش�.
		// memcpy : �޸� ���� �Լ��̴�.
		// 1�����ڿ� �� �޸� �ּҿ� 2�����ڿ� �� �޸� �ּҷκ���
		// 3�����ڿ� �� ����Ʈ ����ŭ �޸𸮸� �����Ѵ�.
		// ���Ͱ� ��á�ٸ� ���� �迭�� �̹� ���� ���ִ�.
		// �׷��� ������ ������ 2�踸ŭ �����迭�� �Ҵ����ְ�
		// �Ʒ����� ���� �Ҵ��� ������ ���� ��� 20����� ���� ������
		// 10���̴�. ���� ������(2������) �����Ҵ�� �޸� �ּҵ���
		// ���� �Ҵ�� �������� 10����ŭ �������ִ� ���̴�.
		memcpy(ppArray, m_pMonsterArray, sizeof(CMonster*) * m_iMonsterCount);
		delete[]	m_pMonsterArray;

		m_pMonsterArray = ppArray;
	}

	// ���� ���� ��ü�� �Ҵ��Ѵ�.
	CMonster* pMonster = new CMonster;

	if (!pMonster->Init())
	{
		SAFE_DELETE(pMonster);
		return NULL;
	}

	// ���� ��ġ������ �����Ѵ�.
	pMonster->SetPos(x, y);

	// ���� �迭�� �־��ش�.
	m_pMonsterArray[m_iMonsterCount] = pMonster;
	++m_iMonsterCount;

	return pMonster;
}

bool CStage::CheckMonster(int x, int y)
{
	for (int i = 0; i < m_iMonsterCount; i++)
	{
		if (m_pMonsterArray[i]->GetPos().x == x &&
			m_pMonsterArray[i]->GetPos().y == y)
			return true;
	}
	return false;
}
