#include<iostream>
#include<stdlib.h>
#include<stack>
using namespace std;
#define len 15						//����һ������

typedef int ElemType;

typedef struct BiTNode
{
	ElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct Node
{
	BiTree btnode;
	bool isfirst;
}Node, *node;

//���±������ҵ��ڵ�sӦ�ò����λ�ã��ڵ����ظ�ʱ����������ڵ�
void SearchTreeNode(BiTree &root, BiTree &s)	//ע�⣺ʹ�����ô���
{
	if (root == NULL)
		return;
	if (s->data > root->data)
	{
		if (root->rchild == NULL)
		{
			root->rchild = s;
			return;
		}
		SearchTreeNode(root->rchild, s);//sֵ���ڸ��ڵ�ֵ��δ����Ҷ�ӽڵ㣬�������Һ��ӱ���
	}

	else if (s->data < root->data)
	{
		if (root->lchild == NULL)
		{
			root->lchild = s;
			return;
		}
		SearchTreeNode(root->lchild, s);//sֵС�ڸ��ڵ�ֵ��δ����Ҷ�ӽڵ㣬���������ӱ���
	}
}

//����һ���ڵ㣬��Ϊ�գ�����ڵ㼴Ϊ���ڵ㣬�����Һ��ʵ�λ�ò���
void InsertNode(BiTree &tree, BiTree &s)		//ע�⣺ʹ�����ô���
{
	if (tree == NULL)
		tree = s;
	else
		SearchTreeNode(tree, s);
}

//����������������ÿ������һ����㣬�嵽���еĶ�������ȥ
void CreateOrderBinaryTree(BiTree &tree, int *a)
{
	for (int i = 0; i < len; i++)
	{
		BiTree s = (BiTree)malloc(sizeof(BiTNode));
		s->data = a[i];
		s->lchild = NULL;
		s->rchild = NULL;
		InsertNode(tree, s);
	}
}
//�ǵݹ�ǰ�����
void ProOrder(BiTree pRoot)
{
	if (pRoot == NULL)
		return;
	BiTree p = pRoot;
	stack<BiTree>s;

	while (p != NULL || !s.empty())
	{
		while (p != NULL)
		{
			s.push(p);
			cout << p->data << " ";		//��һ��������ʱ�����
			p = p->lchild;
		}
		if (!s.empty())
		{
			p = s.top();
			s.pop();
			p = p->rchild;
		}
	}
}



//�ǵݹ��������
void midOrder(BiTree pRoot)
{
	if (pRoot == NULL)
		return;
	BiTree p = pRoot;
	stack<BiTree>s;
	while (p != NULL || !s.empty())
	{
		while (p != NULL)
		{
			s.push(p);
			p = p->lchild;
		}
		if (!s.empty())
		{
			p = s.top();
			cout << p->data << " ";		//�ڶ���������ʱ�����
			s.pop();
			p = p->rchild;
		}
	}
}



//�ǵݹ�ʵ�ֺ�������
void postOrder(BiTree pRoot)
{
	if (pRoot == NULL)
		return;
	stack<node>s;
	BiTree p = pRoot;
	node tmp;
	while (p != NULL || !s.empty())
	{
		while (p != NULL)		//��������һֱ����������ֱ������û���������Ľ��
		{
			node btn = (node)malloc(sizeof(Node));
			btn->btnode = p;
			btn->isfirst = true;
			s.push(btn);
			p = p->lchild;
		}
		if (!s.empty())
		{
			tmp = s.top();
			s.pop();
			if (tmp->isfirst == true)			//��һ�γ�����ջ��
			{
				tmp->isfirst = false;
				s.push(tmp);
				p = tmp->btnode->rchild;
			}
			else						//�ڶ��γ�����ջ��
			{
				cout << tmp->btnode->data << " ";
				p = NULL;
			}
		}
	}
}



int main()
{
	int a[len] = { 2,  44 ,38, 47, 35, 73, 51, 99, 37, 93, 23, 27, 45, 21, 12 };

	BiTree tree = NULL;
	//����һ�������������������
	CreateOrderBinaryTree(tree, a);

	cout << "ǰ�����" << endl;
	ProOrder(tree);
	cout << endl;


	cout << "�������" << endl;
	midOrder(tree);
	cout << endl << endl;

	cout << "�������" << endl;
	postOrder(tree);
	cout << endl << endl;
}
