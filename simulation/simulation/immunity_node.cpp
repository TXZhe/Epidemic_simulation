#include "stdafx.h"
#include "immunity.h"


set<int> immunize_node_aqirf(double pha, net_work &irf_neighbor, vector<int> &nodes)
{
	srand((unsigned int)time(NULL));

	int range = int(nodes.size());
	int immu_size = int(range * pha);

	set<int> immunized;

	vector<int> tmpimmu(range);
	for (int i = 0; i < range; i++)
	{
		tmpimmu[i] = i;
	}
	random_shuffle(tmpimmu.begin(), tmpimmu.end());

	for (int i = 0; i < immu_size; i++)
	{
		int candidate = nodes[tmpimmu[i]];
		while (!irf_neighbor.check_node(candidate))
		{
			candidate++;
			if (candidate >= USRNUM)
			{
				candidate = 0;
			}
		}
		int neighbors = irf_neighbor.neighbors_num(candidate);
		int choosed = rand() % neighbors;
		int b = irf_neighbor.find_edge_by_index(candidate, choosed);

		//去重，保证免疫节点数量
		set<int>::iterator tmpvector;
		int tmpcounter = 1;
		bool key = true;
		while ((tmpvector = immunized.find(b)) != immunized.end())
		{
			if (tmpcounter >= neighbors)
			{
				key = false;
				break;
			}
			choosed++;
			if (choosed >= neighbors)
			{
				choosed = 0;
			}
			tmpcounter++;
			b = irf_neighbor.find_edge_by_index(candidate, choosed);
		}

		if (key)
		{
			immunized.insert(b);
		}
		else
		{
			//cout << "Error: in model " << immune_type << " ," << candidate << "only have " << neighbors << " neighbors" << endl;
			for (int j = 0; j < range; j++)
			{
				if ((tmpvector = immunized.find(nodes[j])) == immunized.end())
				{
					immunized.insert(nodes[j]);
					break;
				}
			}
		}
	}
	return immunized;
}

set<int> immunize_node(double pha, int immune_type, vector<net_work> &social_tie, net_work &edges, vector<int> &nodes)
{
	srand((unsigned int)time(NULL));
	//vector<USERS> immunized;

	int range = int(nodes.size());
	int immu_size = int(range * pha);

	set<int> immunized;

	switch (immune_type)
	{
	case 7: //随机免疫
	{
		vector<int> tmpimmu(range);
		for (int i = 0; i < range; i++)
		{
			tmpimmu[i] = i;
		}
		random_shuffle(tmpimmu.begin(), tmpimmu.end());

		for (int i = 0; i < immu_size; i++)
		{
			immunized.insert(nodes[tmpimmu[i]]);
		}
		break;
	}

	case 8: //熟人免疫
	{
		vector<int> tmpimmu(range);
		for (int i = 0; i < range; i++)
		{
			tmpimmu[i] = i;
		}
		random_shuffle(tmpimmu.begin(), tmpimmu.end());

		for (int i = 0; i < immu_size; i++)
		{
			int candidate = nodes[tmpimmu[i]];
			while (!edges.check_node(candidate))
			{
				candidate++;
				if (candidate >= USRNUM)
				{
					candidate = 0;
				}
			}
			int neighbors = edges.neighbors_num(candidate);
			int choosed = rand() % neighbors;
			int b = edges.find_edge_by_index(candidate, choosed);
			
			//去重，保证免疫节点数量
			set<int>::iterator tmpvector;
			int tmpcounter = 1;
			bool key = true;
			while ((tmpvector = immunized.find(b)) != immunized.end())
			{
				if (tmpcounter >= neighbors)
				{
					key = false;
					break;
				}
				choosed++;
				if (choosed >= neighbors)
				{
					choosed = 0;
				}
				tmpcounter++;
				b = edges.find_edge_by_index(candidate, choosed);
			}

			if (key)
			{
				immunized.insert(b);
			}
			else
			{
				//cout << "Error: in model " << immune_type << " ," << candidate << "only have " << neighbors << " neighbors" << endl;
				for (int j = 0; j < range; j++)
				{
					if ((tmpvector = immunized.find(nodes[j])) == immunized.end())
					{
						immunized.insert(nodes[j]);
						break;
					}
				}
			}
			
		}
		break;
	}

	case 9: //熟人免疫S
	case 10: //熟人免疫F
	case 11: //熟人免疫FS
	case 12: //熟人免疫IR
	{
		vector<int> tmpimmu(range);
		for (int i = 0; i < range; i++)
		{
			tmpimmu[i] = i;
		}
		random_shuffle(tmpimmu.begin(), tmpimmu.end());

		for (int i = 0; i < immu_size; i++)
		{
			int candidate = nodes[tmpimmu[i]];
			while (!social_tie[immune_type - 9].check_node(candidate))
			{
				candidate++;
				if (candidate >= USRNUM)
				{
					candidate = 0;
				}
			}
			int neighbors = social_tie[immune_type - 9].neighbors_num(candidate);
			int choosed = rand() % neighbors;
			int b = social_tie[immune_type - 9].find_edge_by_index(candidate, choosed);

			//去重，保证免疫节点数量
			set<int>::iterator tmpvector;
			int tmpcounter = 1;
			bool key = true;
			while ((tmpvector = immunized.find(b)) != immunized.end())
			{
				if (tmpcounter >= neighbors)
				{
					key = false;
					break;
				}
				choosed++;
				if (choosed >= neighbors)
				{
					choosed = 0;
				}
				tmpcounter++;
				b = social_tie[immune_type - 9].find_edge_by_index(candidate, choosed);
			}

			if (key)
			{
				immunized.insert(b);
			}
			else
			{
				//cout << "Error: in model " << immune_type << " ," << candidate << "only have " << neighbors << " neighbors （" <<immunized.size()<<","<< immu_size <<")"<< endl;
				for (int j = 0; j < range; j++)
				{
					if ((tmpvector = immunized.find(nodes[j])) == immunized.end())
					{
						immunized.insert(nodes[j]);
						break;
					}
				}
			}

		}
		break;
	}

	default:
		cout << "ERROR: immune_type " << immune_type << " out of range!" << endl;
		break;
	}

	return immunized;
}