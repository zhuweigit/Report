#include<iostream>
#include<stdlib.h>
#include<stack>
using namespace std;
#define len 15						//定义一个长度

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

//向下遍历，找到节点s应该插入的位置，节点有重复时，忽略这个节点
void SearchTreeNode(BiTree &root, BiTree &s)	//注意：使用引用传递
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
		SearchTreeNode(root->rchild, s);//s值大于根节点值，未到达叶子节点，继续向右孩子遍历
	}

	else if (s->data < root->data)
	{
		if (root->lchild == NULL)
		{
			root->lchild = s;
			return;
		}
		SearchTreeNode(root->lchild, s);//s值小于根节点值，未到达叶子节点，继续向左孩子遍历
	}
}

//插入一个节点，树为空，插入节点即为根节点，否则找合适的位置插入
void InsertNode(BiTree &tree, BiTree &s)		//注意：使用引用传递
{
	if (tree == NULL)
		tree = s;
	else
		SearchTreeNode(tree, s);
}

//二叉排序树创建，每次增加一个结点，插到现有的二叉树上去
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
//非递归前序遍历
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
			cout << p->data << " ";		//第一次遇见的时候输出
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



//非递归中序遍历
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
			cout << p->data << " ";		//第二次遇见的时候输出
			s.pop();
			p = p->rchild;
		}
	}
}



//非递归实现后续遍历
void postOrder(BiTree pRoot)
{
	if (pRoot == NULL)
		return;
	stack<node>s;
	BiTree p = pRoot;
	node tmp;
	while (p != NULL || !s.empty())
	{
		while (p != NULL)		//沿左子树一直往下搜索，直至出现没有左子树的结点
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
			if (tmp->isfirst == true)			//第一次出现在栈顶
			{
				tmp->isfirst = false;
				s.push(tmp);
				p = tmp->btnode->rchild;
			}
			else						//第二次出现在栈顶
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
	//创建一个二叉树，并中序遍历
	CreateOrderBinaryTree(tree, a);

	cout << "前序遍历" << endl;
	ProOrder(tree);
	cout << endl;


	cout << "中序遍历" << endl;
	midOrder(tree);
	cout << endl << endl;

	cout << "后序遍历" << endl;
	postOrder(tree);
	cout << endl << endl;
}
