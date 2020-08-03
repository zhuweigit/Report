#include"Graph.h"
#include<iostream>
using namespace std;

int main()
{
	Graph graph;
    graph.Create();

	cout << "深度优先遍历" << endl;
	graph.DFSTraverse();
	cout << "广度度优先遍历" << endl;
	graph.BFSTraverse();


	 
}