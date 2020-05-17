#include <iostream>
#include <time.h>
//time.h에 시간관련 기능들어있음

using namespace std;

int main()
{
	// 상수 : 변하지 않는 수. 값을 한번 지정해놓으면 바꿀 수 없다.
	// 상수는 선언과 동시에 값을 지정해 두어야 한다.
	//constant, 헝가리안 표기법 int형 변수의 경우 n,i등을 앞에 많이 붙임
	//0x로 시작하면 16진수 int가 4바이트를 차지하니 32비트이고
	//16진수 한자리가 2진수 4개를 가지고 있으므로 4비트이고
	//16진수 8자리가 2진수 32개를 가지고 있으므로 32비트를 차지하게 된다
	//아래의 16진수 상수 변수는 8자리의 16진수 자리를 가지고 있으므로 
	//32비트를 차지하고 있다고 생각하고 2진수로 변환하면 주석과 같은 값이 된다.
	const int iAttack = 0x00000001; //       1
	const int iArmor = 0x00000002; //	    10
	const int iHP = 0x00000004; //		   100
	const int iMP = 0x00000008; //		  1000
	const int iCritical = 0x00000010; // 10000

	// 이러한 형식으로 비트별로 32개의 버프가 지정가능하다.
	// 비트단위 논리연산자 : 2진수 단위의 연산을 한 뒤 값 대 값을 연산하여 값으로 나온다.
	// 종류 : and(&), or(|), not(~), xor(^)
	// 위의 비트단위 논리연산자를 참고해 버프를 키고 껴는 스위치로 활용할 수 있다.
	// ex) iAttack ^ iArmor if 조건문을 이용해 어택버프 혹은 아머버프 둘중 하나라도 켜져 있으면 다른 버프는 적용 되지않는 형식.

	int iBuf = iAttack | iHP | iCritical;
	// 001 | 100 = 101 | 10000 = 10101

	// 위 비트연산식을 보면 |(or) 연산을 통해 마치 그림처럼 버프가 추가되는 것을 볼 수 있다.
	// 때문에 버프 추가를 위해서는 16진수의 끝자리부터 1,2,4,8이 반복되는 형식으로 ex)0x00000001~8 0x00000010~80 0x00000100~800
	// 지정하여 비트 논리 or 연산을 진행해주면 10101010... 형식의 값을 통해 버프를 효율적으로 처리할 수 있다.
	
	// 위의 | 비트 연산식 한줄로 어택,hp,크리티컬 버프를 추가했으니
	// 아래의 & 비트 연산식으로 버프의 유무를 확인해 볼 수 있다.

	// 10101 & 00001 = 1
	cout << "Attack : " << (iBuf & iAttack) << endl;
	// 10101 & 00010 = 0
	cout << "Armor : " << (iBuf & iArmor) << endl;
	// 10101 & 100 = 1
	cout << "HP : " << (iBuf & iHP) << endl;
	// 10101 & 1000 = 0
	cout << "MP : " << (iBuf & iMP) << endl;
	// 10101 & 10000 = 1
	cout << "Critical : " << (iBuf & iCritical) << endl;
	// 1은 true값이다 즉 버프가 존재한다는 뜻. 0은 버프가 없다는 뜻이다.
	// 1 4 16 이 나오므로 0이 아니면 버프가 켜져있다는 식으로 활용가능.
	// 이런식으로 코딩하면 로어-컴퓨털뤼 하기 땜에 연산이 빨라 속도가 빠르다


	// 연산자 축약형 : 연산자를 줄여서 사용할 수 있다.
	// 아래를 풀어서 쓰면 iBuf = iBuf ^ iHP;
	iBuf ^= iHP;
	// 10101 ^ 00100 = 10001
	iBuf ^= iHP;
	// 10001 ^ 00100 = 10101
	// 위 xor (^) 비트연산자를 보면 마치 스위치가 켜졌다 꺼졌다 하는 듯이 버프가 사라지고
	// 다시 켜지고 하는걸 볼 수 있다. 이를 이용해 버프가 꺼졌다 켜졌다 하게 만들 수 있다.
	// 한번 사용시 값이 0이 되고 다시 사용하면 0 이상의 값이 되므로 쉽게 버프를 관리 할 수 있고
	// 버프 외에도 다방면으로 응용해 샐수없이 많은 방면으로 사용 가능하다.

	//!요약 상수 변수와 16진수, 비트연산자를 이용해 
	// | 연산으로 버프 추가.
	// & 연산으로 버프 확인.
	// ^ 연산으로 버프 토글 및 [원하는 영역만 콕 집어서] 제어 가능하다.


	/*
	쉬프트 연산자 : <<, >> 값 대 값을 연산하여 값으로 나오게 된다.
	이 연산자 또한 이진수 단위의 연산을 하게 된다.

	20 << 2 = 80
	20 << 3 = 160
	20 << 4 = 320
	20을 2진수로 변환한다.
	1010000  20을 2진수로 바꾸고 왼쪽으로 2칸 민다. 즉 00을 오른쪽에 2개 붙이면 됨
	10100000 
	101000000
	<< n 숫자가 늘어갈수록 결과값이 2배씩 불어나고 x * 2의 n승이 결과값이 된다

	!) 연산이 굉장히 단순해서 빠른 곱셈이라고 불림. (<< = x * 2의 n승)
	2의 n승을 곱해야 하는 작업에서는 이 연산자를 통해 최적화가 가능하다

	20 >> 2 = 5
	20 >> 3 = 2
	반대로 오른쪽으로 2칸 민다. 
	10100 => 101.00 이 되나 정수값만 인식하므로 101로 5가 나온다. 결과적으로 오른쪽 2개를 지운다고 생각하면됨.
	10100 => 10   2
	
	!) 빠른 나눗셈이라고 불림. (>> =   x / 2의 n승) (나머지 제외)
	2의 n승으로 나눠야 하는 작업에서는 이 연산자를 통해 최적화가 가능하다
	ex. 짝수 구할때 /, % 대신 x >> 1 사용시 비트연산이 가능하므로 최적화. 
	나눗셈 연산은 무겁다. 2를 나누는것보다 0.5를 곱하는게 빠르다. 그리고 쉬프트 연산은 그보다 더 빠르다.
	*/


	/*
	비트필드 최적화 방법. 변수 쪼개쓰기.
	*/
	int iHigh = 187;
	int iLow = 13560;

	int iNumber = iHigh;
	// int는 4바이트이고 32비트이므로 low, high를 16비트씩 나누는것을 가정한다

	iNumber <<= 16;
	// iNumber에는 187 값이 들어가있다. 이 값을 <- 이 방향으로 16비트 이동시키면
	// 상위 16비트에 값이 들어가게 된다.

	// 하위 16비트를 채운다.
	iNumber |= iLow;
	//여기까지 iNumber 하나의 변수에 차곡차곡 iHigh와 iLow가 사이좋게 상위 하위에 적재된 상태.
	//다만 변수값을 10진수로 변환하면 두 수의 이진법상태가 합쳐진 상태므로 말도안되는 큰 수가 나온다.

	// High 값을 출력하는법
	cout << "High : " << (iNumber >> 16) << endl;
	// >> 16으로 하위 16비트를 날리고 이전에 0 16개 붙여놓은 iHigh값이 하위로 오면서 
	// 본래 하위에 16비트만큼 쳐먹고 있던 iLow는 밀리면서 값이 날라가니
	// 말도안되는 큰값이 아닌 순수한 iHigh 값만을 (본래 적재된 상태는 Low를 넣기전 0을 16개나 붙여서 
	// 상위로 밀어놔서 110000~~0 뭐 이런식이었을테니) 출력.

	// Low 값을 출력하는법
	cout << "Low : " << (iNumber & 0x0000ffff) << endl;
	// 0x0000ffff는 16진수가 8개인 32비트(2진수가 4개씩 8묶음 있는거니까)
	// 상위 16비트를 모두 0으로 채우고 하위 16비트의 공간에 1111111111111111한 값을 
	// & 비트연산 해버리면 상위에 있던 High 값이 모두 0이 되어 사라지고 
	// (앞을 모두 0으로 해버린 16진수 즉 상위(high가 있는곳) 16비트 가량이 무조건 false가 나올 수 밖에 없는 구조를 만듬)
	// 결국 하위의 Low 값만이 & 비트연산되어 본래 값을 가지게 되므로 본래 Low값이 출력된다.


	//!) 온몸비틀며 이진법에 가깝게 코딩하고 메모리를 아낄수록 최적화가 가능하다


	// 증감연산자 : ++, -- 가 있다. 1증가, 1감소이다.
	iNumber = 10;

	// 전치
	++iNumber;  // 11

	// 후치
	iNumber++;  // 11
	// 12

	cout << ++iNumber << endl; // 13
	cout << iNumber++ << endl; // 13 중요
	// 14
	cout << iNumber << endl; // 14


	// 조건문
	/*분기문에는 크게 2가지 종류가 있다. if문, switch 문이 존재한다.
	if문 : 조건을 체크해주는 기능이다.
	형태 : if(조건식) {} <- (코드블럭)
	if문은 조건식이 true가 될 경우 코드블럭 안의 코드가 동작된다.
	false가 될 경우에는 동작되지 않는다.
	*/
	if (false)
	{
		cout << "if문 조건이 true 입니다." << endl;
	}

	// 버프가 있는지 확인한다.
	if ((iBuf & iAttack) != 0)
	{
		cout << "Attack 버프가 있습니다." << endl;
	}

	//if문 아래에 들어갈 코드가 1줄일 경우 {}(코드블럭을 생략 가능)
	if ((iBuf & iArmor) != 0)
		cout << "Armor 버프가 있습니다." << endl;

	if ((iBuf & iHP) != 0)
		cout << "HP버프가 있습니다." << endl;

	if ((iBuf & iMP) != 0)
		cout << "MP버프가 있습니다." << endl;

	if ((iBuf & iCritical) != 0)
		cout << "Critical버프가 있습니다." << endl;

	/*
	else : if문과 반드시 같이 사용이 되어야 한다.
	if문 조건이 false일 경우 else가 있다면 else 구문 안의 코드가 동작된다.
	
	else if : if 문과 반드시 같이 사용이 되어야 한다.
	if문 아래 와야하고 else 보다는 위에 있어야 한다.
	else if는 자신의 위에 있는 조건식이 false일 경우 다음 else if의 조건식을 체크한다.
	else if는 몇개든 사용이 가능하다.
	*/

	if (false)
		cout << "if문 조건이 true 입니다." << endl;
	else
		cout << "if문 조건이 false 입니다." << endl;

	cout << "숫자를 입력하세요 : ";
	/*  cin >> iNumber;   */ 

	//입력받는 부분인데 아래 공부하느라 잠깐 주석처리

	if (10 <= iNumber && iNumber <= 20)
		cout << "10 ~ 20 사이의 숫자입니다." << endl;
	else if(21 <= iNumber && iNumber <= 30)
		cout << "21 ~ 30 사이의 숫자입니다." << endl;
	else if (31 <= iNumber && iNumber <= 40)
		cout << "31 ~ 40 사이의 숫자입니다." << endl;
	else
		cout << "그 외의 숫자입니다." << endl;


	// 난수 테이블 발생. 
	// unsigned를 통해 음수제거. 변수의 형변환이라 한다. 타입캐스팅.
	srand((unsigned int)time(0));
	//time(0)으로 현재시간을 뽑아오고 그중 음수를 제거해 양수값만 가져와 난수테이블을 생성.

	//rand()는 발생한 테이블에서 임의값을 얻어오는 함수이다.
	cout << rand() << endl;
	cout << rand() << endl;
	cout << rand() << endl;
	//0~99까지의 난수를 얻고싶다. 100으로 나눈 나머지. 
	//어떤 큰 양수도 끝에는 100으로 나누어떨어지지 않는 상태에 이르면 
	//나머지는 0~99밖에 안나온다.
	cout << (rand() % 100) << endl;

	//0 ~ 100이 나오게 하고싶다
	cout << (rand() % 101) << endl;

	//100 ~ 200을 얻고싶다
	cout << ((rand() % 101) + 100) << endl;

	//0 ~ 99.99까지 얻고싶다
	cout << ((rand() % 10000) / 100.f) << endl;
	//.f를 붙이면 float 타입으로 바뀌어 소수점까지 나온다.

	

	// 아이템 강화 단계에 따른 강화성공실패 프로그램

	int iUpgrade = 0;
	cout << "Upgrade 기본 수치를 입력하세요 : ";
	cin >> iUpgrade;

	// 강화 확률을 구한다.
	float fPercent = rand() % 10000 / 100.f;

	// 강화 확률 : 업그레이드가 0 ~ 3 : 100% 성공	4 ~ 6 : 40%		7 ~ 9 : 10%
	// 10 ~ 13 : 1%		14 ~ 15 : 0.01%
	cout << "Upgrade : " << iUpgrade << endl;
	cout << "Percent : " << fPercent << endl;

	if (iUpgrade <= 3)
		cout << "강화 성공" << endl;

	else if (4 <= iUpgrade && iUpgrade <= 6)
	{
		if (fPercent < 40.f)
			cout << "강화 성공" << endl;
		else
			cout << "강화 실패" << endl;
	}
	else if (7 <= iUpgrade && iUpgrade <= 9)
	{
		if (fPercent < 10.f)
			cout << "강화 성공" << endl;
		else
			cout << "강화 실패" << endl;
	}
	else if (10 <= iUpgrade && iUpgrade <= 13)
	{
		if (fPercent < 1.f)
			cout << "강화 성공" << endl;
		else
			cout << "강화 실패" << endl;
	}
	else if (14 <= iUpgrade && iUpgrade <= 15)
	{
		if (fPercent < 0.01f)
			cout << "강화 성공" << endl;
		else
			cout << "강화 실패" << endl;
	}


	return 0;
}