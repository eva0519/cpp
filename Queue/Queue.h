#pragma once

template <typename T>
class CQueueNode
{
private:
	CQueueNode() :
		m_pNext(NULL),
		m_pPrev(NULL),
		m_Data(NULL)
	{

	}
	~CQueueNode()
	{

	}

private:
	template <typename T>
	friend class CQueue;

private:
	T					m_Data;
	CQueueNode<T>*		m_pNext;
	CQueueNode<T>*		m_pPrev;
};

template <typename T>
class CQueue
{
public:
	CQueue()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}
	~CQueue()
	{
		// Begin, End를 포함해 싹다 지운다.
		PNODE	pNode = m_pBegin;

		while (pNode)
		{
			PNODE pNext = pNode->m_pNext;
			delete pNode;
			pNode = pNext;
		}
	}

private:
	typedef CQueueNode<T>		NODE;
	typedef CQueueNode<T>*		PNODE;

private:
	PNODE			m_pBegin;
	PNODE			m_pEnd;
	unsigned int	m_iSize;

public:
	void push(const T& data)
	{
		PNODE pNode = new NODE;

		pNode->m_Data = data;

		PNODE pPrev = m_pEnd->m_pPrev;

		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;

		++m_iSize;
	}

	// 자료구조 상에 먼저 나올 첫번째 노드의 데이터를 뽑아내고 
	// (제일 처음에 넣었던 데이터) 노드를 삭제하는 함수
	T pop()
	{
		if (empty())
			return 0;

		PNODE pNode = m_pBegin->m_pNext;

		T data = pNode->m_Data;

		// begin의 다음 노드를 지우므로 begin과 지울 노드의 다음노드를
		// 서로 연결해준다.
		m_pBegin->m_pNext = pNode->m_pNext;
		pNode->m_pNext->m_pPrev = m_pBegin;

		delete pNode;

		--m_iSize;

		return data;
	}

	bool empty()
	{
		return m_iSize == 0;
	}
};

// 환형큐 (배열.ver)

// 비 타입 템플릿 인자. (#define과 비슷하다)
// 함수의 디폴트인자처럼 상수 갯수를 정해놓을 수 있다.
// 정적 배열의 갯수는 변수로 선언할 수 없기 때문에
// (지역 변수 같은 경우는 프로그램 구동중 언제든 스택메모리에 
// 오르내리며 생성,삭제,변경될 수 있으니까)
// 배열의 갯수로 써먹을 용도로 설정했다.
template<typename T, int SIZE = 100>
class CCircleQueue
{
public:
	CCircleQueue()
	{
		m_iSize = 0;
		m_iHead = 0;
		m_iTail = 0;
	}
	~CCircleQueue()
	{

	}

private:
	T				m_Data[SIZE + 1] = {};
	unsigned int	m_iSize;
	unsigned int 	m_iHead;
	unsigned int 	m_iTail;

public:
	void push(const T& data)
	{
		if (full())
			return;

		int idx = (m_iTail + 1) % (SIZE + 1);

		m_Data[idx] = data;

		m_iTail = idx;

		++m_iSize;
	}

	T pop()
	{
		if (empty())
			return 0;

		int idx = (m_iHead + 1) % (SIZE + 1);

		T data = m_Data[idx];

		m_iHead = idx;

		--m_iSize;

		return data;
	}

	bool full()
	{
		return m_iSize == SIZE;
	}

	bool empty()
	{
		return m_iSize == 0;
	}
};