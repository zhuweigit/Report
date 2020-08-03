#include "Graph.h"
#include<queue>
#include<iostream>
using namespace  std;

Graph::Graph()
{
	vexs[MAXVEX] = {0};      //顶点表
	for(int i=0;i<MAXVEX;i++)
		for (int j = 0; j < MAXVEX; j++)
	     arc[i][j]= INFINITY;   //边表

	int numVertexes=0, numEdges=0;      //当前的顶点数和边数

	for (int i = 0; i < MAXVEX; i++)  //初始化都没有走过
		visited[i] = false;  
}

void Graph::Create()
{
	int i,j=0, k, w;
	cout << "请输入顶点个数和边数： \n";
	cin >> numVertexes >> numEdges;
	cout << "按顺序输入顶点值:\n";
	for (i = 0; i < numVertexes; i++)    //
		cin >> vexs[i];

	
	for (k = 0; k < numEdges; k++)   //输入边,建立矩阵
	{
		cout << "输入边（vi,vj）上的下标i,下标j和权w:\n";
		cin >> i >> j ;

		//arc[i][j] = w;
		arc[j][i] = arc[i][j];  //因为是无向图 所以矩阵对称
	}
}

void Graph::DFS(int i)  
{
	int j;
	visited[i] = true;
	cout << vexs[i] << " ";

	for (j = 0; j < numVertexes; j++)
		if (arc[i][j] == 1 && !visited[j])
			DFS(j);    //对为访问的邻接顶点递归调用

}

void Graph::DFSTraverse()
{
	for (int i = 0; i < MAXVEX; i++)  //初始化都没有走过
		visited[i] = false;
	for (int i = 0; i < numVertexes; i++)  //有一个附加作用：相当于再检查一下遗漏
	{
		if (!visited[i])  //没访问才进行调用DFS
			DFS(i);
	}
	cout << endl;

	
}

void Graph::BFSTraverse()
{
	for (int i = 0; i < MAXVEX; i++)  //初始化都没有走过
		visited[i] = false;
	int i, j;
	queue<VertexType> Q ;
	for (i = 0; i < numVertexes; i++)
	{
		if (!visited[i])
		{
			visited[i] = true;   //先设置这个顶点我防问过了
			cout << vexs[i]<<" ";
			Q.push(vexs[i]);  //入队
			while (!Q.empty())
			{
			
				Q.pop();    //出队

				for (j = 0; j < numVertexes; j++)  //遍历找出所有相关联（值为1）的点，并拉进来
				{
					if (arc[i][j] == 1 && !visited[j])
					{
						visited[j] = true;
						cout << vexs[j] << " ";
						Q.push(vexs[j]);
					}

                       
				}
			}
 
		}
	}

		

}
 
