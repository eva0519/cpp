
#include <iostream>
#include "Stack.h"

// First In, Last Out  Stack �ڷ� ������
// ó������ �� �����Ͱ� ���������� ������ �ڷᱸ���̴�.
// �����ϰ� �̱۸�ũ�帮��Ʈ�����ε� ���� �����ϴ�.
// �迭�ε� ���� ������ ����.

using namespace std;

int main()
{
	CStack<int> stackInt;

	for (int i = 0; i < 100; i++)
	{
		stackInt.push(i + 1);
	}

	while (!stackInt.empty())
	{
		cout << stackInt.pop() << endl;
	}

	return 0;
}