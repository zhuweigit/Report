#include"stack.h"
#include<iostream>
using namespace std;


int main()
{
	Stack stack;
	int element;  //   

	cout << "输入需要入栈元素，停止请按-1" << endl;
	while(cin >> element&&element!=-1)
	stack.Push(element);
	cout << "栈顶元素多少： " << endl;
	cout<<stack.GetTop()<<endl;              //返回栈顶元素
 
	
	cout << "长度多少： "<<endl;
	if (!stack.IsEmpty())           //是否为空
		cout << stack.GetLength();
	else
		cout << "空" << endl;
	stack.Clear();             //清空栈

}