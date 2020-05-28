
#pragma once

template<typename T>
class CListNode
{
	// 생성자와 소멸자를 private하게 되면 외부에서 객체를 생성하고 객체를
	// 해제할 수 없다.
	// 생성자는 객체를 생성할때 자동으로 호출이 되는 함수인데 private으로
	// 되면 객체를 생성하면서 호출시 접근이 불가능하다.
private:
	CListNode() :
		m_pNext(NULL),
		m_pPrev(NULL),
		m_Data(NULL)
	{

	}
	~CListNode()
	{

	}

private:
	// friend : 친구로 만들어준다. friend로 지정해준 클래스에서
	// 이 클래스의 private이나 protected에 접근이 가능해진다.
	// 일반 클래스는 friend 라인만 적으면 되지만 template 클래스의 경우
	// 아래처럼 template을 지정해 주어야 한다.
	template <typename T>
	friend class CLinkedList;
	template <typename T>
	friend class CListIterator;

private:
	T	m_Data;
	CListNode<T>* m_pNext;
	CListNode<T>* m_pPrev;
};

// 반복자 클래스 : 리스트의 노드를 반복해서 순회할 수 있는 기능을 제공하는
// 클래스이다.
template <typename T>
class CListIterator
{
public:
	CListIterator()
	{

	}
	~CListIterator()
	{

	}

private:
	template <typename T>
	friend class CLinkedList;

private:
	typedef CListNode<T>	NODE;
	typedef CListNode<T>*	PNODE;

private:
	PNODE	m_pNode;

public:
	// 재정의된 오퍼레이터 사용 다음의 (여기서는 listInt.end())를 인자로 넘겨받는다.
	bool operator == (const CListIterator<T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator != (const CListIterator<T>& iter)
	{
		return m_pNode != iter.m_pNode;
	}

	void operator ++()
	{
		m_pNode = m_pNode->m_pNext;
	}

	void operator --()
	{
		m_pNode = m_pNode->m_pPrev;
	}

	T operator *()
	{
		return m_pNode->m_Data;
	}
};

template <typename T>
class CLinkedList
{
public:
	CLinkedList()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}
	~CLinkedList()
	{
		clear();
		delete m_pBegin;
		delete m_pEnd;
		m_iSize = 0;
	}

private:
	typedef CListNode<T>	NODE;
	typedef CListNode<T>*	PNODE;

public:
	typedef CListIterator<T>	iterator;

private:
	PNODE			m_pBegin;
	PNODE			m_pEnd;
	unsigned int	m_iSize;

public:
	// 레퍼런스는 참조하는 대상의 값을 변경할 수 있다. 그런데 const를 붙여주면
	// 참조하는 대상의 값을 변경할 수 없다.
	// 단순 변수값 전체를 인자로 받아오는 것보다 참조만 하는것이 4바이트로 훨씬 빠르고
	// 데이터를 단순히 받아와 뒤에 넣는 함수이기 때문에 const를 사용해 데이터를
	// 변경할 수 없게 제한하는 것이다.
	void push_back(const T& data)
	{
		PNODE	pNode = new NODE;

		pNode->m_Data = data;

		// End 의 이전 노드가 가장 마지막 노드이다.
		PNODE	pPrev = m_pEnd->m_pPrev;

		// 연결해준다.
		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;

		++m_iSize;
	}

	void push_front(const T& data)
	{
		PNODE	pNode = new NODE;

		pNode->m_Data = data;

		// Begin의 다음 노드는 가장 첫번쨰 노드이다.
		PNODE	pFirst = m_pBegin->m_pNext;

		pFirst->m_pPrev = pNode;
		pNode->m_pNext = pFirst;

		pNode->m_pPrev = m_pBegin;
		m_pBegin->m_pNext = pNode;

		++m_iSize;
	}

	// 멤버함수 뒤에 const를 붙여주면 이 함수 내에서 멤버변수의 값을
	// 변경할 수 없다.
	unsigned int size() const
	{
		return m_iSize;
	}

	bool empty()	const
	{
		return m_iSize == 0;
	}

	void clear()
	{
		// 첫번쨰 노드를 얻어온다.
		PNODE pNode = m_pBegin->m_pNext;

		// pNode가 End가 되면 반복을 종료한다. 이렇게 해서 Begin과 End를
		// 제외한 모든 노드를 삭제한다.
		while (pNode != m_pEnd)
		{
			PNODE pNext = pNode->m_pNext;
			delete pNode;
			pNode = pNext;
		}

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
		m_iSize = 0;
	}

	iterator begin()
	{
		iterator	iter;
		iter.m_pNode = m_pBegin->m_pNext;
		return iter;
	}

	iterator end()
	{
		iterator	iter;
		iter.m_pNode = m_pEnd;
		return iter;
	}
};

