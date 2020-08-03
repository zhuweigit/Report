#include "LinkStack.h"

LinkStack::LinkStack()
{
	 node.data=0;
	  node.next = nullptr;  //各部分也写好
	  count=0;

}

bool LinkStack::Push(int element)
{
	LinkStack*p=new LinkStack;
	p->node.data = element;
	

}

bool LinkStack::Pop()
{
	return false;
}
