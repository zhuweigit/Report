#include<iostream>
using namespace std;

#define MAXSIZE 10
#define ENDLESS  121221221

 

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

void Cout(SqList*L);
void SelectSort(SqList*L);    //ѡ������

//ѡ������  �� �Ӹ�ȫ�ֱ���min ��¼�Ƚ�ʱ����Сֵ�Ǹ���ַ  ����ʱ��������
void SelectSort(SqList* L)
{

	for (int i = 0; i < L->Length - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < L->Length ; j++)
		{

			if (L->ans[j] < L->ans[min])
				min = j;

		}
		if (min != i)
		{
			Swap(L, min, i);
		}
	}
	cout << "ѡ���������� \n";
	Cout(L);
}
void Cout(SqList*L)
{
	for (int i = 0; i < L->Length; i++)
		cout << L->ans[i] << " ";
	cout << endl;
}

int main()
{

	SqList* sql = new SqList();
	cout << "������" << MAXSIZE << " ��" << endl;
	for (int i = 0; i < MAXSIZE; i++)
	{
		cin >> sql->ans[i];
	} 
	SelectSort(sql);

}