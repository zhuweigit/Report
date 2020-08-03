#include<iostream>
#include<queue>
using namespace std;

typedef char VertexType;   //顶点类型
typedef int EdgeType;     //边上的权值类型
#define MAXVEX 100         //最大顶点数
#define INFINITY 65535      //用大数表示无穷



 

struct EdgeNode    //边表节点
{
	int adjvex;        //邻接点域
	//EdgeType weight;    //权值
	EdgeNode*next;     //链域
};

struct VertexNode    //顶点表节点
{
	VertexType data;   //顶点域，存储顶点的信息
	EdgeNode*firstedge;  //边表头指针
	 
};

class GraphAdjList  //图
{
public:

	VertexNode adjList[MAXVEX];   //顶点
	int numVertexes, numEdges;  //图中实际创建的总：顶点和边数
	bool visited[MAXVEX];

	GraphAdjList() :adjList(),numVertexes(0), numEdges(0){  
		for (int i = 0; i < MAXVEX; i++)
			visited[i] = false;
	}
};

void CreateALGraph(GraphAdjList*G)
{
	int i, j, k;   //i j 是序号 k 是遍历边的次数
	EdgeNode*e;
	cout << "请输入顶点数和边数\n";
	cin >> G->numVertexes >> G->numEdges;
	for (i = 0; i < G->numVertexes; i++)          //读入顶点信息，建立顶点表
	{
		cout << "输入顶点信息 \n";
		cin >> G->adjList[i].data;
		G->adjList[i].firstedge = nullptr;  //将边表置空
	}

	for (k = 0; k < G->numEdges;k++)  //建立边表  有几个边就是要输入几次
	{
		cout << "输入边（Vi,Vj）上的顶点序号：\n";
		cin >> i >> j;
		e = new EdgeNode;  //向内存申请节点

		e->adjvex = j;    //邻接序号就是j
		e->next = G->adjList[i].firstedge;  //将e的尾指针指向g
		G->adjList[j].firstedge = e;

		//因为是双向的所以还有一个对称的

		e = new EdgeNode;  //向内存申请节点

		e->adjvex = i;
		e->next = G->adjList[j].firstedge;
		G->adjList[i].firstedge = e;

	}


}

void DFS(GraphAdjList*G, int i)
{
	EdgeNode*p;
	G->visited[i] = true;
	cout << G->adjList[i].data<<" ";
	p = G->adjList[i].firstedge;
	while (p)   //p为空时
	{
		if (!G->visited[p->adjvex])  //邻接域没有被访问
			DFS(G, p->adjvex);   //为对访问的邻接顶点进行递归递归调用
	 	p = p->next;
	}
	cout << endl;

}

void DFSTraverse(GraphAdjList*G)
{
	int i;
	for (int i = 0; i < G->numVertexes; i++)
		if (!G->visited[i])
			DFS(G,i);
}
 
void BFSTraverse(GraphAdjList*G)
{
	int i;
	EdgeNode*p;
	queue<VertexNode>Q;   //队列 放顶点
	for (i = 0; i < G->numVertexes; i++)
	{
		G->visited[i] = true;
		cout << G->adjList[i].data << " ";
		Q.push(G->adjList[i]);
		while (!Q.empty())          
		{ 
			Q.pop();    
			p = G->adjList[i].firstedge;  //找到当前顶点的边表链表头指针
			while (p)          // 广度遍历 重点： 就是把它相邻（每个顶点的所有的相邻表！）的都放进
			{
				if (!G->visited[p->adjvex])  //该节点没有被访问
				{
					G->visited[p->adjvex] = true;
					cout << G->adjList[p->adjvex].data << " ";
					Q.push(G->adjList[p->adjvex]);   // 下一个是谁把  它入队
				}
				p = p->next;
			}


		}

	}
	    

}


int main()
{
	GraphAdjList grap ;
	GraphAdjList* pGrap=&grap;
	CreateALGraph(pGrap);
	cout << "深度优先遍历" << endl;   
	DFSTraverse(pGrap);
	cout << "广度度优先遍历" << endl;
	BFSTraverse(pGrap);
}