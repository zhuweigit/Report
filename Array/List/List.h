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
 
	LinkList*head;   //头指针
	LinkList*L;     // 链表

public:
	List();
	void CreateList();                 //构造链表
	int GetElem( int i);  //链表的读取
};
