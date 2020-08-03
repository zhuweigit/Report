#pragma once
#define MAXSIZE 5
template<typename T>

class CircularQueue
{
	T data[MAXSIZE];
	int front;   //ͷָ��
	int rear;     //βָ��

public:

	CircularQueue();   //��ʼ��
	int GetLength();        //��ȡ���г���
	bool Push(T e);            //���  δ����ʱ��Ų���
	bool Pop(T* e);             //����  ��e�洢
	void Cout();            //���




};

