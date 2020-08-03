#pragma once
#define STACKSIZE 5


class Stack
{
	int data[STACKSIZE];
	int top;       //指示元素栈顶
public:

	Stack(); //初始化
	void Destroy();           //如果栈存在就销毁它
	void Clear();             //清空栈
	bool IsEmpty();            //是否为空
	int GetTop();              //返回栈顶元素
	bool Push(int element);               //入栈  返回操作状态
	bool Pop(int element);                //出栈并返回删除的元素
	int GetLength();           //获取栈的个数

 


};