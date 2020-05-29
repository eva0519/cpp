
#include <iostream>
#include "LinkedList.h"

using namespace std;

int main()
{
	CLinkedList<int>	listInt;
	CLinkedList<float>	listFloat;

	for (int i = 0; i < 100; ++i)
	{
		listInt.push_back(i + 1);
	}

	/*cout << listInt.size() << endl;*/

	CLinkedList<int>::iterator iter;
	for (iter = listInt.begin(); iter != listInt.end(); ++iter)
	{
		cout << *iter << endl;
	}

	cout << "==== reverse ====" << endl;
	CLinkedList<int>::reverse_iterator riter;

	for (riter = listInt.rbegin(); riter != listInt.rend(); ++riter)
	{
		cout << *riter << endl;
	}

	return 0;
}