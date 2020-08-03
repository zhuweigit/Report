#include "List.h"

 

List::List()
{
	head = nullptr;
	L = nullptr;
}

void List::CreateList()
{
	LinkList * s, *p; // s指向新结点，p指向链表中最后的结点 
	p = nullptr;
	s = new LinkList;   //动态建立第一个新结点
	cout << "请输入一个整数值作为新结点的数据信息,输入0时建立链表结束" << endl;

	cin >> s->data;  //输入新结点数据
	head = NULL;   //头指针初始值为NULL
	if (s->data == 0)  //第一个结点数据就为0，建立一个空链表
	{
		cout << "您建立的空链表" << endl;
		delete  s;  //释放数据为0的结点
	}
	else //建立非空链表
	{
		while (s->data != 0)  //通过判断新结点数据来进行循环
		{
			if (head == NULL)   head = s; //头指针赋值
			else  p->next = s;  //将新结点插入已有链表的最后
			p = s; // p指向链表中最后的结点 

			s = new LinkList; //动态建立一个新结点
			cout << "请输入一个整数值作为新结点的数据信息,输入0时建立链表结束" << endl;
			cin >> s->data; //输入新结点数据
		}
		p->next = NULL; //设置链表尾部为空
		delete  s;  //释放数据为0的结点
		cout << endl << "链表建立完成...";

	}
	L = head;
}

int List::GetElem(int i)
{
	int j;
	LinkList* p;   //声明一节点p
	p = L->next;   //让p指向L的第一个链表、
	j = 1;     //j为计数器
	while (p&&j < i)       //当前指针不为空且没到i尾部
	{
		p = p->next;   //指向下一个节点
		++j;

	}
	if (!p || j > 1)     //第i个元素不存在
	{
		return   -1;
	}
 
	return p->data;
}



