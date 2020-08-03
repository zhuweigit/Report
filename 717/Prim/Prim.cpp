#include<iostream>
#include<vector>

using namespace std;

void prim(vector<vector<int>> &VGraph, vector<int> &lowcost, vector<int> &closest, vector<bool> &visited)  
{
	int size = lowcost.size();
	visited[0] = true;
	for (int i = 1; i < size; i++)
	{
		lowcost[i] = VGraph[0][i];
	    closest[i] = 0;
		visited[i] = false;
	}
	cout << "0";
	int weight = 0;
	for (int i = 0; i < size; i++)
	{
		int min = 99999;
		int index = 1;
		for (int j = 0; j < size; j++)
		{
			if (lowcost[j] < min && !visited[j])
			{
				min = lowcost[j];
				index = j;
			}
		}
		if (index == 1 && min == 99999)
		{
			cout << "\n��С������ȨֵΪ:" << weight << endl;
			return;
		}
		else
		{
			weight += min;
		}
		cout << " -> " << index;
		visited[index] = true;
		for (int j = 1; j < size; j++)  //��Ϊ�¼�����j��,����Ҫ�����¼����j�㵽δ��S�еĵ�K�е�Ȩֵ�ǲ��ǿ�����˸�С
		{
			if ((VGraph[index][j] < lowcost[j]) && (!visited[j]))  //lowcost��ʾ����֪����ĳһ�����踶������СȨֵ
			{			 
				lowcost[j] = VGraph[index][j];
				closest[j] = index;
			}
		}
	}
}

int main()
{
	int M, N;
	cin >> M >> N;
	vector<vector<int>> VGraph(M);
	vector<int> lowcost(M);
	vector<int> closest(M);
	vector<bool> visited(M);
	for (int i = 0; i < M; i++)
	{
		VGraph[i].resize(M);
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			VGraph[i][j] = 99999;
		}
	}
	for (int i = 0; i < N; i++)
	{
		int a, b;
		cin >> a >> b;
		int length;
		cin >> length;
		VGraph[a][b] = VGraph[b][a] = length;
	}
	prim(VGraph, lowcost, closest, visited);
}
