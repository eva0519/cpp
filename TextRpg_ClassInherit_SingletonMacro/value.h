#pragma once

#include <iostream>
#include <vector>
#include <list>

using namespace std;

// 사용자정의 헤더
#include "defines.h"

template <typename T>
T Input()
{
	T data;
	cin >> data;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return 0;
	}

	return data;
}

template <typename T>
void Safe_Delete_VecList(T& p)
{
	// 스테이지의 경우 T가 받아올 인자타입은 vector<class CStage*>이고 
	// m_vecStage의 주소를 참조하여 인자로 받아올것이다.
	// 아래는 과거에 만들었던 iter기능과 같이 stl에 있는 기본함수 기능들이다.
	// stl standard로 지원이 되기 때문에 헤더만 include 해주면
	// iterator를 따로 만들지 않아도 사용할수있다.
	T::iterator iter;
	T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	p.clear();
}