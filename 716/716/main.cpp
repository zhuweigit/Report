#include"ListStack.h"
#include<iostream>
using namespace std;

int main()
{
	LinkStack linksta;
	int element;
	int Value=-1;

	cout << "�������������Ԫ�أ��س� CTRL+Z��������" << endl;
	
	while (cin >> element)            //�س� CTRL+Z ����
		linksta.Push(element);

	
	int*RemoveVal = &Value;
	
	if (linksta.Pop(RemoveVal))
		cout << *RemoveVal << endl;
	
	

}