#pragma once
struct Node {
	int data;
	Node*next;

};

class LinkStack
{
	Node node;
	LinkStack* top;
	int count;   //����
public:
	LinkStack();
	bool Push(int element);
	bool Pop();




};