#include <iostream>

using namespace std;

/*
��� : Ŭ������ ���ΰ��� �θ�� �ڽŰ��踦 ������ �� �ִ�.
�ڽ� Ŭ������ �θ�Ŭ������ ������� ����� �� �ִ�.

�θ�Ŭ�������� public�̳� protected�� �Ǿ��ִ� ������� ��� ����������,
private���� �Ǿ��ִ� ����� �ڽĿ����� ����� �Ұ����ϴ�.

����� ���� : public, private ����� �ִ�.

������ : ��Ӱ��迡 �ִ� Ŭ�������� ���� ����ȯ�� ������ ������ ���Ѵ�.

�����Լ� : �Լ� �������̵� �̶�� �θ���. �Լ��� �������ϴ� ����̴�.
����Լ� �տ� virtual Ű���带 ���̸� �ش� �Լ��� �����Լ��� �ȴ�.
���� CParent Ŭ������ virtual void Output() �Լ��� �ִٸ� �ڽ�Ŭ����������
�� �����Լ��� ������ �� �� �ִ�. �����Ǵ� �Լ��̸��� ���ڰ� ������ �Ȱ��ƾ�
�Ѵ�.

�����Լ��� ������ �ִ� Ŭ������ ���������� �����Լ� ���̺��̶�� ���� ����
�Ѵ�. �����Լ����̺��� �����Լ����� �޸� �ּҸ� �����ϴ� ���̺��̴�.

���� CParent�� Output�� �����Լ��̰� CChild Ŭ������ Output�� �������Ѵٸ�
�׷� �� CChild ��ü�� �����ϸ� �����Լ� ���̺��� CChild Ŭ������ Output
�ּҰ� �ö󰡰� �ȴ�.

���� CParent ��ü�� �����Ѵٸ� CParent �� Output �ּҰ� �ö󰡰� �ȴ�

�׷��� Output�Լ�, �� �����Լ��� ȣ���ϰ� �Ǹ� ���� �����Լ� ���̺��� ����
�ؼ� �޸� �ּҸ� Ȯ���Ѵ�. �����Լ����̺� CChild �� Output �ּҰ�
�� �ִٸ� �� �ּ��� �Լ��� ȣ�����ִ� �����̴�.

�߿�) �θ� Ŭ������ �Ҹ��ڴ� �׻� ����Ҹ��ڷ� ������ش�.

�Ҹ��ڵ� �����Լ��� ���� �� �ִ�. �θ��� �Ҹ��ڴ� �����Լ��� ��������.
*/

class CParent
{
public:
	CParent()
	{
		cout << "CParent ������" << endl;
	}
	virtual ~CParent()
	{
		cout << "CParent �Ҹ���" << endl;
	}

public:
	int m_iA = 0;

protected:
	int m_iB = 0;

private:
	int m_iC = 0;

public:
	virtual void Output()
	{
		cout << "Parent Ouput Function" << endl;
	}

	// ���������Լ� : �����Լ� �ڿ� = 0 �� �ٿ��ָ� �ش� �����Լ���
	// ���������Լ��� �ȴ�. ���������Լ��� �����κ��� �������� �ʴ´�.
	// ���������Լ��� ������ �ִ� Ŭ������ �߻�Ŭ������� �θ���.
	// �߻�Ŭ������ �ν��Ͻ�(��ü) ������ �Ұ����ϴ�.
	// ���������Լ��� �ڽĿ��� �ݵ�� ������ �ؾ��Ѵ�. �ֳ��ϸ� ���������Լ���
	// ���� �κ��� ���� ������ �ݵ�� �ڽĿ��� �������ؼ� ����� ��������
	// ������ִ� �Լ��̱� �����̴�.
	virtual void OutputPure() = 0;
};

class CChild :public CParent
{
public:
	CChild()
	{
		m_iB = 200;
		// m_iC�� private�̱� ������ �ڽ� ���ο����� ������ �Ұ����ϴ�.
		/*m_iC = 300;*/
		cout << "CChild ������" << endl;
	}
	virtual ~CChild()
	{
		cout << "CChild �Ҹ���" << endl;
	}

protected:
	int m_iD = 0;

public:
	void ChildOutput()
	{
		cout << "Child Ouput Function" << endl;
	}

	virtual void Output()
	{
		CParent::Output();
		cout << "Child Ouput Function" << endl;
	}

	virtual void OutputPure()
	{

	}
};

class CChild1 :private CParent
{
public:
	CChild1()
	{
		m_iA = 100;
		m_iB = 200;
		cout << "CChild1 ������" << endl;
	}
	~CChild1()
	{
		cout << "CChild1 �Ҹ���" << endl;
	}

private:
	int m_iD = 0;

public:
	virtual void OutputPure()
	{

	}
};

class CChildChild :public CChild
{
public:
	CChildChild()
	{
		m_iD = 500;
		cout << "CChildChild ������" << endl;
	}
	~CChildChild()
	{
		cout << "CChildChild �Ҹ���" << endl;
	}

private:
	int m_iE = 0;
};

int main()
{
	/*
	��Ӱ��迡���� ������ ȣ�� ���� : �θ� -> �ڽ� ������ ȣ��ȴ�.
	��Ӱ��迡���� �Ҹ��� ȣ�� ���� : �ڽ� -> �θ� ������ ȣ��ȴ�.
	*/
	
	/*CParent parent;
	CChild	child;
	CChild1 child1;
	CChildChild childchild;*/
	
	/*child.Output();*/
	// �θ��� ��� �Լ����� ���� �ϳ��� private�̾ �Լ� ��ü�� public�̶�
	// �ܺο��� ���� �����ϴ�.
	/*child1.Output();*/
	// �̰� �ȵȴ�. ���ʿ� private���� ��ӹް�������.

	/*parent.m_iA = 100;

	child.m_iA = 200;*/

	// CChild1 Ŭ������ CParent�� private ����� �ϰ� �����Ƿ� CParent��
	// public���� �����Ǿ��ִ� ����鵵 �ܺο����� ������ �Ұ����ϴ�.
	/*child1.m_iA = 300;*/
	/*child1.Output();*/

	// CChild Ŭ������ CParent Ŭ������ ��ӹް� �ִ�.
	// new CChild�� �ϰ� �Ǹ� CChild ��ü �ϳ��� �������ְ� �� �޸� �ּ�
	// �� ��ȯ�Ѵ�.
	// �׷��� �Ʒ������� CParent* Ÿ�� ������ �� ��ȯ�� �ּҸ� �������ְ�
	// �ִ�. �θ� ������Ÿ�Կ� CChild ��ü�� �޸� �ּҸ� ���� �� �ִ�
	// ������ ��Ӱ��迡 �ֱ� �����̴�. �ڽ� �޸� �ּҸ� �θ������� Ÿ������
	// ����ȯ �� ���̱� �����̴�. �̷� ����ȯ�� ��ĳ�����̶�� �Ѵ�.
	// �ڽ� -> �θ� Ÿ�� ����ȯ : ��ĳ����
	// �θ� -> �ڽ� Ÿ�� ����ȭ : �ٿ�ĳ����
	CParent* pParent = new CChild;
	CChild child1;
	// CParent Ŭ������ �߻�Ŭ�����̱� ������ ��ü ������ �Ұ����ϴ�.
	// �����ʹ� ��ü ������ �ƴϰ� �޸� �ּҸ� ��� ������ �����ϴ�.
	// ����� �������̽� ���� �����Ҷ� �����ϴ�.
	//CParent parent;
	/*CParent* pParent1 = new CChild1;*/
	// CChild1�� private���� ��ӹް� ������ ����ȯ�� �ȵȴ�.
	/*CParent* pParent2 = new CChildChild;

	CParent* pParentArr[2] = {};

	pParentArr[0] = new CChild;
	pParentArr[1] = new CChildChild;*/

	// �Ʒ� �� Ŭ������ ��� CParent Ŭ������ ��ӹް� �ִ�.
	// �׷��Ƿ� pParent�� �� Ÿ�� ��� �ٿ�ĳ���� �����ϴ�.
	// �׷��� pParent�� CChild�� �Ҵ��� ��ü�̴�.
	// �� ��ü�� CChild1 Ÿ������ �ٿ�ĳ�����Ͽ� �־��ְ� �Ǹ�
	// �� ��ü�� ����Ҷ� ������ �߻��� �� �ִ�. �ֳ��ϸ� ���ʿ� ������ ��ü
	// �� �ƴ� �ٸ�Ÿ������ ��ȯ�Ʊ� �����̴�. (CChild -> CParent -> CChild1)
	CChild* pChild = (CChild*)pParent;
	CChild1* pChild1 = (CChild1*)pParent;

	// CChild Ŭ������ �ִ� ChildOutput �Լ��� ������ �� ����.
	// �ֳ��ϸ� pParent�� CParent ������Ÿ���̱� ������ �ڽ� ����� 
	// ������ �Ұ����ϱ� �����̴�. ���� �����ϰ� �ʹٸ� ����ȯ �ؾ��Ѵ�.
	//((CChild*)pParent)->ChildOutput();
	pParent->Output();
	// pParent�� CChild Ÿ������ �����Ҵ��� ��ĳ���õ� �����Ͱ�ü��
	// CChild���� Output�� �����Լ��� ������ �Ǿ������Ƿ� CChild�� Output�� ���´�.
	// CChild�� �����Ǹ� Ǯ�� �θ��� output �����Լ��� ��µȴ�.
	/*pParent->CParent::Output();*/
	// ��ó�� ��������� ��� Output���� �������ָ� ���ϴ� �����Լ��� ȣ������ �� �ִ�.

	// ���� delete�� �ϰ� �Ǹ� CChild �Ҹ��� -> CParent �Ҹ��ڰ� ȣ��Ǿ��
	// �ϴµ� ������ CParent �Ҹ��ڸ� ȣ��ȴ�.
	// �ֳ��ϸ� �ٺ������� pParent�� CParent ������ Ÿ���̴�. CParent ������
	// Ÿ���̱� ������ CChild �Ҹ��ڰ� ȣ��� �� �ִ�.
	delete pParent;
	// �Ҹ��ڿ� delete ��� �ۼ��� �ڽ�->�θ� ������ ȣ���� ���ٵ� �ڽ��� 
	// delete�� �ȵǼ� �ڽ��� �����Ҵ� �޸� ������ �ȵǹǷ� ������ �Ǵ°��̴�. 
	// �׷��� �θ� �Ҹ��ڸ� �����Լ��� ����� �����Լ����̺��� �����ϰ���
	// �ڽ��� �Ҹ��ڵ� ȣ��ǰ��ؼ� delete �Ҽ� �ְ� �ϴ� ���̴�.
	// CChild�� CChildChild�� �θ��̴� CChild �Ҹ��ڵ� �����Լ��� ������Ѵ�.

	/*delete pChild;*/
	//�̷��� ��ȯ�� pChild�� delete�ϸ� �Ҹ��ڰ� �Ѵ� ���´�.
	/*delete pParent2;*/

	for (int i = 0; i < 2; i++)
	{
		/*delete pParentArr[i];*/
	}

	return 0;
}