#include"BinaryTree.h"
#include<iostream>
#include<stdlib.h>
using namespace std;
 
template<typename T>
BinaryTree<T>::BinaryTree()
{

	//root->lchild = nullptr;
	//root->rchild = nullptr;
	root = nullptr;	//根的位置

}

 template<typename T>
 void BinaryTree<T>::InOrderTraverse(Node<T>*T)
 {
	 if (T == nullptr)
		 return;


	 InOrderTraverse(T->lchild);

	 cout << "中序输出二叉树的值： " << endl;
	 cout << T->data << " " << endl;

	 InOrderTraverse(T->rchild);


 }

 


 template<typename T>
 void BinaryTree<T>::PreOrderTraverse(Node<T>*T)
 {
	 if (T == nullptr)
		 return;


	 PreOrderTraverse(T->lchild);

	 cout << "中序输出二叉树的值： " << endl;
	 cout << T->data << " " << endl;

	 PreOrderTraverse(T->rchild);


 }

 template<typename T>
 void BinaryTree<T>::PostOrderTaverse(Node<T>*T)
 {
	 if (T == nullptr)
		 return;
	 cout << "前序输出二叉树的值： " << endl;
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
		 if (ch == '#')    //空节点
			 root = nullptr;
		 else               //有数节点
		 {
			 root = new Node;
			 if (!root)
				 exit(-1);
			 root->data = ch;
			 root->lchild = nullptr;
			 root->rchild = nullptr;

			 root->lchild = Create(root->lchild);  //构造左子树       //????????怎么写！！！！ 不能传参又要需要参数 又不能传自己矛盾！！！
			 root->rchild = Create(root->rchild);   //构造右子树

		 }
		 return root;
	 }

 }

 
