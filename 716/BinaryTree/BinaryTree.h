#pragma once

template<typename T>       //只是声明T

struct Node {
	T data;
	Node*lchild;   //左孩子指针
	Node*rchild;   //右孩子指针

	Node(T val, Node*l=nullptr, Node*r=nullptr) :data(val), lchild(l), rchild(r) {}; // 构造函数
};  //节点

template<typename T>
class BinaryTree
{
	Node<int> *root;	//根的位置


public:

	/*BinaryTree():Node(); */         //构造空树(初始)
	BinaryTree();
	void PreOrderTraverse(Node<T>*);   //前序遍历
	void InOrderTraverse(Node<T>*);    //中序遍历
	void PostOrderTaverse(Node<T>*);    //后序遍历
	
	Node<T>* Create();         //按照定义构造树


	

};

