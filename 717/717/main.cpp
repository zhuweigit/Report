#include"Graph.h"
#include<iostream>
using namespace std;

int main()
{
	Graph graph;
    graph.Create();

	cout << "������ȱ���" << endl;
	graph.DFSTraverse();
	cout << "��ȶ����ȱ���" << endl;
	graph.BFSTraverse();


	 
}