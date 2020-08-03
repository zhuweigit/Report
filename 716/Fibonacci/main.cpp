#include<iostream>
using namespace std;

template<typename T>
int Fbi(T i)
{
	if (i < 2)
	{
		return i == 0 ? 0 : 1;
	}
	return Fbi(i - 1) + Fbi(i - 2);
}

int main()
{
	int Max = 10;   //最大值
	for (int i = 0; i < Max; i++)
	{
		cout << "第" << i << "个的斐波那契数是：" << endl;
		cout << Fbi(i) << " " << endl;
	}

	cout << endl;




}