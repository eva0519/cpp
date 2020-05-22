
// #pragma once : 이 헤더파일을 딱 1번만 포함시키겠다 라는 의미이다.
#pragma once

#include <iostream>

using namespace std;

enum OUTPUT_TYPE
{
	OT_NONE,
	OT_OUTPUT,
	OT_INVERSE
};

enum SORT_TYPE
{
	ST_NONE,
	ST_NUMBER,
	ST_AVG
};

enum SORT_OPTION
{
	SO_NONE,
	SO_CRIVE,
	SO_DESCRIVE
};

// 헤더파일에는 보통 함수 선언부분을 만들어준다.

#define NAME_SIZE	32

typedef struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
}STUDENT, * PSTUDENT;

typedef struct _tagNode
{
	STUDENT		tStudent;
	_tagNode* pNext;
	_tagNode* pPrev;
}NODE, * PNODE;

typedef struct _tagList
{
	// pBegin과 pEnd는 명시적으로 처음과 끝을 의미하도록 만든다. 실제 데이터를 저장하는
	// 노드는 아니다. 실제 데이터를 저장하는 노드는 pBegin과 pEnd 사이에 존재하게 만들어준다.
	PNODE	pBegin;
	PNODE	pEnd;
	int		iSize;
}LIST, * PLIST;

// 헤더에 함수와 정의를 동시에 할 경우에는 static을 붙여줘야
// 두개이상의 cpp 파일에서 중복선언된 것으로 인식되어 오류가 나는것을 막을 수 있다.
static int InputInt()
{
	int iInput;
	cin >> iInput;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}

	return iInput;
}

static void InputString(char* pString, int iSize)
{
	cin.clear();
	cin.ignore(1024, '\n');
	cin.getline(pString, iSize - 1);
}

// 선언된 함수 블록후 ctrl+. 을 눌러 선언/정의 만들기를 하면 
// List.cpp 쪽에 정의 부분이 모두 만들어진다

void InitList(PLIST pList);
//void ClearList(PLIST pList);
void DestroyList(PLIST pList);
void Push_Back(PLIST pList);
void Push_Front(PLIST pList);
void OutputStudent(const PSTUDENT pStudent);
void Output(PLIST pList);
void Search(PLIST pList);
void Delete(PLIST pList);
void Sort(PLIST pList);