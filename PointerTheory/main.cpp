
#include <iostream>
#include <string>

using namespace std;

struct _tagStudent
{
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAvg;
};

int main()
{
	/*
	������ : ����Ű��. �Ϲ� ������ �Ϲ����� ���� �����ϰ� ������
	������ ������ �޸� �ּҸ� �����ϰ� �ȴ�. ��� ���� Ÿ���� ������ Ÿ����
	������ �� �ִ�. int������ �ּҴ� int ������ ������ ������ �ؾ��Ѵ�.
	�����ʹ� �޸� �ּҸ� ��Ƴ��� �����̱� ������ x86���� �����Ҷ���
	������ 4byte�� ���´�. x64�϶��� 8byte�� ���´�.

	�����ʹ� �ڱ� ������ �ƹ����ϵ� �� �� ����. �ݵ�� �ٸ� ������ �޸�
	�ּҸ� ������ �־�� ���� �� �� �ִµ� ������ �ִ� �� �޸� �ּҿ�
	�����ؼ� ���� ������ �� �ִ�.

	���� : ����Ÿ�� *������; �� ���·� �����Ѵ�.
	*/
	int iNumber = 100;
	// ���� ����� *�� �ٿ��ָ� �ش� Ÿ���� ������ ������ ����ȴ�.
	// ���� �տ� &�� �ٿ��ָ� �ش� ������ �޸� �ּҰ� �ȴ�.
	// pNum�� iNUmber������ �޸� �ּҸ� ������ ���� �ƴ�. �׷��Ƿ� pNum
	// �� �̿��ؼ� iNumber�� ���� ������ �� �ְ� �� ���̴�.
	int *pNum = &iNumber;

	cout << sizeof(int*) << endl;
	cout << sizeof(char*) << endl;
	cout << sizeof(double*) << endl;

	// pNum�� �̿��ؼ� iNumber�� ���� �����غ���.
	// �������� �̿��ؼ� ���� �����ų� ������ �� �ִ�.
	// �������� ������ ���� �տ� *�� ���̰� �Ǹ� �������� �ȴ�.
	cout << *pNum << endl;
	*pNum = 1234;

	cout << "iNumber Value : " << iNumber << endl;
	cout << "iNumber Address : " << &iNumber << endl;
	cout << "pNum Value : " << pNum << endl;
	cout << "pNum Address : " << &pNum << endl;

	/*
	�����Ϳ� �迭�� ���� : �迭���� �����ʹ�. �迭�� ��ü�� �ش� �迭��
	�޸𸮿����� ������ �ּҸ� �ǹ��Ѵ�.
	*/
	int iArray[10] = { 1,2,3,4,5,6,7,8,9,10 };

	cout << "Array Address : " << iArray << endl;
	cout << "Array Address : " << &iArray[0] << endl;

	int *pArray = iArray;

	cout << pArray[2] << endl;

	/*
	������ ���� : +, -  ������ �����Ѵ�. ++, -- �� �����ѵ� 1�� �����ϰԵǸ�
	�ܼ��� �޸��ּҰ��� 1�����ϴ� ���� �ƴϴ�. int �������� ���
	int Ÿ���� �޸� �ּҸ� ���� �Ǵµ� �޸� �ּҿ� 1�� �����ָ�
	1������ �ƴ� �ش� ������Ÿ���� ����Ÿ�� ũ�⸸ŭ �����ϰԵȴ�.
	int �������̹Ƿ� int�� ũ���� 4��ŭ ���� �����ϰ� �Ǵ°��̴�.
	*/
	cout << pArray << endl;
	cout << pArray + 2 << endl;
	cout << *pArray << endl;
	cout << *(pArray + 2) << endl;  
	cout << *pArray + 100 << endl;

	char *pText = "�׽�Ʈ ���ڿ�"; 
	// char�����͹��ڿ��� �����ؼ� �ٷ� ���ڿ��� �������� vs2017 �̻���ʹ� const Ÿ������ ���������Ѵ�.
	// �ƴϸ� ������Ʈ �Ӽ����� ���� c++ ����� �ؼ��Ӽ��� �������ָ� �ȴ�.

	cout << pText << endl;
	cout << (int*)pText << endl;

	pText = "abcd";
	
	cout << pText << endl;
	cout << (int*)pText << endl;

	pText = "abcdefg";

	cout << pText << endl;
	cout << (int*)pText << endl;

	char	str[8] = "abcdefg";

	cout << str << endl;
	cout << (int*)str << endl;
	cout << (int*)&str[0] << endl;

	// ����Ʈ�� ���� ���� : �����ʹ� �ٸ� ������ �޸��ּҸ� ������ �ǰ�
	// �� �޸��ּҸ� �˰��ֱ� ������ �ű⿡ �����ؼ� ���� �����ϴ� ��Ȱ���Ѵ�.

	_tagStudent	tStudent = {};

	tStudent.iKor = 100;

	_tagStudent* pStudent = &tStudent;

	// ������ �켱���� ������ .�� ���� �ν��ϰ� �ȴ�. �޸��ּ�.�� �߸���
	// �����̴�. �׷��Ƿ� *pStudent�� ��ȣ�� ������ �Ŀ� .�� �̿��ؼ�
	// ����Ű�� ����� ��������� �����ؾ� �Ѵ�.
	(*pStudent).iKor = 50;

	// �޸��ּ�-> �� �̿��ؼ� ����Ű�� ����� ����� ������ �� �ִ�.
	pStudent->iKor = 80;
	// ���� �ΰ��� ���� ���� �ǹ��̴�.
	cout << tStudent.iKor << endl;

	// void : Ÿ���� ����. void�� ������Ÿ���� Ȱ���� �� �ִ�.
	// void* ������ �����ϰ� �Ǹ� �� ������ � Ÿ���� �޸� �ּҵ�
	// ��� ���尡���ϴ�. ��, �������� �Ұ����ϰ� �޸� �ּҸ� ����
	// �����ϴ�.
	void* pVoid = &iNumber;

	cout << "iNumber Address : " << pVoid << endl;
	/**pVoid = 10;*/
	int* pConvert = (int*)pVoid;
	*pConvert = 10101010;
	// ���̵� �����ʹ� �������� �Ұ����ϱ� ������ ��ó�� Ÿ���� ����
	// �����ͺ����� ������ ����ȯ ���ִ½����� �ؾ� ������ �� �� �ִ�.

	cout << iNumber << endl;

	pVoid = &tStudent;

	cout << "tStudent Address : " << pVoid << endl;

	int iNumber1 = 1111;
	iNumber = 2222;
	pNum = &iNumber;

	// ���� ������ : *�� 2�� ���δ�. �Ϲ� ������ ������ �Ϲ� ������ �޸�
	// �ּҸ� �����ϴ� ������� ���������ʹ� �������� �������̴�. ��, ����
	// �����ʹ� ������ ������ �޸� �ּҸ� �����ϴ� �������̴�.
	int** ppNum = &pNum;

	*ppNum = &iNumber1;
	// pNum�� iNumber�� �����ϰ� �־����� pNum�� ���������� �����ϴ�
	// ppNum�� �������� �� pNum�� ���� pNum�� �����ϴ� ������ �ּҸ� iNumber1���� 
	// ppNum�� �ٲ�������ν� ������� ��� �ٲ�� �ȴ�.
	// �ᱹ �ٷ� �Ʒ����� pNum �������� iNumber �� ���� �ٲٴ� �Ϳ���
	// iNumber1 ���� �ٲٰ� �Ǵ� ��.
	*pNum = 3333;

	cout << "iNumber : " << iNumber << endl;
	cout << "iNumber Addr : " << &iNumber << endl;
	cout << "*pNum : " << *pNum << endl;
	cout << "pNum Value : " << pNum << endl;
	cout << "pNum Addr : " << &pNum << endl;
	cout << "*ppNum : " << *ppNum << endl;
	cout << "**ppNum : " << **ppNum << endl;
	cout << "ppNum Value : " << ppNum << endl;
	cout << "ppNum Addr : " << &ppNum << endl;


	return 0;
}