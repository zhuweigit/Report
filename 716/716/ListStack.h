#pragma once
struct Node {
	int data;
	Node*next;

};

class LinkStack
{
	Node node;
	Node* top;
	int count;   //计数
public:
	LinkStack();
	bool Push(int element);
	bool Pop(int*e);      //用e返回被删除的数据值
	bool  IsEmpty();   //判断整个链表是否为空  

};