#include "List.h"

 

List::List()
{
	head = nullptr;
	L = nullptr;
}

void List::CreateList()
{
	LinkList * s, *p; // sָ���½�㣬pָ�����������Ľ�� 
	p = nullptr;
	s = new LinkList;   //��̬������һ���½��
	cout << "������һ������ֵ��Ϊ�½���������Ϣ,����0ʱ�����������" << endl;

	cin >> s->data;  //�����½������
	head = NULL;   //ͷָ���ʼֵΪNULL
	if (s->data == 0)  //��һ��������ݾ�Ϊ0������һ��������
	{
		cout << "�������Ŀ�����" << endl;
		delete  s;  //�ͷ�����Ϊ0�Ľ��
	}
	else //�����ǿ�����
	{
		while (s->data != 0)  //ͨ���ж��½������������ѭ��
		{
			if (head == NULL)   head = s; //ͷָ�븳ֵ
			else  p->next = s;  //���½�����������������
			p = s; // pָ�����������Ľ�� 

			s = new LinkList; //��̬����һ���½��
			cout << "������һ������ֵ��Ϊ�½���������Ϣ,����0ʱ�����������" << endl;
			cin >> s->data; //�����½������
		}
		p->next = NULL; //��������β��Ϊ��
		delete  s;  //�ͷ�����Ϊ0�Ľ��
		cout << endl << "���������...";

	}
	L = head;
}

int List::GetElem(int i)
{
	int j;
	LinkList* p;   //����һ�ڵ�p
	p = L->next;   //��pָ��L�ĵ�һ������
	j = 1;     //jΪ������
	while (p&&j < i)       //��ǰָ�벻Ϊ����û��iβ��
	{
		p = p->next;   //ָ����һ���ڵ�
		++j;

	}
	if (!p || j > 1)     //��i��Ԫ�ز�����
	{
		return   -1;
	}
 
	return p->data;
}



