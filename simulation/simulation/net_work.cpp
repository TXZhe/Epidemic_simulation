#include "stdafx.h"
#include "net_work.h"


net_work::net_work(int u)
{
	USRNUM = u;
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

void net_work::add_edge(int a, int b, int l)		//添加边
{
	if (min(a, b) < 0 || max(a, b) >= USRNUM)
	{
		return;
	}
	unordered_map<int, int>::iterator tmp = adjacent_table[a].find(b);
	if (tmp == adjacent_table[a].end())
	{
		adjacent_table[a][b] = l;
		adjacent_table[b][a] = l;
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

int net_work::check_edge(int a, int b)		//检查是否有这个边
{
	unordered_map<int, int>::iterator tmp = adjacent_table[a].find(b);
	if (tmp != adjacent_table[a].end())
	{
		return tmp->second;
	}
	else
	{
		return -1;
	}
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

unordered_map<int, int> net_work::neighbors(int a)
{
	return(adjacent_table[a]);
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
		if (!adjacent_table[i].empty())
		{
			cout << i << ": ";
			for (unordered_map<int, int>::iterator itr = adjacent_table[i].begin(); itr != adjacent_table[i].end(); itr++)
			{
				cout << '(' << itr->first << ',' << itr->second << ')';
			}
			cout << endl;
		}
	}

	cout << "nodes=" << node_num << " edges=" << edge_num << endl;
	cout << endl;
}

void net_work::print_to_file(fstream &fout, int ts)
{
	for (int i = 0; i < adjacent_table.size(); i++)
	{
		if (!adjacent_table[i].empty())
		{
			for (unordered_map<int, int>::iterator itr = adjacent_table[i].begin(); itr != adjacent_table[i].end(); itr++)
			{
				if (i < itr->first)
					fout << i << ',' << itr->first << ',' << ts << ',' << itr->second << endl;
			}
		}
	}
}