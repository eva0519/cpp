#pragma once

#include <iostream>
#include <vector>
#include <list>

#include <unordered_map>
// ����Ʈ�� �ʱ���. �ݾ� �߶� Ž���ϱ� ������ Ž�������� �ξ� ������. ����Ʈ���̱� ������
// ���� �ڽ� ������ 2������ �ڽ��� ��� ���ԵǴ� ����. ���� ����� ����Ʈ�� ������ �Ǿ��ִ�.
// ����� ����Ʈ���� ��带 �ܹ����� �ƴ� �¿� ������ ���� �����Ѵ�.
// �߰� ������ ����Ҷ��� ������. ������ �ѹ� �����س��� ã�ƾ����� ������ ������ ������.
// �Ϲ� map�� ��� ������ ������. unordered_map�� ��� ���������� ��� �˰������� �Ǿ��־� ������.
// unordered_map �� �ν�Ʈ ���̺귯������ cpp std�� �Ѿ�Դ�.
#include <string>
// ��Ʈ�� Ŭ������ ��� ���ڿ��� ���� ���ϰ� �ϱ� ���� ���������. ������ ������ �ʴ�.

#include "Flags.h"

using namespace std;

// ��������� ���
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
	// ���������� ��� T�� �޾ƿ� ����Ÿ���� vector<class CStage*>�̰� 
	// m_vecStage�� �ּҸ� �����Ͽ� ���ڷ� �޾ƿð��̴�.
	// �Ʒ��� ���ſ� ������� iter��ɰ� ���� stl�� �ִ� �⺻�Լ� ��ɵ��̴�.
	// stl standard�� ������ �Ǳ� ������ ����� include ���ָ�
	// iterator�� ���� ������ �ʾƵ� ����Ҽ��ִ�.
	T::iterator iter;
	T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	p.clear();
}