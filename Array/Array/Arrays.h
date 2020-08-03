#pragma once

 

class  Arrays 
{
     
	int* Data ;      //存储空间的起始位置
	int Length;       //线性表当前长度

public:
	Arrays(int *a, int size);
	bool GetElem(int i, int* e);    //将数组中的第i个位置的元素返回给e  不需要数据成员不需要传参

	bool ListInsert( int i, int e);    //将数组中的第i个位置插入新元素e

	bool ListDelete(int i, int* e);       //删除第i个位置的元素，并将第i个位置用e返回

	void out();
};