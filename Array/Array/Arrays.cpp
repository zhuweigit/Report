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
	if (Length == 20)    //���˲岻����
		return false;
	if (i<1 || i>Length + 1)       //����λ�ò�����
		return  false;
	if (i <= Length)    //λ�ò���β��
	{
		for (k = Length - 1; k > i - 1; k--)   //����ÿ��֮�������Ԫ������ƶ�һλ
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
	if (Length == 0)   //���Ա�Ϊ��
		return false;
	if (i<1 || i>Length)   //ɾ��λ�ò���
		return false;
	*e = data[i-1];  //��¼��ɾ������    i�Ǹ��� i-1����������
	if (i < Length)  //���ɾ���������һ��
	{
		for (k = i; k < Length; k++)  //�����һ�磬��ǰ�ƶ�
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
