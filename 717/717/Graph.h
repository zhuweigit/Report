#pragma once
typedef char VertexType;   //��������
typedef int EdgeType;     //���ϵ�Ȩֵ����
#define MAXVEX 100         //��󶥵���
#define INFINITY 65535      //�ô�����ʾ����




class Graph
{
	VertexType vexs[MAXVEX];      //�����
	EdgeType arc[MAXVEX][MAXVEX];   //�߱�
	int numVertexes, numEdges;      //��ǰ�Ķ������ͱ���
	bool visited[MAXVEX];    //���ʱ�־������

	//���ݶ���ķǿռ��Ϻͱߵļ���
public:
	Graph();     //��ʼ��
	void Create();  // ����ͼ
	 void DFS(int i);   //�ڽӾ����������ȵݹ��㷨  ��ͼG����������ȱ�������iλ�ÿ�ʼ���� �ڱ��������жԸ�������е���
	 void  DFSTraverse();  //��ȱ�������
	 void  BFSTraverse();     //��ͼG���й�����ȱ������ڱ��������жԸ�������е���
};