
#include <iostream>

using namespace std;

#define NAME_SIZE 32
#define STUDENT_MAX 3

typedef struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;


}STUDENT, *PSTUDENT;

int main()
{
	/*파일 만들기*/
	//STUDENT tStudent[STUDENT_MAX] = {};

	//for (int i = 0; i < STUDENT_MAX; i++)
	//{
	//	cout << "이름 : ";
	//	cin >> tStudent[i].strName;

	//	tStudent[i].iNumber = i + 1;

	//	cout << "국어 : ";
	//	cin >> tStudent[i].iKor;

	//	cout << "영어 : ";
	//	cin >> tStudent[i].iEng;

	//	cout << "수학 : ";
	//	cin >> tStudent[i].iMath;

	//	tStudent[i].iTotal = tStudent[i].iKor + tStudent[i].iEng + tStudent[i].iMath;
	//	tStudent[i].fAvg = tStudent[i].iTotal / 3.f;
	//}

	//// 학생 정보를 파일에 저장한다.
	//int iStudentCount = STUDENT_MAX;

	//FILE* pFile = NULL;

	//fopen_s(&pFile, "Student.std", "wb");

	//if (pFile)
	//{
	//	//학생 수를 저장한다.
	//	fwrite(&iStudentCount, 4, 1, pFile);

	//	for (int i = 0; i < iStudentCount; ++i)
	//	{
	//		// 학생 구조체를 통으로 저장한다.
	//		fwrite(&tStudent[i], sizeof(STUDENT), 1, pFile);
	//	}

	//	fclose(pFile);
	//}


	STUDENT tStudent[STUDENT_MAX] = {};
	int iStudentCount = 0;

	FILE* pFile = NULL;

	fopen_s(&pFile, "Student.std", "rb");

	if (pFile)
	{

		// 저장할때 학생수를 가장 먼저 저장했기 때문에
		// 학생 수를 먼저 읽어온다.
		fread(&iStudentCount, 4, 1, pFile);

		for (int i = 0; i < iStudentCount; ++i)
		{
			fread(&tStudent[i], sizeof(STUDENT), 1, pFile);
		}

		// 읽어온 학생을 출력한다
		for (int i = 0; i < iStudentCount; i++)
		{
			cout << "이름 : " << tStudent[i].strName << endl;
			cout << "학번 : " << tStudent[i].iNumber << endl;
			cout << "국어 : " << tStudent[i].iKor << endl;
			cout << "영어 : " << tStudent[i].iEng << endl;
			cout << "수학 : " << tStudent[i].iMath << endl;
			cout << "총점 : " << tStudent[i].iTotal << endl;
			cout << "평균 : " << tStudent[i].fAvg << endl << endl;
		}

		fclose(pFile);
	}



	return 0;
}
