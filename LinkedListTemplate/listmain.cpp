
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
	return 0;
}