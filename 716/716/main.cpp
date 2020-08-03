#include"ListStack.h"
#include<iostream>
using namespace std;

int main()
{
	LinkStack linksta;
	int element;
	int Value=-1;

	cout << "请输入像输入的元素，回车 CTRL+Z结束输入" << endl;
	
	while (cin >> element)            //回车 CTRL+Z 结束
		linksta.Push(element);

	
	int*RemoveVal = &Value;
	
	if (linksta.Pop(RemoveVal))
		cout << *RemoveVal << endl;
	
	

}