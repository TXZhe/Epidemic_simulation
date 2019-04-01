#pragma once

#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

class net_work
{
private:
	vector< unordered_map<int, int> > adjacent_table;		//邻接表
	int edge_num;
	int node_num;
	int USRNUM;
public:
	net_work(int u);
	net_work(const net_work &a);				//拷贝构造函数
	~net_work();
	void add_edge(int a, int b, int l);
	int edges_num();
	int neighbors_num(int a);
	int check_edge(int a, int b);
	bool check_node(int a);
	unordered_map<int, int> neighbors(int a);
	void clear();
	void print();
	void print_to_file(fstream &fout, int ts);
};

