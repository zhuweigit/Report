#include "StaticLinkList.h"
#include<iostream>
using namespace std;

StaticLinkList::StaticLinkList()
{
	int i;
	for (i = 0; i < MAXSIZE - 1; i++)
	{
		space[i].cur = i + 1;
		space[i].data = -1;
	}
		
	 
	space[MAXSIZE - 1].cur=0;

}

int StaticLinkList::New()
{
	int i = space[0].cur;  //从首数组里取出空闲下标，存在i
	if (space[0].cur)  //不是只有他自己 有内容时
	{
		space[0].cur = space[i].cur;   //更新了cur  空闲数组位
	}

	return i;
}

bool StaticLinkList::Insert(int i, int e)
{
	int j, k ,l;    
	k = MAXSIZE - 1;   //k是最后一个元素下标
	if (i<1 || i>Length()+1)  //不在有效范围之内
		return false;
	j = New();    //获得空闲变量的下标
	if (j)
	{
		space[j].data = e;   //先把值填了
		for (l = 1; l <= i - 1; l++)                     //找到第i之前的位置
		{
			k = space[k].cur;   //    
		}
		
		space[j].cur = space[k].cur;
		space[k].cur = j;
		return true;
	}
	return  false;
}

bool StaticLinkList::Delete(int i)
{
	int j, k;     //j最终存要删元素的位置  k最终记录要删元素前一个元素位置
	if (i<0 || i>MAXSIZE - 1)        //判断输入无效数字
		return false;
	k = MAXSIZE - 1;           //k同上是数组“头节点”
	for (j = 1; j < i; j++)         //找到前一个结点位置
	{
		k = space[k].cur;      
	}
	j = space[k].cur;  
	space[k].cur = space[j].cur;
	FreeMemory(j);
		return true;
}

void StaticLinkList::FreeMemory(int j)
{

	space[j].cur = space[0].cur;  
	space[0].cur = j;


}

void StaticLinkList::Put()
{
	if (!space[0].cur)
		return ;
	for (int i = 0; i <= Length(); i++)
	{
		cout << space[i].data<<" ";
	}
	cout << endl;
 
}

int StaticLinkList::Length()
{
	if (!space[0].cur)
		return 0;
	int i=0;
	int count = 0;   //计数
	while(space[i].cur!=0)
	{
		 
		i=space[i].cur;
		
		count++;
	}
	 
	return count;
}
