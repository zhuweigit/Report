#include"stack.h"
#include<iostream>
using namespace std;


int main()
{
	Stack stack;
	int element;  //   

	cout << "������Ҫ��ջԪ�أ�ֹͣ�밴-1" << endl;
	while(cin >> element&&element!=-1)
	stack.Push(element);
	cout << "ջ��Ԫ�ض��٣� " << endl;
	cout<<stack.GetTop()<<endl;              //����ջ��Ԫ��
 
	
	cout << "���ȶ��٣� "<<endl;
	if (!stack.IsEmpty())           //�Ƿ�Ϊ��
		cout << stack.GetLength();
	else
		cout << "��" << endl;
	stack.Clear();             //���ջ

}