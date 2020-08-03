#include <iostream>
using namespace std;

void adjust_heap(int* a, int node, int size)
{
	int left = 2 * node + 1;
	int right = 2 * node + 2;
	int max = node;
	if (left < size && a[left] > a[max])
		max = left;
	if (right < size && a[right] > a[max])
		max = right;
	if (max != node)
	{
		swap(a[max], a[node]);
		adjust_heap(a, max, size);
	}
}



void heap_sort(int* a, int len)
{
	for (int i = len / 2 - 1; i >= 0; --i)
		adjust_heap(a, i, len);

	for (int i = len - 1; i >= 0; i--)
	{
		swap(a[0], a[i]);           // 将当前最大的放置到数组末尾
		adjust_heap(a, 0, i);              // 将未完成排序的部分继续进行堆排序
	}
}



int main()
{
	int a[] = { 3, 2, 7, 4 };
	int len = sizeof(a) / sizeof(int);
	for (int i = 0; i < len; ++i)
		cout << a[i] << ' ';
	cout << endl;
	heap_sort(a, len);
	for (int i = 0; i < len; ++i)
		cout << a[i] << ' ';
	cout << endl;
	return 0;
}
