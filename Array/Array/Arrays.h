#pragma once

 

class  Arrays 
{
     
	int* Data ;      //�洢�ռ����ʼλ��
	int Length;       //���Ա�ǰ����

public:
	Arrays(int *a, int size);
	bool GetElem(int i, int* e);    //�������еĵ�i��λ�õ�Ԫ�ط��ظ�e  ����Ҫ���ݳ�Ա����Ҫ����

	bool ListInsert( int i, int e);    //�������еĵ�i��λ�ò�����Ԫ��e

	bool ListDelete(int i, int* e);       //ɾ����i��λ�õ�Ԫ�أ�������i��λ����e����

	void out();
};