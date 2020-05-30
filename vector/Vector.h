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

// �߰� ����, ������ ���� �ʰ� �ܼ� ������ ����뿡�� ���Ͱ� �� ���� �� �ְ�
// (�޸𸮸� �̸� ��Ƴ��� ���常 �ϸ� �Ǳ⶧��, ������ �ݺ������� �����ͻ��� ���� ������ ��������Ѵ�)
// �߰� ����, ������ ���� �ؾ��Ѵٸ� ����Ʈ�� �����ϴ�.
// (�����ͳ���� �յڸ� �������ָ� �Ǳ� ����, ������ �Ź� �����Ҵ��� ���ֱ� ������ �ܼ������� �Է¿��� ���� �� �ִ�)
// ������� ���α׷��� ��Ȳ�� ���߾� �ڷᱸ���� �����ؾ��Ѵ�.
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

	// ������ �����ε��� ���ؼ� reserve�� ���� ����� ����� �� ���� �ִ�.
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
	// ���ʹ� push_front�� ������ ���� ���̴�.
	// �� �ε������� ��带 �߰��ϸ� �� �ڷ� �ε��� �����͸� ���� ��ĭ�� �о���ϱ� ������
	// �����Ͱ� ���������� ������ ��������.
	void push_back(const T& data)
	{
		if (full())
			resize(m_iSize * 2);

		m_pArray[m_iSize + 1].m_Data = data;
		// 0���� begin�̴�. �׷��� ���� 1���ε������� ��尡
		// �߰��Ǵµ� ó�� �߰��� ���� 0������ �ε�����
		// �ֵ��� �Ѵ�.
		m_pArray[m_iSize + 1].m_iIndex = m_iSize;
		++m_iSize;
	}

	void resize(int iSize)
	{
		// +2 �� ���ִ� ������ begin�� end��带 ���Խ��Ѽ�
		// �����ϱ� ���ؼ��̴�.
		PNODE	pArray = new NODE[iSize + 2];

		// ������ 2�踸ŭ ������ ���� �Ҵ��ϰ� ������ �ִ�
		// ����� �����͸� ���� �Ҵ��� ������ �������ش�.
		// �޸� �ּҿ� +1�� ���� ������ 1�� �ε�������
		// �����̱� ������ ������� ���縦 ���ֱ� ���ؼ�
		// +1�� ���־���.
		memcpy(pArray + 1, m_pArray + 1, sizeof(NODE) * m_iSize);

		// ���� ��带 �����Ѵ�.
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

	// CVector Ŭ������ �迭ó�� �׼��� �ϱ� ���� ���۷����͸� �������ش�.
	// �߿�. ���� ��������.
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

