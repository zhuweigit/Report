#pragma once
#define MAXSIZE 6
struct Node            //����ڵ�         
{
	int data;
	int cur;

};

class StaticLinkList   //��̬��������
{
	Node space[MAXSIZE];  //һά����������

public:

	StaticLinkList();            //��ʼ��״̬   
	int New();                  //�½ڵ������   �����·���Ľڵ���±�ڵ�
	bool Insert(int i,int e);              //�������  �ڵ�iԪ�أ���������ţ�λ�ã����Ǵ���һ��ͷ�ڵ�Ԫ�س��������ģ�֮ǰ��������Ԫ��e
	bool Delete(int i);                    //ɾ������ ��i��Ԫ��
	void FreeMemory(int j);                 //�����ڴ�  j��Ҫ�����ڴ�ĵ�ַ
	void Put();
	int Length();       //��Ч����
};