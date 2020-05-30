#pragma once

template <typename T>
class CStackNode
{
private:
	CStackNode():
		m_pNext(NULL)
	{

	}
	~CStackNode()
	{

	}

private:
	template <typename T>
	friend class CStack;

private:
	T				m_Data;
	CStackNode<T>*	m_pNext;
};

template <typename T>
class CStack
{
public:
	CStack()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;

		m_iSize = 0;
	}
	~CStack()
	{
		PNODE	pNode = m_pBegin;

		while (pNode)
		{
			PNODE pNext = pNode->m_pNext;
			delete pNode;
			pNode = pNext;
		}
	}
	
private:
	typedef class CStackNode<T>		NODE;
	typedef class CStackNode<T>*	PNODE;

private:
	PNODE			m_pBegin;
	PNODE			m_pEnd;
	unsigned int	m_iSize;

public:
	void push(const T& data)
	{
		PNODE	pNode = new NODE;

		pNode->m_Data = data;

		PNODE	pNext = m_pBegin->m_pNext;

		pNode->m_pNext = pNext;

		m_pBegin->m_pNext = pNode;

		++m_iSize;
	}

	T pop()
	{
		if (empty())
			return 0;

		// 가져올 노드는 begin의 다음 노드이다.
		PNODE pNode = m_pBegin->m_pNext;

		// 가져올 노드를 지워주려면 begin과 가져올 노드의
		// 다음노드를 연결해 주어야 한다.
		PNODE pNext = pNode->m_pNext;

		T	data = pNode->m_Data;

		delete pNode;

		m_pBegin->m_pNext = pNext;

		--m_iSize;

		return data;
	}

	T top()
	{
		if (empty())
			return 0;

		return m_pBegin->m_pNext->m_Data;
	}

	bool empty()
	{
		return m_iSize == 0;
	}
};

