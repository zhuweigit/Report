#include"CircularQueue.h"
#include<iostream>
using namespace std;

template<typename T>
CircularQueue<T>::CircularQueue()
{


	front = 0;
	rear = 0;

}

template<typename T>
int CircularQueue<T>::GetLength()
{
	return (rear - front + MAXSIZE) % MAXSIZE;   // 两段合一起
}

template<typename T>
bool CircularQueue<T>::Push(T e)
{
	if ((rear + 1) % MAXSIZE == front)  //队满 都是紧挨就是满
		return false;
	data[rear] = e;
	rear = (rear + 1) % MAXSIZE;
	return true;
}

template<typename T>
bool CircularQueue<T>::Pop(T* e)
{

	if (front == rear)
		return false;
	*e = data[front];
	front = (front + 1) % MAXSIZE;

	return true;
}

template<typename T>
void CircularQueue<T>::Cout()
{
	cout << "请输入不超过" << MAXSIZE - 1 << "的数" << endl;
	for (int i = 0; i < MAXSIZE; i++)
		cout << data[i] << " ";
	cout << endl;
}
