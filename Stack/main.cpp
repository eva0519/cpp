
#include <iostream>
#include "Stack.h"

// First In, Last Out  Stack 자료 구조형
// 처음으로 들어간 데이터가 마지막으로 나오는 자료구조이다.
// 간단하게 싱글링크드리스트만으로도 구현 가능하다.
// 배열로도 쉽게 나오는 구조.

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