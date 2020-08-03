#include<iostream>
using namespace std;

#define MAXSIZE 10
#define ENDLESS  121221221

//冒泡排序法

struct SqList        //顺序存储表
{
	int ans[MAXSIZE];  //存储结果
	int Length;           //实际长度
	SqList() { Length = MAXSIZE; };
};

void Swap(SqList* L, int i, int j)
{
	int temp = L->ans[i];
	L->ans[i] = L->ans[j];
	L->ans[j] = temp;
      
}


void Cout(SqList*L);       
void BubbleSort(SqList* L);   //冒泡排序法


//冒泡排序法
void BubbleSort(SqList* L)
{
	int i, j;
	bool flag = true;
	for (i = 0; i < L->Length||flag; i++)  //指定排序位置
	{
		flag = false;
		for (j = L->Length - 2; j >= i; j--)
		{
			if (L->ans[j] > L->ans[j+1])  //当前位置比后一个大 就逆序
			{
				Swap(L, j, j + 1);
				flag = true;
			}
				
		}
	}
	cout << "冒泡排序法排序： \n";
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
	cout << "请输入" << MAXSIZE << " 个" << endl;
	for (int i = 0; i < MAXSIZE; i++)
	{
		cin >> sql->ans[i];
	}
	// sql->ans[MAXSIZE] = ENDLESS;  //哨兵

	BubbleSort(sql);

}