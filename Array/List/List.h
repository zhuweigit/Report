#pragma once
#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct LinkList
{
	int data;
	LinkList*next;
};

class List{
 
	LinkList*head;   //ͷָ��
	LinkList*L;     // ����

public:
	List();
	void CreateList();                 //��������
	int GetElem( int i);  //����Ķ�ȡ
};
