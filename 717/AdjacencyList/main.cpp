#include<iostream>
#include<queue>
using namespace std;

typedef char VertexType;   //��������
typedef int EdgeType;     //���ϵ�Ȩֵ����
#define MAXVEX 100         //��󶥵���
#define INFINITY 65535      //�ô�����ʾ����



 

struct EdgeNode    //�߱�ڵ�
{
	int adjvex;        //�ڽӵ���
	//EdgeType weight;    //Ȩֵ
	EdgeNode*next;     //����
};

struct VertexNode    //�����ڵ�
{
	VertexType data;   //�����򣬴洢�������Ϣ
	EdgeNode*firstedge;  //�߱�ͷָ��
	 
};

class GraphAdjList  //ͼ
{
public:

	VertexNode adjList[MAXVEX];   //����
	int numVertexes, numEdges;  //ͼ��ʵ�ʴ������ܣ�����ͱ���
	bool visited[MAXVEX];

	GraphAdjList() :adjList(),numVertexes(0), numEdges(0){  
		for (int i = 0; i < MAXVEX; i++)
			visited[i] = false;
	}
};

void CreateALGraph(GraphAdjList*G)
{
	int i, j, k;   //i j ����� k �Ǳ����ߵĴ���
	EdgeNode*e;
	cout << "�����붥�����ͱ���\n";
	cin >> G->numVertexes >> G->numEdges;
	for (i = 0; i < G->numVertexes; i++)          //���붥����Ϣ�����������
	{
		cout << "���붥����Ϣ \n";
		cin >> G->adjList[i].data;
		G->adjList[i].firstedge = nullptr;  //���߱��ÿ�
	}

	for (k = 0; k < G->numEdges;k++)  //�����߱�  �м����߾���Ҫ���뼸��
	{
		cout << "����ߣ�Vi,Vj���ϵĶ�����ţ�\n";
		cin >> i >> j;
		e = new EdgeNode;  //���ڴ�����ڵ�

		e->adjvex = j;    //�ڽ���ž���j
		e->next = G->adjList[i].firstedge;  //��e��βָ��ָ��g
		G->adjList[j].firstedge = e;

		//��Ϊ��˫������Ի���һ���ԳƵ�

		e = new EdgeNode;  //���ڴ�����ڵ�

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
	while (p)   //pΪ��ʱ
	{
		if (!G->visited[p->adjvex])  //�ڽ���û�б�����
			DFS(G, p->adjvex);   //Ϊ�Է��ʵ��ڽӶ�����еݹ�ݹ����
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
	queue<VertexNode>Q;   //���� �Ŷ���
	for (i = 0; i < G->numVertexes; i++)
	{
		G->visited[i] = true;
		cout << G->adjList[i].data << " ";
		Q.push(G->adjList[i]);
		while (!Q.empty())          
		{ 
			Q.pop();    
			p = G->adjList[i].firstedge;  //�ҵ���ǰ����ı߱�����ͷָ��
			while (p)          // ��ȱ��� �ص㣺 ���ǰ������ڣ�ÿ����������е����ڱ����Ķ��Ž�
			{
				if (!G->visited[p->adjvex])  //�ýڵ�û�б�����
				{
					G->visited[p->adjvex] = true;
					cout << G->adjList[p->adjvex].data << " ";
					Q.push(G->adjList[p->adjvex]);   // ��һ����˭��  �����
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
	cout << "������ȱ���" << endl;   
	DFSTraverse(pGrap);
	cout << "��ȶ����ȱ���" << endl;
	BFSTraverse(pGrap);
}