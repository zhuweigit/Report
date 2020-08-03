#include "stack.h"

Stack::Stack()
{
   data[STACKSIZE] = {0};
   top=-1;      //¿Õ

}

int Stack::GetTop()
{
	if (top == -1)  return -1;

	return data[top];
}

bool Stack::Push(int element)
{
	if (top == STACKSIZE - 1)   //Èç¹ûÂúÁË
		return false;
	top++;
	data[top] = element;
	return true;
}

bool Stack::Pop(int element)
{
	if (top == -1)
		return false;
	element = data[top];
	top--;
	return true;
		
}

int Stack::GetLength()
{
	
	return top+1;
}

void Stack::Destroy()
{
	top = -1;
}

void Stack::Clear()
{
	top = -1;
}

bool Stack::IsEmpty()
{
	if (top == -1)  return true;
	return false;
}