
#include <iostream>

using namespace std;

int main()
{
	/*
	레퍼런스 : 다른 대상을 참조하게 만들어주는 기능이다.
	참조를 하게 되면 그 대상에 접근하여 값을 변경할 수 있다.
	단, 레퍼런스는 처음 레퍼런스 변수 생성시 참조하는 대상을 지정해
	주어야 한다.
	변수타입 &레퍼런스명 = 참조할변수명; 으로 한다.
	*/
	int iNumber = 100;
	int iNumber1 = 9999;

	// iRefNum 레퍼런스 변수는 iNumber를 참조한다.
	int& iRefNum = iNumber;

	iRefNum = 1234;

	iRefNum = iNumber1;

	cout << iNumber << endl;
	cout << sizeof(iRefNum) << endl;

	// 레퍼런스 역시 참조만을 하고 4바이트를 차지하기에
	// 메모리 활용 등을 위해 구조체나 인자 등으로 많이쓰인다.


	return 0;
}