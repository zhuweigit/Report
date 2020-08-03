#include"BinaryTree.h"
#include"BinaryTree.cpp"
#include<iostream>
using namespace std;

int main()
{
	BinaryTree<char> bt();
	BinaryTree<char>*pbt = &bt;
	Node<int>*root= pbt->Create();
	pbt->PreOrderTraverse(root);

	 
}