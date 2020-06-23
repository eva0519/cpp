#pragma once

#include <iostream>
#include <vector>
#include <list>

#include <unordered_map>
// 이진트리 맵구조. 반씩 잘라서 탐색하기 때문에 탐색성능이 훨씬 빠르다. 이진트리이기 때문에
// 각각 자식 노드들은 2개씩의 자식을 계속 갖게되는 구조. 맵은 레드블랙 이진트리 구조로 되어있다.
// 레드블랙 이진트리는 노드를 단방향이 아닌 좌우 균형을 맞춰 생성한다.
// 추가 삭제가 빈번할때는 부적합. 하지만 한번 저장해놓고 찾아쓸때는 성능이 굉장히 빠르다.
// 일반 map의 경우 굉장히 느리다. unordered_map의 경우 내부적으로 헤싱 알고리즘으로 되어있어 빠르다.
// unordered_map 은 부스트 라이브러리에서 cpp std로 넘어왔다
#include <string>
// 스트링 클래스의 경우 문자열을 쓰기 편하게 하기 위해 만들어졌다. 성능이 빠르진 않다.

using namespace std;

// 사용자정의 헤더
#include "defines.h"
#include "Flags.h"

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
	// iterator를 따로 만들지 않아도 사용할 수 있다.
	T::iterator iter;
	T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	p.clear();
}

template <typename T>
void Safe_Delete_Map(T& p)
{
	T::iterator iter;
	T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		// first : key, second : value
		// value 에 동적할당한 메모리 주소를 저장한 map이라면
		// 이 함수를 이용해 맵 안의 동적할당된 객체들이 모두 메모리해제가 되는
		// 시스템이다.
		SAFE_DELETE(iter->second);
	}

	p.clear();
}