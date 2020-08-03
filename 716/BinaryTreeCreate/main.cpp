#include<iostream>
using namespace std;

struct Node {
	char data;
	Node*lchild;
	Node*rchild;
};

Node* CreateTree(Node*T)    //��ǰ��˳��  ��һ���ط����Ƿ�ֵ����
{
	char ch;
	 
	
    while (cin >> ch)
	{
		if (ch == '#')    //�սڵ�
			T = nullptr;
		else               //�����ڵ�
		{
			T = new Node;
			if (!T)
				exit(-1);
			T->data = ch;
			T->lchild = nullptr;
			T->rchild = nullptr;

			T->lchild=CreateTree(T->lchild);  //����������
			T->rchild=CreateTree(T->rchild);   //����������

		}
		return T;
	}
	
}

void InOrderTraverse(Node*T)
{
	if (T == nullptr)
		return;


	InOrderTraverse(T->lchild);

	cout << "���������������ֵ�� " << endl;
	cout << T->data << " " << endl;

	InOrderTraverse(T->rchild);

}

void PreOrderTraverse(Node*T)
{
	if (T == nullptr)
		return;
	cout << "ǰ�������������ֵ�� " << endl;
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



 