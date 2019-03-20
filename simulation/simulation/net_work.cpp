#include "stdafx.h"
#include "net_work.h"


net_work::net_work()
{
	adjacent_table.resize(USRNUM);			//初始化邻接表长度
	edge_num = 0;
	node_num = 0;
}

net_work::net_work(const net_work &a)
{
	edge_num = a.edge_num;
	node_num = a.node_num;
	adjacent_table.assign(a.adjacent_table.begin(), a.adjacent_table.end());
}

net_work::~net_work()
{
}

void net_work::add_edge(int a, int b)		//添加边
{
	if (min(a, b) < 0 || max(a, b) >= USRNUM)
	{
		return;
	}
	vector<int>::iterator tmp = find(adjacent_table[a].begin(), adjacent_table[a].end(), b);
	if (tmp == adjacent_table[a].end())
	{
		adjacent_table[a].push_back(b);
		adjacent_table[b].push_back(a);
		edge_num++;
		if (adjacent_table[a].size() == 1)
		{
			node_num++;
		}
		if (adjacent_table[b].size() == 1)
		{
			node_num++;
		}
	}
	return;
}

int net_work::edges_num()					//返回网络中边的数量
{
	return(edge_num);
}

int net_work::neighbors_num(int a)			//返回指定节点邻居数量
{
	return(int(adjacent_table[a].size()));
}

bool net_work::check_edge(int a, int b)		//检查是否有这个边
{
	vector<int>::iterator tmp = find(adjacent_table[a].begin(), adjacent_table[a].end(), b);
	return (tmp != adjacent_table[a].end());
}

bool net_work::check_node(int a)
{
	if (adjacent_table[a].size() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int net_work::find_edge_by_index(int a, int index)	//按序号找指定边
{
	return (adjacent_table[a][index]);
}

void net_work::clear()
{
	adjacent_table.clear();
	//adjacent_table.shrink_to_fit();
	adjacent_table.resize(USRNUM);
	edge_num = 0;
	node_num = 0;
}

void net_work::print()
{
	for (int i = 0; i < adjacent_table.size(); i++)
	{
		if (adjacent_table[i].size() != 0)
		{
			cout << i << ": ";
			for (int j = 0; j < adjacent_table[i].size(); j++)
			{
				cout << adjacent_table[i][j] << ' ';
			}
			cout << endl;
		}
	}
	
	cout << "nodes=" << node_num << " edges=" << edge_num << endl;
	cout << endl;
}