#include<iostream>
#include "TraverseBinaryTree.h"
using namespace std;

BitNode* BitTree::Create()
{
	char ch;
	cin >> ch;
	if (ch == '#')  T = nullptr;
	else
	{
		T = new BitNode;
		T->data = ch;

		T = T->lchild;
		T->lchild = Create();
		T = T->rchild;
		T->rchild = Create();
 
	}

	 
}
