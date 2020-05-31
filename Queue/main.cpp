
#include <iostream>
#include "Queue.h"

using namespace std;

// Queue 자료형은 First In, First Out 이다.
// Queue 자료형도 여러 종류가 있다. 서클큐(환형(원형)큐)-네트워크패킷전송작업할때,
// 양방향큐, 우선순위큐(힙정렬을 이용한 큐(길찾기알고리즘)) 등등이 있다.

int main()
{
	CQueue<int> queue;

	for (int i = 0; i < 100; i++)
	{
		queue.push(i + 1);
	}

	while (!queue.empty())
	{
		cout << queue.pop() << endl;
	}


	// 환형큐

	// #define이면 이런짓이 불가능하다.
	// 원하는 큐의 배열크기를 마음대로 정해서 만들기 쓰기위해 비타입 인자를 사용한다.
	CCircleQueue<int, 10> queue1;
	//CCircleQueue<int> queue2;
	//CCircleQueue<int, 300> queue3;

	for (int i = 0; i < 10; i++)
	{
		queue1.push(i + 1);
	}

	cout << "3개 pop" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << queue1.pop() << endl;
	}

	cout << "4개 push" << endl;
	for (int i = 0; i < 4; i++)
	{
		queue1.push(i + 1);
	}

	cout << "전부 pop" << endl;
	while (!queue1.empty())
	{
		cout << queue1.pop() << endl;
	}

	return 0;
}