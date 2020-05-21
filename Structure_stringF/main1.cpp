#include <iostream>

// ctrl + spacebar로 자동완성 기능을 사용하면 편하고 빠르다.
// 정의되거나 구조체를 만들어뒀다면 소문자로 치고 자동완성이 빠름.
// ctrl 마우스좌클릭으로 단어채로 선택가능하다.
// ctrl + alt + 좌클릭 원하는 부위 동시편집
// alt + 드래그 원하는 영역 줄별로 동시편집

using namespace std;

#define NAME_SIZE 32
#define ADDRESS_SIZE 128
#define PHONE_SIZE 14  // 000-0000-0000+(null값) 14비트
#define STUDENT_MAX 10

struct _tagStudent
{
	char	strName[NAME_SIZE];
	char	strAddress[ADDRESS_SIZE];
	char	strPhoneNumber[PHONE_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
};

enum MENU
{
	MENU_NONE,
	MENU_INSERT,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT
};

int main()
{
	_tagStudent tStudentArr[STUDENT_MAX] = {};
	// 배열에 추가된 개수를 저장할 변수를 만들어준다.
	int iStudentCount = 0;
	int iStdNumber = 1;
	char	strName[NAME_SIZE] = {};

	while (true)
	{
		system("cls");

		// 메뉴를 출력한다.
		cout << "1. 학생등록" << endl;
		cout << "2. 학생삭제" << endl;
		cout << "3. 학생탐색" << endl;
		cout << "4. 학생출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";
		int iMenu;
		cin >> iMenu;

		// cin은 만약 오른쪽에 int변수가 오면 정수를 입력해야 한다. 오른쪽에
		// 오는 변수 타입에 맞춰서 값을 입력해야 하는데 실수로 정수가 아닌
		// 문자를 입력할 경우 에러가 발생한다. 그렇기 때문에 예외처리로 에러가
		// 발생했는지를 여기에서 체크하여 에러가 발생하면 cin 내부의 에러버퍼를
		// 비워주고 cin 내부에 입력버퍼가 있는데 입력버퍼는 입력한 값을 저장
		// 해놓고 그 값을 변수에 넣어주는 역할을 한다. 이 입력버퍼에 \n 이
		// 남아있으므로 버퍼를 순회하여 \n을 지워야한다.
		// 버퍼 : 임시저장공간 이다.
		// 먼저 에러를 체크한다. cin.fail() 을 했을때 입력 에러가 발생했을
		// 경우 true를 반환한다.
		if (cin.fail())
		{
			// 에러버퍼를 비워준다.
			cin.clear();

			// 입력버퍼에 \n이 남아있으므로 입력버퍼를 검색하여 \n을 지워준다.
			// 첫번째에는 검색하고자 하는 버퍼 크기를 지정한다. 넉넉하게 1024
			// 바이트정도 지정해주었다. 2번째는 찾고자 하는 문자를 넣어준다.
			// 그래서 입력버퍼 처음부터 \n이 있는 곳까지 찾아서 그 부분을 모두
			// 지워줘서 다시 입력받을 수 있도록 해준다.
			cin.ignore(1024, '\n');
			continue;
			// 잘못 입력한 것이니 다시 하라고 continue
		}

		// 예외처리시 스위치 문에 들어가는 break는 switch문을 빠져나오는 break이므로
		// while문을 빠져나오는 break는 if문으로 처리해줘야 한다.
		if (iMenu == MENU_EXIT)
			break;
		
		switch (iMenu)
		{
		case MENU_INSERT:
			system("cls");
			cout << "================ 학생추가 ================" << endl;

			// 등록된 학생이 등록할 수 있는 최대치일 경우 더이상 등록이
			// 안되게 막는다.
			if (iStudentCount == STUDENT_MAX)
				break;

			// 학생정보를 추가한다. 학생정보는 이름, 주소, 전화번호,
			// 국어, 영어, 수학 점수는 입력받고 학번, 총점 평균은 연산을
			// 통해 계산해준다.
			cout << "이름 : ";
			cin >> tStudentArr[iStudentCount].strName;

			cin.ignore(1024, '\n');
			//cin 이후에 getline 함수를 함께 사용시 cin을 사용해 입력후 입력버퍼에 
			//\n이 남아있기 때문에 getline이 엔터로 인해 그냥 넘어가버린다. 
			//\n을 찾아 초기화.

			cout << "주소 : ";
			cin.getline(tStudentArr[iStudentCount].strAddress, ADDRESS_SIZE);
			//cin.getline(입력받을변수,입력받을최대수치)
			//스페이스바를 null값(문자열의 끝)으로 인식하지 않고 문자열로 인식해
			//전체 문자열을 받아오는 함수다. cin으로 하면 스페이스바 뒤로는 잘림.
			
			cout << "전화번호 : ";
			cin.getline(tStudentArr[iStudentCount].strPhoneNumber, PHONE_SIZE);

			cout << "국어 : ";
			cin >> tStudentArr[iStudentCount].iKor;

			cout << "영어 : ";
			cin >> tStudentArr[iStudentCount].iEng;

			cout << "수학 : ";
			cin >> tStudentArr[iStudentCount].iMath;

			tStudentArr[iStudentCount].iTotal =
				tStudentArr[iStudentCount].iKor +
				tStudentArr[iStudentCount].iEng +
				tStudentArr[iStudentCount].iMath;
			tStudentArr[iStudentCount].fAvg =
				tStudentArr[iStudentCount].iTotal / 3.f;

			tStudentArr[iStudentCount].iNumber = iStdNumber;
			++iStdNumber;
			++iStudentCount;

			cout << "학생 추가 완료" << endl;
			break;
		case MENU_DELETE:
			system("cls");

			cout << "================ 학생삭제 ================" << endl;

			cin.ignore(1024, '\n');
			cout << "삭제할 이름을 입력하세요 : ";
			cin.getline(strName, NAME_SIZE);

			// 등록되어있는 학생 수만큼 반복하며 학생을 찾는다.
			for (int i = 0; i < iStudentCount; ++i)
			{
				// 학생을 찾았을 경우
				if (strcmp(tStudentArr[i].strName, strName) == 0)
				{
					// !중요! 삭제라기보단 덮어 씌워서 앞으로 땡긴다는 개념. 프레스 기능.
					for (int j = i; j < iStudentCount - 1; ++j) 
					{
						tStudentArr[i] = tStudentArr[i + 1];
					}
					// 등록 끝배열과 전배열이 중복되긴하나 어차피 아래 --로 카운트를
					// 줄이기에 다음에 입력되는 데이터가 중복된 끝배열을 덮어쓴다.
					// 게다가 iStudentCount 만큼만 출력하기 때문에 중복 배열을 볼 일도 없다.

					--iStudentCount;

					cout << "학생을 삭제하였습니다." << endl;
					break;
				}
			}

			break;
		case MENU_SEARCH:
			system("cls");

			cout << "================ 학생탐색 ================" << endl;

			cin.ignore(1024, '\n');
			cout << "탐색할 이름을 입력하세요 : ";
			cin.getline(strName, NAME_SIZE);

			// 등록되어있는 학생 수만큼 반복하며 학생을 찾는다.
			for (int i = 0; i < iStudentCount; i++)
			{
				// 학생을 찾았을 경우
				if (strcmp(tStudentArr[i].strName, strName) == 0)
				{
					cout << "이름 : " << tStudentArr[i].strName << endl;
					cout << "전화번호 : " << tStudentArr[i].strPhoneNumber << endl;
					cout << "주소 : " << tStudentArr[i].strAddress << endl;
					cout << "학번 : " << tStudentArr[i].iNumber << endl;
					cout << "국어 : " << tStudentArr[i].iKor << endl;
					cout << "영어 : " << tStudentArr[i].iEng << endl;
					cout << "수학 : " << tStudentArr[i].iMath << endl;
					cout << "총점 : " << tStudentArr[i].iTotal << endl;
					cout << "평균 : " << tStudentArr[i].fAvg << endl << endl;
					break;
				}
			}
			break;
		case MENU_OUTPUT:
			system("cls");

			cout << "================ 학생출력 ================" << endl;

			// 등록된 학생 수만큼 반복하며 학생정보를 출력한다.
			for (int i = 0; i < iStudentCount; ++i)
			{
				cout << "이름 : " << tStudentArr[i].strName << endl;
				cout << "전화번호 : " << tStudentArr[i].strPhoneNumber << endl;
				cout << "주소 : " << tStudentArr[i].strAddress << endl;
				cout << "학번 : " << tStudentArr[i].iNumber << endl;
				cout << "국어 : " << tStudentArr[i].iKor << endl;
				cout << "영어 : " << tStudentArr[i].iEng << endl;
				cout << "수학 : " << tStudentArr[i].iMath << endl;
				cout << "총점 : " << tStudentArr[i].iTotal << endl;
				cout << "평균 : " << tStudentArr[i].fAvg << endl << endl;
			}
			break;
		default:
			cout << "메뉴를 잘못 선택하셨습니다" << endl;
			break;
		}

		system("pause");
		// pause 시켜야 위에서 cls해서 "잘못선택하셨습니다" 문구가 지워지는걸 막는다.
	}

	return 0;
}