#include<iostream>
#include"CircularQueue.h"
#include"CircularQueue.cpp"


int main()
{
	CircularQueue<int> CirQueue;   //zhiding
	int element;
	int result = 0;
	int*poped = &result;
	while (cin >> element)
		CirQueue.Push(element);
	CirQueue.Cout();
	if (CirQueue.Pop(poped))
	{
		cout << "删除的数：" << endl;
		cout << *poped<<endl;
	}

	cout << "删除过之后：" << endl;
	CirQueue.Push(element);
	CirQueue.Cout();



}
