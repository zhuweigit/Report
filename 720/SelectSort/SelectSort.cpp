#include<iostream>
using namespace std;

#define MAXSIZE 10
#define ENDLESS  121221221

 

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
void SelectSort(SqList*L);    //选择排序法

//选择排序法  ： 加个全局变量min 记录比较时的最小值那个地址  交换时交换即可
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
	cout << "选择排序法排序： \n";
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
	SelectSort(sql);

}