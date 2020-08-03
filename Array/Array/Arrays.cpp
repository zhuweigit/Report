 #include "Arrays.h"

Arrays::Arrays(int *a,int size)
{
	for (int i = 0; i < size; i++)
	{
		Data[i] = a[i];
	}
	Length = size;
  		 
 
}

bool Arrays::GetElem(int i, int* e)
{
	if (i < 1 || i>20)
		return false;
	*e = Data[i];
	return true;
}

bool Arrays::ListInsert(int i, int e)
{
	int k;
	if (Length == 20)    //满了插不了了
		return false;
	if (i<1 || i>Length + 1)       //插入位置不合理
		return  false;
	if (i <= Length)    //位置不在尾部
	{
		for (k = Length - 1; k > i - 1; k--)   //遍历每个之后的数据元素向后移动一位
		{
			data[k + 1] = data[k];
		}
	}
	data[i - 1] = e;
	Length--;
	return true;

}

bool Arrays::ListDelete(int i, int* e)
{
	int k;
	if (Length == 0)   //线性表为空
		return false;
	if (i<1 || i>Length)   //删除位置不对
		return false;
	*e = data[i-1];  //记录被删除的数    i是个数 i-1整体才是序号
	if (i < Length)  //如果删除不是最后一个
	{
		for (k = i; k < Length; k++)  //后面的一坨，向前移动
		{
			data[k - 1] = data[k];
		}
	}
	Length--;
	return true;
}

void Arrays::out()
{
	if (Length < 0)
		return ;

	for (int i = 0; i < Length - 1; i++)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}
