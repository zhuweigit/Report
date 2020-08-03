#pragma once
#define MAXSIZE 5
template<typename T>

class CircularQueue
{
	T data[MAXSIZE];
	int front;   //头指针
	int rear;     //尾指针

public:

	CircularQueue();   //初始化
	int GetLength();        //获取队列长度
	bool Push(T e);            //入队  未满的时候才插入
	bool Pop(T* e);             //出队  用e存储
	void Cout();            //输出




};

