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

void Cout(SqList*L)
{
	for (int i = 0; i < L->Length; i++)
		cout << L->ans[i] << " ";
	cout << endl;
}

void InsertSort(SqList* L)    //插入排序
{
	int i, j,value;
	for (i = 0; i < L->Length-1; i++)  
	{
		value = L->ans[i+1];  
		for (j = i + 1; value < L->ans[j - 1] && j>0;j-- )  //需要挪动顺序  
		{
			 
			L->ans[j] = L->ans[j-1]; //将前面那个元素往后面挪
		    
		}
		 L->ans[j]= value;   //将i所在的值挪到j-1留的空地去
	}
	cout << "插入排序法排序： \n";
	Cout(L);
}
int main()
{
	SqList* sql = new SqList();
	cout << "请输入" << MAXSIZE << " 个" << endl;
	for (int i = 0; i < MAXSIZE; i++)
	{
		cin >> sql->ans[i];
	}
	InsertSort(sql);
}