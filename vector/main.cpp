
#include <iostream>
#include "Vector.h"

using namespace std;

// 일반 배열처럼 사용하면서 공간과 데이터 타입을 가변적으로 사용하기 때문에
// 일반 배열에서는 불가능한 메모리 추가도 자유롭고 유용하다.
// 하지만 resize 함수가 실행될 때는 성능이 느려질 수 있기 때문에.
// reserve 라는 기능을 만든다. reserve를 통해 미리 사용할 멤버변수에 동적할당을
// 충분히 해놓기 때문에 resize를 안하고 바로 데이터를 넣기 때문에 성능은 더 좋다.
int main()
{
	CVector<int>	vecInt;

	vecInt.reserve(100);

	for (int i = 0; i < 100; i++)
	{
		vecInt.push_back(i + 1);
	}

	// 오퍼레이터를 해두면 이런 짓이 가능하다.
	for (int i = 0; i < vecInt.size(); i++)
	{
		cout << vecInt[i] << endl;
	}


	return 0;
}