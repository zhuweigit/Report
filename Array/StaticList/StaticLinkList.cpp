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
	int i = space[0].cur;  //����������ȡ�������±꣬����i
	if (space[0].cur)  //����ֻ�����Լ� ������ʱ
	{
		space[0].cur = space[i].cur;   //������cur  ��������λ
	}

	return i;
}

bool StaticLinkList::Insert(int i, int e)
{
	int j, k ,l;    
	k = MAXSIZE - 1;   //k�����һ��Ԫ���±�
	if (i<1 || i>Length()+1)  //������Ч��Χ֮��
		return false;
	j = New();    //��ÿ��б������±�
	if (j)
	{
		space[j].data = e;   //�Ȱ�ֵ����
		for (l = 1; l <= i - 1; l++)                     //�ҵ���i֮ǰ��λ��
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
	int j, k;     //j���մ�ҪɾԪ�ص�λ��  k���ռ�¼ҪɾԪ��ǰһ��Ԫ��λ��
	if (i<0 || i>MAXSIZE - 1)        //�ж�������Ч����
		return false;
	k = MAXSIZE - 1;           //kͬ�������顰ͷ�ڵ㡱
	for (j = 1; j < i; j++)         //�ҵ�ǰһ�����λ��
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
	int count = 0;   //����
	while(space[i].cur!=0)
	{
		 
		i=space[i].cur;
		
		count++;
	}
	 
	return count;
}
