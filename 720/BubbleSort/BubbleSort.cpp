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


void Cout(SqList*L);       
void BubbleSort(SqList* L);   //ð������


//ð������
void BubbleSort(SqList* L)
{
	int i, j;
	bool flag = true;
	for (i = 0; i < L->Length||flag; i++)  //ָ������λ��
	{
		flag = false;
		for (j = L->Length - 2; j >= i; j--)
		{
			if (L->ans[j] > L->ans[j+1])  //��ǰλ�ñȺ�һ���� ������
			{
				Swap(L, j, j + 1);
				flag = true;
			}
				
		}
	}
	cout << "ð���������� \n";
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
	// sql->ans[MAXSIZE] = ENDLESS;  //�ڱ�

	BubbleSort(sql);

}