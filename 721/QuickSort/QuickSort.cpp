//˼·�����������飬ÿ���н��в�������
#include <iostream>
#include <stdlib.h>

#define MAXSIZE 1000
using namespace std;
struct sqlist {
	int r[MAXSIZE + 1];//r[0]���ڱ��ã������м��ٱȽϲ���  //Ԥ������  ��һ��ȫ���� ����ϵͳ���վͺ�
	int length;      //ʵ��ʹ�ó���
	int pivotloc;   //���ĵ�λ��
	sqlist(int num[], int len)
	{
		length = len;
		for (int i = 0; i < length; i++)
		{
			r[i+1] = num[i];
		}


	}
};

void QSort(sqlist* L,int low,int hight);
int Partition(sqlist*L, int low, int hight);
void printlist(sqlist* L);


 


void printlist(sqlist* L) {
	for (int i = 1; i < L->length; i++) {
		cout << L->r[i] << ',';

	}
	cout << '\n';
}


 
void QSort(sqlist* L, int low, int hight)
{
	if (low < hight)
	{
		L->pivotloc = Partition(L, low, hight);
		QSort(L, low, L->pivotloc - 1);
		QSort(L, L->pivotloc + 1, hight);
	}
	 	
}

int Partition(sqlist*L, int low, int hight)   //dk������
{
	L->r[0] = L->r[low];  //�ᵽ0λ��
	L->pivotloc =L->r[low];
	while (hight > low) 
	{
		while (low < hight&& L->pivotloc<= L->r[hight])  --hight;
		L->r[low] = L->r[hight];

		while (low<hight&&L->pivotloc>=L->r[low]) ++low;
		L->r[hight] = L->r[low];
	}
	L->r[low] = L->r[0];
		return low;
 
}



int main() {

 
	int nums[10] = { 8,9,1,5,8, 3, 7 ,4 ,6};
 

	sqlist* L = new sqlist(nums, 10);
      QSort(L,1,9);
	printlist(L);
	system("pause");
	return 1;
}
