#include<iostream>

using namespace std;

typedef int status;

//定义一个数的结构体
typedef struct BiTNode
{
	int data;
	struct BiTNode* lchild, *rchild;
}BiTNode, *BiTree;

//函数声明
void CreateBST(BiTree* T, int a[], int n);
void outputBST(BiTree T);
status InsertBST(BiTree* T, int key);
status DeleteBST(BiTree*T, int key);
status Delete(BiTree *p);

//二叉排序树的查找函数定义
status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
	if (!T)
	{
		*p = f;
		return false;
	}
	else if (key == T->data)
	{
		*p = T;
		return true;
	}
	else if (key < T->data)
	{
		return SearchBST(T->lchild, key, T, p);
	}
	else
	{
		return SearchBST(T->rchild, key, T, p);
	}
}

//二叉排序树的插入函数定义
status InsertBST(BiTree *T, int key)
{
	BiTree p = NULL, s = NULL;
	if (!SearchBST(*T, key, NULL, &p))
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		if (!p)
			* T = s;
		else if (key < p->data)
			p->lchild = s;
		else
			p->rchild = s;
		return true;
	}
	return false;
}

//二叉排序树的删除操作函数定义
status DeleteBST(BiTree* T, int key)
{
	if (!*T)
		return false;
	else
	{
		if (key == (*T)->data)
		{
			return Delete(T);
		}
		else if (key < (*T)->data)
		{
			return DeleteBST(&(*T)->lchild, key);
		}
		else
		{
			return DeleteBST(&(*T)->rchild, key);
		}
	}
}

//根据情况来删除节点
status Delete(BiTree* p)
{
	BiTree q, s;
	if ((*p)->rchild == NULL)
	{
		q = *p; *p = (*p)->lchild; free(q);
	}
	else if ((*p)->lchild == NULL)
	{
		q = *p; *p = (*p)->rchild; free(q);
	}
	else
	{
		q = *p; s = (*p)->lchild;
		while (s->rchild)
		{
			q = s; s = s->rchild;
		}
		(*p)->data = s->data;
		if (q != *p)
			q->rchild = s->lchild;
		else
			q->lchild = s->lchild;
		free(s);
	}
	return true;
}

//通过一个数组来创建二叉排序树
void CreateBST(BiTree*T, int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		InsertBST(T, a[i]);
	}
}

//把一个二叉排序树中序遍历打印
void outputBST(BiTree T)
{
	if (T == NULL)
	{
		return;
	}
	outputBST(T->lchild);
	cout << T->data << " ";
	outputBST(T->rchild);
}

//主函数
int main()
{
	int a[] = { 6,8,8,7,35,73,1,99,37,93 };
	BiTree T = NULL;

	//创建二叉排序树
	CreateBST(&T, a, 10);

	//在二叉排序树中插入95
	InsertBST(&T, 95);

	//在二叉排序树中查找节点
	int b = 95;
	BiTree p = NULL;
	if (!SearchBST(T, b, NULL, &p))
		cout << "没有找到" << endl;
	else
	{
		cout << b << "查找结果的指针为:\n" << p << endl;
	}

	//在二叉排序树中删除88节点
	DeleteBST(&T, 88);

	//验证上述的插入和删除操作
	outputBST(T);
	cout << endl;

	return 0;
}