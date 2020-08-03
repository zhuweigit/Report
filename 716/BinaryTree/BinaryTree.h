#pragma once

template<typename T>       //ֻ������T

struct Node {
	T data;
	Node*lchild;   //����ָ��
	Node*rchild;   //�Һ���ָ��

	Node(T val, Node*l=nullptr, Node*r=nullptr) :data(val), lchild(l), rchild(r) {}; // ���캯��
};  //�ڵ�

template<typename T>
class BinaryTree
{
	Node<int> *root;	//����λ��


public:

	/*BinaryTree():Node(); */         //�������(��ʼ)
	BinaryTree();
	void PreOrderTraverse(Node<T>*);   //ǰ�����
	void InOrderTraverse(Node<T>*);    //�������
	void PostOrderTaverse(Node<T>*);    //�������
	
	Node<T>* Create();         //���ն��幹����


	

};

