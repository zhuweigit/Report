#pragma once
#define MAXSIZE 6
struct Node            //数组节点         
{
	int data;
	int cur;

};

class StaticLinkList   //静态数组链表
{
	Node space[MAXSIZE];  //一维数组做链表

public:

	StaticLinkList();            //初始化状态   
	int New();                  //新节点的申请   返回新分配的节点的下标节点
	bool Insert(int i,int e);              //插入操作  在第i元素（不是数组号（位置），是从最一个头节点元素出发计数的）之前插入数据元素e
	bool Delete(int i);                    //删除操作 第i个元素
	void FreeMemory(int j);                 //回收内存  j是要回收内存的地址
	void Put();
	int Length();       //有效长度
};