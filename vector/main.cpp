
#include <iostream>
#include "Vector.h"

using namespace std;

// �Ϲ� �迭ó�� ����ϸ鼭 ������ ������ Ÿ���� ���������� ����ϱ� ������
// �Ϲ� �迭������ �Ұ����� �޸� �߰��� �����Ӱ� �����ϴ�.
// ������ resize �Լ��� ����� ���� ������ ������ �� �ֱ� ������.
// reserve ��� ����� �����. reserve�� ���� �̸� ����� ��������� �����Ҵ���
// ����� �س��� ������ resize�� ���ϰ� �ٷ� �����͸� �ֱ� ������ ������ �� ����.
int main()
{
	CVector<int>	vecInt;

	vecInt.reserve(100);

	for (int i = 0; i < 100; i++)
	{
		vecInt.push_back(i + 1);
	}

	// ���۷����͸� �صθ� �̷� ���� �����ϴ�.
	for (int i = 0; i < vecInt.size(); i++)
	{
		cout << vecInt[i] << endl;
	}


	return 0;
}