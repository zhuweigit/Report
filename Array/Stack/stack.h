#pragma once
#define STACKSIZE 5


class Stack
{
	int data[STACKSIZE];
	int top;       //ָʾԪ��ջ��
public:

	Stack(); //��ʼ��
	void Destroy();           //���ջ���ھ�������
	void Clear();             //���ջ
	bool IsEmpty();            //�Ƿ�Ϊ��
	int GetTop();              //����ջ��Ԫ��
	bool Push(int element);               //��ջ  ���ز���״̬
	bool Pop(int element);                //��ջ������ɾ����Ԫ��
	int GetLength();           //��ȡջ�ĸ���

 


};