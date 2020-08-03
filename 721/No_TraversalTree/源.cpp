#include<iostream>
#include<stack>
#include<vector>

using namespace std;
#define DATA '#'

struct BitNode
{
	char data;
	BitNode*lchild, *rchild;
	BitNode() :data(DATA), lchild(nullptr), rchild(nullptr) {}
};

struct Node   //加一个标志
{
	BitNode*bitnode;   //地址
	bool tag;    //作为标志
	Node(BitNode*pos, int Tag) { bitnode = pos; tag = Tag; }

};

BitNode* CreateBiTree()  //先序创建
{
	BitNode*T;
	char ch;
	while (cin >> ch)
	{

		if (ch == '#')  T = nullptr;
		else
		{
			T = new BitNode;
			T->data = ch;
			T->lchild = nullptr;  //新生成的初始化
			T->rchild = nullptr;
			T->lchild = CreateBiTree();
			T->rchild = CreateBiTree();
		}
		return T;
	}

}




void PreOrderTraverse(BitNode*&T) {
	//vector<char>ans;
	if (!T)  //T为空  
		return;   //返回结果
	auto cur = T;
	stack<BitNode*>st;  //栈
	cout << "先序遍历的顺序为： \n";
	while (cur || !st.empty())  //cur st都不空
	{
		while (cur)
		{
			//ans.push_back(cur->data);  //先进行访问    //访问节点的操作
			cout << cur->data << " ";
			st.push(cur);               //然后压栈
			cur = cur->lchild;
		}
		//cur为空时且st栈不为空
		//就从栈顶取出节点，进入其右子树
		if (!st.empty())
		{
			cur = st.top();
			st.pop();
			cur = cur->rchild;
		}
	}
	//当前节点和栈都为空时，结束
	cout << endl;
}

void Inorder(BitNode*&T)
{
	//vector<char>ans;
	if (!T)  return;
	auto cur = T;
	stack<BitNode*>st;  //栈


	cout << "中序遍历的顺序为： \n";
	while (cur || !st.empty())  //cur不空或者 栈有元素
	{
		while (cur)  //cur不空  入栈    
		{
			st.push(cur);
			cur = cur->lchild;
		}
		if (!st.empty())  //cur 空时  但是栈不空
		{
			cur = st.top();

			//ans.push_back(cur->data);  //要节点的值  对根节点的操作
			cout << cur->data << " ";
			st.pop();

			cur = cur->rchild;

		}
	}
	cout << endl;
}


//先遍历完左右子树才能退栈
void Posorder(BitNode*&T)
{
	//树指针  栈指针
	BitNode*p = T;     //此时指向的树   两个结构一个是树  一个是栈    分开的 通过赋值来进行栈与树之间通信
	stack<Node*>st1;    //栈顶元素
	do {
		while (p != nullptr)  //p不为空    
		{
			st1.push(new Node(p, false));   //把节点和标志位的节点放进去   要新建！！！
			p = p->lchild;  //树往下走

		}
		//P ****************

		//p为空时  用while 不用if是因为要考虑栈顶元素取出来是否为Ture  //所以判断不止一次  直到栈顶元素为Ture为止
		while (!st1.empty())   //栈的操作！！
		{  //栈存储的是以前的信息（浏览器的退回记录一样）  取出最近记录 拿出来看内容符合不符合 决定压栈出栈
			Node*TopElem = st1.top(); //把栈顶元素信息取出来
			if (TopElem->tag)   //如果栈顶元素的标志位Ture**  否则（标志位为false）就**
			{
				cout << TopElem->bitnode->data << " ";   //将取出的元素的值输出

				st1.pop();   //弹出
			}
			else // 否则（标志位为false）  //拿出来修改之后再放进去
			{

				//BitNode*temp = TopElem->bitnode;

				p = TopElem->bitnode->rchild;  //从记录里取出上一个根的右孩子地址将p指向它  下一个树的根节点更新了p
				//st1.pop();
				TopElem->tag = true;
				// st1.push(new Node(TopElem->tag, true));  //把之前存的地址，并且将它压栈  //此时相当于它的右节点了
				break;        //退出当前while

				//只要进入右子树就要这样重新来一遍 ！！开始进入do ！！！
			}
		}//结束之后产生新的p 又一轮
	} while (!st1.empty());   //栈为空时退出
}



int main()
{
	BitNode*T;
	cout << "创建一棵树，用A-Z字符代表树的数据，用#字符代表空树：    \n";
	T = CreateBiTree();
	cout << "先序遍历： \n";
	PreOrderTraverse(T);
	cout << "中序遍历： \n";
	Inorder(T);
	cout << "后续遍历：  \n";
	Posorder(T);
	cout << endl;


}