#pragma once
struct Node {
	int data;
	Node*next;

};

class LinkStack
{
	Node node;
	Node* top;
	int count;   //����
public:
	LinkStack();
	bool Push(int element);
	bool Pop(int*e);      //��e���ر�ɾ��������ֵ
	bool  IsEmpty();   //�ж����������Ƿ�Ϊ��  

};