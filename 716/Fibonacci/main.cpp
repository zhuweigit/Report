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
	int Max = 10;   //���ֵ
	for (int i = 0; i < Max; i++)
	{
		cout << "��" << i << "����쳲��������ǣ�" << endl;
		cout << Fbi(i) << " " << endl;
	}

	cout << endl;




}