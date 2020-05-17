
#include <iostream>

//이렇게 함으로써 앞에 귀찮게 std를 안붙여줘도 된다.
using namespace std;

// 실행 과정 : 컴파일 -> 빌드 -> 실행
// 컴파일 : 번역작업이다.
// ctrl + shift+b 빌드작업 가능. exe 생성. 컴파일도 당연히 함께 실행됨.
// ctrl + f5를 통해 디버깅하지 않고 바로 실행해 볼수 있다.

int main()
{
	// C++ 표준 기능의 대두분은 std namespace 안에 존재하고 있다. 
	/*이름이 겹치는 것을 방지해주기 위해서이다*/
	// cout 문자열 출력 기능. endl 엔드라인 \n 같은것
	// 위에서 아래로 읽고 오른쪽에서 왼쪽으로 읽는다
	std::cout << "Test Output" << std::endl;
	std::cout << "가나다라" << std::endl;
	cout << "std namespace 사용" << endl;

	/*
	변수 : 변하는 수. 값이 바뀔 수 있다.
	용량의 최소 단위 : bit
	1byte = 8bit
	1kbyte = 1024byte
	1mbyte = 1024kbyte
	1gbyte = 1024mbyte
	1tbyte = 1024gbyte
	1바이트는 256가지를 표현. 0포함. 문자를 표현할때는 아스키코드 참조.
	0000 0000 ~ 1111 1111  0~255  256가지
	false : 0
	true : 0이 아닌 모든 수
	unsigned : 부호가 없다
	종류  ㅣ 용량   ㅣ 데이터  ㅣ 표현 범위       ㅣ unsigned
	char  ㅣ 1byte  ㅣ 문자	   ㅣ -128 ~ 127      ㅣ 0 ~ 255
	bool  ㅣ 1byte  ㅣ 참/거짓 ㅣ true/false      ㅣ true/false
	short ㅣ 2byte  ㅣ 정수    ㅣ -32768 ~ 32767  ㅣ 0 ~ 65535
	int   ㅣ 4byte  ㅣ 정수    ㅣ 약 -22억 ~ 21억 ㅣ 0 ~ 약 43억
	float ㅣ 4byte  ㅣ 실수    ㅣ cout의 경우 5자리~6자리까지 표현해줌
	doubleㅣ 8byte  ㅣ 실수	   ㅣ 
	용량이나 메모리 최적화를 위해서 표현범위를 알고 필요한 용량만큼의 타입만 써서 잘 사용해야 겠다 */
	// 변수 앞에는 영문자나 _만 가능

	int Number = 10;

	cout << Number << endl;

	bool bTest = true;
	bTest = false;

	cout << bTest << endl;
	//false는 0

	char cTest = 't';
	cout << cTest << endl;
	//문자를 하나 쓸때는 작은 따옴표. 
	//한문/일어/한글은 글자하나당 2byte를 차지하기 때문에 char 하나에 저장하기 힘듬

	float fNumber = 3.14f;
	// f를 붙이면 float타입 실수, 안붙이면 double타입
	// 대개 c쪽 고급언어는 float인데 실수 뒤에 f 안붙이면 경고창이 뜬다.
	// 데이터를 double로 인식하고 4바이트가 초과하는 영역은 잘리게 되기 때문.
	cout << fNumber << endl;

	double dNumber = 123.4567;
	cout << dNumber << endl;

	/*
	사칙연산자 : +,-,*,/,%(나머지 MOD)
	관계연산자 : >, >=, <, <=, ==, !=
	논리연산자 : 참거짓대 참거짓을 연산하여 참거짓으로 반환
	&&,||(shift+\),!(not)
	*/
	cout << "10 < 20 = " << (10 < 20) << endl;
	cout << "10 >= 20 = " << (10 >= 20) << endl;
	cout << "10 > 20 = " << (10 > 20) << endl;
	cout << "10 <= 20 = " << (10 <= 20) << endl;
	cout << "10 == 20 = " << (10 == 20) << endl;
	cout << "10 != 20 = " << (10 != 20) << endl;

	// cout = cosoleOutput, cin = consoleInput, endl = endLine
	cout << "숫자를 입력하세요 : ";
	cin >> Number;

	cout << "10 ~ 20 = " << (10 <= Number && Number <= 20) << endl;

	// 비트단위 논리연산자 : 2진수 단위의 연산을 한 뒤 값 대 값을 연산하여 값으로 나온다.
	// 종류 : and(&), or(|), not(~), xor(^)

	cout << "87 & 53 = " << (87 & 53) << endl;
	//게임으로 치면 버프 저장 등에 활용할 수 있다.
	//각각의 비트 단위로 상태를 저장할 수 있으므로
	//변수 하나 4바이트 즉 32비트 2진수로 변환하면 32개의 상태가 가능하므로
	//변수 하나만으로 32가지의 버프를 저장할 수 있다는 것
	//유추하면 이런식으로 쓸모없는 메모리 낭비를 없애고 최적화가 가능하다

	return 0;
}