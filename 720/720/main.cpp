#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

typedef int Status;

constexpr auto LH = +1;
constexpr auto EH = 0;
constexpr auto RH = -1;


//����ƽ��������Ľڵ�ṹ(�ڶ����������м���һ��bf���洢ƽ������)
typedef struct BiTNode
{
	int data;
	int bf;
	struct BiTNode* lchild, *rchild;
}BiTNode, *BiTree;


void R_Rotate(BiTree* p);
void L_Rotate(BiTree* p);
void LeftBalance(BiTree *T);
void RightBalance(BiTree* T);
void InOrderTraverse(BiTree *T);
Status InsertAVL(BiTree *T, int e, Status *taller);


//���ж���ƽ����ʱ����������
void R_Rotate(BiTree *p)
{
	BiTree L;
	L = (*p)->lchild;
	(*p)->lchild = L->rchild;
	L->rchild = *p;
	*p = L;
}


//���ж���ƽ����ʱ����������
void L_Rotate(BiTree *p)
{
	BiTree R;
	R = (*p)->rchild;
	(*p)->rchild = R->lchild;
	R->lchild = (*p);
	*p = R;
}

//��ƽ�⴦����
void LeftBalance(BiTree* T)
{
	BiTree L, Lr;
	L = (*T)->lchild;
	switch (L->bf)
	{/*���T����������ƽ��ȣ�������Ӧ�Ĵ���*/
	case LH:/*�½ڵ��������T�����ӵ��������ϣ�ֻҪ������������*/
		(*T)->bf = L->bf = EH;
		R_Rotate(T);
		break;
	case RH:/*�½ڵ��������T�����ӵ��������ϣ�Ҫ��˫������
			ͨ���ж�T�����ӵ��������ĸ��ڵ��bf����������˫���������Ե�bfֵ*/
		Lr = L->rchild;
		switch (Lr->bf)
		{
		case LH:
			(*T)->bf = RH;
			L->bf = EH;
			break;
		case EH:
			(*T)->bf = L->bf = EH;
			break;
		case RH:
			(*T)->bf = EH;
			L->bf = LH;
			break;
		}
		Lr->bf = EH;
		L_Rotate(&(*T)->lchild);
		R_Rotate(T);
	}
}

//��ƽ�⴦����
void RightBalance(BiTree* T)
{
	BiTree R, Rl;
	R = (*T)->rchild;
	switch (R->bf)
	{/*���T����������ƽ��ȣ�������Ӧ�Ĵ���*/
	case RH://�½ڵ��������T���Һ��ӵ��������ϣ�ֻҪ������������
		(*T)->bf = R->bf = EH;
		L_Rotate(T);
		break;
		//�½ڵ��������T���Һ��ӵ��������ϣ�Ҫ��˫������ͨ���ж�T���Һ��ӵ��������ĸ��ڵ��bf����������˫���������Ե�bfֵ
	case LH:
		Rl = R->lchild;
		switch (Rl->bf)
		{
		case LH:
			(*T)->bf = EH;
			R->bf = RH;
			break;
		case EH:
			(*T)->bf = R->bf = EH;
			break;
		case RH:
			(*T)->bf = LH;
			R->bf = EH;
			break;
		}
		Rl->bf = EH;
		R_Rotate(&(*T)->rchild);
		L_Rotate(T);
	}
}




//��������ƽ��������
Status InsertAVL(BiTree* T, int e, Status* taller)
{
	if (!*T)
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		(*T)->bf = EH;
		(*T)->lchild = (*T)->rchild = NULL;
		*taller = true;
	}
	else
	{
		if (e == (*T)->data)
		{
			*taller = false;
			return false;
		}
		if (e < (*T)->data)
		{
			int result = InsertAVL(&(*T)->lchild, e, taller);
			if (!result)
			{
				return false;
			}
			if (*taller)
			{
				switch ((*T)->bf)
				{
				case LH:
					LeftBalance(T);
					*taller = false;
					break;
				case EH:
					(*T)->bf = LH;
					*taller = true;
					break;
				case RH:
					(*T)->bf = EH;
					*taller = false;
					break;
				}
			}
		}
		else
		{
			int result = InsertAVL(&(*T)->rchild, e, taller);
			if (!result)
			{
				return false;
			}
			if (*taller)
			{
				switch ((*T)->bf)
				{
				case LH:
					(*T)->bf = EH;
					*taller = false;
					break;
				case EH:
					(*T)->bf = RH;
					*taller = true;
					break;
				case RH:
					RightBalance(T);
					*taller = false;
					break;
				}
			}
		}
	}
	return true;
}


//��������������ݹ��㷨
void InOrderTraverse(BiTree* T)
{
	if (*T == NULL)
	{
		return;
	}
	InOrderTraverse(&(*T)->lchild);
	cout << (*T)->data << " ";
	InOrderTraverse(&(*T)->rchild);
}

int main()
{
	int i;
	int a[10] = { 3,2,1,4,5,6,7,10,9,8 };
	BiTree T = NULL;
	Status Numtaller;
	for (i = 0; i < 10; i++)
	{
		InsertAVL(&T, a[i], &Numtaller);
	}
	//�������������
	InOrderTraverse(&T);
}