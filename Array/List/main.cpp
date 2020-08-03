#include"List.h"
#include<stdlib.h>
using namespace std;

int main()
{
	int i;
	List list;
LinkList *L = nullptr;
	 list.CreateList();

	 cout << "请输入查找第几个元素的数" << endl;
	 cin >> i;
	cout << list.GetElem(i);
	system("pause");
 }