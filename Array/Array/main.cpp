#include"Arrays.h"
#include<iostream>
using namespace std;

int main()
{ 
	int a[] = { 1,2,3,4,5,6 };
	Arrays arr(a,6);

	int GetElement = 0;
	int*e = &GetElement;
	if (arr.GetElem(3, e))
	{
		cout << "得到的元素:" << *e<<endl;
	}

	if (arr.ListInsert(3, 3))
	{
		arr.out();
	}
	 
	if (arr.ListDelete(3, e))       //删除第i个位置的元素，并将第i个位置用e返回
	{
		arr.out();
	}





}
