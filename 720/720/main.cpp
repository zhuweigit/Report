#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

typedef int Status;

constexpr auto LH = +1;
constexpr auto EH = 0;
constexpr auto RH = -1;


//定义平衡二叉树的节点结构(在二叉排序树中加入一个bf来存储平衡因子)
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


//进行二叉平衡树时的右旋操作
void R_Rotate(BiTree *p)
{
	BiTree L;
	L = (*p)->lchild;
	(*p)->lchild = L->rchild;
	L->rchild = *p;
	*p = L;
}


//进行二叉平衡树时的左旋操作
void L_Rotate(BiTree *p)
{
	BiTree R;
	R = (*p)->rchild;
	(*p)->rchild = R->lchild;
	R->lchild = (*p);
	*p = R;
}

//左平衡处理函数
void LeftBalance(BiTree* T)
{
	BiTree L, Lr;
	L = (*T)->lchild;
	switch (L->bf)
	{/*检查T的左子树的平衡度，并做相应的处理*/
	case LH:/*新节点插入在了T的左孩子的左子树上，只要做单左旋处理*/
		(*T)->bf = L->bf = EH;
		R_Rotate(T);
		break;
	case RH:/*新节点插入在了T的左孩子的右子树上，要做双旋处理，
			通过判断T的左孩子的右子树的根节点的bf来决定进行双旋处理后各自的bf值*/
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

//右平衡处理函数
void RightBalance(BiTree* T)
{
	BiTree R, Rl;
	R = (*T)->rchild;
	switch (R->bf)
	{/*检查T的右子树的平衡度，并做相应的处理*/
	case RH://新节点插入在了T的右孩子的右子树上，只要做单左旋处理
		(*T)->bf = R->bf = EH;
		L_Rotate(T);
		break;
		//新节点插入在了T的右孩子的左子树上，要做双旋处理，通过判断T的右孩子的左子树的根节点的bf来决定进行双旋处理后各自的bf值
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




//构建二叉平衡树函数
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


//二叉树中序遍历递归算法
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
	//中序遍历输出结果
	InOrderTraverse(&T);
}