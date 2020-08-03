#include "Graph.h"
#include<queue>
#include<iostream>
using namespace  std;

Graph::Graph()
{
	vexs[MAXVEX] = {0};      //�����
	for(int i=0;i<MAXVEX;i++)
		for (int j = 0; j < MAXVEX; j++)
	     arc[i][j]= INFINITY;   //�߱�

	int numVertexes=0, numEdges=0;      //��ǰ�Ķ������ͱ���

	for (int i = 0; i < MAXVEX; i++)  //��ʼ����û���߹�
		visited[i] = false;  
}

void Graph::Create()
{
	int i,j=0, k, w;
	cout << "�����붥������ͱ����� \n";
	cin >> numVertexes >> numEdges;
	cout << "��˳�����붥��ֵ:\n";
	for (i = 0; i < numVertexes; i++)    //
		cin >> vexs[i];

	
	for (k = 0; k < numEdges; k++)   //�����,��������
	{
		cout << "����ߣ�vi,vj���ϵ��±�i,�±�j��Ȩw:\n";
		cin >> i >> j ;

		//arc[i][j] = w;
		arc[j][i] = arc[i][j];  //��Ϊ������ͼ ���Ծ���Գ�
	}
}

void Graph::DFS(int i)  
{
	int j;
	visited[i] = true;
	cout << vexs[i] << " ";

	for (j = 0; j < numVertexes; j++)
		if (arc[i][j] == 1 && !visited[j])
			DFS(j);    //��Ϊ���ʵ��ڽӶ���ݹ����

}

void Graph::DFSTraverse()
{
	for (int i = 0; i < MAXVEX; i++)  //��ʼ����û���߹�
		visited[i] = false;
	for (int i = 0; i < numVertexes; i++)  //��һ���������ã��൱���ټ��һ����©
	{
		if (!visited[i])  //û���ʲŽ��е���DFS
			DFS(i);
	}
	cout << endl;

	
}

void Graph::BFSTraverse()
{
	for (int i = 0; i < MAXVEX; i++)  //��ʼ����û���߹�
		visited[i] = false;
	int i, j;
	queue<VertexType> Q ;
	for (i = 0; i < numVertexes; i++)
	{
		if (!visited[i])
		{
			visited[i] = true;   //��������������ҷ��ʹ���
			cout << vexs[i]<<" ";
			Q.push(vexs[i]);  //���
			while (!Q.empty())
			{
			
				Q.pop();    //����

				for (j = 0; j < numVertexes; j++)  //�����ҳ������������ֵΪ1���ĵ㣬��������
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
 
