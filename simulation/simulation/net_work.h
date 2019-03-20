#pragma once

#include<vector>
#include"commonvariables.h"
#include<algorithm>

using namespace std;

class net_work
{
private:
	vector<vector<int> > adjacent_table;		//邻接表
	int edge_num;
	int node_num;
public:
	net_work();
	net_work(const net_work &a);				//拷贝构造函数
	~net_work();
	void add_edge(int a, int b);
	int edges_num();
	int neighbors_num(int a);
	bool check_edge(int a, int b);
	bool check_node(int a);
	int find_edge_by_index(int a, int index);
	void clear();
	void print();
};

