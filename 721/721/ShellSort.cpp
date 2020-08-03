//˼·�����������飬ÿ���н��в�������
#include <iostream>
#include <stdlib.h>

#define MAXSIZE 1000
using namespace std;
struct sqlist {
	int r[MAXSIZE + 1];//r[0]���ڱ��ã������м��ٱȽϲ���  //Ԥ������  ��һ��ȫ���� ����ϵͳ���վͺ�
	int length;      //ʵ��ʹ�ó���
	sqlist(int num[], int len)
	{
		length = len;
		for (int i = 1; i <= length; i++)
		{
			r[i] = num[i];
		}


	}
};

void ShellSort(sqlist* L, int dlta[], int t);
void ShellInsert(sqlist*L, int dk);
void swap(sqlist* L, int i, int j);
void printlist(sqlist* L);



void swap(sqlist* L, int i, int j) {
	int temp = L->r[i];
	L->r[i] = L->r[j];
	L->r[j] = temp;
}


void printlist(sqlist* L) {
	for (int i = 1; i < L->length; i++) {
		cout << L->r[i] << ',';

	}
	cout << '\n';
}




//ϣ������   Length ������
void ShellSort(sqlist* L, int dlta[], int t)
{
	for (int k = 0; k < t; k++)   //���Ĵ���
	{
		ShellInsert(L, dlta[k]);
	}

}

void ShellInsert(sqlist*L, int dk)   //dk������
{
	int i, j;
	for (i = dk + 1; i <= L->length; ++i) // i�ܵ���
	{
		if (L->r[i] < L->r[i - dk])  //��ͷ�Ƚ� ˳�����
		{
			L->r[0] = L->r[i];
			//������ٿ������ǰ��Ԫ���ǲ��Ǻ��ʣ�Ҫ��֤����˳�������
			////�ڷֵ����L-<r[0]������С��¼�����ڿ������ĸ��ȽϺ�  ����� ����һ�ξͺ�
			for (j = i - dk; j > 0 && L->r[0] < L->r[j]; j = j - dk)
			{
				L->r[j + dk] = L->r[j];
			}
			L->r[j + dk] = L->r[0];
		}
	}
}



int main() {

	//init(L, 100);
	int nums[10] = { 0,9,1,5,8, 3, 7 ,4 ,6, 2 };
	int dlta[] = { 4,2,1 };//����

	sqlist* L = new sqlist(nums, 9);
	ShellSort(L, dlta, 3);
	printlist(L);
	system("pause");
	return 1;
}
