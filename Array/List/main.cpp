#include"List.h"
#include<stdlib.h>
using namespace std;

int main()
{
	int i;
	List list;
LinkList *L = nullptr;
	 list.CreateList();

	 cout << "��������ҵڼ���Ԫ�ص���" << endl;
	 cin >> i;
	cout << list.GetElem(i);
	system("pause");
 }