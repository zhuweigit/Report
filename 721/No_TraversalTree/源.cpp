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

struct Node   //��һ����־
{
	BitNode*bitnode;   //��ַ
	bool tag;    //��Ϊ��־
	Node(BitNode*pos, int Tag) { bitnode = pos; tag = Tag; }

};

BitNode* CreateBiTree()  //���򴴽�
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
			T->lchild = nullptr;  //�����ɵĳ�ʼ��
			T->rchild = nullptr;
			T->lchild = CreateBiTree();
			T->rchild = CreateBiTree();
		}
		return T;
	}

}




void PreOrderTraverse(BitNode*&T) {
	//vector<char>ans;
	if (!T)  //TΪ��  
		return;   //���ؽ��
	auto cur = T;
	stack<BitNode*>st;  //ջ
	cout << "���������˳��Ϊ�� \n";
	while (cur || !st.empty())  //cur st������
	{
		while (cur)
		{
			//ans.push_back(cur->data);  //�Ƚ��з���    //���ʽڵ�Ĳ���
			cout << cur->data << " ";
			st.push(cur);               //Ȼ��ѹջ
			cur = cur->lchild;
		}
		//curΪ��ʱ��stջ��Ϊ��
		//�ʹ�ջ��ȡ���ڵ㣬������������
		if (!st.empty())
		{
			cur = st.top();
			st.pop();
			cur = cur->rchild;
		}
	}
	//��ǰ�ڵ��ջ��Ϊ��ʱ������
	cout << endl;
}

void Inorder(BitNode*&T)
{
	//vector<char>ans;
	if (!T)  return;
	auto cur = T;
	stack<BitNode*>st;  //ջ


	cout << "���������˳��Ϊ�� \n";
	while (cur || !st.empty())  //cur���ջ��� ջ��Ԫ��
	{
		while (cur)  //cur����  ��ջ    
		{
			st.push(cur);
			cur = cur->lchild;
		}
		if (!st.empty())  //cur ��ʱ  ����ջ����
		{
			cur = st.top();

			//ans.push_back(cur->data);  //Ҫ�ڵ��ֵ  �Ը��ڵ�Ĳ���
			cout << cur->data << " ";
			st.pop();

			cur = cur->rchild;

		}
	}
	cout << endl;
}


//�ȱ�������������������ջ
void Posorder(BitNode*&T)
{
	//��ָ��  ջָ��
	BitNode*p = T;     //��ʱָ�����   �����ṹһ������  һ����ջ    �ֿ��� ͨ����ֵ������ջ����֮��ͨ��
	stack<Node*>st1;    //ջ��Ԫ��
	do {
		while (p != nullptr)  //p��Ϊ��    
		{
			st1.push(new Node(p, false));   //�ѽڵ�ͱ�־λ�Ľڵ�Ž�ȥ   Ҫ�½�������
			p = p->lchild;  //��������

		}
		//P ****************

		//pΪ��ʱ  ��while ����if����ΪҪ����ջ��Ԫ��ȡ�����Ƿ�ΪTure  //�����жϲ�ֹһ��  ֱ��ջ��Ԫ��ΪTureΪֹ
		while (!st1.empty())   //ջ�Ĳ�������
		{  //ջ�洢������ǰ����Ϣ����������˻ؼ�¼һ����  ȡ�������¼ �ó��������ݷ��ϲ����� ����ѹջ��ջ
			Node*TopElem = st1.top(); //��ջ��Ԫ����Ϣȡ����
			if (TopElem->tag)   //���ջ��Ԫ�صı�־λTure**  ���򣨱�־λΪfalse����**
			{
				cout << TopElem->bitnode->data << " ";   //��ȡ����Ԫ�ص�ֵ���

				st1.pop();   //����
			}
			else // ���򣨱�־λΪfalse��  //�ó����޸�֮���ٷŽ�ȥ
			{

				//BitNode*temp = TopElem->bitnode;

				p = TopElem->bitnode->rchild;  //�Ӽ�¼��ȡ����һ�������Һ��ӵ�ַ��pָ����  ��һ�����ĸ��ڵ������p
				//st1.pop();
				TopElem->tag = true;
				// st1.push(new Node(TopElem->tag, true));  //��֮ǰ��ĵ�ַ�����ҽ���ѹջ  //��ʱ�൱�������ҽڵ���
				break;        //�˳���ǰwhile

				//ֻҪ������������Ҫ����������һ�� ������ʼ����do ������
			}
		}//����֮������µ�p ��һ��
	} while (!st1.empty());   //ջΪ��ʱ�˳�
}



int main()
{
	BitNode*T;
	cout << "����һ��������A-Z�ַ������������ݣ���#�ַ����������    \n";
	T = CreateBiTree();
	cout << "��������� \n";
	PreOrderTraverse(T);
	cout << "��������� \n";
	Inorder(T);
	cout << "����������  \n";
	Posorder(T);
	cout << endl;


}