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
			cout << "\n最小生成树权值为:" << weight << endl;
			return;
		}
		else
		{
			weight += min;
		}
		cout << " -> " << index;
		visited[index] = true;
		for (int j = 1; j < size; j++)  //因为新加入了j点,所以要查找新加入的j点到未在S中的点K中的权值是不是可以因此更小
		{
			if ((VGraph[index][j] < lowcost[j]) && (!visited[j]))  //lowcost表示从已知树到某一点所需付出的最小权值
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
