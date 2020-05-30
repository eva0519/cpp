#pragma once

template <typename T>
class CVectorNode
{
private:
	CVectorNode()
	{

	}
	~CVectorNode()
	{

	}

private:
	template <typename T>
	friend class CVector;

private:
	T		m_Data;
	int		m_iIndex;
};

// 중간 삽입, 삭제가 많지 않고 단순 데이터 저장용에는 벡터가 더 좋을 수 있고
// (메모리를 미리 잡아놓고 저장만 하면 되기때문, 하지만 반복문으로 데이터삭제 마다 앞으로 땡겨줘야한다)
// 중간 삽입, 삭제를 많이 해야한다면 리스트가 유리하다.
// (데이터노드의 앞뒤만 연결해주면 되기 때문, 하지만 매번 동적할당을 해주기 때문에 단순데이터 입력에는 느릴 수 있다)
// 만드려는 프로그램의 상황에 맞추어 자료구조를 선택해야한다.
template <typename T>
class CVector
{
public:
	CVector()
	{
		m_iSize = 0;
		m_iCapacity = 2;

		m_pArray = new NODE[m_iCapacity + 2];
	}

	// 생성자 오버로딩을 통해서 reserve와 같은 기능을 만들어 둘 수도 있다.
	CVector(int iSize)
	{
		m_pArray = new NODE[iSize + 2];
		m_iCapacity = iSize;
		m_iSize = 0;
	}

	~CVector()
	{
		delete[]	m_pArray;
	}

private:
	typedef CVectorNode<T>		NODE;
	typedef CVectorNode<T>*		PNODE;

private:
	PNODE			m_pArray;
	unsigned int	m_iSize;
	unsigned int	m_iCapacity;

public:
	// 벡터는 push_front를 만들지 않을 것이다.
	// 앞 인덱스에서 노드를 추가하면 그 뒤로 인덱스 데이터를 전부 한칸씩 밀어야하기 때문에
	// 데이터가 많아질수록 성능이 느려진다.
	void push_back(const T& data)
	{
		if (full())
			resize(m_iSize * 2);

		m_pArray[m_iSize + 1].m_Data = data;
		// 0번은 begin이다. 그런데 실제 1번인덱스부터 노드가
		// 추가되는데 처음 추가된 노드는 0번부터 인덱스를
		// 주도록 한다.
		m_pArray[m_iSize + 1].m_iIndex = m_iSize;
		++m_iSize;
	}

	void resize(int iSize)
	{
		// +2 를 해주는 이유는 begin과 end노드를 포함시켜서
		// 생성하기 위해서이다.
		PNODE	pArray = new NODE[iSize + 2];

		// 위에서 2배만큼 공간을 새로 할당하고 기존에 있는
		// 노드의 데이터를 새로 할당한 공간에 복사해준다.
		// 메모리 주소에 +1을 해준 이유는 1번 인덱스부터
		// 시작이기 때문에 여기부터 복사를 해주기 위해서
		// +1을 해주었다.
		memcpy(pArray + 1, m_pArray + 1, sizeof(NODE) * m_iSize);

		// 기존 노드를 삭제한다.
		delete[]	m_pArray;

		m_pArray = pArray;

		m_iCapacity = iSize;
	}

	void clear()
	{
		delete[]	m_pArray;
		m_iSize = 0;
		m_iCapacity = 2;
		m_pArray = new NODE[m_iCapacity + 2];
	}

	bool full()
	{
		return m_iSize == m_iCapacity;
	}

	bool empty()
	{
		m_iSize == 0;
	}

	unsigned int size() const
	{
		return m_iSize;
	}

	unsigned int capacity() const
	{
		return m_iCapacity;
	}

	// CVector 클래스를 배열처럼 액세스 하기 위해 오퍼레이터를 설정해준다.
	// 중요. 몹시 편해진다.
	T operator [](int idx)
	{
		return m_pArray[idx + 1].m_Data;
	}

	void reserve(int iSize)
	{
		delete[]	m_pArray;
		m_pArray = new NODE[iSize + 2];

		m_iCapacity = iSize;
		m_iSize = 0;
	}
};

