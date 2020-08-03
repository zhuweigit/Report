#pragma once
typedef char VertexType;   //顶点类型
typedef int EdgeType;     //边上的权值类型
#define MAXVEX 100         //最大顶点数
#define INFINITY 65535      //用大数表示无穷




class Graph
{
	VertexType vexs[MAXVEX];      //顶点表
	EdgeType arc[MAXVEX][MAXVEX];   //边表
	int numVertexes, numEdges;      //当前的顶点数和边数
	bool visited[MAXVEX];    //访问标志的数组

	//数据顶点的非空集合和边的集合
public:
	Graph();     //初始化
	void Create();  // 创建图
	 void DFS(int i);   //邻接矩阵的深度优先递归算法  对图G进行深度优先遍历，从i位置开始遍历 在遍历过程中对各顶点进行调用
	 void  DFSTraverse();  //深度遍历操作
	 void  BFSTraverse();     //对图G进行广度优先遍历，在遍历过程中对各顶点进行调用
};