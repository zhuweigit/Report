#include<iostream>

using namespace std;

typedef int status;

//����һ�����Ľṹ��
typedef struct BiTNode
{
	int data;
	struct BiTNode* lchild, *rchild;
}BiTNode, *BiTree;

//��������
void CreateBST(BiTree* T, int a[], int n);
void outputBST(BiTree T);
status InsertBST(BiTree* T, int key);
status DeleteBST(BiTree*T, int key);
status Delete(BiTree *p);

//�����������Ĳ��Һ�������
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

//�����������Ĳ��뺯������
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

//������������ɾ��������������
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

//���������ɾ���ڵ�
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

//ͨ��һ����������������������
void CreateBST(BiTree*T, int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		InsertBST(T, a[i]);
	}
}

//��һ���������������������ӡ
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

//������
int main()
{
	int a[] = { 6,8,8,7,35,73,1,99,37,93 };
	BiTree T = NULL;

	//��������������
	CreateBST(&T, a, 10);

	//�ڶ����������в���95
	InsertBST(&T, 95);

	//�ڶ����������в��ҽڵ�
	int b = 95;
	BiTree p = NULL;
	if (!SearchBST(T, b, NULL, &p))
		cout << "û���ҵ�" << endl;
	else
	{
		cout << b << "���ҽ����ָ��Ϊ:\n" << p << endl;
	}

	//�ڶ�����������ɾ��88�ڵ�
	DeleteBST(&T, 88);

	//��֤�����Ĳ����ɾ������
	outputBST(T);
	cout << endl;

	return 0;
}