#include<iostream>
using namespace std;

struct Node {
	char data;
	Node*lchild;
	Node*rchild;
};

Node* CreateTree(Node*T)    //按前序顺序建  到一个地方看是否传值操作
{
	char ch;
	 
	
    while (cin >> ch)
	{
		if (ch == '#')    //空节点
			T = nullptr;
		else               //有数节点
		{
			T = new Node;
			if (!T)
				exit(-1);
			T->data = ch;
			T->lchild = nullptr;
			T->rchild = nullptr;

			T->lchild=CreateTree(T->lchild);  //构造左子树
			T->rchild=CreateTree(T->rchild);   //构造右子树

		}
		return T;
	}
	
}

void InOrderTraverse(Node*T)
{
	if (T == nullptr)
		return;


	InOrderTraverse(T->lchild);

	cout << "中序输出二叉树的值： " << endl;
	cout << T->data << " " << endl;

	InOrderTraverse(T->rchild);

}

void PreOrderTraverse(Node*T)
{
	if (T == nullptr)
		return;
	cout << "前序输出二叉树的值： " << endl;
	cout << T->data << " " << endl;

	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);

}

int main()
{
	Node node = { 0,nullptr,nullptr };
	Node*pNode = &node;
	Node*Root=CreateTree(pNode);
	PreOrderTraverse(Root);
	InOrderTraverse(Root);
}



 