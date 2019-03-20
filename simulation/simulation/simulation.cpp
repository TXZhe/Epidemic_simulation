// simulation.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "commonvariables.h"
#include "net_work.h"
#include "immunity.h"
#include "process.h"
#include <vector>
#include <list>

#define AVG_TIMES 10		//仿真平均次数
#define IMMU_STR 7
#define IMMU_END 12

using namespace std;

int main()
{
	double star_pha = 0, end_pha = 1, delta_pha = 0.05;
	vector<int> IMMU_TYPE = { 14 };
	cout << "Please inputting start pha:" << endl;
	cin >> star_pha;
	cout << "Please inputting end pha:" << endl;
	cin >> end_pha;
	cout << "Please inputting delta pha:" << endl;
	cin >> delta_pha;

	int usr1, usr2, t, timeStep;
	int st, dt, loc;
	int file_index = 74;
	char coma;

	srand((unsigned int)time(NULL));

	//--------------------读取边之间的关系-----------------
	cout << "Inputting social tie...." << endl;

	net_work irf_neighbor;

	fstream file_char;
	file_char.open("E:\\prosimu\\data\\gaph_char.txt", ios::in);
	//file_char.open("gaph_char_test.txt", ios::in);

	while (!file_char.eof())
	{
		file_char >> usr1  >> coma >> usr2 >> coma >> t;
		if (file_char.fail())
			break;
		if (t == 2 || t == 4)
		{
			irf_neighbor.add_edge(usr1, usr2);
		}
	}

	file_char.close();
	cout << "Input social tie finished. " << endl;

	//---------读入全部边----------
	/*
	fstream fedges;
	fedges.open("E:\\prosimu\\data\\edges_ns.txt", ios::in);
	while (!fedges.eof())
	{
		fedges >> usr1 >> usr2;
		edges.add_edge(usr1, usr2);
	}
	fedges.close();
	*/
	//---------------------读取时变网络---------------------
	cout << "Inputting reaction network..." << endl;

	vector<net_work> reaction_net;
	list<vector<USERS>> next_timestep;

	timeStep = 1;
	file_index = 74;

	net_work rn_tmp;
	
	while (file_index < 88)
	{
		file_index++;
		char *filename = new char[80];
		sprintf(filename, "E:\\prosimu\\data\\greph13LD_%d.txt", file_index);
		//sprintf(filename, "grephtest%d.txt", file_index);
		
		FILE *pin;
		pin = fopen(filename, "r"); cout << filename << endl;
		delete[] filename;
		
		while (!feof(pin))
		{
			fscanf(pin, "%d,%d,%d,%d,%d", &usr1, &usr2, &st, &dt, &loc);

			while (st >= timeStep * STEP_LEN + START_INI)	//交互起始时间不在当前时间步
			{
				reaction_net.push_back(rn_tmp);
				rn_tmp.clear();

				if (next_timestep.size() != 0)
				{
					vector<USERS>::iterator tmpIter;
					for (tmpIter = next_timestep.front().begin(); tmpIter != next_timestep.front().end(); tmpIter++)
					{
						rn_tmp.add_edge(tmpIter->first, tmpIter->second);
					}
					next_timestep.pop_front();
				}

				timeStep++;
			}
			
				
			rn_tmp.add_edge(usr1, usr2);
			
			for (int tmpTS = 0; st + dt > (timeStep + tmpTS)*STEP_LEN + START_INI; tmpTS++)	//交互持续到下一个时间步的对,用一个链表来维护
			{
				USERS tmpPair = make_pair(usr1, usr2);
				if (next_timestep.size() <= tmpTS)
				{
					vector<USERS> tmpVector;
					tmpVector.push_back(tmpPair);
					next_timestep.push_back(tmpVector);
				}
				else
				{
					list<vector<USERS>>::iterator tmpIter = next_timestep.begin();
					for (int i = 0; i < tmpTS; i++)
					{
						tmpIter++;
					}
					tmpIter->push_back(tmpPair);
				}
			}
		}
		fclose(pin);
	}
	reaction_net.push_back(rn_tmp);
	rn_tmp.clear();

	while (next_timestep.size() != 0)
	{
		vector<USERS>::iterator tmpIter;
		for (tmpIter = next_timestep.front().begin(); tmpIter != next_timestep.front().end(); tmpIter++)
		{
			rn_tmp.add_edge(tmpIter->first, tmpIter->second);
		}
		next_timestep.pop_front();
		reaction_net.push_back(rn_tmp);
		rn_tmp.clear();
	}

	cout << "Input reaction network finished." << endl;
	
	/*for (int i = 0; i < reaction_net.size(); i++)
	{
		reaction_net[i].print();
	}
	system("pause");*/

	//-----------读入全部节点------------
	vector<int> nodes;
	fstream fnodes;
	fnodes.open("E:\\prosimu\\data\\nodes.txt", ios::in);
	while (!fnodes.eof())
	{
		fnodes >> usr1;
		nodes.push_back(usr1);
	}
	fnodes.close();

	//---------------------开始仿真---------------------
	fstream fout;
	char *filename = new char[80];
	sprintf(filename, "result_%.2f_%.2f.txt", star_pha, end_pha);
	fout.open(filename, ios::out);
	delete[] filename;

	//time_t start, ends;

	double beta = 1;
	double pha = 0.00;

	for (int index = 0; index < nodes.size(); index++)							//传染源
	{
		int source = nodes[index];

		set<int> tmpimmunized;
		double htzero = -1;
		htzero = process_halftime(source, beta, reaction_net, tmpimmunized);		//得到无免疫时的半感染延迟时间

		if (htzero <= 0)
		{
			cout << "error: original,source:" << source << ',' << pha << " half time error" << endl;
			continue;
		}
		for (vector<int>::iterator immutype = IMMU_TYPE.begin(); immutype != IMMU_TYPE.end(); immutype++)			//免疫方案
		{
			for (double pha = star_pha; pha <= end_pha; pha += delta_pha)		//免疫密度
			{
				cout << "now:(" << index << "," << source << ") " << *immutype << " " << pha << endl;
				double sumhtr = 0;
				for (int test_num = 0; test_num < AVG_TIMES; test_num++)		//多次仿真平均
				{
					//---免疫-------
					set<int> immunized;
					switch (*immutype)
					{
					case 14:
						immunized = immunize_node_aqirf(pha, irf_neighbor, nodes);
						break;
					}

					//---传播------
					double halftime = -1;
					halftime = process_halftime(source, beta, reaction_net, immunized);
					if (halftime <= 0)
					{
						cout << "error:" << source << *immutype << ',' << pha << " half time error" << endl;
						continue;
					}
					else
					{
						sumhtr += (halftime - htzero) / htzero;
					}
				}
				fout << source << ',' << *immutype << ',' << pha << ',' << sumhtr / AVG_TIMES << endl;	//---输出结果---
			}
		}
	}
	fout.close();

	system("pause");
	return 0;
}

