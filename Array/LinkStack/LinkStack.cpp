#include "LinkStack.h"

LinkStack::LinkStack()
{
	 node.data=0;
	  node.next = nullptr;  //������Ҳд��
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
