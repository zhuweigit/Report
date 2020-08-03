#include "ListStack.h"

LinkStack::LinkStack()
{
	node.data = 0;
	node.next = nullptr;  //各部分也写好
	count = 0;

}

bool LinkStack::Push(int element)
{
	Node*p = new Node;
	p->data = element;
	p->next = top;
	top = (Node*)p;
	count++;
	return true;


}

bool LinkStack::Pop(int*e)
{
	//Node*p;
	if (IsEmpty())
		return false;
	*e = top->data;
	top = top->next;   //top向下
	count--;
	//delete p;
	return true;
  
}

bool LinkStack::IsEmpty()
{
	return false;
}

 

 