#include"BinaryTree.h"
#include<iostream>
#include<stdlib.h>
using namespace std;
 
template<typename T>
BinaryTree<T>::BinaryTree()
{

	//root->lchild = nullptr;
	//root->rchild = nullptr;
	root = nullptr;	//����λ��

}

 template<typename T>
 void BinaryTree<T>::InOrderTraverse(Node<T>*T)
 {
	 if (T == nullptr)
		 return;


	 InOrderTraverse(T->lchild);

	 cout << "���������������ֵ�� " << endl;
	 cout << T->data << " " << endl;

	 InOrderTraverse(T->rchild);


 }

 


 template<typename T>
 void BinaryTree<T>::PreOrderTraverse(Node<T>*T)
 {
	 if (T == nullptr)
		 return;


	 PreOrderTraverse(T->lchild);

	 cout << "���������������ֵ�� " << endl;
	 cout << T->data << " " << endl;

	 PreOrderTraverse(T->rchild);


 }

 template<typename T>
 void BinaryTree<T>::PostOrderTaverse(Node<T>*T)
 {
	 if (T == nullptr)
		 return;
	 cout << "ǰ�������������ֵ�� " << endl;
	 cout << T->data << " " << endl;

	 PostOrderTraverse(T->lchild);
	 PostOrderTraverse(T->rchild);
 }

 template<typename T>
Node<T>* BinaryTree<T>::Create()   //
 {
	 char ch;


	 while (cin >> ch)
	 {
		 if (ch == '#')    //�սڵ�
			 root = nullptr;
		 else               //�����ڵ�
		 {
			 root = new Node;
			 if (!root)
				 exit(-1);
			 root->data = ch;
			 root->lchild = nullptr;
			 root->rchild = nullptr;

			 root->lchild = Create(root->lchild);  //����������       //????????��ôд�������� ���ܴ�����Ҫ��Ҫ���� �ֲ��ܴ��Լ�ì�ܣ�����
			 root->rchild = Create(root->rchild);   //����������

		 }
		 return root;
	 }

 }

 
