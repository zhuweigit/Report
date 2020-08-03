#include<iostream>
using namespace std;

#define MAXSIZE 10
#define ENDLESS  121221221

//ð������

struct SqList        //˳��洢��
{
	int ans[MAXSIZE];  //�洢���
	int Length;           //ʵ�ʳ���
	SqList() { Length = MAXSIZE; };
};

void Swap(SqList* L, int i, int j)
{
	int temp = L->ans[i];
	L->ans[i] = L->ans[j];
	L->ans[j] = temp;

}

void Cout(SqList*L)
{
	for (int i = 0; i < L->Length; i++)
		cout << L->ans[i] << " ";
	cout << endl;
}

void InsertSort(SqList* L)    //��������
{
	int i, j,value;
	for (i = 0; i < L->Length-1; i++)  
	{
		value = L->ans[i+1];  
		for (j = i + 1; value < L->ans[j - 1] && j>0;j-- )  //��ҪŲ��˳��  
		{
			 
			L->ans[j] = L->ans[j-1]; //��ǰ���Ǹ�Ԫ��������Ų
		    
		}
		 L->ans[j]= value;   //��i���ڵ�ֵŲ��j-1���Ŀյ�ȥ
	}
	cout << "������������ \n";
	Cout(L);
}
int main()
{
	SqList* sql = new SqList();
	cout << "������" << MAXSIZE << " ��" << endl;
	for (int i = 0; i < MAXSIZE; i++)
	{
		cin >> sql->ans[i];
	}
	InsertSort(sql);
}