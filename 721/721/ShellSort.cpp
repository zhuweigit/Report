//思路：按步长分组，每组中进行插入排序
#include <iostream>
#include <stdlib.h>

#define MAXSIZE 1000
using namespace std;
struct sqlist {
	int r[MAXSIZE + 1];//r[0]做哨兵用，快排中减少比较操作  //预先申请  不一定全用完 大不了系统回收就好
	int length;      //实际使用长度
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




//希尔排序   Length 是增量
void ShellSort(sqlist* L, int dlta[], int t)
{
	for (int k = 0; k < t; k++)   //做的次数
	{
		ShellInsert(L, dlta[k]);
	}

}

void ShellInsert(sqlist*L, int dk)   //dk是增量
{
	int i, j;
	for (i = dk + 1; i <= L->length; ++i) // i能到哪
	{
		if (L->r[i] < L->r[i - dk])  //两头比较 顺序改正
		{
			L->r[0] = L->r[i];
			//在组里，再看这个与前面元素是不是合适（要保证组里顺序纠正）
			////在分的组里，L-<r[0]就是最小记录，现在看插入哪个比较好  最近的 所以一次就好
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
	int dlta[] = { 4,2,1 };//步长

	sqlist* L = new sqlist(nums, 9);
	ShellSort(L, dlta, 3);
	printlist(L);
	system("pause");
	return 1;
}
